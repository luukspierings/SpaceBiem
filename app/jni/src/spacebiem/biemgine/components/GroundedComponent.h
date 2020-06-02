#pragma once


#include "../entities/Entity.h"
#include "Component.h"

namespace biemgine
{
    class GroundedComponent :
        public Component
    {
    public:
        bool isGrounded() const;
        GroundedComponent * setGrounded(bool pGrounded, Entity * pGroundedOn);
        Entity * getGroundedOn() const;

    private:
        bool grounded = false;
        Entity * groundedOn;
    };
}
