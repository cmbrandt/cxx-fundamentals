#include <cassert>
#include <cmath>
#include <iostream>
#include <string_view>

class Rational {
public:
  // Constructors
  Rational() = default;
  Rational(int n)        : num{n}         { }
  Rational(int n, int d) : num{n}, den{d} { normalize(); }

  // Destructor
  ~Rational() = default;

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
  void set_num(int n) { num = n; normalize(); }
  void set_den(int d) { den = d; normalize(); }

  // Arithmetic
  Rational& operator+=(Rational const& other);
  Rational& operator+=(int other);

private:
  void normalize();
  void reduce();
  int  gcd(int a, int b) const;

  int num{0};
  int den{1};
};

//
// Member functions

void Rational::normalize()
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
  // Reduced form
  reduce();
}

void Rational::reduce()
{
  int n = Rational::gcd(num, den);
  num = num / n;
  den = den / n;
}

int Rational::gcd(int a, int b) const
{
  int n = std::abs(a);
  while (b != 0) {
    int tmp = n % b;
    n = b;
    b = tmp;
  }
  return n;
}

Rational& Rational::operator+=(Rational const& other)
{
  num = num * other.den + other.num * den;
  den = den * other.den;
  normalize();
  return *this;
}

Rational& Rational::operator+=(int other)
{
  Rational tmp{other};
  return *this += tmp;
}

//
// Non-Member functions

// Arithmetic
Rational operator+(Rational const& lhs, Rational const& rhs)
{
  Rational tmp{lhs};
  return tmp += rhs;
}

Rational operator+(Rational const& lhs, int rhs)
{
  Rational tmp{rhs};
  return tmp += lhs;
}

Rational operator+(int lhs, Rational const& rhs)
{
  Rational tmp{lhs};
  return tmp += rhs;
}

// Equality
bool operator==(Rational const& lhs, Rational const& rhs)
{
  return lhs.get_num() == rhs.get_num()
     and lhs.get_den() == rhs.get_den();
}

bool operator!=(Rational const& lhs, Rational const& rhs)
{
  return not(lhs == rhs);
}

// Ordering
bool operator<(Rational const& lhs, Rational const& rhs)
{
  int n1 = lhs.get_num();
  int d1 = lhs.get_den();
  int n2 = rhs.get_num();
  int d2 = rhs.get_den();

  return (n1 * d2) < (n2 * d1);
}

bool operator>(Rational const& lhs, Rational const& rhs)
{
  return (rhs < lhs);
}

bool operator<=(Rational const& lhs, Rational const& rhs)
{
  return not(lhs > rhs);
}

bool operator>=(Rational const& lhs, Rational const& rhs)
{
  return not(lhs < rhs);
}

void print(std::string_view sv, Rational const& r)
{
  std::cout << sv
            << "\nr.num = " << r.get_num()
            << "\nr.den = " << r.get_den() << std::endl;
}

int main()
{
  Rational r1;
  print("\nDefault constructor", r1);            // = 0/1

  Rational r2{5};
  print("\nInteger conversion constructor", r2); // = 5/1

  Rational r3{2, 4};
  print("\nParameterized constructor", r3);      // = 1/2

  Rational r4{r3};
  print("\nCopy constructor", r4);               // = 1/2

  Rational r5 = r3;
  print("\nCopy assignment operator", r5);       // = 1/2

  Rational r6{std::move(r3)};
  print("\nMove constructor", r6);               // = 1/2

  Rational r7 = std::move(r4);
  print("\nMove assignment operator", r7);       // = 1/2


  Rational a1{-2, 7};
  Rational a2{4, -3};
  a1 += a2;
  print("\nMember addition (Rational, Rational)", a1);     // = -34/21

  Rational a3{-2, 7};
  a3 += 1;
  print("\nMember addition (Rational, int)", a3);          // = 5/7

  Rational a4{-2, 7};
  Rational a5{4, -3};
  Rational a6 = a4 + a5;
  print("\nNon-Member addition (Rational, Rational)", a6); // = -34/21

  Rational a7 = a4 + 1;
  print("\nNon-Member addition (Rational, int)", a7);      // = 5/7

  Rational a8 = 1 + a4;
  print("\nNon-Member addition (int, Rational)", a8);      // = 5/7


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
