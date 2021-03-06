#pragma once

#include "string.h"

/**
    Interface for an object that can be serialized to a string.
    
    Objects are serialized to C++.
*/
template <typename>
struct Serialize;

template <typename x>
using serialize = typename Serialize<x>::type;

/**
    Serialize templated class `name` with `elements` template paramters.
*/
template <typename name, typename... elements>
using serialize_class =
    string_join<String<>,
        name,
        String<'<'>,
        string_join<String<','>, serialize<elements>...>,
        String<'>'>>;

/**
    Serialize enum class `name` of type `t` and value `x`.
*/
template <typename name, typename t, t x>
using serialize_enum =
    string_join<String<>,
        decltype("static_cast<"_string),
        name,
        String<'>', '('>,
        int_to_string<static_cast<std::underlying_type_t<t>>(x)>,
        String<')'>>;

/*------------------------------------------------------------------------------
    Basic Type Serialization
*/
template <> struct Serialize<bool> { using type = decltype("bool"_string); };
template <> struct Serialize<int> { using type = decltype("int"_string); };
template <> struct Serialize<unsigned> { using type = decltype("unsigned"_string); };
template <> struct Serialize<size_t> { using type = decltype("size_t"_string); };

/*------------------------------------------------------------------------------
    Value Type Serialization
*/
/**
    Wrapper around a type that can be serialized.
*/
template <typename T, T x>
struct SerializableValue { };

template <typename T, T x>
struct Serialize<SerializableValue<T, x>> {
    using type = int_to_string<x>;
};

template <> struct Serialize<SerializableValue<bool, false>> { using type = decltype("false"_string); };
template <> struct Serialize<SerializableValue<bool, true>> { using type = decltype("true"_string); };
