# Class Design: Essentials (WIP)

A class is a collection of data and the algorithms that operate on that data. A class is a user-defined type, and serves as the definition of an object. An object is a concrete instance of a class, and all objects have an address (a location in memory). Given the popularity of the object oriented programming facilities within C++, objects often serve as the basis for C++ programs.

In C++, the data contained within a class are referred to as data members (or attributes). The algorithms that operate on that data are implemented as functions and may be defined inside or outside of the class. Functions defined inside of the class are member functions (or methods), and functions defined outside of the class are non-member functions.

Below, we will explore idiomatic C++ class design through the example of a rational number class. Mathematical abstractions are ideal for demonstrating C++ class design because they provide a straightforward and intuitive example of data and behavior. We will begin by specifying the data representation of the class, then describe the functionality of the class by detailing the implemention of all member and non-member functions.

# Content

### [Data Members](https://github.com/cmbrandt/cxx-fundamentals/blob/master/01_class_design_essentials.md#data-members-1)

* Invariants
* Access Specifiers
* Encapsulation

### [Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/01_class_design_essentials.md#member-functions-1)

* Constructors
* Destructor
* Copy Operations
* Move Operations
* Implementation Functions
* Public Functions

### [Non-Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/01_class_design_essentials.md#non-member-functions-1)

* Arithmetic Operators
* Equality Comparison
* Relational Comparison

### [Additional Resources](https://github.com/cmbrandt/cxx-fundamentals/blob/master/01_class_design_essentials.md#additional-resources-1)


# Data Members

Data members are created and destroyed as part of the object’s lifecycle. When an instance of a class is created, memory is allocated for all data members of that object, and data members are created in their order of declaration within the class definition. When the object goes out of scope or is explicitly deleted, data members are destroyed in the reverse order of their declaration. Data members may include fundamental types, pointers, references, built-in arrays, bit fields, or other user-defined types.

A rational number is expressed as the quotient of two integers: $\frac{n}{d}$ (numerator over denominator). The choice for integer data members is natural given the formal definition of rational numbers, which is the equivalence class of the quotient set of the Cartesian product of all integers (excluding zero from the set of integers in the second term of the product). Restating that definition in terms of the rational number class, the numerator can be any integer value, and the denominator can be any integer value but zero.

## Invariants

A class invariant is a condition or property that must hold true throughout the lifetime of all instances of a class. They are established when an object is fully constructed and must be preserved throughout any state change.


Properties that exist for the set of all rational numbers include the following:
* for all $n$, $\frac{n}{0}$ is undefined
* for all $m$, $n$, it is the case that $\frac{0}{m} = \frac{0}{n}$
* for all $n$, $d$, it is the case that $\frac{n}{\text{-}d} = \frac{\text{-}n}{d}$
* observe that $\frac{1}{2} = \frac{2}{4} = \frac{3}{6} = \frac{4}{8}$

The requirement that the denominator cannot equal zero is a restriction that exists for the domain of all rational numbers. However, the remaining three properties are logical equivalences that can be incorporated into our class design to greatly simplify arithmetic, equality, and comparison operations.

For the rational number class, we will employ the following class invariants:
* to prevent undefined values, `assert` when the denominator is set to zero
* to provide a unique representation for zero, set the denominator to one when the numerator is set to zero
* to provide a consistent representation for negative values, ensure that only the numerator may be negative
* to ensure equality among equivalent values, always represent the object as a reduced fraction

The responsibility for establishing and maintaining these invariants will be managed by a set of private member functions, the details of which will be provided subsequently.

## Access Specifiers

Access specifiers provide the ability to determine which class members are accessible to the users of the class (the class interface) and which class members are for internal use only (the class implementation). C++ has three access specifiers: `public`, `private`, and `protected`. Public members form the public interface of the class and are accessible anywhere. Private members form the implementation of the class and are accessible only by other members. Protected members are accessible by other members of the class and provide unique access to objects within a class hierarchy, which will be discussed in [Class Design: Hierarchies](https://github.com/cmbrandt/cxx-fundamentals/blob/master/03_class_design_hierarchies.md)).

A common convention for ordering the declaration of class members is to group them by their accessibility level. This convention improves code readability and makes it easier to understand the class interface. The general guideline is to order class members from most accessible to least accessible (`public` before `protected` before `private`).

In C++, a class may be declared using the keyword `struct` or the keyword `class`. From a language perspective, the only difference between these two keywords is the default access to class members: `struct` provides default public access and `class` provides default private access.

The two class definitions below are equivalent:

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

The choice of using the keywords `struct` or `class` can vary by individual, project, or team. The general guideline is to use the keyword `class` if the class has an invariant or if any class member is non-public. The use of `struct` is typically reserved for a class whose data members can vary independently.

## Encapsulation

Good class design begins from the outside-in: start with the interface, then move to the implementation. The public interface provides a simplified view of the class that works naturally within the vocabulary of the domain. Unnecessary details are intentionally hidden, and we encapsulate (put into a capsule) the implementation details. This is typically achieved by exposing only the desired functionality through the public interface, making all data members and implementation functions private.

Our rational number class will have public member functions to observe (accessors) and modify (mutators) each data member. Through this design, we can restrict access to the data members, ensuring the preservation of class invariants throughout state transitions over the lifetime of each instance of the class. The encapsulation of implemenation details not only safeguards the class against unintended use, but also ensures that modifications to the implementation will not affect other software components that interact with the class.

# Member Functions

Member functions define the operations and behaviors associated with a class. They provide a structured manner for objects to manipulate their internal data, offering controlled access and modification. By encapsulating operations within the class, member functions contribute to organized and reusable code, enhancing the overall maintainability of software.

Member functions are declared within the class definition and may be defined inside or outside of the class. Functions defined outside of the class use the scope resolution operator `::` to specify the class to which the function belongs. The typical convention is that small, simple functions are defined within the class definition, while larger functions are defined outside of the class. This helps to keep class definitions concise and readable, especially for larger classes or when more complex logic is required.

Under certain conditions, the compiler will automatically generate certain member functions for the class. These functions, known as the special member functions, include the default constructor, copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor. Each of these special functions are discussed below, though a much more comprehensive treatment of each individual function is conducted in [Class Design: Special Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/02_class_design_special.md).

## Constructors

The constructor is a member function that is used to create an instance of a class. When the constructor is called, all data members of the class are default initialized. A class may provide an overload set of multiple constructors to initialize it’s data members under different conditions, using different values.

### Default Constructor

A default constructor is a constructor that can be called with no arguments. If no other constructor is explicitly defined in the class, the compiler will generate a default constructor for the class.

Below is an empty default constructor for our rational number class.

```cpp
class Rational {
public:
  Rational() { }

private:
  int num;
  int den;
};
```

In this example, default initialization is performed for each data member, as no explicit value has been provided. In the case of our integer data members, this leads to indeterminant values.

Explicit values may be assigned to each data member in the body of the constructor, as shown below.

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

In the above example, each data member is default initialized before reaching the opening brace of the constructor body, then a specific value is assigned to them. This is highly inefficient and considered poor practice.

[order of elements in member initializer list]

Instead, C++ provide a member initializer list to specify the direct-initialization of data members within the default constructor. The member initializer list is the colon character `:` followed by a comma-separated list of one of more member-initializers. By using the initializer list, we can avoid the less-efficient two-step process observed in the previous example of member-wise assignment.

```cpp
class Rational {
public:
  Rational() : num{0}, den{1} { } // ": num{0}, den{1}" is the initializer list

private:
  int num;
  int den;
};
```

Alternately, we can use in-class initializers for each data member, enabling us to remove the member initializer list and define the constructor using `=default`.  This is the preferred convention since it clearly specifies the desired default value for each data member and leads to the shortest and most efficient code.

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

Constructing an instance using only a single integer value, the parameter is used to initialize `num`, while `den` is initialized to `1` using the default value provided by the in-class member initializer, providing a representation that defaults to a reduced form and preserving the invariants of the class.

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

The destructor is a special member function that is invoked at the end of an object’s lifetime and tasked with releasing any resources the object may have acquired during its existence. Specific operations necessary to ensure the proper release of owned resources are defined within the body of the destructor. After executing the body of the destructor, the compiler calls the destructor for each data member in reverse order of declaration.

The destructor has the same name as the class, preceded by a tilde `~`. It does not accept arguments, nor does it return a value (or `void`).

The default destructor implementation has an empty body, as depicted below.

```cpp
// Explicit default destructor
Rational::~Rational() { };
```

Our rational number class contains only fundamental type that do not require any special instructions before destruction. As such, the destructor may be defaulted.

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

The compound assignment `operator+=` modifies the current value of an object by performing an addition assignment operation.

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

Binary operators are typically implemented as non-member functions to maintain symmetry.  blah-blah-blah ... `Rational + Rational`, `Rational + int`, `int + Rational`...

Note that very binary arithmetic arithmetic operator has a corresponding compound assignment operator. Therefore, the canonical forms of binary arithmetic operators are implemented in terms of their compound assignments.

```cpp
Rational a{n1, d1};
Rational b{n2, d2};
int i{ii};

Rational c = a + b;
Rational d = a + i;
Rational e = i + b;
```

This non-member free function is defined in terms of the member unary addition operator.

```cpp
Rational operator+(Rational lhs, Rational const& rhs)
{
  return lhs += rhs;
}
```

Rational + int overload:

```cpp
Rational operator+(Rational lhs, int rhs)
{
  return lhs += rhs;
}
```

int + Rational overload

```cpp
Rational operator+(int lhs, Rational rhs)
{
  return rhs + lhs;
}
```


## Equality Comparison

For composite types, two objects are considered equal if their corresponding parts are considered equal (applied recursively). Using this definition, binary equality can be defined in terms of member-wise equality.

Recall that the `normalize` member function ensures a unique representation for all equivalent values. From this, we can implement `operator==` by testing `num` and by testing `den` for two objects.

Two rational numbers are considered equivalent when they represent the same value despite potentially having different numerical representations. In other words, if the ratios of their numerators and denominators are the same, the rational numbers are considered equivalent.

Recall that our class invariants ensure that each instance of the rational number class have a unique representation for zero, do not have a negatve denominator, and exist in reduced form. Maintaining these properties throughout hte lifetime of each object ensures that 

Maintaining these properties throughout the lifetime of each object enables us to implement the equality operator using only two binary equality operations. Furthermore, the logical AND operator performs short-circuit evaluation, and does not evaluate the second operand if the result is false.

```cpp
constexpr bool operator==(Rational const& lhs, Rational const& rhs)
{
  return lhs.get_num() == rhs.get_num()
     and lhs.get_den() == rhs.get_den();
}
```

The inequality operator is typically implemented in terms of the equality operator.

```cpp
constexpr bool operator==(Rational const& lhs, Rational const& rhs) { /* perform the comparison */ }
constexpr bool operator!=(Rational const& lhs, Rational const& rhs) { return not(lhs == rhs); }
```

## Relational Comparison

Operator less-than evaluates the expression $r_1 < r_2$, where $r_1 = \frac{n_1}{d_1}$ and $r_2 = \frac{n_2}{d_2}$.

Because division has a higher latency than multiplication, we choose to instead evaluate the mathematically equivalent (and computationally less expensive) expression $n_1d_2 < n_2d_1$.

```cpp
constexpr bool operator<(Rational const& lhs, Rational const& rhs)
{
  int n1 = lhs.get_num();
  int d1 = lhs.get_den();
  int n2 = rhs.get_num();
  int d2 = rhs.get_den();

  return (n1*d2) < (n2*d1);
}
```

Typically, once `operator<` is provided, the other relational operators are implemented in terms of it.

```cpp
constexpr bool operator< (Rational const& lhs, Rational const& rhs) { /* perform the comparison */ }
constexpr bool operator> (Rational const& lhs, Rational const& rhs) { return rhs < lhs;      }
constexpr bool operator<=(Rational const& lhs, Rational const& rhs) { return not(lhs > rhs); }
constexpr bool operator>=(Rational const& lhs, Rational const& rhs) { return not(lhs < rhs); }
```


TODO: `operator<=>`

# Additional Resources

* Stroustrup, B. [What is Object-Oriented Programming?](https://www.stroustrup.com/whatis.pdf) (1991 revised version). Proc. 1st European Software Festival. February, 1991.
* Iglberger, K. [CppCon]. (2021, October 25). *Back to Basics: Designing Classes (part 2 of 2)*. [Video]. [www.youtube.com/watch?v=9BM5LAvNtus](https://www.youtube.com/watch?v=O65lEiYkkbc)
* Stroustrup, B., Sutter, H. "Classes and Class Hierarchies." *C++ Core Guidelines*, April 2023. [http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-class](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-class)
* Pikus, F. *[Hands-On Design Patterns with C++](https://www.amazon.com/Hands-Design-Patterns-problems-applications-dp-1804611557/dp/1804611557/)*, 2nd ed., Packt, 2023.
* "Classes and Objects." *Standard C++*, [https://isocpp.org/wiki/faq/classes-and-objects](https://isocpp.org/wiki/faq/classes-and-objects). Accessed August 2023. 
