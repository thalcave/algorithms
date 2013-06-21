#include <iostream>

template <unsigned long X, unsigned long Y>
struct Problem15
{
   enum : unsigned long { steps = Problem15<X - 1, Y>::steps + Problem15<X, Y - 1>::steps };
};

template<>
struct Problem15<0, 0>
{
   enum : unsigned long { steps = 1 };
};

template<unsigned long Y>
struct Problem15<-1, Y>
{
   enum : unsigned long { steps = 0 };
};

template<unsigned long X>
struct Problem15<X, -1>
{
   enum : unsigned long { steps = 0 };
};

int
main()
{
   std::cout << Problem15<20, 20>::steps << std::endl;

   return 0;
}
