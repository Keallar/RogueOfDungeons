#include "Credits.h"
#include "Managers.h"
#include "Game.h"

Credits::Credits()
{
    GameTextures = TextureBase::Instance();

    background = GameTextures->GetTexture("PlayBack");
    creators = FontManager::renderText("Creators", PATH_IN_FONT, COLOR, 64, Game::renderer);
    firstName = FontManager::renderText("Keallar", PATH_IN_FONT, COLOR, 64, Game::renderer);
    secondName = FontManager::renderText("zezzeebka", PATH_IN_FONT, COLOR, 64, Game::renderer);
    thirdName = FontManager::renderText("Legida", PATH_IN_FONT, COLOR, 64, Game::renderer);
    fourthName = FontManager::renderText("Balalarga", PATH_IN_FONT, COLOR, 64, Game::renderer);
    fifthName = FontManager::renderText("Pohitysha", PATH_IN_FONT, COLOR, 64, Game::renderer);

    buttonForBack = new Button(GameTextures->GetTexture("Button"), Game::renderer, {0, 0, 0, 0});
}

void Credits::render()
{
    RenderManager::CopyToRender(background, Game::renderer, 0, 0, SCREEN_HEGHT, SCREEN_WEIGHT);
    SDL_QueryTexture(creators, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(creators, Game::renderer, SCREEN_HEGHT/3, SCREEN_WEIGHT/3, textW, textH);
    SDL_QueryTexture(firstName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(firstName, Game::renderer, SCREEN_HEGHT/3, SCREEN_WEIGHT/3, textW, textH);
    SDL_QueryTexture(secondName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(secondName, Game::renderer, SCREEN_HEGHT/3, SCREEN_WEIGHT/3, textW, textH);
    SDL_QueryTexture(thirdName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(thirdName, Game::renderer, SCREEN_HEGHT/3, SCREEN_WEIGHT/3, textW, textH);
    SDL_QueryTexture(fourthName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(fourthName, Game::renderer, SCREEN_HEGHT/3, SCREEN_WEIGHT/3, textW, textH);
    SDL_QueryTexture(fifthName, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(fifthName, Game::renderer, SCREEN_HEGHT/3, SCREEN_WEIGHT/3, textW, textH);
}
