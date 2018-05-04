#include <iostream>
#include <vector>
#include <cmath>
#include "units.h"
#include "si_units.h"

using G_units = SI_Units<double, Dimensions<3,-2,-1,0,0,0,0,0>>;
G_units G(6.674e-11);

//Generic type for three dimensional vectors.
//We only define the operations which are needed
//in the code below.
template <typename T>
struct V3 {
    T x, y, z;

    V3() : x(0), y(0), z(0)              {}
    V3(T a, T b, T c) : x(a), y(b), z(c) {}

    //compute the norm squared of a vector
    auto norm2() -> decltype(T() * T()) {
        return x*x + y*y + z*z;
    }

    auto norm() -> T {
        auto sq = norm2();  
        return T( std::sqrt( sq.raw_value ) ); //TODO: Make this unnessary.
    }

    V3<T> operator+(V3<T>& v) 
    { return V3(x+v.x, y+v.y, z+v.z); }
    V3<T> operator-(V3<T>& v) 
    { return V3(x-v.x, y-v.y, z-v.z); }

    template <typename T2>
    auto operator*(T2 s) -> V3<decltype(T() * T2())>
    { return V3<decltype(T()*T2())>(x*s, y*s, z*s); }

    template <typename T2>
    auto operator/(T2 s) -> V3<decltype(T() / T2())>
    { return V3<decltype(T()/T2())>(x/s, y/s, z/s); }
};

//This structure encapsulates all the information about the
//actors in our n-body simulation.
struct Body {
    Kilograms  mass;
    V3<Meters> pos;
    V3<MpS>    vel;
};

using NBodySystem = std::vector<Body>;

//Computes the gravitational acceleration on body a due to body b.
V3<MpSsq> gravitational_accel(Body a, Body b) 
{
    V3<Meters> displacement = b.pos - a.pos;

    Meters  r  = displacement.norm();
    Meters2 r2 = displacement.norm2();

    MpSsq magnitude = G * b.mass / r2;
    V3<MpSsq> accel = (displacement / r) * magnitude;

    return accel;
}

//Preform a single iteration of Euler's method.
void integrate(NBodySystem& sys, Seconds step)
{
    std::vector<V3<MpSsq>> accels(sys.size());

    for (uint i=0; i<sys.size(); ++i) {
        for (uint j=i+1; j<sys.size(); ++j) {
            Body a = sys[i]; 
            Body b = sys[j];
            V3<MpSsq> delta_accel = gravitational_accel(a,b);
            accels[i] = accels[i] + delta_accel;
            accels[j] = accels[j] - delta_accel;
        }
    }

    for (uint i=0; i<sys.size(); ++i) {
        Body& b = sys[i];

        V3<MpS> delta_v = accels[i] * step;
        b.vel = b.vel + delta_v;

        V3<Meters> delta_pos = b.vel * step;
        b.pos = b.pos + delta_pos;
    }
}

int main() {
    Body a; a.mass = Kilograms(10e6); a.pos={-1,0,0}; a.vel={0,-1e-3,0};
    Body b; b.mass = Kilograms(10e6); b.pos={ 1,0,0}; b.vel={0, 1e-3,0};
    
    NBodySystem sys;
    sys.push_back(a);
    sys.push_back(b);

    Seconds time_step = 3;

    for (int i=0; i<10; ++i) {
        integrate(sys, time_step);
        std::cout << sys[0].pos.x.raw_value << ", " 
                  << sys[0].pos.y.raw_value << "\t | \t"
                  << sys[1].pos.x.raw_value << ", "
                  << sys[1].pos.y.raw_value << "\n";
    }

    return 0;
}
