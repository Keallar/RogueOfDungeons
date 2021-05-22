#include "Buttons.h"
#include "Managers.h"
#include "Inventory.h"
#include <iostream>
#include "EntityPosition.h"
#include "Player.h"
#include "Level.h"
#include "Game.h"

Button::Button(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect)
    : ren(renderer)
{
    button.x = rect.x;
    button.y = rect.y;
    button.w = rect.w;
    button.h = rect.h;
    buttonTexture = texture;
}

Button::Button(std::string textButton, SDL_Texture* texture, SDL_Renderer* renderer, const SDL_Rect rect,
               std::function <void()> callbackFunction, std::function <void()> hoverFunction,
               std::function <void()> leaveHoverFunction):
    buttonText (textButton), ren(renderer), callback(callbackFunction),
    hover(hoverFunction), leaveHover(leaveHoverFunction)
{
    button.x = rect.x;
    button.y = rect.y;
    button.w = rect.w;
    button.h = rect.h;


    if (callback == NULL)
        std::cout << "callback isn't ready " << std::endl;

    if (hover == NULL)
        std::cout << "hover isn't ready" << std::endl;

    buttonTexture = texture;
}

void Button::handleEvents(SDL_Event& buttonEvent)
{
    switch (buttonEvent.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (buttonText == "left" || buttonText == "LEFT" || buttonText == "Left")
        {
            if (buttonEvent.button.button == SDL_BUTTON_LEFT)
            {
                mouse.x = buttonEvent.button.x;
                mouse.y = buttonEvent.button.y;
                if (Button::mouseInArea(button.x, button.y, button.w, button.h))
                {
                    callback();
                }
            }

        }
        else if (buttonText == "right" || buttonText == "RIGHT" || buttonText == "Right")
        {
            if (buttonEvent.button.button == SDL_BUTTON_RIGHT)
            {
                mouse.x = buttonEvent.button.x;
                mouse.y = buttonEvent.button.y;
                if (Button::mouseInArea(button.x, button.y, button.w, button.h))
                {
                    callback();
                }
            }
        }
        else
        {
            try
            {
                if (buttonText != "left" || buttonText != "LEFT" ||
                        buttonText != "Left" || buttonText != "right" ||
                        buttonText != "RIGHT" || buttonText != "Right" ||
                        buttonText == "place" || buttonText == "PLACE" ||
                        buttonText == "Place")
                    throw "You entered a bank or wrong side of button mouse";
            }
            catch (const char* exception)
            {
                std::cerr << "Catch in Button::handleEvent. Error: " << exception << std::endl;
            }
        }
        break;
    case SDL_MOUSEMOTION:
        mouse.x = buttonEvent.motion.x;
        mouse.y = buttonEvent.motion.y;
        if (Button::mouseInArea(button.x, button.y, button.w, button.h) &&
                FlagManager::flagHover == 1 &&
                hover != NULL)
        {
            hover();
        }
        else if (leaveHover != NULL)
        {
            leaveHover();
        }
        break;
    default:
        if (buttonText == "place" || buttonText == "PLACE" || buttonText == "Place")
        {
            callback();
        }
        break;
    }
}

bool Button::mouseInArea(int x, int y, int w, int h)
{
    bool validity;
    if ((mouse.x >= x) && (mouse.y >= y) && (mouse.x <= x + w) && (mouse.y <= y + h))
    {
        validity = true;
        FlagManager::flagHover = 1;
    }
    else
    {
        validity = false;
        FlagManager::flagHover = 0;
    }

    return validity;
}

void Button::Render()
{
    if (buttonTexture != NULL)
        RenderManager::CopyToRender(buttonTexture, ren, {button.x, button.y, button.w, button.h});
//    else
//        std::cout << "Error in Button::Render" << std::endl;
}

void Button::updateCoords(int newx, int newy)
{
    button.x = newx;
    button.y = newy;
}

void Button::updateScaleButton(int newx, int newy, int newh, int neww)
{
    button.x = newx;
    button.y = newy;
    button.w = neww;
    button.h = newh;
}

void Button::updateTexture(SDL_Texture* tex)
{
    buttonTexture = tex;
}

void Button::deleteTexture()
{
    SDL_DestroyTexture(buttonTexture);
    buttonTexture = 0;
}

Keyboard::Keyboard(SDL_Scancode scancode, std::function <void()> callbackFunction):
    code (scancode), callback(callbackFunction)
{
    try
    {
        if (callback == NULL)
            throw "callback in Keyboard is NULL";
    }
    catch (const char* exception)
    {
        std::cerr << "Catch exception in Keyboard::Keyboard. Error: " << exception << std::endl;
    }
}

Keyboard::~Keyboard()
{

}

void Keyboard::handleEvents(SDL_Event& keyboardEvent)
{
    if (buttonIsPressed(keyboardEvent) == true)
    {
        callback();
    }
}

bool Keyboard::buttonIsPressed(SDL_Event& keyboardEvent)
{
    SDL_Scancode tempcode = keyboardEvent.key.keysym.scancode;
    bool validity = false;
    switch (keyboardEvent.type)
    {
    case SDL_KEYDOWN:
        if (code == tempcode)
            validity = true;
        break;
    case SDL_KEYUP:
        validity = false;
        break;
    default:
        break;
    }
    return validity;
}

