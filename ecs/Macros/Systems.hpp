/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Macros/Systems.hpp
*/

#ifndef GAME_ENGINE_MACROS_SYSTEMS_HPP
#define GAME_ENGINE_MACROS_SYSTEMS_HPP

#include "Registry.hpp"

#define REGISTRY_DEFAULT_NAME r

#define CLEAR_EVENT(EVENT) r.clearEvent<EVENT>()

#define CLEAR_EVENT_FROM(EVENT, REGISTRY) registry.clearEvent<EVENT>()

#define DO_COMPONENT_CONTAINS_AT(COMPONENT, ID) (ID < COMPONENT.size() && COMPONENT[ID].has_value())

#define EXTRACT_COMPONENT(COMPONENT, VARIABLE) auto &VARIABLE = REGISTRY_DEFAULT_NAME.getComponent<COMPONENT>()
#define EXTRACT_COMPONENT_CONST(COMPONENT, VARIABLE)                                                                   \
    auto const &VARIABLE = REGISTRY_DEFAULT_NAME.getComponent<COMPONENT>()

#define EXTRACT_COMPONENT_FROM(COMPONENT, VARIABLE, REGISTRY) auto &VARIABLE = REGISTRY.getComponent<COMPONENT>()
#define EXTRACT_COMPONENT_FROM_CONST(COMPONENT, VARIABLE, REGISTRY)                                                    \
    auto const &VARIABLE = REGISTRY.getComponent<COMPONENT>()

#define EXTRACT_EVENT(EVENT, VARIABLE) auto &VARIABLE = REGISTRY_DEFAULT_NAME.getComponent<EVENT>()
#define EXTRACT_EVENT_CONST(EVENT, VARIABLE)                                                                   \
    auto const &VARIABLE = REGISTRY_DEFAULT_NAME.getComponent<EVENT>()

#define EXTRACT_EVENT_FROM(EVENT, VARIABLE, REGISTRY) auto &VARIABLE = REGISTRY.getComponent<EVENT>()
#define EXTRACT_EVENT_FROM_CONST(EVENT, VARIABLE, REGISTRY)                                                    \
    auto const &VARIABLE = REGISTRY.getComponent<EVENT>()

#define FROM_COMPONENT_TO_VARIABLE(COMPONENT, ID, VARIABLE, VARIABLE_HAS)                                              \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID);                                                 \
    auto &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];
#define FROM_COMPONENT_TO_VARIABLE_CONST(COMPONENT, ID, VARIABLE, VARIABLE_HAS)                                        \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID);                                                 \
    auto const &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];

#endif