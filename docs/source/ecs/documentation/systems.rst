.. _ecs-documentation-systems:

ECS - Systems Documenation
====================

Know everything you have to know about monitoring your project's content.

Table of Contents
-----------------

- `GameEngine::System.attackSystem`_
- `GameEngine::System.collisionSystem`_
- `GameEngine::System.controlSystem`_
- `GameEngine::System.deleteEntitiesSystem`_
- `GameEngine::System.drawSystem`_
- `GameEngine::System.initEnemy`_
- `GameEngine::System.movementSystem`_
- `GameEngine::System.spriteSystem`_

GameEngine::System.attackSystem
-----------------

Creates projectiles from controllable entities.

Arguments:

.. code:: cpp

    GameEngine::Registry &r
    std::vector<GameEngine::Entity> &entityVector

Requires GameEngine::Controllable, GameEngine::Position and GameEngine::Size.

GameEngine::System.collisionSystem
-----------------

Manages collision between controllable entities and non-controllable entities.

If these two types of entities collides, it also manages the loss of health.

Arguments:

.. code:: cpp

    GameEngine::Registry &r
    int &score

Requires GameEngine::Controllable, GameEngine::Hitbox, GameEngine::Life, GameEngine::Position, GameEngine::Projectile and GameEngine::Size.

GameEngine::System.controlSystem
-----------------

Moves controllable entities from the keyboard input.

Arguments:

.. code:: cpp

    GameEngine::Registry &r

Requires GameEngine::Controllable, GameEngine::Position, GameEngine::Size and GameEngine::Velocity.

GameEngine::System.deleteEntitiesSystem
-----------------

Deletes every entity that has a GameEngine::Position component.

Arguments:

.. code:: cpp

    GameEngine::Registry &r

Requires GameEngine::Position.

GameEngine::System.drawSystem
-----------------

Draws every drawable entity on a window.

Arguments:

.. code:: cpp

    GameEngine::Registry &r
    sf::RenderWindow &window

Requires GameEngine::Color, GameEngine::Controllable, GameEngine::Drawable, GameEngine::Outline, GameEngine::Position, GameEngine::Sprite, GameEngine::SpriteTextureAnimation, GameEngine::SpriteTextureRect, GameEngine::Text and GameEngine.ZIndex.

GameEngine::System.initEnemy
-----------------

Creates a new entity enemy. It will spawn at a random y (vertical) position.

Arguments:

.. code:: cpp

    GameEngine::Registry &r

Requires GameEngine::Controllable, GameEngine::Hitbox, GameEngine::Path, GameEngine::Position and GameEngine::Projectile.

GameEngine::System.movementSystem
-----------------

Moves every entity based on their velocity.

Arguments:

.. code:: cpp

    GameEngine::Registry &r

Requires GameEngine::Controllable, GameEngine::Path, GameEngine::Position, GameEngine::Projectile, GameEngine::Size and GameEngine::Velocity.

GameEngine::System.spriteSystem
-----------------

Generate the textures required for the sprites to be displayed.

Arguments:

.. code:: cpp

    GameEngine::Registry &r

Requires GameEngine::Size and GameEngine::Sprite.
