.. _entity_class:

Entity Class
=============

Overview
--------

The ``Entity`` class in the R-Touhou_Bootstrap project is designed to represent an entity within the Entity-Component-System (ECS) architecture. Entities are the fundamental building blocks in an ECS system and serve as containers for components.

Usage
-----

Before using the ``Entity`` class, ensure that you have a basic understanding of ECS and how entities are managed within the R-Touhou_Bootstrap project.

Table of Contents
-----------------

1. :ref:`entity_how_to_use`
2. :ref:`entity_explanation`

How to Use the Entity Class
--------------------------

1. Include the ``Entity.hpp`` header file in your source code.

   Example:

   .. code-block:: cpp

      #include "Entity.hpp"

2. Create an instance of the ``Entity`` class using the ``Registry`` class.

   Example:

   .. code-block:: cpp

      // Create an instance of the Registry class
      GameEngine::Registry registry;

      // Create a new entity using the Registry
      GameEngine::Entity entity = registry.spawnEntity();

3. Optionally, access the underlying numeric identifier of the entity.

   Example:

   .. code-block:: cpp

      // Access the numeric identifier of the entity
      std::size_t entityId = static_cast<std::size_t>(entity);

Explanation of the Entity Class
-------------------------------

The ``Entity`` class has the following components:

1. **Friend Class Declaration**

   The ``Entity`` class declares the ``Registry`` class as a friend, allowing the ``Registry`` class to access private members of the ``Entity`` class.

   Example:

   .. code-block:: cpp

      friend class Registry;

2. **Default Destructor**

   The default destructor for the ``Entity`` class is declared as default.

   Example:

   .. code-block:: cpp

      ~Entity() = default;

3. **Conversion Operator**

   The ``Entity`` class overloads the conversion operator to allow treating an instance of ``Entity`` as a ``std::size_t``. This enables using the entity's numeric identifier directly.

   Example:

   .. code-block:: cpp

      operator std::size_t() const { return _entity; };

4. **Explicit Constructor**

   The explicit constructor is used to create an entity with a specified numeric identifier.

   Example:

   .. code-block:: cpp

      explicit Entity(std::size_t entity) : _entity(entity){};

5. **Private Member**

   - ``_entity``: The numeric identifier representing the entity. It is declared as a private member to encapsulate the internal representation of the entity.

   Example:

   .. code-block:: cpp

      std::size_t _entity;

Note: This documentation provides an overview of the ``Entity`` class and its usage within the R-Touhou_Bootstrap project. For detailed implementation details and usage examples, refer to the corresponding source code.
