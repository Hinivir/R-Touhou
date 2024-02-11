/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Entity
*/

#ifndef ENTITY_H_
#define ENTITY_H_

#include <cstddef>

namespace GameEngine
{
    class Registry;

    /// @brief Entity class used to represent an entity in the ECS
    class Entity
    {
      public:
        friend class Registry;

        /// @brief Explicit constructor to create an entity
        /// @param entity Number of the entity
        explicit Entity(std::size_t entity) : _entity(entity){};

        /// @brief Default destructor
        Entity() = default;
        ~Entity() = default;

        /// @brief Overload to be able to use the Entity class as a std::size_t
        operator std::size_t() const { return _entity; };

      private:
        /// @brief Number of the entity
        std::size_t _entity;
    };
} // namespace GameEngine

#endif // ENTITY_H_
