#include "TitleScreen.h"

TitleScreen::TitleScreen(const char* titleText, SDL_Texture* texture, SDL_Renderer* renderer)
{
    auto Skip {
        [this]()
        {
            flag = false;
        }
    };
    flag = false;
    GameTextures = TextureBase::Instance();
    ren = renderer;
    titleTextTexture = FontManager::renderText(titleText, "data/fonts/manaspc.ttf", { 255, 255, 255, 255 }, 80, ren);
    textureUnderTitle = texture;
    SkipButton = new Button("Left", GameTextures->GetTexture("Button"), ren, {1148, 638, 32, 32}, Skip, NULL, NULL);
    SDL_QueryTexture(titleTextTexture, NULL, NULL, &textW, &textH);
    SDL_QueryTexture(textureUnderTitle, NULL, NULL, &textWunder, &textHunder);
}

TitleScreen::~TitleScreen() {
    SDL_DestroyTexture(titleTextTexture);
}

void TitleScreen::Render() {
    RenderManager::CopyToRender(GameTextures->GetTexture("PlayBack"), ren);
    if(textureUnderTitle != nullptr) {
        RenderManager::CopyToRender(textureUnderTitle, ren, {(1280-textWunder)/2, (720-textHunder)/2 + 100, textWunder, textHunder});
    }
    RenderManager::CopyToRender(titleTextTexture, ren, {(1280-textW)/2, (720-textH)/2 - 200, textW, textH});
    SkipButton->Render();
}

void TitleScreen::handleEvents(SDL_Event& event) {
    SkipButton->handleEvents(event);
}
