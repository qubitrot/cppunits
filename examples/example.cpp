#include <iostream>
#include <typeinfo>
#include "units.h"

using MetersPerSecond = SI_Units<double,
    decltype( dimensional_quotient(Dim_Length(), Dim_Time()) )
    >;

template <typename Units, typename T>
Time<Units, T> t(Time<Units, T> in) 
{
    return in *= 3;
}

MetersPerSecond f(Meters x) {
    auto c = x / Seconds(2);
    return c;
}

int main()
{
    Seconds a = 3;
    Meters b(3);

    a *= 2;

    auto d = a + Seconds(2);

    auto mps = f(b);
   
    std::cout << d.raw_value << "\n";
    std::cout << t(a).raw_value << "\n";
    std::cout << mps.raw_value << "\n";
    std::cout << typeid(mps).name() << "\n";
    std::cout << typeid(b).name() << "\n";
    std::cout << typeid(d).name() << "\n";

    return 0;
}
