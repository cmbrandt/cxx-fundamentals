# Class Design: Essentials

A C++ class is a user-defined data type that serves as a blueprint for creating objects. It encapsulates data members, which represent the state or characteristics of the objects, and member functions, defining the behavior or actions that can be performed on those objects. Classes enable code organization, data encapsulation, and code reusability in C++, allowing you to model real-world entities or abstract concepts and work with objects in a structured and intuitive manner.

Below, we will explore the design and implementation of a rational number class. Mathematical abstractions are ideal for demonstrating C++ class design because they provide a straightforward and intuitive representation of data and behavior. We will begin with the high-level representation of the class, then work through the implementation of all member and non-member functions, emphasizing idiomatic C++ design along the way.

## Content

### [Representation]()

* Invariants
* Accessibility

### [Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#member-functions-1)

* Constructors
* Destructor
* Copy Operations
* Move Operations
* Accessors and Mutators
* Implementation Functions

### [Non-Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#non-member-functions-1)

* Equality
* Ordering


# Representation

A rational number is expressed as the quotient of two numbers: `n/d` (numerator over denominator). Typical operations performed on rational numbers include basic arithmetic operations (addition, substraction, multiplication, and division), equality, distinction, and ordering.

## Invariants

A class invariant is a condition or property that must always hold true for all instances of a class throughout its lifetime. They are established when an object is fully constructed, and must be preserved throughout any state change.

Properties that exist for the set of all rational numbers include the following:
* for all $n$, $\frac{n}{0}$ is undefined
* for all $m$, $n$, it is the case that $\frac{0}{m} = \frac{0}{n}$
* for all $n$, $d$, it is the case that $\frac{n}{\text{-}d} = \frac{\text{-}n}{d}$
* note that $\frac{1}{2} = \frac{2}{4} = \frac{3}{6} = \frac{4}{8}$

To preserver these properties, the following class invariants can be established:
* to prevent undefined values, `assert` when the denominator is set to zero
* to provide a unique representation for zero, set the denominator to zero when the numerator is set to one
* to provide a consistent representation for negative values, ensure that only the numerator may be negative
* to ensure equality among equivalent values, always represent the object as a reduced fraction

These properties can be captured by a private member function, which will be described later herein.

## Accessibililty

Direct access to data members allows programmers to break invariants established by the constructor. The internal details of a class can be protected by changing the visibility of data members and member functions.

C++ provides the following three access specifiers: `public`, `protected`, and `private`. Public members for a part of the public interface of a class, and are accessible anywhere. Protected members of a class are only accessible (1) to the members and friends of that class, and (2) to the members of any derived class of that class. Private members form the implementation of a class, and are only accessible to the members and friends of that class.

User-defined types are declared using the keywords `class` and `struct`, which are identical except for the default member acess: `struct` is public by default, while `class` is private by default.

The following two class definitions can be considered equivalent definitions:

```cpp
// struct has default public access
struct Rational {
  // Constructors
  // Assignment operators
  // Destructor
private:
  int num;
  int den;
};
```

```cpp
// class has default private access
class Rational {
public:
  // Constructors
  // Assignment operators
  // Destructor
private:
  int num;
  int den;
};
```

# Member Functions

In C++, member functions (also referred to as methods), are functions defined within a class and work with the class's data members (attributes). They serve as the primary means of interacting with the data encapsulated in the class and play a vital role in implementing the class's behavior and operations.

## Constructors

A C++ constructor is a special member function within a class that is automatically called when an object of that class is created. The primary purpose of a constructor is to initialize the object's data members to specific values, ensuring that the object starts in a valid and consistent state. Constructors play a fundamental role in the process of object creation and are essential for proper memory allocation and initialization of object attributes.

### Default Constructor

A default constructor is a constructor that accepts no arguments and is used to create objects of the class with default initial values for its data members. If no other constructor is explicitly defined for the class, the compiler will provide generate a default constructor for the class.

The default constructor performs member-wise assignment for each data member.

```cpp
// assignment
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

Member-wise assignment in the body of the constuctor is inefficient because (...). Instead, prefer to use member initializer lists.

```cpp
// member initializer list
class Rational {
public:
  Rational() : num{0}, den{1} { }

private:
  int num;
  int den;
};
```

Things can be simplified even further by using in-class initializers for defining default data member values. This also allows the default constructor to be defaulted by the compiler (defining it using `= default`).

```cpp
// in-class member initializer with defaulted constructor
class Rational {
public:
  Rational() = default;

private:
  int num{0};
  int den{1};
};
```

### Parameterized Constructors

Constructing an instance using only a single integer value, the parameter is used to initialize `num`, while `den` is initialized to one using the default values provided to the in-class member initializers, thereby preserving the invariants of the class and providing a representation that defaults to a reduced form.

```cpp
explicit Rational::Rational(int n) : num{n} { }
```

Using a pair of integers, both `num` and `dem` are initialized using a member initializer list. Since this function has the ability to overwrite both default values, the class invariants will need to be established during construction. Therefore, within the constructor body, the private member function `normalize` is called, which will be discussed later.


```cpp
Rational::Rational(int n, int d) : num{n}, den{d}
{
  normalize(); // private implementation function
}
```

## Destructor

The destructor is responsible for cleaning up all resources associated with the class. The default destructor implementation has an empty body, as depicted below.

```cpp
// Explicit default destructor
~Rational::Rational() { };
```
The rational number class is a **plain old data** class, which does not require any special instructions for cleanup. As such, it may be defaulted.

```cpp
// Defaulted destructor
~Rational() = default;
```

## Copy Operations

C++ copy operations refer to two speical member functions, the copy constructor and copy assignment operator. The copy constructor creates a new object as a copy of an existing object, while the copy assignment operator is used for assigning the contents of one object to another object.

### Copy Constructor

The copy constructor is responsible for performing a member-wise copy of each data member from the source object to the newly created object. The copy constructor defined below performs element-wise copy assignment in the constructor body.

```cpp
// Copy constructor using copy assignment
Rational::Rational(Rational const& other)
{
  num = other.num;
  den = other.den;
}
```

As with other constructors, the preferred definition of the copy constructor uses member initializers to perform the member-wise copy.

```cpp
// Copy constructor using member initializers
Rational::Rational(Rational const& other)
  : num{other.num}, den{other.den} { }
```

### Copy Assignment Operator

The default copy assignment operator performs a member-wise copy assignment of each data member.

```cpp
// Copy assignment operator
Rational& Rational::operator=(Rational const& other)
{
  num = other.num;
  den = other.den;
}
```

Once again, since the rational number class is a **plain old data** class, both the copy constructor and copy assignment operator may be defaulted, opting to use the compiler generated versions instead.


## Move Operations

C++ move operations allow for the efficient transfer of resources from one object to another. Comprising the move constructor and move assignment operator, they are essential for implementing move semantics and improving performance in situations where objects are temporary or about to be destructed.

### Move Constructor

The move constructor initializes a new object by "stealing" the resources from the source object, leaving the source object in a valid but unspecified state. This enables faster object creation by avoiding expensive deep copying of resources and, instead, transferring ownership of the resources to the new object.

The move constructor below is implemented using member initilizers to perform a member-wise move.

```cpp
// Move constructor using member initializers
Rational::Rational(Rational&& other)
  : num{std::move(other.num)} , den{std::move(other.den)} { }
```

### Move Assignment Operator

The move assignment operator assigns the contents of one object to another object, efficiently transferring resources from the source object to the target object. The member-wise move assignment operations avoid unnecessary duplication of resources for data members that provide move operations themselves.

```cpp
// Move assignment operator
Rational& Rational::operator=(Rational&& other)
{
  num = std::move(other.num);
  den = std::move(other.den);
}
```

Again, because the rational number class is a **plain old data** class, both the move constructor and move assignment operator may be defaulted, opting to use the compiler generated versions instead.


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
int Rational::gcf()
{
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
void Rational::normalize()
{
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


## Ordering

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
