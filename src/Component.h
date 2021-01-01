#pragma once

#include "Entity.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class Entity;

        class Component
        {
        public:
            virtual ~Component() {}
            virtual void Initialize() {}
            virtual void Update(float deltaTime) {}
            virtual void Render() {}

        public:
            Entity* m_Owner;
        };

    }
}
