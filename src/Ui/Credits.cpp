#include "Credits.h"
#include "Managers.h"
#include "Game.h"

Credits::Credits(MainMenu* Menu)
{
    GameTextures = TextureBase::Instance();

    background = GameTextures->GetTexture("PlayBack");
    creators = FontManager::renderText("Creators", PATH_IN_FONT, COLOR, 64, Game::renderer);
    firstName = FontManager::renderText("Keallar", PATH_IN_FONT, COLOR, 64, Game::renderer);
    secondName = FontManager::renderText("zezzeebka", PATH_IN_FONT, COLOR, 64, Game::renderer);
    thirdName = FontManager::renderText("Legida", PATH_IN_FONT, COLOR, 64, Game::renderer);
    fourthName = FontManager::renderText("Balalarga", PATH_IN_FONT, COLOR, 64, Game::renderer);
    fifthName = FontManager::renderText("Pohitysha", PATH_IN_FONT, COLOR, 64, Game::renderer);
    auto callback
    {
        [=]()
        {
            Menu->flag = 1;
        }
    };
    buttonForBack = new Button("Left", GameTextures->GetTexture("Button"), Game::renderer, {SCREEN_WEIGHT/2+250, 640, 64, 64}, callback, NULL, NULL);
}

void Credits::render()
{
    RenderManager::CopyToRender(background, Game::renderer, 0, 0, SCREEN_HEIGHT, SCREEN_WEIGHT);
    SDL_QueryTexture(creators, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(creators, Game::renderer, SCREEN_WEIGHT/2+60, 20, textW, textH);
    SDL_QueryTexture(firstName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(firstName, Game::renderer, SCREEN_HEIGHT/2+300, 40, textW, textH);
    SDL_QueryTexture(secondName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(secondName, Game::renderer, SCREEN_HEIGHT/2+250, 640, textW, textH);
    SDL_QueryTexture(thirdName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(thirdName, Game::renderer, 40, 40, textW, textH);
    SDL_QueryTexture(fourthName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(fourthName, Game::renderer, SCREEN_HEIGHT/3, SCREEN_WEIGHT/2, textW, textH);
    SDL_QueryTexture(fifthName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(fifthName, Game::renderer, 40, 640, textW, textH);
    buttonForBack->Render();
}
void Credits::handleEvent(SDL_Event &e)
{
    buttonForBack->handleEvents(e);
}
