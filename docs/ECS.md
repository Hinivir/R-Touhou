# LTYPE - ECS

/

# Table of Contents
- [LTYPE - ECS](#ltype---ecs)
- [Table of Contents](#table-of-contents)
- [Guides](#guides)
- [Documentation](#documentation)
- [Questions](#questions)
  - [How do I import LType's ECS?](#how-do-i-import-ltypes-ecs)
  - [Do I need to register my components before using them?](#do-i-need-to-register-my-components-before-using-them)
  - [What is the **sf** namespace](#what-is-the-sf-namespace)
  - [Can I register multiple components in one line?](#can-i-register-multiple-components-in-one-line)
  - [Do you like ice cream?](#do-you-like-ice-cream)

# Guides

# Documentation

[🔨 **Systems**](ecs/SYSTEMS.md) - Know everything you have to know about monitoring your project's content

[🔧 **Components**](ecs/COMPONENTS.md) - Learn more about the components used for definining your entities.

[🧰 **Macros**](ecs/MACROS.md) - Miscellaneous macros used for simplifying your code.

# Questions

## How do I import LType's ECS?

All the code that you'll need is inside headers. (.hpp files)

You just have to import the headers that you need in your files.

For example, if you have the following code:

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>
int main(void)
{
    int nbRegistry = 1024;
    bool isGameOver = false;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ECS");
    GameEngine::Registry registry(nbRegistry);
    GameEngine::System system;
    registry.registerComponent<GameEngine::Drawable>();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        system.drawSystem(registry, window);
        window.display();
        window.clear();
    }
    return 0;
}
```

You'll just need to import the following headers at the start of your code:

```cpp
#include "Registry.hpp"
#include "Systems.hpp"
#include "Components/Window.hpp"
```

## Do I need to register my components before using them?

Yes, you'll need to register your components before using them. Otherwise, the ECS can't store your data.

## What is the **sf** namespace

The **sf** namespace is used by the multimedia library called [SFML](https://www.sfml-dev.org).

This ECS uses SFML for everything related to graphics.

Code from SFML does **NOT** come from this ECS.

## Can I register multiple components in one line?

Technically no, but sort of. The only way to register multiple components in one line should be something like:

```cpp
registry.registerComponent<GameEngine::Color>(); registry.registerComponent<GameEngine::Drawable>(); registry.registerComponent<GameEngine::Sprite>();
```

But it's not really pretty and readable, isn't it?

If you really want to define multiple components like this, you can still use the `GAME_ENGINE_FOR_EACH` macro in the following way:

```cpp
#include "Macros/ForEach.hpp"
#define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();
GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT, GameEngine::Color, GameEngine::Drawable, GameEngine::Sprite)
```

## Do you like ice cream?

Yes I do.