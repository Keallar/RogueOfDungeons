#include "Credits.h"
#include "Managers.h"
#include "Game.h"

Credits::Credits()
{
    GameTextures = TextureBase::Instance();

    background = GameTextures->GetTexture("PlayBack");
    firstName = FontManager::renderText("Keallar", PATH_IN_FONT, COLOR, 64, Game::renderer);

}

void Credits::render()
{

}
