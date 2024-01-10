# LTYPE - COMPONENTS

# Table of Contents
- [LTYPE - COMPONENTS](#ltype---components)
- [Table of Contents](#table-of-contents)
- [Components](#components)
  - [Color](#color)
    - [Members](#members)
    - [Associated Content](#associated-content)
  - [Controllable](#controllable)
    - [Members](#members-1)
  - [Drawable](#drawable)
    - [Members](#members-2)
  - [Hitbox](#hitbox)
    - [Members](#members-3)
  - [Life](#life)
  - [Path](#path)
  - [Position](#position)
  - [Projectile](#projectile)
  - [Size](#size)
  - [Sprite](#sprite)
  - [SpriteTextureAnimation](#spritetextureanimation)
  - [SpriteTextureRect](#spritetexturerect)
  - [Text](#text)
  - [Velocity](#velocity)
  - [Window](#window)
  - [ZIndex](#zindex)

# Components

## Color

*From Components/Color.hpp*

Defines a entity's color by it's RGBA value.

This component can be used to change the color (**r**, **g**, **b**) or the opacity (**a**) of an entity's sprite.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|r|ColorValue|Red channel|255 (GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE)|
|g|ColorValue|Green channel|255 (GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE)|
|b|ColorValue|Blue channel|255 (GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE)|
|a|ColorValue|Alpha channel|255 (GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE)|

### Associated Content

Associated Content:
```cpp
#define GAME_ENGINE_COLOR_VALUE_MIN_VALUE 0
#define GAME_ENGINE_COLOR_VALUE_DEFAULT_VALUE 255
#define GAME_ENGINE_COLOR_VALUE_MAX_VALUE 255
```
```cpp
using GameEngine::ColorValue = unsigned char;
```

## Controllable

*From ecs/Components/Controllable.hpp*

Defines if an entity can be controlled by the player

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|isControllable|bool|If the entity can be controlled by the player|false|

## Drawable

*From Cecs/omponents/Drawable.hpp*

Defines an entity's visibility.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|isVisible|bool|If the sprite has to be drawn on screen|false|

## Hitbox

*From ecs/Components/Hitbox.hpp*

Defines an entity's hitbox for collisions.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|

## Life

## Path

## Position

## Projectile

## Size

## Sprite

## SpriteTextureAnimation

## SpriteTextureRect

## Text

## Velocity

## Window

## ZIndex