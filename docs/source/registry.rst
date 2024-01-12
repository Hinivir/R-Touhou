.. _registry_class:

Registry Class
==============

Overview
--------

The ``Registry`` class in the R-Touhou_Bootstrap project serves as a central hub for managing and storing components in an Entity-Component-System (ECS) architecture. It allows the registration of different components, entity creation, component addition/removal, and entity deletion.

Usage
-----

The ``Registry`` class is a fundamental part of ECS systems, enabling the organization and manipulation of game entities and their associated components.

Table of Contents
-----------------

1. :ref:`registry_how_to_use`
2. :ref:`registry_explanation`

How to Use the Registry Class
-----------------------------

Before using the ``Registry`` class, ensure that you have a basic understanding of ECS and the components used in the R-Touhou_Bootstrap project.

1. Instantiate the ``Registry`` class with the desired maximum number of entities.
2. Register components using the ``registerComponent`` method.
3. Spawn entities using the ``spawnEntity`` method.
4. Add, remove, or modify components for entities as needed.

Example:

.. code-block:: cpp

   GameEngine::Registry registry(100); // Maximum 100 entities
   auto &positions = registry.registerComponent<GameEngine::Position>();
   auto &velocities = registry.registerComponent<GameEngine::Velocity>();
   auto &drawables = registry.registerComponent<GameEngine::Drawable>();

   GameEngine::Entity entity = registry.spawnEntity();
   positions.emplaceAt(entity);
   velocities.emplaceAt(entity, 1, 0);
   drawables.emplaceAt(entity, "example_sprite.png");

Explanation of the Registry Class
---------------------------------

The ``Registry`` class consists of the following components:

1. **Constructor**

   The constructor initializes a ``Registry`` instance with the specified maximum number of entities.

   Example:

   .. code-block:: cpp

      explicit Registry(const std::size_t maxEntities);

2. **Register Component Method**

   The ``registerComponent`` method registers a new component to the registry.

   Example:

   .. code-block:: cpp

      template <class Component>
      SparseArray<Component> &registerComponent();

3. **Get Component Method**

   The ``getComponent`` method retrieves a reference to the ``SparseArray`` of a specified component.

   Example:

   .. code-block:: cpp

      template <class Component>
      SparseArray<Component> &getComponent();

   Note: There are multiple implementations of this method in the source code.

4. **Spawn Entity Methods**

   - ``spawnEntity()``: Spawns a new entity.
   - ``spawnEntity(const std::size_t &index)``: Spawns a new entity with a specific index.

   Example:

   .. code-block:: cpp

      Entity spawnEntity();
      Entity spawnEntity(const std::size_t &index);

5. **Kill Entity Method**

   The ``killEntity`` method marks an entity for removal.

   Example:

   .. code-block:: cpp

      void killEntity(const Entity &entity);

6. **Add Component Methods**

   - ``addComponent``: Adds a component to an entity.
   - ``emplaceComponent``: Adds a component to an entity with additional parameters.

   Example:

   .. code-block:: cpp

      template <typename Component>
      typename SparseArray<Component>::ReferenceType addComponent(const Entity &entity, Component &&component);

      template <typename Component, typename... Params>
      typename SparseArray<Component>::ReferenceType emplaceComponent(const Entity &entity, Params &&...params);

7. **Remove Component Method**

   The ``removeComponent`` method removes a component from an entity.

   Example:

   .. code-block:: cpp

      template <typename Component>
      void removeComponent(const Entity &entity);

Private Members
---------------

- ``_container``: Unordered map containing all the components.
- ``_deleters``: Vector containing all the deleters.
- ``_systems``: Vector containing all the systems.
- ``_emptyIndexes``: Vector containing all the empty indexes.
- ``_maxEntities``: Maximum number of entities.
- ``_numEntities``: Number of entities.

Note: This documentation provides an overview of the ``Registry`` class and its usage within the R-Touhou_Bootstrap project. For detailed implementation details and usage examples, refer to the corresponding source code.
