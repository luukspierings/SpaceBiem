#pragma once

#include "../../biemgine/Biemgine.h"


using biemgine::Component;

namespace spacebiem
{
    class ScoreBonusComponent :public Component
    {
    public:
        ScoreBonusComponent(int pScoreBonus, bool pScoreGiven = false);
        int getScoreBonus() const;

        void setScoreGiven(bool pScoreGiven);
        bool isScoreGiven() const;

    private:
        int scoreBonus;
        bool scoreGiven = false;
    };
}
