#include <cassert>
#include <cmath>
#include <iostream>
#include <string_view>

class Rational {
public:
  Rational() = default;
  Rational(int n)        : num{n}, den {1} { normalize(); }
  Rational(int n, int d) : num{n}, den {d} { normalize(); }

  // Copy constructor
  Rational(Rational const& other)
    : num{other.num}, den{other.den} { }

  // Copy assignment operator
  Rational& operator=(Rational const& other)
  {
    num = other.num;
    den = other.den;
    return *this;
  }

  // Move constructor
  Rational(Rational&& other)
    : num{std::move(other.num)}, den{std::move(other.den)} { }

  // Move assignment operator
  Rational& operator=(Rational&& other)
  {
    num = std::move(other.num);
    den = std::move(other.den);
    return *this;
  }

  // Accessors
  int get_num() const { return num; }
  int get_den() const { return den; }

  // Mutators
  void set_num(int n) { num = n; }
  void set_den(int d) { den = d; }

  // Arithmetic
  Rational& operator+=(Rational const& other);

private:
  int gcd(int a, int b) const;
  int lcm(int a, int b) const;
  void reduce();
  void normalize();

  int num{0};
  int den{1};
};

//----------------------------------------------------------------//
// Member functions

inline int Rational::gcd(int a, int b) const
{
  int n = std::abs(a);

  while (b != 0) {
    int temp = n % b;
    n = b;
    b = temp;
  }

  return n;
}

inline int Rational::lcm(int a, int b) const
{
  return  (a * b) / gcd(a, b);
}

inline void Rational::reduce()
{
  int n = Rational::gcd(num, den);
  num = num / n;
  den = den / n;
}

inline void Rational::normalize()
{
  // Denominator cannot equal zero
  assert(den != 0);
  // Unique representation for zero
  if (num == 0)
    den = 1;
  // Only the numerator should be negative
  else if (den < 0) {
    num = -num;
    den = -den;
  }
  // Reduce
  reduce();
}

inline Rational& Rational::operator+=(Rational const& other)
{
  num = num * other.den + other.num * den;
  den = den * other.den;
  reduce();
  return *this;
}

//----------------------------------------------------------------//
// Non-Member functions

// Arithmetic
Rational operator+(Rational const& r1, Rational const& r2)
{
  Rational temp{r1};
  return temp += r2;
}

// Equality
bool operator==(Rational const& r1, Rational const& r2)
{
  int n1 = r1.get_num();
  int d1 = r1.get_den();
  int n2 = r2.get_num();
  int d2 = r2.get_den();

  return (n1*d2) == (n2*d1);
}

bool operator!=(Rational const& r1, Rational const& r2)
{
  return !operator==(r1, r2);
}

// Ordering
bool operator<(Rational const& r1, Rational const& r2)
{
  int    n1 = r1.get_num();
  int    n2 = r2.get_num();
  double d1 = r1.get_den();
  double d2 = r2.get_den();

  return (n1/d2) < (n2/d1);
}

bool operator>(Rational const& r1, Rational const& r2)
{
  return (r2 < r1);
}

bool operator<=(Rational const& r1, Rational const& r2)
{
  return !(r1 > r2);
}

bool operator>=(Rational const& r1, Rational const& r2)
{
  return !(r1 < r2);
}

void print_rational(std::string_view sv, Rational const& r)
{
  std::cout << sv
            << "\nr.num = " << r.get_num()
            << "\nr.den = " << r.get_den() << std::endl;
}

int main()
{
  Rational r1;
  print_rational("\nDefault constructor", r1);              // = 0/1

  Rational r2{5};
  print_rational("\nInteger conversation constructor", r2); // = 5/1

  Rational r3{2, 4};
  print_rational("\nParameterized constructor", r3);        // = 1/2

  Rational r4{r3};
  print_rational("\nCopy constructor", r4);                 // = 1/2

  Rational r5 = r3;
  print_rational("\nCopy assignment operator", r5);         // = 1/2

  Rational r6{std::move(r3)};
  print_rational("\nMove constructor", r6);                 // = 1/2

  Rational r7 = std::move(r4);
  print_rational("\nMove assignment operator", r7);         // = 1/2


  Rational a1{-2, 7};
  Rational a2{4, 2};
  a1 += a2;
  print_rational("\nMember addition", a1);     // = 12/7

  Rational a3{-2, 7};
  Rational a4{4, 2};
  Rational a5 = a3 + a4;
  print_rational("\nNon-Member addition", a5); // = 12/7

  Rational c1{-1, 2};
  Rational c2{2, -4};

  std::cout << std::boolalpha
            << "\n(-1/2) == (2/-4) = " << (c1 == c2) // = true
            << "\n(-1/2) != (2/-4) = " << (c1 != c2) // = false
            << "\n(-1/2) <  (2/-4) = " << (c1 <  c2) // = false
            << "\n(-1/2) >  (2/-4) = " << (c1 >  c2) // = false
            << "\n(-1/2) <= (2/-4) = " << (c1 <= c2) // = true
            << "\n(-1/2) >= (2/-4) = " << (c1 >= c2) // = true
            << std::endl;
}
