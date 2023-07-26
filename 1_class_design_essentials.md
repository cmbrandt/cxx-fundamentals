# Class Design: Essentials

A C++ class is a user-defined data type that serves as a blueprint for creating objects. It encapsulates data members, which represent the state or characteristics of the objects, and member functions, defining the behavior or actions that can be performed on those objects. Classes enable code organization, data encapsulation, and code reusability in C++, allowing you to model real-world entities or abstract concepts and work with objects in a structured and intuitive manner.

Below, we will explore the design and implementation of a rational number class. Mathematical abstractions are ideal for demonstrating C++ class design because they provide a straightforward and intuitive representation of data and behavior. We will begin with the design and representation of the class, then work through the implementation of all member and non-member functions, emphasizing idiomatic C++ design along the way.

## Content

### [Rational Number Class]()

* Representation
* Encapsulation
* Functionality


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

### [Preliminaries](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#preliminaries-1)

* Access Specifiers
* Value Semantics
* Semiregular and Regular Types



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

Constructing an instance using only a single integer value, the parameter is used to initialize `num`, while `den` is initialized to one using the in-class member initializer.

```cpp
explicit Rational::Rational(int n) : num{n} { }
```

Using a pair of integers, both `num` and `dem` are initialized using a member initializer list. Within the constructor body, the private member function `normalize` is called, which will be discussed later.


```cpp
Rational::Rational(int n, int d) : num{n}, den{d} {
  normalize(); // private implementation function
}
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
