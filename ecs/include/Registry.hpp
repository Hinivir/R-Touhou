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

#include "Components/Drawable.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Controllable.hpp"

namespace GameEngine
{
    /// @brief Registry class used to store all the components of the ECS
    class Registry
    {
      public:
        /// @brief Constructor
        /// @param maxEntities Maximum number of entities
        explicit Registry(const std::size_t maxEntities) : _maxEntities(maxEntities){};

        /// @brief Register a new Component to the registry
        /// @tparam Component Type of the component to register
        /// @return A reference to the newly created sparseArray
        /*template <class Component>
        SparseArray<Component> &registerComponent()
        {
            _container.insert({std::type_index(typeid(Component)), SparseArray<Component>()});
            SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container[std::type_index(typeid(Component))]);
            ret.resize(_maxEntities);
            std::function<void(Registry &, const Entity &)> deleter = [](Registry &registry, const Entity &entity) {
                registry.getComponent<Component>().erase(entity);
            };
            _deleters.push_back(deleter);
            return ret;
        };*/

        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            auto typeIndex = std::type_index(typeid(Component));
            _container[typeIndex] = SparseArray<Component>();
            return std::any_cast<SparseArray<Component>&>(_container[typeIndex]);
        };
        /*template <class Component>
        SparseArray<Component> &registerComponent()
        {
            auto it = _container.find(std::type_index(typeid(Component)));
            if (it == _container.end()) {
                // Component not registered yet, create a new SparseArray
                auto [newIt, success] = _container.emplace(std::type_index(typeid(Component)), SparseArray<Component>());
                if (!success) {
                    throw std::runtime_error("Failed to register component in the registry");
                }
                return std::any_cast<SparseArray<Component> &>(newIt->second);
            } else {
                // Component already registered, return the existing SparseArray
                return std::any_cast<SparseArray<Component> &>(it->second);
            }
        }*/

        // Register the components to the registry
        //SparseArray<Position> &positions = registerComponent<Position>();
        //SparseArray<Velocity> &velocities = registerComponent<Velocity>();
        //SparseArray<Drawable> &drawables = registerComponent<Drawable>();
        //SparseArray<Controllable> &controllables = registerComponent<Controllable>();

        /// @brief Get a component from the registry
        /// @tparam Component Type of the component to get
        /// @return A reference to the SparseArray of the component
        /*template <class Component>
        SparseArray<Component> &getComponent()
        {
            SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container[std::type_index(typeid(Component))]);
            return ret;
        };*/
        /*template <class Component>
        SparseArray<Component> &getComponent()
        {
            auto &anyRef = _container[std::type_index(typeid(Component))];

            try {
                return std::any_cast<SparseArray<Component> &>(anyRef);
            } catch (const std::bad_any_cast &) {
                throw std::runtime_error("Component not found in registry");
            }
        };*/
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

        /// @brief Logging system
        /// @param r The registry
        static void loggingSystem(Registry &r)
        {
            auto const &positions = r.getComponent<Position>();
            auto const &velocities = r.getComponent<Velocity>();

            for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                auto const &pos = positions[i];
                auto const &vel = velocities[i];
                if (pos && vel) {
                    std::cerr << i << ": Position = { " << pos.value().pos_x << ", " << pos.value().pos_y
                              << " } , Velocity = { " << vel.value().x << ", " << vel.value().y << " }" << std::endl;
                }
            }
        }

        /// @brief Position system
        /// @param r The registry
        void positionSystem(Registry &r)
        {
            auto &positions = getComponent<Position>();
            auto &velocities = getComponent<Velocity>();

            for (std::size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
                auto &pos = positions[i];
                auto &vel = velocities[i];
                if (pos && vel) {
                    pos.value().pos_x += vel.value().x;
                    pos.value().pos_y += vel.value().y;
                }
            }
        }

        /// @brief Control system
        /// @param r The registry
        static void controlSystem(Registry &r)
        {
            // todo
        }

        /// @brief Draw system
        /// @param r The registry
        void drawSystem(Registry &r)
        {
            auto &positions = getComponent<Position>();
            auto &drawables = getComponent<Drawable>();

            for (std::size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
                auto &pos = positions[i];
                const auto &draw = drawables[i];
                if (pos && draw) {
                    std::cout << "Drawing entity " << i << " at position " << pos.value().pos_x << ", "
                              << pos.value().pos_y << std::endl;
                    // draw the sprite
                }
            }
        }

        template <class... Components, typename Function>
        void addSystem(Function &&function)
        {
            _systems.push_back([this, function = std::forward<Function>(function)]() {
                auto &components = std::tuple<SparseArray<Components> &...>(getComponent<Components>()...);
                function(*this, components);
            });
        }

        template <class... Components, typename Function>
        void addSystem(Function const &f)
        {
            _systems.push_back([this, function = std::forward<Function>(f)]() {
                auto &components = std::tuple<SparseArray<Components> &...>(getComponent<Components>()...);
                function(*this, components);
            });
        };

        void runSystem()
        {
            for (auto &system : _systems)
                system();
        };

        /// @brief Get an entity by its id
        /// @param id Id of the entity to get
        /// @return The entity
        static Entity getEntityById(const std::size_t &id) { return Entity(id); };

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
        /* template <typename Component>
        typename SparseArray<Component>::ReferenceType addComponent(const Entity &entity, Component &&component)
        {
            return getComponent<Component>().insertAt(entity, component);
        }; */

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
