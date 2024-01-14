# LTYPE - ECS - MACROS

[Go back to ECS](../ECS.md)

# Table of Contents
- [LTYPE - ECS - MACROS](#ltype---ecs---macros)
- [Table of Contents](#table-of-contents)
- [Macros](#macros)
  - [GAME\_ENGINE\_FOR\_EACH](#game_engine_for_each)
    - [Code](#code)
    - [Example](#example)
    - [Warning](#warning)

# Macros

## GAME_ENGINE_FOR_EACH

*From Macros/ForEach.hpp*

Applies another macro ACTION to multiple arguments. (up to **30** arguments)

### Code

```cpp
#define GAME_ENGINE_FOR_EACH(ACTION,...) GAME_ENGINE_GET_MACRO(_0,__VA_ARGS__ \
    ,GAME_ENGINE_FE_30,GAME_ENGINE_FE_29,GAME_ENGINE_FE_28,GAME_ENGINE_FE_27,GAME_ENGINE_FE_26 \
    ,GAME_ENGINE_FE_25,GAME_ENGINE_FE_24,GAME_ENGINE_FE_23,GAME_ENGINE_FE_22,GAME_ENGINE_FE_21 \
    ,GAME_ENGINE_FE_20,GAME_ENGINE_FE_19,GAME_ENGINE_FE_18,GAME_ENGINE_FE_17,GAME_ENGINE_FE_16 \
    ,GAME_ENGINE_FE_15,GAME_ENGINE_FE_14,GAME_ENGINE_FE_13,GAME_ENGINE_FE_12,GAME_ENGINE_FE_11 \
    ,GAME_ENGINE_FE_10,GAME_ENGINE_FE_9,GAME_ENGINE_FE_8,GAME_ENGINE_FE_7,GAME_ENGINE_FE_6 \
    ,GAME_ENGINE_FE_5,GAME_ENGINE_FE_4,GAME_ENGINE_FE_3,GAME_ENGINE_FE_2,GAME_ENGINE_FE_1 \
    )(ACTION,__VA_ARGS__)
```

### Example

For example, the following code:

```cpp
registry.registerComponent<GameEngine::Color>();
registry.registerComponent<GameEngine::Drawable>();
registry.registerComponent<GameEngine::Position>();
registry.registerComponent<GameEngine::Sprite>();
```

Can be rewritten the following way:

```cpp
#define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();
GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT, GameEngine::Color, GameEngine::Drawable, GameEngine::Position, GameEngine::Sprite)
```

We still have to define our ACTION macro (here, `REGISTER_COMPONENT`).

### Warning

May **not** work on **Windows** devices!