#pragma once

#include <type_traits>

template <int Length_Exponent,
          int Time_Exponent,
          int Mass_Exponent,
          int Current_Exponent,
          int Temperature_Exponent,
          int Amount_Exponent,
          int Intensity_Exponent,
          int Angle_Exponent>
struct Dimensions {};

using Dim_None        = Dimensions<0,0,0,0,0,0,0,0>;
using Dim_Length      = Dimensions<1,0,0,0,0,0,0,0>;
using Dim_Time        = Dimensions<0,1,0,0,0,0,0,0>;
using Dim_Mass        = Dimensions<0,0,1,0,0,0,0,0>;
using Dim_Current     = Dimensions<0,0,0,1,0,0,0,0>;
using Dim_Temperature = Dimensions<0,0,0,0,1,0,0,0>;
using Dim_Amount      = Dimensions<0,0,0,0,0,1,0,0>;
using Dim_Intensity   = Dimensions<0,0,0,0,0,0,1,0>;
using Dim_Angle       = Dimensions<0,0,0,0,0,0,0,1>;

template <typename Derived, //units type
          typename T,       //numeric type
          typename D>       //dimensions
struct Quantity
{
    static_assert(std::is_arithmetic<T>::value);

    T        raw_value; 
    static D dimensions;

    Quantity(T q) : raw_value(q) {}
    Quantity()    : raw_value(1) {}
    
    Quantity<Derived,T,D>& operator=(T q) {
        raw_value = q;
        return *this;
    }

    Quantity<Derived,T,D> operator*=(T a) {
        raw_value *= a;
        return *this;
    }

    Quantity<Derived,T,D> operator/=(T a) {
        raw_value /= a;
        return *this;
    }
};

#define BASE_QUANTITY(name, dim)            \
    template <typename Derived, typename T> \
    using name = Quantity<Derived, T, dim>;

BASE_QUANTITY(Length,      Dim_Length);
BASE_QUANTITY(Time,        Dim_Time);
BASE_QUANTITY(Mass,        Dim_Mass);
BASE_QUANTITY(Current,     Dim_Current);
BASE_QUANTITY(Temperature, Dim_Temperature);
BASE_QUANTITY(Amount,      Dim_Amount);
BASE_QUANTITY(Intensity,   Dim_Intensity);
BASE_QUANTITY(Angle,       Dim_Angle);

#define UNIT_SYSTEM(name)                            \
    template <typename T,                            \
              typename D>                            \
    struct name : Quantity<name<T,D>, T, D>          \
    {                                                \
        name(T q) : Quantity<name<T,D>, T, D>(q)     \
        {}                                           \
        name()    : Quantity<name<T,D>, T, D>()      \
        {}                                           \
    };                                               

#include "units.hpp"
