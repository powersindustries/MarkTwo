#pragma once
#include <vector>

#include "Entity.h"
#include "Component.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class Entity;

        class EntityManager
        {
        public:
            void Update(float deltaTime);
            void Render();
            void ClearData();
            bool HasNoEntities();
            unsigned int GetEntityCount();
            void ListAllEntities() const;
            void DestroyInactiveEntities();

            Entity& AddEntity(std::string entityName, LayerType layer);

            Entity* GetEntityByName(std::string entityName) const;
            
            std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
            std::vector<Entity*> GetEntities() const;

            CollisionType CheckCollisions() const;

        private:
            std::vector<Entity*> entities;
        };

    }
}
