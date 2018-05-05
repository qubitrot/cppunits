# cppunits
A header-only library for statically-typed dimensionful quantities.

The aim of this library is to provide the ability to add dimensions and units to 
variables representing physical quantities. This makes it easier to reason about
programs, as well as allowing the compiler to catch errors when the units don't 
work out. The function

```C++
double averageVelocity(double distance, double time) {
  return distance/time;
}
```
can now be enhanced:
```C++
MetersPerSecond averageVelocity(Meters distance, Seconds time) {
  return distance/time;
}
```
Or, more generically,
```C++
//T gives the numeric representation, typically double.
template <typename Units, typename T> 
Velocity<Units, T> averageVelocity(Length<Units,T> distance, Time<Units,T> time) {
  return distance/time;
}
```
An example is provided for simulating n-body gravitation.
