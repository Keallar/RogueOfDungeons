#include "ClassChoose.h"

ClassChoose::ClassChoose(SDL_Renderer* renderer) : ren(renderer)
{
    auto ClassChoose {
        [=]()
        {
            haveClass = true;
            int mouseX; int mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            choosedClass = 1;
            if (mouseX > 541) choosedClass = 2;
            if (mouseX > 723) choosedClass = 3;
        }
    };
    flag = 0;
    choosedClass = 0;
    haveClass = false;
    GameTextures = TextureBase::Instance();
    Text = FontManager::renderText("Choose Class", "data/fonts/manaspc.ttf", { 255, 255, 255, 255 }, 60, ren);
    SDL_QueryTexture(Text, NULL, NULL, &textW, &textH);
    warriorB = new Button("left", GameTextures->GetTexture("WarriorClass"), ren, {413, 296, 128, 128}, ClassChoose, NULL);
    archerB = new Button("left", GameTextures->GetTexture("ArcherClass"), ren, {575, 296, 128, 128}, ClassChoose, NULL);
    mageB = new Button("left", GameTextures->GetTexture("MageClass"), ren, {739, 296, 128, 128}, ClassChoose, NULL);
}
void ClassChoose::handleEvents(SDL_Event event) {
    warriorB->handleEvents(event);
    archerB->handleEvents(event);
    mageB->handleEvents(event);
}

void ClassChoose::Render() {
    RenderManager::CopyToRender(GameTextures->GetTexture("PlayBack"), ren);
    RenderManager::CopyToRender(Text, ren, (1280-textW)/2, (720-textH)/2 - 200, textW, textH);
    warriorB->Render();
    archerB->Render();
    mageB->Render();
}

