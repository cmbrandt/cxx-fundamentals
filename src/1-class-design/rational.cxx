#include <cassert>
#include <iostream>
#include <string_view>

class Rational {
public:
  Rational() = default;
  Rational(int n)        : num{n}, den {1} { normalize(); }
  Rational(int n, int d) : num{n}, den {d} { normalize(); }

  // Copy operations
  Rational(Rational const& other) : num{other.num}, den{other.den} { }
  Rational& operator=(Rational const& other)
  {
    num = other.num;
    den = other.den;
    return *this;
  }

  // Move operations
  Rational(Rational&& other)
  : num{std::move(other.num)}, den{std::move(other.den)} { }
  Rational& operator=(Rational&& other)
  {
    num = std::move(other.num);
    den = std::move(other.den);
    return *this;
  }

  int get_num() const { return num; }
  int get_den() const { return den; }

  void set_num(int n) { num = n; }
  void set_den(int d) { den = d; }

private:
  int gcf() const;
  void normalize();

  int num{0};
  int den{1};
};

int Rational::gcf() const {
  int n = std::abs(num);
  int d = den;
  int temp;

  while (d != 0) {
    temp = n % d;
    n = d;
    d = temp;
  }

  return n;
}

void Rational::normalize() {
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
  int n = Rational::gcf();
  num = num / n;
  den = den / n;
}

bool operator==(Rational const& r1, Rational const& r2) {
  int n1 = r1.get_num();
  int d1 = r1.get_den();
  int n2 = r2.get_num();
  int d2 = r2.get_den();

  return (n1*d2) == (d1*n2);
}

bool operator!=(Rational const& r1, Rational const& r2) {
  return !operator==(r1, r2);
}

bool operator<(Rational const& r1, Rational const& r2) {
  int n1 = r1.get_num();
  int n2 = r2.get_num();
  double d1 = r1.get_den();
  double d2 = r2.get_den();

  return (n1/d2) < (n2/d1);
}

bool operator>(Rational const& r1, Rational const& r2) {
  return operator<(r2, r1);
}

bool operator<=(Rational const& r1, Rational const& r2) {
  return !operator>(r1, r2);
}

bool operator>=(Rational const& r1, Rational const& r2) {
  return !operator<(r1, r2);
}

void print_rational(std::string_view sv, Rational const& r) {
  std::cout << sv
            << "\nr.num = " << r.get_num()
            << "\nr.den = " << r.get_den() << std::endl;
}

int main()
{
  Rational r1;
  print_rational("\nDefault constructor", r1);

  Rational r2{5};
  print_rational("\nInteger conversation constructor", r2);

  Rational r3{2, 4};
  print_rational("\nParameterized constructor", r3);

  Rational r4{r3};
  print_rational("\nCopy constructor", r4);

  Rational r5 = r3;
  print_rational("\nCopy assignment operator", r5);

  Rational r6{std::move(r3)};
  print_rational("\nMove constructor", r6);
  print_rational("Moved from value", r3);

  Rational r7 = std::move(r4);
  print_rational("\nMove assignment operator", r7);
  print_rational("Moved from value", r4);


  Rational c1{-1, 2};
  Rational c2{2, -4};

  std::cout << "\n(-1/2) == (2/-4) = " << (c1 == c2)
            << "\n(-1/2) != (2/-4) = " << (c1 != c2)
            << "\n(-1/2) <  (2/-4) = " << (c1 <  c2)
            << "\n(-1/2) >  (2/-4) = " << (c1 >  c2)
            << "\n(-1/2) <= (2/-4) = " << (c1 <= c2)
            << "\n(-1/2) >= (2/-4) = " << (c1 >= c2)
            << std::endl;
}