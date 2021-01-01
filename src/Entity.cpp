#include <iostream>
#include "Entity.h"

namespace MarkTwo
{
    namespace GameCore
    {
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Entity::Entity(EntityManager& manager) : m_Manager(manager)
        {
            m_bIsActive = true;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        Entity::Entity(EntityManager& manager, std::string name, LayerType layer) : m_Manager(manager), m_Name(name), m_Layer(layer)
        {
            m_bIsActive = true;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Entity::Update(float deltaTime)
        {
            // Loop throguh all components and update them all
            for (auto& component : m_Components)
            {
                component->Update(deltaTime);
            }
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Entity::Render()
        {
            // Loop throguh all components and render them all
            for (auto& component : m_Components)
            {
                component->Render();
            }
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Entity::Destroy()
        {
            m_bIsActive = false;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        bool Entity::IsActive() const
        {
            return m_bIsActive;
        }


        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        void Entity::ListAllComponents() const
        {
            for (auto mapElement : m_ComponentTypeMap)
            {
                std::cout << " Component<" << mapElement.first->name() << ">" << std::endl;
            }
        }

    }
}

