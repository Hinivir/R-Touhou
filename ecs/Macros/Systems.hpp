/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Macros/Systems.hpp
*/

#ifndef GAME_ENGINE_MACROS_SYSTEMS_HPP
#define GAME_ENGINE_MACROS_SYSTEMS_HPP

#include "Registry.hpp"

#define DO_COMPONENT_CONTAINS_AT(COMPONENT, ID) (ID < COMPONENT.size() && COMPONENT[ID].has_value())

#define EXTRACT_COMPONENT(COMPONENT, VARIABLE) auto &VARIABLE = r.getComponent<COMPONENT>()
#define EXTRACT_COMPONENT_CONST(COMPONENT, VARIABLE) auto const &VARIABLE = r.getComponent<COMPONENT>()

#define EXTRACT_COMPONENT_FROM(COMPONENT, VARIABLE, REGISTRY) auto &VARIABLE = REGISTRY.getComponent<COMPONENT>()
#define EXTRACT_COMPONENT_FROM_CONST(COMPONENT, VARIABLE, REGISTRY)                                                    \
    auto const &VARIABLE = REGISTRY.getComponent<COMPONENT>()

#define FROM_COMPONENT_TO_VARIABLE(COMPONENT, ID, VARIABLE, VARIABLE_HAS)                                              \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID);                                                 \
    auto &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];
#define FROM_COMPONENT_TO_VARIABLE_CONST(COMPONENT, ID, VARIABLE, VARIABLE_HAS)                                        \
    bool const VARIABLE_HAS = DO_COMPONENT_CONTAINS_AT(COMPONENT, ID);                                                 \
    auto const &VARIABLE = COMPONENT[VARIABLE_HAS ? ID : 0];

#endif