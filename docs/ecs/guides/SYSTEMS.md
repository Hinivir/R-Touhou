# LTYPE - ECS - GUIDE - SYSTEMS

[Go back to ECS](../../ECS.md)

# Table of Contents
- [LTYPE - ECS - GUIDE - SYSTEMS](#ltype---ecs---guide---systems)
- [Table of Contents](#table-of-contents)
- [Declaring a system](#declaring-a-system)
    - [Note](#note)
- [Extracting data from the registry](#extracting-data-from-the-registry)
    - [Note](#note-1)
- [Looping through our entities](#looping-through-our-entities)
    - [Note](#note-2)
- [Result](#result)
- [Calling the system](#calling-the-system)
- [Expendaing with MyGame::Gravity](#expendaing-with-mygamegravity)
  - [Extract](#extract)
  - [Loop](#loop)
  - [Result](#result-1)

# Declaring a system

First, a system from the ECS takes the form of a function.

To create a new system, declare a function having a Registry class as arguments:

```cpp
void systemGravity(GameEngine::Registry &r)
{ }
```

### Note

We can also declare `r` as const if we don't plan on changing anything about the registry.

If we need to access things like the current window, we can also include it in the arguments, giving us `void systemGravity(GameEngine::Registry &r, sf::RenderWindow &window)` instead.

# Extracting data from the registry

From now on, we can extract any data that we want. Here, we want to create a simple gravity system, so we'll need the positions of our entities.

For that, we'll use the `EXTRACT_COMPONENT_FROM` macro, creating us a list of values from a registry.

```cpp
    EXTRACT_COMPONENT_FROM(GameEngine::Position, positions, r)
```

Since we are calling our registry `r`, we can also simplify it with the `EXTRACT_COMPONENT` macro:

```cpp
    EXTRACT_COMPONENT(GameEngine::Position, positions)
```

### Note

If the data we're declaring doesn't have to be modified, we can use the `EXTRACT_COMPONENT_CONST` and `EXTRACT_COMPONENT_FROM_CONST` macros instead.

# Looping through our entities

We'll first make a loop iterating through our positions, giving us `for (std::size_t i = 0; i < positions.size(); ++i)`.

Then, we'll need to extract from `positions` the current position of the entity at `i`: `FROM_COMPONENT_TO_VARIABLE(positions, i, position, hasPosition);`

Here, we are declaring 2 variables :
- `position` being a `std::optional` containing (if possible) our GameEngine::Position.
- `hasPosition` being a `bool` containing if we have or not a position at `i` in positions.

### Note

We can also use `FROM_COMPONENT_TO_VARIABLE_CONST` for a const alternative of `FROM_COMPONENT_TO_VARIABLE`.

If we just want to extract `hasPosition`, we can also use `bool const hasPosition = DO_COMPONENT_CONTAINS_AT(positions, i)`.


# Result

Putting everything together, we have:

```cpp
void systemGravity(GameEngine::Registry &r) {
    EXTRACT_COMPONENT(GameEngine::Position, positions);
    for (std::size_t i = 0; i < positions.size(); ++i) {
        FROM_COMPONENT_TO_VARIABLE(positions, i, position, hasPosition);
        if (hasPosition)
            position.value().y -= 2;
    }
}
```

# Calling the system

Hop back in your main and add `systemGravity(registry);` before calling `system.drawSystem(registry, window);`.

# Expendaing with MyGame::Gravity

In [**Guide - Components**](COMPONENTS.md), we made a new component called `MyGame::Gravity`, let's use it.

## Extract

We'll extract our component as we did for `GameEngine::Position`, but this time as a const: `EXTRACT_COMPONENT_CONST(MyGame::Gravity, gravities)`

## Loop

Extracting the entity data from our component list should be (almost) the same: `FROM_COMPONENT_TO_VARIABLE_CONST(gravities, i, gravity, hasGravity)`

## Result

Putting everything together, we have:

```cpp
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
```
