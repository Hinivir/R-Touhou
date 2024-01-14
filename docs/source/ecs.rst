.. _ecs-doc:

ECS
====================

Welcome to the ECS documentation. Here you'll find everything that you need for creating your own game!

Table of Contents
-----------------

1. `Guides`_
2. `Detailed Documentation`_
3. `Questions`_

Guides
------

.. toctree::
   :maxdepth: 2

   ecs/guides/components
   ecs/guides/systems

Detailed Documentation
----------------------

.. toctree::
   :maxdepth: 2

   ecs/documentation/components
   ecs/documentation/systems
   ecs/documentation/macros

Questions
---------

How do I import LType's ECS?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

All the code that you'll need is inside headers. (.hpp files)

You just have to import the headers that you need in your files.

For example, if you have the following code:

.. code:: cpp

   #include <SFML/Graphics.hpp>
   #include <iostream>
   int main(void)
   {
      // Initialisation
      int nbRegistry = 1024;
      sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ECS");
      GameEngine::Registry registry(nbRegistry);
      GameEngine::System system;
      // Registering components for system.spriteSystem and system.drawSystem
      registry.registerComponent<GameEngine::Color>();
      registry.registerComponent<GameEngine::Controllable>();
      registry.registerComponent<GameEngine::Drawable>();
      registry.registerComponent<GameEngine::Outline>();
      registry.registerComponent<GameEngine::Position>();
      registry.registerComponent<GameEngine::Size>();
      registry.registerComponent<GameEngine::Sprite>();
      registry.registerComponent<GameEngine::SpriteTextureAnimation>();
      registry.registerComponent<GameEngine::SpriteTextureRect>();
      registry.registerComponent<GameEngine::Text>();
      registry.registerComponent<GameEngine::ZIndex>();
      // Main Loop
      while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
               if (event.type == sf::Event::Closed)
                  window.close();
            // Initializing sprite textures
            system.spriteSystem(registry);
            // Drawing entities on screen
            system.drawSystem(registry, window);
            // Displaying SFML window, then clearing it
            window.display();
            window.clear();
      }
      return 0;
   }

You'll just need to import the following headers at the start of your code:

.. code:: cpp

   #include "Registry.hpp"
   #include "Systems.hpp"

Do I need to register my components before using them?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Yes, you'll need to register your components before using them. Otherwise, the ECS can't store your data.

What is the **sf** namespace
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The **sf** namespace is used by the multimedia library called [SFML](https://www.sfml-dev.org).

This ECS uses SFML for everything related to graphics.

Code from SFML does **NOT** come from this ECS.

Can I register multiple components in one line?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Technically no, but sort of. The only way to register multiple components in one line should be something like:

.. code:: cpp

   registry.registerComponent<GameEngine::Color>(); registry.registerComponent<GameEngine::Drawable>(); registry.registerComponent<GameEngine::Sprite>();

But it's not really pretty and readable, isn't it?

If you really want to define multiple components like this, you can still use the `GAME_ENGINE_FOR_EACH` macro in the following way:

.. code:: cpp

   #include "Macros/ForEach.hpp"
   #define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();
   GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT, GameEngine::Color, GameEngine::Drawable, GameEngine::Sprite)

Warning! As seeen in :ref:`ecs-documentation-macros`, the `GAME_ENGINE_FOR_EACH` macro may **not** work on **Windows** devices!

Do you like ice cream?
~~~~~~~~~~~~~~~~~~~~~~

Yes I do.