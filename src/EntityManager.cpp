#include <iostream>
#include <vector>
#include "EntityManager.h"
#include "Components/ColliderComponent.h"
#include "Collision.h"

namespace MarkTwo
{
    namespace GameCore
    {
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void EntityManager::Update(float deltaTime)
        {
            for (auto& entity : entities)
            {
                entity->Update(deltaTime);
            }

            DestroyInactiveEntities();
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void EntityManager::Render()
        {
            for (int layerNumber = 0; layerNumber < NUM_LAYERS; ++layerNumber)
            {
                for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
                {
                    entity->Render();
                }
            }
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void EntityManager::ClearData()
        {
            for (auto& entity : entities)
            {
                entity->Destroy();
            }
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        bool EntityManager::HasNoEntities()
        {
            return entities.size() == 0;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Entity& EntityManager::AddEntity(std::string entityName, LayerType layer)
        {
            Entity* entity = new Entity(*this, entityName, layer);
            entities.emplace_back(entity);

            return *entity;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Entity* EntityManager::GetEntityByName(std::string entityName) const {
            for (auto* entity: entities) {
                if (entity->m_Name.compare(entityName) == 0) {
                    return entity;
                }
            }
            return NULL;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
        {
            std::vector<Entity*> selectedEntities;
            for (auto& entity : entities)
            {
                if (entity->m_Layer == layer)
                {
                    selectedEntities.emplace_back(entity);
                }
            }

            return selectedEntities;
        }

        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        std::vector<Entity*> EntityManager::GetEntities() const
        {
            return entities;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        CollisionType EntityManager::CheckCollisions() const
        {
            // --------------------------------- 
            // REDUCE COMPLEXITY LATER!
            // --------------------------------- 
            for (int i = 0; i < entities.size() - 1; i++)
            {
                auto& thisEntity = entities[i];
                if (thisEntity->HasComponent<ColliderComponent>())
                {
                    ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
                    for (int j = i + 1; j < entities.size(); j++)
                    {
                        auto& thatEntity = entities[j];
                        if (thisEntity->m_Name.compare(thatEntity->m_Name) != 0 &&
                            thatEntity->HasComponent<ColliderComponent>())
                        {
                            ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
                            if (Collision::CheckRectangleCollision(thisCollider->m_Collider, thatCollider->m_Collider))
                            {
                                if (thisCollider->m_ColliderTag.compare("PLAYER") == 0 &&
                                    thatCollider->m_ColliderTag.compare("ENEMY") == 0)
                                {
                                    return PLAYER_ENEMY_COLLISION;
                                }
                                if (thisCollider->m_ColliderTag.compare("PLAYER") == 0 &&
                                    thatCollider->m_ColliderTag.compare("PROJECTILE") == 0)
                                {
                                    return PLAYER_PROJECTILE_COLLISION;
                                }
                                if (thisCollider->m_ColliderTag.compare("ENEMY") == 0 &&
                                    thatCollider->m_ColliderTag.compare("FRIENDLY_PROJECTILE") == 0)
                                {
                                    return ENEMY_PROJECTILE_COLLISION;
                                }
                                if (thisCollider->m_ColliderTag.compare("PLAYER") == 0 &&
                                    thatCollider->m_ColliderTag.compare("LEVEL_COMPLETE") == 0)
                                {
                                    return PLAYER_LEVEL_COMPLETE_COLLISION;
                                }

                                // Player shooting projectile
                                if (thisCollider->m_ColliderTag.compare("PLAYERPROJECTILE") == 0 &&
                                    thatCollider->m_ColliderTag.compare("ENEMY") == 0)
                                {
                                    return PLAYERPROJECTILE_ENEMY_COLLISION;
                                }
                                if (thisCollider->m_ColliderTag.compare("PLAYERPROJECTILE") == 0 &&
                                    thatCollider->m_ColliderTag.compare("VEGETATION") == 0)
                                {
                                    return PLAYERPROJECTILE_VEGETATION_COLLISION;
                                }
                            }
                        }
                    }
                }
            }

            return NO_COLLISION;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        unsigned int EntityManager::GetEntityCount()
        {
            return entities.size();
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void EntityManager::ListAllEntities() const
        {
            unsigned int i = 0;
            for (auto& entity : entities)
            {
                std::cout << "Entity[" << i << "]: " << entity->m_Name << std::endl;
                entity->ListAllComponents();
                ++i;
            }
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void EntityManager::DestroyInactiveEntities()
        {
            for (int x = 0; x < entities.size(); ++x)
            {
                if (!entities[x]->IsActive())
                {
                    entities.erase(entities.begin() + x);
                }
            }
        }

    }
}
