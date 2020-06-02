#pragma once


namespace biemgine {
    struct TextureAndUsage {
        SDL_Texture* texture;
        int usageCount = 0;

    };
}
