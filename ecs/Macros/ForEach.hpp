/*
** EPITECH PROJECT, 2023
** R-Touhou_Bootstrap
** File description:
** ForEach.hpp
*/

#ifndef GAME_ENGINE_MACROS_FOREACH_HPP
#define GAME_ENGINE_MACROS_FOREACH_HPP

#define GAME_ENGINE_FE_0(WHAT)
#define GAME_ENGINE_FE_1(WHAT, X) WHAT(X)
#define GAME_ENGINE_FE_2(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_1(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_3(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_2(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_4(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_3(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_5(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_4(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_6(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_5(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_7(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_6(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_8(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_7(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_9(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_8(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_10(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_9(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_11(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_10(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_12(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_11(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_13(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_12(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_14(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_13(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_15(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_14(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_16(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_15(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_17(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_16(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_18(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_17(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_19(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_18(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_20(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_19(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_21(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_20(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_22(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_21(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_23(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_22(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_24(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_23(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_25(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_24(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_26(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_25(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_27(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_26(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_28(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_27(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_29(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_28(WHAT, __VA_ARGS__)
#define GAME_ENGINE_FE_30(WHAT, X, ...) WHAT(X)GAME_ENGINE_FE_29(WHAT, __VA_ARGS__)

#define GAME_ENGINE_GET_MACRO(_0, \
    _1,_2,_3,_4,_5,_6,_7,_8,_9,_10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
    NAME,...) NAME

#define GAME_ENGINE_FOR_EACH(ACTION,...) GAME_ENGINE_GET_MACRO(_0,__VA_ARGS__ \
    ,GAME_ENGINE_FE_30,GAME_ENGINE_FE_29,GAME_ENGINE_FE_28,GAME_ENGINE_FE_27,GAME_ENGINE_FE_26 \
    ,GAME_ENGINE_FE_25,GAME_ENGINE_FE_24,GAME_ENGINE_FE_23,GAME_ENGINE_FE_22,GAME_ENGINE_FE_21 \
    ,GAME_ENGINE_FE_20,GAME_ENGINE_FE_19,GAME_ENGINE_FE_18,GAME_ENGINE_FE_17,GAME_ENGINE_FE_16 \
    ,GAME_ENGINE_FE_15,GAME_ENGINE_FE_14,GAME_ENGINE_FE_13,GAME_ENGINE_FE_12,GAME_ENGINE_FE_11 \
    ,GAME_ENGINE_FE_10,GAME_ENGINE_FE_9,GAME_ENGINE_FE_8,GAME_ENGINE_FE_7,GAME_ENGINE_FE_6 \
    ,GAME_ENGINE_FE_5,GAME_ENGINE_FE_4,GAME_ENGINE_FE_3,GAME_ENGINE_FE_2,GAME_ENGINE_FE_1 \
    )(ACTION,__VA_ARGS__)

#endif