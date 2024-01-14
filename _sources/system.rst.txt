.. _system_class:

System Class
============

Overview
--------

The ``System`` class in the R-Touhou_Bootstrap project represents a set of systems that handle different aspects of the game, such as logging, updating positions, controlling entities, and drawing on the screen. It interacts with the ``Registry`` class to access and manipulate entity components.

Usage
-----

The ``System`` class provides various methods for different functionalities. Users can utilize these methods to perform tasks related to game logic and rendering.

Table of Contents
-----------------

1. :ref:`system_how_to_use`
2. :ref:`system_explanation`

How to Use the System Class
---------------------------

Before using the ``System`` class, ensure that you have a basic understanding of the ECS architecture and the components used in the R-Touhou_Bootstrap project.

1. Instantiate the ``System`` class.
2. Use the provided methods to perform different system-related tasks.

Example:

.. code-block:: cpp

   GameEngine::System gameSystem;
   gameSystem.loggingSystem(registry);
   gameSystem.positionSystem(registry);
   gameSystem.controlSystem(registry);
   gameSystem.drawSystem(registry, window);

Explanation of the System Class
-------------------------------

The ``System`` class consists of the following components:

1. **Default Constructor**

   The default constructor initializes a ``System`` instance.

   Example:

   .. code-block:: cpp

      System() = default;

2. **Destructor**

   The default destructor cleans up resources associated with the ``System``.

   Example:

   .. code-block:: cpp

      ~System() = default;

3. **Logging System**

   The ``loggingSystem`` method logs the positions and velocities of entities.

   Example:

   .. code-block:: cpp

      void loggingSystem(GameEngine::Registry &r);

4. **Position System**

   The ``positionSystem`` method updates the positions of entities based on their velocities.

   Example:

   .. code-block:: cpp

      void positionSystem(GameEngine::Registry &r);

5. **Control System**

   The ``controlSystem`` method handles user input to control entities.

   Example:

   .. code-block:: cpp

      void controlSystem(GameEngine::Registry &r);

6. **Draw System**

   The ``drawSystem`` method renders entities on the screen.

   Example:

   .. code-block:: cpp

      void drawSystem(GameEngine::Registry &r, sf::RenderWindow &window);

Private Members
---------------

- None

Note: This documentation provides an overview of the ``System`` class and its usage within the R-Touhou_Bootstrap project. For detailed implementation details and usage examples, refer to the corresponding source code.
