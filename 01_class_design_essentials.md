# Class Design: Essentials (WIP)

A class is a collection of data and the algorithms that operate on that data. A class is a user-defined type, and serves as the definition of an object. An object is a concrete instance of a class, and all objects have an address (a location in memory).  Since C++ is primarily an object-oriented language, objects serve as the basis for C++ programs.

In C++, the data contained within a class are referred to as data members (or attributes). The algorithms that operate on that data are implemented as functions and may be defined inside or outside of the class. Functions defined inside of the class are member functions (or methods), and functions defined outside of the class are non-member functions.

Below, we will explore idiomatic C++ class design through the example of a rational number class. Mathematical abstractions are ideal for demonstrating C++ class design because they provide a straightforward and intuitive representation of data and behavior. We will begin with the specification and encapsulation of data members, then illustrate the functionality of the class by stepping through the implemention of all member and non-member functions.

# Content

### [Data Members](https://github.com/cmbrandt/cxx-fundamentals/blob/master/01_class_design_essentials.md#data-members-1)

* Invariants
* Access Specifiers
* Encapsulation

### [Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#member-functions-1)

* Constructors
* Implementation Functions
* Destructor
* Copy Operations
* Move Operations
* Public Functions

### [Non-Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#non-member-functions-1)

* Arithmetic Operators
* Equality Operators
* Comparison Operators

### [Additional Resources](https://github.com/cmbrandt/cxx-fundamentals/blob/master/01_class_design_essentials.md#additional-resources-1)


# Data Members

Data members are created and destroyed as part of the object’s lifecycle. When an instance of a class is created, memory is allocated for all data members of that object. Data members are initialized in the order they are declared in the class and destroyed in the reverse order of their declaration when the object goes out of scope. Data members may include fundamental types, pointers, references, built-in arrays, bit fields, or other user-defined types.

A rational number is expressed as the quotient of two integers: $\frac{n}{d}$ (numerator over denominator). The choice for integer data members is natural, given the formal definition of rational numbers as the equivalence class of the quotient set of the Cartesian product of all integers (excluding zero from the set of integers in the second term of the product). Restating that definition in terms of the rational number class, the denominator can never be zero.

## Invariants

A class invariant is a condition or property that must always hold true for all instances of a class throughout their lifetime. They are established when an object is fully constructed and must be preserved throughout any state change.


Properties that exist for the set of all rational numbers include the following:
* for all $n$, $\frac{n}{0}$ is undefined
* for all $m$, $n$, it is the case that $\frac{0}{m} = \frac{0}{n}$
* for all $n$, $d$, it is the case that $\frac{n}{\text{-}d} = \frac{\text{-}n}{d}$
* observe that $\frac{1}{2} = \frac{2}{4} = \frac{3}{6} = \frac{4}{8}$

The requirement that the denominator cannot equal zero is a restriction that exists for the domain of all rational numbers. However, the remaining three properties are logical equivalences that can be incorporated into our class design to greatly simplify arithmetic, equality, and comparison operations.

For our rational number class, we will employ the following class invariants:
* to prevent undefined values, `assert` when the denominator is set to zero
* to provide a unique representation for zero, set the denominator to one when the numerator is set to zero
* to provide a consistent representation for negative values, ensure that only the numerator may be negative
* to ensure equality among equivalent values, always represent the object as a reduced fraction

The responsibility for establishing and maintaining these properties will be handled by a set of private member functions, which will be described herein.

## Access Specifiers

Access specifiers provide the author of the class the ability to decide which class members are accessible to the users of the class (the class interface) and which members are for internal use only (the class implementation). There are three access specifiers: `public`, `private`, and `protected`. Public members form the public interface of the class and are accessible anywhere. Private members are only accessible by other members of the class and form the implementation of the class. Protected members are accessible by other members of the class and provide unique access within a class hierarchy (to be discussed in detail in a future topic).

In C++, a class may be defined using the keyword `class` or the keyword `struct`. From a language perspective, the only difference between these two keywords is the default access to class members: `struct` provides default public access, and `class` provides default private access.

The two class definitions below are considered equivalent:

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

A common convention for ordering class members in their declaration is to group them by their accessibility level. This convention improves code readability and makes it easier to understand the class interface. The general guideline is to order class members from most accessible to least accessible (`public` before `protected` before `private`).

The choice between using the keywords `class` or `struct` can vary by individual, project, or team. A common convention is to use the keyword `class` if the class has an invariant or if any member is non-public. The use of `struct` is typically reserved for a class whose data members can vary independently.

## Encapsulation

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

## Encapsulation

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

## Implementation Functions

### Normalize

```cpp
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
  reduce();
}
```

### Reduce

```cpp
void Rational::reduce()
{
  int n = Rational::gcd(num, den);
  num = num / n;
  den = den / n;
}
```

### Greatest Common Denominator

```cpp
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
```

Note: we need to update the implementation of the following functions to include a call to the normalize member function: parameterized constructors and mutators. All other member functions will preserver the previously established class invariants.


## Destructor

The destructor is responsible for cleaning up all resources associated with the class. The default destructor implementation has an empty body, as depicted below.

```cpp
// Explicit default destructor
Rational::~Rational() { };
```
The rational number class is a **plain old data** class, which does not require any special instructions for cleanup. As such, it may be defaulted.

```cpp
// Defaulted destructor
Rational::~Rational() = default;
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


## Public Functions

### Accessors

```cpp
int Rational::get_num() const
{
  return num;
}

int Rational::get_den() const
{
  return den;
}
```

### Mutators

```cpp
void Rational::set_num(int n)
{
  num = n;
  reduce();
}

void Rational::set_den(int d)
{
  den = d;
  normalize();
}
```

### Arithmetic

Perform the operation:

```cpp
Rational a{n1, d1};
Rational b{n2, d2};

a += b;
```

Asfadf dafdadsf adfa fdss

```cpp
// Member addition
Rational& Rational::operator+=(Rational const& other)
{
  num = num * other.den + other.num * den;
  den = den * other.den;
  reduce();
  return *this;
}
```

# Non-Member Functions

Description adf adf fa fad fadfa adf adf

## Arithmetic Operators

The non-member binary addition operator performs the operation:

```cpp
Rational a{n1, d1};
Rational b{n2, d2};

Rational c = a + b;
```

This non-member free function is defined in terms of the member unary addition operator.

```cpp
// Non-Member Addition
Rational operator+(Rational const& lhs, Rational const& rhs)
{
  Rational tmp{lhs};
  return tmp += rhs;
}
```

## Equality Operators

Equality performs member-wise equality comparisons. Note that the logical AND and logical OR operators perform short-circuit evaluation (does not evaluate the second operand if the result is known after evaluating the first operand).

```cpp
// Equality
bool operator==(Rational const& lhs, Rational const& rhs)
{
  return lhs.get_num() == rhs.get_num()
     and lhs.get_den() == rhs.get_den();
}
```

Distinction is defined in terms of equality.

```cpp
// Distinction
bool operator!=(Rational const& lhs, Rational const& rhs)
{
  return not(lhs == rhs);
}
```

## Comparison Operators

Operator less-than evaluates the expression $r_1 < r_2$, where $r_1 = \frac{n_1}{d_1}$ and $r_2 = \frac{n_2}{d_2}$.

Because division has a higher latency than multiplication, we choose to instead evaluation the mathematically equivalent (and computationally less expensive) expression $n_1 \times d_2 < n_2 \times d_1$.

```cpp
// Less-than
bool operator<(Rational const& lhs, Rational const& rhs)
{
  int n1 = lhs.get_num();
  int n2 = rhs.get_num();
  int d1 = lhs.get_den();
  int d2 = rhs.get_den();

  return (n1*d2) < (n2*d1);
}
```

Operator greater-than is defined in terms of operator less-than, swapping the order of the arguments `lhs` and `rhs` within the operator less-than expression.
```cpp
// Greater-than
bool operator>(Rational const& lhs, Rational const& rhs)
{
  return (rhs < lhs);
}
```

Less-or-equal and greater-or-equal are defined in terms of less-than and greater-than.

```cpp
// Less-or-equal
bool operator<=(Rational const& lhs, Rational const& rhs)
{
  return not(lhs > rhs);
}

// Greater-or-equal
bool operator>=(Rational const& lhs, Rational const& rhs)
{
  return not(lhs < rhs);
}
```

TODO: `operator<=>`

# Additional Resources

* Stroustrup, B. [What is Object-Oriented Programming?](https://www.stroustrup.com/whatis.pdf) (1991 revised version). Proc. 1st European Software Festival. February, 1991.
* Iglberger, K. [CppCon]. (2021, October 25). *Back to Basics: Designing Classes (part 2 of 2)*. [Video]. [www.youtube.com/watch?v=9BM5LAvNtus](https://www.youtube.com/watch?v=O65lEiYkkbc)
* Stroustrup, B., Sutter, H. "Classes and Class Hierarchies." *C++ Core Guidelines*, April 2023. [http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-class](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-class)
* Pikus, F. *[Hands-On Design Patterns with C++](https://www.amazon.com/Hands-Design-Patterns-problems-applications-dp-1804611557/dp/1804611557/)*, 2nd ed., Packt, 2023.
* "Classes and Objects." *Standard C++*, [https://isocpp.org/wiki/faq/classes-and-objects](https://isocpp.org/wiki/faq/classes-and-objects). Accessed August 2023. 
* "Working Draft." *Draft C++ Standard*, [https://eel.is/c++draft/#class](https://eel.is/c++draft/#class). Accessed August 2023. 
