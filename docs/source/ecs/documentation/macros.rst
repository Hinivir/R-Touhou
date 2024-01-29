.. _ecs-documentation-macros:

ECS - Macros Documenation
====================

Miscellaneous macros used for simplifying your code.

Table of Contents
-----------------

- `DO_COMPONENT_CONTAINS_AT`_
- `EXTRACT_COMPONENT(_CONST)`_
- `EXTRACT_COMPONENT_FROM(_CONST)`_
- `FROM_COMPONENT_TO_VARIABLE(_CONST)`_
- `GAME_ENGINE_FOR_EACH ⚠️`_
- `REGISTRY_DEFAULT_NAME`_

DO_COMPONENT_CONTAINS_AT
-----------------

*From Macros/Systems.hpp*

Condition checking if a COMPONENT variable contains a value at a certain ID.
The COMPONENT variable can be first extracted with `EXTRACT_COMPONENT(_CONST)`_ or `EXTRACT_COMPONENT_FROM(_CONST)`_.

Code
~~~~~~~~~~~~~~~~~

.. code:: cpp

    #define DO_COMPONENT_CONTAINS_AT(COMPONENT, ID) (ID < COMPONENT.size() && COMPONENT[ID].has_value())

EXTRACT_COMPONENT(_CONST)
-----------------

*From Macros/Systems.hpp*

Extracts the content of a REGISTRY_DEFAULT_NAME's COMPONENT component to a new VARIABLE variable as a list.
Both use the `REGISTRY_DEFAULT_NAME`_ macro. To use another registry name, use `EXTRACT_COMPONENT_FROM(_CONST)`_.

Code
~~~~~~~~~~~~~~~~~

.. code:: cpp

    #define EXTRACT_COMPONENT(COMPONENT, VARIABLE) \
        auto &VARIABLE = REGISTRY_DEFAULT_NAME.getComponent<COMPONENT>()
    #define EXTRACT_COMPONENT_CONST(COMPONENT, VARIABLE) \
        auto const &VARIABLE = REGISTRY_DEFAULT_NAME.getComponent<COMPONENT>()

EXTRACT_COMPONENT_FROM(_CONST)
-----------------

*From Macros/Systems.hpp*

Extracts the content of a REGISTRY's COMPONENT component to a new VARIABLE variable as a list.

Code
~~~~~~~~~~~~~~~~~

.. code:: cpp

    #define EXTRACT_COMPONENT_FROM(COMPONENT, VARIABLE, REGISTRY) \
        auto &VARIABLE = REGISTRY.getComponent<COMPONENT>()
    #define EXTRACT_COMPONENT_FROM_CONST(COMPONENT, VARIABLE, REGISTRY) \
        auto const &VARIABLE = REGISTRY.getComponent<COMPONENT>()

FROM_COMPONENT_TO_VARIABLE(_CONST)
-----------------

*From Macros/Systems.hpp*

Extracts the value contained in the COMPONENT variable at a position ID, as a VARIABLE variable.
Also creates a VARIABLE_HAS const variable containing weither or not COMPONENT contains a value at the position ID.
The COMPONENT variable can be first extracted with `EXTRACT_COMPONENT(_CONST)`_ or `EXTRACT_COMPONENT_FROM(_CONST)`_.

Code
~~~~~~~~~~~~~~~~~

.. code:: cpp

    #define FROM_COMPONENT_TO_VARIABLE(COMPONENT, ID, VARIABLE, VARIABLE_HAS)           \
        bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID);              \
        auto &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];
    #define FROM_COMPONENT_TO_VARIABLE_CONST(COMPONENT, ID, VARIABLE, VARIABLE_HAS)     \
        bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID);              \
        auto const &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];

GAME_ENGINE_FOR_EACH ⚠️
-----------------

*From Macros/ForEach.hpp*

Applies another macro ACTION to multiple arguments. (up to **30** arguments)

Code
~~~~~~~~~~~~~~~~~

.. code:: cpp

    #define GAME_ENGINE_FOR_EACH(ACTION,...) GAME_ENGINE_GET_MACRO(_0,__VA_ARGS__ \
        ,GAME_ENGINE_FE_30,GAME_ENGINE_FE_29,GAME_ENGINE_FE_28,GAME_ENGINE_FE_27,GAME_ENGINE_FE_26 \
        ,GAME_ENGINE_FE_25,GAME_ENGINE_FE_24,GAME_ENGINE_FE_23,GAME_ENGINE_FE_22,GAME_ENGINE_FE_21 \
        ,GAME_ENGINE_FE_20,GAME_ENGINE_FE_19,GAME_ENGINE_FE_18,GAME_ENGINE_FE_17,GAME_ENGINE_FE_16 \
        ,GAME_ENGINE_FE_15,GAME_ENGINE_FE_14,GAME_ENGINE_FE_13,GAME_ENGINE_FE_12,GAME_ENGINE_FE_11 \
        ,GAME_ENGINE_FE_10,GAME_ENGINE_FE_9,GAME_ENGINE_FE_8,GAME_ENGINE_FE_7,GAME_ENGINE_FE_6 \
        ,GAME_ENGINE_FE_5,GAME_ENGINE_FE_4,GAME_ENGINE_FE_3,GAME_ENGINE_FE_2,GAME_ENGINE_FE_1 \
        )(ACTION,__VA_ARGS__)

Example
~~~~~~~~~~~~~~~~~

For example, the following code:

.. code:: cpp

    registry.registerComponent<GameEngine::Color>();
    registry.registerComponent<GameEngine::Drawable>();
    registry.registerComponent<GameEngine::Position>();
    registry.registerComponent<GameEngine::Sprite>();

Can be rewritten the following way:

.. code:: cpp

    #define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();
    GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT, GameEngine::Color, GameEngine::Drawable, GameEngine::Position, GameEngine::Sprite)

We still have to define our ACTION macro (here, `REGISTER_COMPONENT`).

Warning
~~~~~~~~~~~~~~~~~

May **not** work on **Windows** devices!

REGISTRY_DEFAULT_NAME
-----------------

*From Macros/Systems.hpp*

Default name for a GameEngine::Registry. Allows the use of the `EXTRACT_COMPONENT(_CONST)`_ macros.

Code
~~~~~~~~~~~~~~~~~

.. code:: cpp

    #define REGISTRY_DEFAULT_NAME r