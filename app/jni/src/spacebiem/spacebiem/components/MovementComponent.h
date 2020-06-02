#pragma once

#include "../../biemgine/Biemgine.h"

using biemgine::Component;

namespace spacebiem
{
    class MovementComponent :
        public Component
    {
    public:
        MovementComponent();
        float getJumpForce() const;
        void setJumpForce(float pJumpForce);
    private:
        float jumpForce = 30.f;
    };
}
