# LTYPE - ECS - COMPONENTS

[Go back to ECS](../ECS.md)

# Table of Contents
- [LTYPE - ECS - COMPONENTS](#ltype---ecs---components)
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
    - [Members](#members-4)
    - [Associated Content](#associated-content-1)
  - [Projectile](#projectile)
  - [Size](#size)
  - [Sprite](#sprite)
  - [SpriteTextureAnimation](#spritetextureanimation)
    - [Members](#members-5)
    - [Associated Content](#associated-content-2)
  - [SpriteTextureRect](#spritetexturerect)
    - [Members](#members-6)
    - [Associated Content](#associated-content-3)
  - [Text](#text)
  - [Velocity](#velocity)
    - [Members](#members-7)
    - [Associated Content](#associated-content-4)
  - [Window](#window)
  - [ZIndex](#zindex)
    - [Members](#members-8)
    - [Associated Content](#associated-content-5)

# Components

## Color

*From ecs/Components/Color.hpp*

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

*From ecs/Components/Drawable.hpp*

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

*From ecs/Components/Position.hpp*

Defines the position of an entity.

It uses `GameEngine::Position2Base` from `ecs/Components/Position2Base.hpp`.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|x|PositionValue|Position on the x (horizontal) axis|0 (GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE)|
|y|PositionValue|Position on the y (vertical) axis|0 (GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE)|

### Associated Content

```cpp
using GameEngine::PositionValue = float;
```
```cpp
#define GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE 0
```
```cpp
template <typename T, char UNIQUE_ID>
struct GameEngine::Position2Base;
```

## Projectile

## Size

## Sprite

## SpriteTextureAnimation

*From ecs/Components/SpriteTextureAnimation.hpp*

Defines the slicing of a entity's sprite's texture for animating.

When combined with `GameEngine::SpriteTextureRect`, the slicing is applied **AFTER** the texture rect.

It uses `GameEngine::Position2Base` and `GameEngine::Position2BaseDefault1` from `ecs/Components/Position2Base.hpp`.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|slicing|SpriteTextureAnimationSlicing|Defines how the texture is sliced|{1,1}|
|frame|SpriteTextureAnimationFrame|Defines which frame should be used|{0,0}|

### Associated Content

```cpp
using GameEngine::SpriteTextureAnimationSlicingValue = int;
using GameEngine::SpriteTextureAnimationSlicing = GameEngine::Position2BaseDefault1<GameEngine::SpriteTextureAnimationSlicingValue, 's'>;
using GameEngine::SpriteTextureAnimationFrameValue = int;
using GameEngine::SpriteTextureAnimationFrame = GameEngine::Position2Base<GameEngine::SpriteTextureAnimationFrameValue, 'f'>;
```
```cpp
#define GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE 0
#define GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE_1 1
```
```cpp
template <typename T, char UNIQUE_ID>
struct GameEngine::Position2Base;
template <typename T, char UNIQUE_ID>
struct GameEngine::Position2BaseDefault1;
```

## SpriteTextureRect

*From ecs/Components/SpriteTextureRect.hpp*

Defines the area displayed from the entity's sprite's texture.

When combined with `GameEngine::SpriteTextureAnimation`, the cropping is applied **BEFORE** the texture animation.

It uses `GameEngine::RectBase` from `ecs/Components/SpriteTextureRect.hpp`.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|left|SpriteTextureRectValue|Left coordinate of the texture rectangle|0 (GAME_ENGINE_RECT_BASE_DEFAULT_VALUE)|
|top|SpriteTextureRectValue|Top coordinate of the texture rectangle|0 (GAME_ENGINE_RECT_BASE_DEFAULT_VALUE)|
|width|SpriteTextureRectValue|Width of the texture rectangle|0 (GAME_ENGINE_RECT_BASE_DEFAULT_VALUE)|
|height|SpriteTextureRectValue|Height of the texture rectangle is sliced|0 (GAME_ENGINE_RECT_BASE_DEFAULT_VALUE)|

### Associated Content

```cpp
using GameEngine::SpriteTextureRectValue = int;
```
```cpp
#define GAME_ENGINE_RECT_BASE_DEFAULT_VALUE 0
```
```cpp
template <typename T, char UNIQUE_ID>
struct GameEngine::RectBase;
```

## Text

## Velocity

*From ecs/Components/Velocity.hpp*

Defines the velocity of an entity, describing the movement of it.

It uses `GameEngine::Position2Base` from `ecs/Components/Position2Base.hpp`.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|x|VelocityValue|Velocity on the x (horizontal) axis|0 (GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE)|
|y|VelocityValue|Velocity on the y (vertical) axis|0 (GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE)|

### Associated Content

```cpp
using GameEngine::VelocityValue = float;
```
```cpp
#define GAME_ENGINE_POSITION_2_BASE_DEFAULT_VALUE 0
```
```cpp
template <typename T, char UNIQUE_ID>
struct GameEngine::Position2Base;
```

## Window

## ZIndex

*From ecs/Components/ZIndex.hpp*

Defines the layer at which the entity is displayed.

For example, a background should have a lower layer than the objects standing before it.

### Members

|Name|Type|Description|Default Value|
|----|----|-----------|-------------|
|zIndex|ZIndexValue|Layer at which the entity should be displayed|1000 (GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE)|

### Associated Content

```cpp
#define GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE 0
#define GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE 1000
```
```cpp
using GameEngine::ZIndexValue = unsigned int;
```
