# Class Design: Essentials
Lorem ipsum dolor sit amet, semper accumsan adolescens eum eu, ea pri modo primis volumus, dico commodo aliquip ex vim. Ad vix minim corpora patrioque, pro enim referrentur no. No quo affert oratio definitionem, sit ut enim consulatu. Eu sit reque causae.

## Content

### [Preliminaries](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#preliminaries-1)

* Access Specifiers
* Value Semantics
* Semiregular and Regular Types

### [Data Members](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#data-members-1)

* Representation
* Invariants

### [Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#member-functions-1)

* Constructors
* Destructor
* Copy Operations
* Move Operations
* Accessors and Mutators
* Implementation Functions

### [Non-Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#non-member-functions-1)

* Equality
* Comparison

# Preliminaries



## Data Members

`struct` has default `public` access:
```cpp
struct Rational {
  int num;
  int den;
};
```

`class` has default `private` acces. The snippet below is equivalent to the snippet abovve. 
Member intializer list:
```cpp
class Rational {
public:
  int num;
  int den;
};
```
## Invariants

* Unique representation for zero
* Unique representation for 1
* Consistent representation for negative values
* 


# Member Functions


## Constructors

### Default Constructor

Assignment:
```cpp
class Rational {
public:
  Rational() {
    num = 0;
    den = 1;
  }

private:
  int num;
  int den;
};
```

Member intializer list:
```cpp
class Rational {
public:
  Rational() : num{0}, den{1} { }

private:
  int num;
  int den;
};
```

In-class member initializer (with defaulted constructor):
```cpp
class Rational {
public:
  Rational() = default;

private:
  int num{0};
  int den{1};
};
```

### Parameterized Constructors

Each parameter is 
```cpp
Rational::Rational(int n, int d) : num{n}, den{d} { }
```


```cpp
explicit Rational::Rational(int n) : num{n} { }
```


## Destructor

Explicit default destructor
```cpp
~Rational::Rational() { };
```

Defaulted destructor
```cpp
~Rational() = default;
```

## Copy Operations


### Copy Constructor

Assignment in the body of the constructor
```cpp
Rational::Rational(Rational const& other) {
  num = other.num;
  den = other.den;
}
```

Using member initializers
```cpp
Rational::Rational(Rational const& other) {
  : num{other.num}, den{other.den} { }
```

### Copy Assignment Operator

```cpp
Rational& Rational::operator=(Rational const& other) {
  num = other.num;
  den = other.den;
}
```


## Move Operations

### Move Constructor

```cpp
Rational::Rational(Rational&& other) {
: num{std::move(other.num)} , den{std::move(other.den)} { }
```

### Move Assignment Operator
```cpp
Rational& Rational::operator=(Rational&& other) {
  num = std::move(other.num);
  den = std::move(other.den);
}
```


## Accessors and Mutators

### Accessors

```cpp
int Rational::get_num() const { return num; }
int Rational::get_den() const { return den; }
```

### Mutators

```cpp
void Rational::set_num(int n) { num = n; }
void Rational::set_den(int d) { den = d; }
```


## Implementation Functions

### Greatest Common Factor

```cpp
int Rational::gcf() {
  int a = std::abs(num);
  int b = den;
  int tmp{};

  while (b != 0) {
    tmp = a % b;
    a = b;
    b = tmp;
  }
  return a;
}
```

### Normalize

```cpp
void Rational::normalize() {
  // Denominator cannot be zero
  assert(den != 0);
  
  // Unique representation for zero
  if (num == 0)
    den = 1;
  // Only the numerator can be negative
  else if (den < 0) {
    num = -num;
    den = -den;
  }
  
  // Simplify
  int n = gcf();
  num = num / n;
  den = den / n;
}
```

Note: we need to update the implementation of the following functions to include a call to the normalize member function: parameterized constructors and mutators. All other member functions will preserver the previously established class invariants.


# Non-Member Functions

## Equality

```cpp
constexpr bool operator==(Rational const& lhs, Rational const& rhs)
{
  return (lhs.num == rhs.num) and (lhs.den == rhs.den);
}
```

```
constexpr bool operator!=(Rational const& lhs, Rational const& rhs)
{
  return !operator==(lhs, rhs);
}
```


## Comparison

```cpp
bool operator<(Rational const& lhs, Rational const& rhs)
{
  int    a = lhs.get_num();
  int    c = rhs.get_num();
  double b = lhs.get_den();
  double d = rhs.get_den();

  return (a/b) < (c/d);
}
```

```cpp
constexpr bool operator>(Rational const& lhs, Rational const& rhs)
{
  return operator<(rhs, lhs);
}
```

```cpp
constexpr bool operator<=(Rational const& lhs, Rational const& rhs)
{
  return !operator>(lhs, rhs);
}
```

```cpp
constexpr bool operator>=(Rational const& lhs, Rational const& rhs)
{
  return !operator<(lhs, rhs);
}
```

TODO: `operator<=>`
