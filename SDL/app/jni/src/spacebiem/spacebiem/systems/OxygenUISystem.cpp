
#include "OxygenUISystem.h"

namespace spacebiem
{
    void OxygenUISystem::onAddEntity(Entity & entity)
    {
        if (!entity.hasComponent("oxygen")) return;

        if (!entity.hasComponent("ui"))
        {
            OxygenEntry oxygenEntry;
            oxygenEntry.entity = &entity;
            oxygenEntry.oxygenComponent = entity.getComponent<OxygenComponent>("oxygen");

            oxygenEntries.push_back(std::move(oxygenEntry));
        }


        TextureEntry textureEntry;
        textureEntry.entity = &entity;
        textureEntry.textureComponents = entity.getComponents<TextureComponent>("texture");

        textureEntries.push_back(std::move(textureEntry));
    }

    void OxygenUISystem::update()
    {
        for (const OxygenEntry& entry : oxygenEntries)
        {
            float oBar = entry.oxygenComponent->getOxygenAmount() / static_cast<float>(entry.oxygenComponent->getOxygenMax());
            float vignet = entry.oxygenComponent->getOxygenAmount() / (static_cast<float>(entry.oxygenComponent->getOxygenMax() / 2));
            float alphaVignet = 255 * (1 - vignet);

            for (const TextureEntry& textureEntry : textureEntries)
            {
                for (const auto& tex : textureEntry.textureComponents)
                {
                    if (tex->getTag() == "oxygenbar")
                    {
                        Color dangerRedColor{204, 94, 94};
                        Color newColor{
                                static_cast<unsigned  char>(dangerRedColor.r + static_cast<char>((tex->getOriginalColor().r - dangerRedColor.r) * oBar)),
                                static_cast<unsigned char>(dangerRedColor.g + static_cast<char>((tex->getOriginalColor().g - dangerRedColor.g) * oBar)),
                                        static_cast<unsigned  char>(dangerRedColor.b + static_cast<char>((tex->getOriginalColor().b - dangerRedColor.b) * oBar))
                        };

                        tex->setWidth(static_cast<int>(tex->getOriginalWidth() * oBar));
                        tex->setColor(newColor);
                    }

                    if (tex->getTag() == "vignet" && vignet <= 1) tex.get()->setColor(tex.get()->getColor().WithAlpha(alphaVignet));
                }  
            }
        }
    }
}
