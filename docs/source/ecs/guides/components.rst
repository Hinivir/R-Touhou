.. _ecs-guides-components:

ECS - Components Guide
====================

Learn how to make components with the creation of a MyGame::Gravity component

Table of Contents
-----------------

1. `Creating the header file`_
2. `Register Component`_
3. `Add the component to an entity`_
4. `Adding the system`_

Creating the header file
-----------------

A component is a property that can be attached to any entity.

It is always **unique** meaning that you can't use the same component for multiple properties.

To make a new component, we'll have to make a new file.

In a `include/GravityComponent.hpp`:

.. code:: cpp

    namespace MyGame
    {
        struct Gravity
        {
            bool isAffectedByGravity = false;
            float weigth = 0;
        };
    }

We always have to use a struct for defining a component. Once it is declared, we can put anything we need inside.

Here, we chose to represent if our entity is affected by gravity with a bool and if gravitional force with a float.

Register Component
-----------------

Hop in your main and add the following line of code before declaring all your entities:

.. code:: cpp

    registry.registerComponent<MyGame::Gravity>();

Of course, you can replace `register` with however you named your `GameEngine::Registry`.

Now our component is ready to be used!

Add the component to an entity
-----------------

We'll make a new entity, calling it... `entity`.

After that, we just need to register the components that we need for it.

.. code:: cpp

    GameEngine::Entity entity = registry.spawnEntity();
    registry.addComponent<MyGame::Gravity>(entity, MyGame::Gravity{true, 2});

Since we want more that just gravity, we'll add other components.

.. code:: cpp

    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{100.0f, 100.0f});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"./resources/R-Touhou/graphics/Fish.png", sf::Sprite(), sf::Texture()});

Of course, `GameEngine::Drawable`, `GameEngine::Position` and `GameEngine::Sprite` will need to be registered with `registry.registerComponent`.

You can change the sprite by replacing `./resources/R-Touhou/graphics/Fish.png`.

Adding the system
-----------------

Since we want `MyGame::Gravity` to do something, we'll need to add a gravity system: :ref:`ecs-guides-systems`.