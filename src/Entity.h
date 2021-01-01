#pragma once
#include <vector>
#include <string>
#include <map>
#include <typeinfo>

#include "Constants.h"
#include "EntityManager.h"
#include "Component.h"

namespace MarkTwo
{
    namespace GameCore
    {
        class EntityManager;
        class Component;

        class Entity
        {
        public:
            Entity(EntityManager& manager);
            Entity(EntityManager& manager, std::string name, LayerType layer);
            void Update(float deltaTime);
            void Render();
            void Destroy();
            bool IsActive() const;
            void ListAllComponents() const;

            template <typename T, typename... TArgs>
            T& AddComponent(TArgs&&... args)
            {
                T* newComponent(new T(std::forward<TArgs>(args)...));
                newComponent->m_Owner = this;

                m_Components.emplace_back(newComponent);
                m_ComponentTypeMap[&typeid(*newComponent)] = newComponent;

                newComponent->Initialize();

                return *newComponent;
            }

            template <typename T>
            bool HasComponent() const
            {
                return m_ComponentTypeMap.count(&typeid(T));
            }


            template <typename T>
            T* GetComponent()
            {
                return static_cast<T*>(m_ComponentTypeMap[&typeid(T)]);
            }

        public:
            std::string m_Name;
            LayerType m_Layer;

        private:
            std::vector<Component*> m_Components;
            std::map<const std::type_info*, Component*> m_ComponentTypeMap;

            EntityManager& m_Manager;
            bool m_bIsActive;
        };
    }
}
