/*
** EPITECH PROJECT, 2023
** R-Touhou_Bootstrap
** File description:
** Registry.hpp
*/

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <any>
#include <cstddef>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include "SparseArray.hpp"
#include "Entity.hpp"

namespace GameEngine
{
    /// @brief Registry class used to store all the components of the ECS
    class Registry
    {
      public:
        void clear()
        {
            // Clear all components and reset the state of the registry
            _container.clear();
            _deleters.clear();
            _systems.clear();
            _emptyIndexes.clear();
            _numEntities = 0;
        }
        /// @brief Constructor
        /// @param maxEntities Maximum number of entities
        explicit Registry(const std::size_t maxEntities) : _maxEntities(maxEntities){};

        std::vector<std::size_t> garbageEntities = {};
        /// @brief Register a new Component to the registry
        /// @tparam Component Type of the component to register
        /// @return A reference to the newly created sparseArray
        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            auto typeIndex = std::type_index(typeid(Component));
            _container[typeIndex] = SparseArray<Component>();
            return std::any_cast<SparseArray<Component>&>(_container[typeIndex]);
        };

        /// @brief Get a component from the registry
        /// @tparam Component Type of the component to get
        /// @return A reference to the SparseArray of the component
        template <class Component>
        SparseArray<Component> &getComponent()
        {
            auto typeIndex = std::type_index(typeid(Component));
            return std::any_cast<SparseArray<Component>&>(_container[typeIndex]);
        }

        /// @brief Get a component from the registry
        /// @tparam Component Type of the component to get
        /// @return A reference to the SparseArray of the component
        template <class Component>
        const SparseArray<Component> &getComponent() const
        {
            auto typeIndex = std::type_index(typeid(Component));
            return std::any_cast<const SparseArray<Component>&>(_container.at(typeIndex));
        };

        /// @brief Spawn a new entity
        /// @return The newly created entity
        Entity spawnEntity()
        {
            std::size_t index = 0;

            if (!_emptyIndexes.empty()) {
                index = _emptyIndexes.front();
                _emptyIndexes.erase(_emptyIndexes.begin());
                return Entity(index);
            }
            if (_numEntities > _maxEntities)
                throw std::out_of_range("numEntities > maxEntities");
            index = _numEntities;
            _numEntities++;
            return Entity(index);
        };

        /// @brief Spawn a new entity
        /// @param index Index of the entity to spawn
        /// @return The newly created entity
        Entity spawnEntity(const std::size_t &index)
        {
            if (index > _maxEntities)
                throw std::out_of_range("index > maxEntity");
            if (!_emptyIndexes.empty()) {
                auto it = std::lower_bound(_emptyIndexes.begin(), _emptyIndexes.end(), index);
                if (it != _emptyIndexes.end() && *it == index)
                    _emptyIndexes.erase(it);
                return Entity(index);
            }
            for (; _numEntities != index; _numEntities++)
                _emptyIndexes.push_back(_numEntities);
            std::sort(_emptyIndexes.begin(), _emptyIndexes.end());
            _numEntities++;
            return Entity(index);
        };

        /// @brief Get an entity by its id
        /// @param id Id of the entity to get
        /// @return The entity
        Entity getEntityById(const std::size_t &id) { return Entity(id); };

        void killEntity(const Entity &entity)
        {
            _emptyIndexes.push_back(entity);
            std::sort(_emptyIndexes.begin(), _emptyIndexes.end());
            for (std::size_t i = 0; i < _deleters.size(); i++)
                _deleters[i](*this, entity);
        };

        /// @brief Add a component to an entity
        /// @tparam Component Type of the component to add
        /// @param entity Entity to add the component to
        /// @param component Component to add
        /// @return A reference to the newly added component
        template <typename Component>
        typename SparseArray<Component>::ReferenceType addComponent(const Entity &entity, Component &&component)
        {
            return getComponent<Component>().insertAt(entity, std::forward<Component>(component));
        };

        /// @brief Add a component to an entity
        /// @tparam Component Type of the component to add
        /// @param entity Entity to add the component to
        /// @param component Component to add
        /// @return A reference to the newly added component
        template <typename Component>
        typename SparseArray<Component>::ReferenceType addComponent(const Entity &entity, const Component &component)
        {
            return getComponent<Component>().insertAt(entity, component);
        };

        /// @brief Add a component to an entity
        /// @tparam Component Type of the component to add
        /// @tparam ...Params Types of the parameters to pass to the constructor
        /// @param entity Entity to add the component to
        /// @param ...params Variadic parameters of the position to insert at
        /// @return A reference to the newly added component
        template <typename Component, typename... Params>
        typename SparseArray<Component>::ReferenceType emplaceComponent(const Entity &entity, Params &&...params)
        { 
            return getComponent<Component>().emplaceAt(entity, params...);
        };

        /// @brief Remove a component from an entity
        /// @tparam Component Type of the component to remove
        /// @param entity Entity to remove the component from
        template <typename Component>
        void removeComponent(const Entity &entity)
        {
            getComponent<Component>().erase(entity);
        };

      private:
        /// @brief Unordered map containing all the components
        std::unordered_map<std::type_index, std::any> _container;
        /// @brief Vector containing all the deleters
        std::vector<std::function<void(Registry &, const Entity &)>> _deleters;
        /// @brief Vector containing all the systems
        std::vector<std::function<void()>> _systems;
        /// @brief Vector containing all the empty indexes
        std::vector<std::size_t> _emptyIndexes;
        /// @brief Maximum number of entities
        std::size_t _maxEntities;
        /// @brief Number of entities
        std::size_t _numEntities = 0;
    };
} // namespace GameEngine

#endif // REGISTRY_H_
