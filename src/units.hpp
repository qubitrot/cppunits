template <int L1, int T1, int M1, int C1, int Tp1, int Am1, int I1, int An1,
          int L2, int T2, int M2, int C2, int Tp2, int Am2, int I2, int An2>
auto dimensional_product(Dimensions<L1, T1, M1, C1, Tp1, Am1, I1, An1> a, 
                         Dimensions<L2, T2, M2, C2, Tp2, Am2, I2, An2> b)
-> Dimensions< L1+L2, T1+T2, M1+M2, C1+C2, Tp1+Tp2, Am1+Am2, I1+I2, An1+An2 >
{}

template <int L1, int T1, int M1, int C1, int Tp1, int Am1, int I1, int An1,
          int L2, int T2, int M2, int C2, int Tp2, int Am2, int I2, int An2>
auto dimensional_quotient(Dimensions<L1, T1, M1, C1, Tp1, Am1, I1, An1> a, 
                          Dimensions<L2, T2, M2, C2, Tp2, Am2, I2, An2> b)
-> Dimensions< L1-L2, T1-T2, M1-M2, C1-C2, Tp1-Tp2, Am1-Am2, I1-I2, An1-An2 >
{}

//////////////////////////////////////////////

template <typename Derived, //raw_value type
          typename T,       //numeric type
          typename D>       //dimensions
auto operator+(const Quantity<Derived,T,D>& a, 
               const Quantity<Derived,T,D>& b) 
-> Derived
{
    return Derived(a.raw_value + b.raw_value);
}

template <typename Derived, //raw_value type
          typename T,       //numeric type
          typename D>       //dimensions
auto operator-(const Quantity<Derived,T,D>& a, 
               const Quantity<Derived,T,D>& b) 
-> Derived
{
    return Derived(a.raw_value - b.raw_value);
}

template <template <typename T, typename D3> class Derived, 
          typename T, 
          typename D1, 
          typename D2>  
auto operator*(const Quantity<Derived<T,D1>,T,D1>& a, 
               const Quantity<Derived<T,D2>,T,D2>& b) 
-> Derived<T, decltype(dimensional_product(a.dimensions, b.dimensions))>
{
    return Derived<T, decltype(dimensional_product(a.dimensions, b.dimensions))>
            (a.raw_value * b.raw_value);
}

template <template <typename T, typename D3> class Derived,
          typename T,
          typename D1>
auto operator*(const Quantity<Derived<T,D1>,T,D1>& a, T b) 
-> Derived<T, D1>
{
    return Derived<T, D1>(a.raw_value * b);
}

template <template <typename T, typename D3> class Derived, 
          typename T, 
          typename D1, 
          typename D2>  
auto operator/(const Quantity<Derived<T,D1>,T,D1>& a, 
               const Quantity<Derived<T,D2>,T,D2>& b) 
-> Derived<T, decltype(dimensional_quotient(a.dimensions, b.dimensions))>
{
    return Derived<T, decltype(dimensional_quotient(a.dimensions, b.dimensions))>
            (a.raw_value / b.raw_value);
}

template <template <typename T, typename D3> class Derived,
          typename T,
          typename D1>
auto operator/(const Quantity<Derived<T,D1>,T,D1>& a, T b) 
-> Derived<T, D1>
{
    return Derived<T, D1>(a.raw_value / b);
}

