#pragma once


#include <typeindex>
#include <typeinfo>

namespace biemgine
{
    class Component
    {
    public:
        Component();
        virtual ~Component();

        const std::type_index type() {
            return std::type_index(typeid(this));
        }
    };
}
