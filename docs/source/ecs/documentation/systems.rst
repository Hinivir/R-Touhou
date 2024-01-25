.. _ecs-documentation-systems:

ECS - Systems Documenation
====================

Know everything you have to know about monitoring your project's content.

Table of Contents
-----------------

- `GameEngine::System::draw`_
- `GameEngine::System::sprite`_
- `GameEngine::SystemGroup.attackSystem`_
- `GameEngine::SystemGroup.collisionSystem`_
- `GameEngine::SystemGroup.controlSystem`_
- `GameEngine::SystemGroup.deleteEntitiesSystem`_
- `GameEngine::SystemGroup.initEnemy`_
- `GameEngine::SystemGroup.movementSystem`_

GameEngine::System::draw
-----------------

Draws every drawable entity on a window.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME
    sf::RenderWindow &window

Requires GameEngine::Color, GameEngine::Controllable, GameEngine::Drawable, GameEngine::Outline, GameEngine::Position, GameEngine::Sprite, GameEngine::SpriteTextureAnimation, GameEngine::SpriteTextureRect, GameEngine::Text and GameEngine::ZIndex.

GameEngine::System::sprite
-----------------

Generate the textures required for the sprites to be displayed.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME

Requires GameEngine::Size and GameEngine::Sprite.

GameEngine::SystemGroup.attackSystem
-----------------

Creates projectiles from controllable entities.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME
    std::vector<GameEngine::Entity> &entityVector

Requires GameEngine::Controllable, GameEngine::Position and GameEngine::Size.

GameEngine::SystemGroup.collisionSystem
-----------------

Manages collision between controllable entities and non-controllable entities.

If these two types of entities collides, it also manages the loss of health.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME
    int &score

Requires GameEngine::Controllable, GameEngine::Hitbox, GameEngine::Life, GameEngine::Position, GameEngine::Projectile and GameEngine::Size.

GameEngine::SystemGroup.controlSystem
-----------------

Moves controllable entities from the keyboard input.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME

Requires GameEngine::Controllable, GameEngine::Position, GameEngine::Size and GameEngine::Velocity.

GameEngine::SystemGroup.deleteEntitiesSystem
-----------------

Deletes every entity that has a GameEngine::Position component.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME

Requires GameEngine::Position.

GameEngine::SystemGroup.initEnemy
-----------------

Creates a new entity enemy. It will spawn at a random y (vertical) position.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME

Requires GameEngine::Controllable, GameEngine::Hitbox, GameEngine::Path, GameEngine::Position and GameEngine::Projectile.

GameEngine::SystemGroup.movementSystem
-----------------

Moves every entity based on their velocity.

Arguments:

.. code:: cpp

    GameEngine::Registry &REGISTRY_DEFAULT_NAME

Requires GameEngine::Controllable, GameEngine::Path, GameEngine::Position, GameEngine::Projectile, GameEngine::Size and GameEngine::Velocity.
