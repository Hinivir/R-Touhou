.. _ecs-guides-systems:

ECS - Systems Guide
====================

Learn how to make system with the creation of a systemGravity component

Table of Contents
-----------------

1. `Declaring a system`_
2. `Extracting data from the registry`_
3. `Looping through our entities`_
4. `Result`_
5. `Expendaing with MyGame::Gravity`_

Declaring a system
-----------------

First, a system from the ECS takes the form of a function.

To create a new system, declare a function having a Registry class as arguments:

.. code:: cpp

    void systemGravity(GameEngine::Registry &r)

Note
~~~~~~~~~~~~~~~~~

We can also declare `r` as const if we don't plan on changing anything about the registry.

If we need to access things like the current window, we can also include it in the arguments, giving us `void systemGravity(GameEngine::Registry &r, sf::RenderWindow &window)` instead.

Extracting data from the registry
-----------------

From now on, we can extract any data that we want. Here, we want to create a simple gravity system, so we'll need the positions of our entities.

For that, we'll use the `EXTRACT_COMPONENT_FROM` macro, creating us a list of values from a registry.

.. code:: cpp

    EXTRACT_COMPONENT_FROM(GameEngine::Position, positions, r)

Since we are calling our registry `r`, we can also simplify it with the `EXTRACT_COMPONENT` macro:

.. code:: cpp

    EXTRACT_COMPONENT(GameEngine::Position, positions)

Note
~~~~~~~~~~~~~~~~~

If the data we're declaring doesn't have to be modified, we can use the `EXTRACT_COMPONENT_CONST` and `EXTRACT_COMPONENT_FROM_CONST` macros instead.

Looping through our entities
-----------------

We'll first make a loop iterating through our positions, giving us `for (std::size_t i = 0; i < positions.size(); ++i)`.

Then, we'll need to extract from `positions` the current position of the entity at `i`: `FROM_COMPONENT_TO_VARIABLE(positions, i, position, hasPosition);`

Here, we are declaring 2 variables :
- `position` being a `std::optional` containing (if possible) our GameEngine::Position.
- `hasPosition` being a `bool` containing if we have or not a position at `i` in positions.

Note
~~~~~~~~~~~~~~~~~

We can also use `FROM_COMPONENT_TO_VARIABLE_CONST` for a const alternative of `FROM_COMPONENT_TO_VARIABLE`.

If we just want to extract `hasPosition`, we can also use `bool const hasPosition = DO_COMPONENT_CONTAINS_AT(positions, i)`.


Result
-----------------

Putting everything together, we have:

.. code:: cpp

    void systemGravity(GameEngine::Registry &r) {
        EXTRACT_COMPONENT(GameEngine::Position, positions);
        for (std::size_t i = 0; i < positions.size(); ++i) {
            FROM_COMPONENT_TO_VARIABLE(positions, i, position, hasPosition);
            if (hasPosition)
                position.value().y -= 2;
        }
    }

Calling the system
-----------------

Hop back in your main and add `systemGravity(registry);` before calling `system.drawSystem(registry, window);`.

Expendaing with MyGame::Gravity
-----------------

In :ref:`ecs-guides-components`, we made a new component called `MyGame::Gravity`, let's use it.

Extract
~~~~~~~~~~~~~~~~~

We'll extract our component as we did for `GameEngine::Position`, but this time as a const: `EXTRACT_COMPONENT_CONST(MyGame::Gravity, gravities)`

Loop
~~~~~~~~~~~~~~~~~

Extracting the entity data from our component list should be (almost) the same: `FROM_COMPONENT_TO_VARIABLE_CONST(gravities, i, gravity, hasGravity)`

Final result
~~~~~~~~~~~~~~~~~

Putting everything together, we have:

.. code:: cpp

    void systemGravity(GameEngine::Registry &r) {
        EXTRACT_COMPONENT(GameEngine::Position, positions);
        EXTRACT_COMPONENT_CONST(MyGame::Gravity, gravities);
        for (std::size_t i = 0; i < positions.size(); ++i) {
            FROM_COMPONENT_TO_VARIABLE(positions, i, position, hasPosition);
            FROM_COMPONENT_TO_VARIABLE_CONST(gravities, i, gravity, hasGravity);
            if (hasPosition && hasGravity && gravity.value().isAffectedByGravity)
                position.value().y -= gravity.value().weigth;
        }
    }

With a main that should look like this:

.. code:: cpp

    #include "Registry.hpp"
    #include "Systems/Draw.hpp"
    #include "Systems/Sprite.hpp"
    #include "GravityComponent.hpp"
    #include <SFML/Graphics.hpp>
    #include <iostream>
    int main(void)
    {
        // Initialisation
        int nbRegistry = 1024;
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ECS");
        window.setFramerateLimit(60);
        GameEngine::Registry registry(nbRegistry);
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
        registry.registerComponent<MyGame::Gravity>();
        // Test Entity
        GameEngine::Entity entity = registry.spawnEntity();
        registry.addComponent<MyGame::Gravity>(entity, MyGame::Gravity{true, 2});
        registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
        registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{100.0f, 100.0f});
        registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"./resources/R-Touhou/graphics/Fish.png", sf::Sprite(), sf::Texture()});
        // Main Loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();
            // Initializing sprite textures
            GameEngine::System::sprite(registry);
            // Our gravity system
            systemGravity(registry);
            // Drawing entities on screen
            GameEngine::System::draw(registry, window);
            // Displaying SFML window, then clearing it
            window.display();
            window.clear();
        }
        return 0;
    }