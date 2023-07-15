# Class Design: Special Member Functions

The *special member functions* are class member functions that, in certain cases, the compiler automatically generates for you. These functions include the default constructor, destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator. If a class does not define one or more of the special member functions, then the compiler may implicitly declare and define them. The compiler-generated implementations are called the *default* member functions, and are not generated if they are not needed.

Default special member functions can be explicitly declared using `= default`. The compiler will define the function only if needed, in the same way as if the function was not declared at all.

In some cases, the compiler may generate *delete* special member functions, where they will not be defined and therefore not callable. These cases vary for each function, and are illustrated below. To prevent the automatic generation of a special member function, it can be declared using `= delete`.


## Content

### [Default Constructor](https://github.com/cmbrandt/modern-cxx-seminar/edit/master/1_class_design.md#fundamentals-1)
* Availability
* Data Member Initialization

### [Destructor](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#special-member-functions)
* Default Destructor Availability
* ...

### [Copy Operations](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#additional-class-operations)
* Compiler Generated
* Manual Implementation
* Temporary Swap
* Optimized Implementation
* std::unique_ptr
* std::shared_ptr

### [Move Operations](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#class-hierarchies)
* Compiler Generated
* Manual Implementation
* Temporary Swap
* Optimized Implementation
* std::unique_ptr
* std::shared_ptr

### [Rule of Three/Five/Zero](https://github.com/cmbrandt/cxx-fundamentals/blob/master/2_class_design_special.md#rule-of-threefivezero-1)
* Rule of Three
* Rule of Five
* Rule of Zero


# Default Constructor

In C++, the standard describes the default constructor for a class as a constructor that can be called with no arguments (this includes a constructor whose parameters all have default arguments). Default constructors are significant because they are invoked in certain circumstances; and therefore, in these circumstances, it is an error for a class to not have a default constructor.

## Availability

If a class has no other explicitly defined constructors, the compiler will implicitly declare and define a default constructor for it. This implicitly defined default constructor is equivalent to an explicitly defined defined one.

```
// Ex 1: Compiler-generated default constructor available
class Widget {
public:
  // ...
};

Widget w1;   // Ok! Compiler generated
Widget w2{}; // Ok! Compiler generated
```

If constructors are explicitly defined for a class, but they are all non-default, the compiler will not implicitly define a default construcctor, leading to a situation where the class does not have a default constructor. This is the reason for a typical error, as demonstrated below.

```
// Ex 2: No compiler-generated default constructor available
class Widget {
public:
  Widget(Widget const&); // Explicit declaration of copy ctor
  // ...                 // Default ctor no longer available
};

Widget w1;   // Error! No default constructor
Widget w2{}; // Error! No default constructor
```

A compiler generated default constructor will be defined as deleted if any class members aren't default-constructable. For example, all members of class type (and their class type members) must have a default constructor and destructors that are accessible.

```
// Ex 3: No compiler-generated default constructor available
class Widget {
public:
  // ...
private:
  NotDefaultConstructable member; // Data member without a default ctor
};

Widget w1;   // Error! No default constructor
Widget w2{}; // Error! No default constructor
```







## Data Member Initialization


The compiler generated default constructor will initialize all data members of class (user-defined) type, but will not initialize the data members of fundamental type.

```
// Ex 1: Default initialization
struct Widget {
  int idx;         // Uninitialized
  std::string str; // Default (empty string)
  Resource* ptr;   // Uninitialized
};

Widget w;          // Default initialization
```

If no default constructor is declared, value initialization with (1) zero-initialize the object, and (2) default-initialzie all non-trivial data members.

```
// Ex 2: Value initialization
struct Widget {
  int idx;         // Initialized to 0
  std::string str; // Default (empty string)
  Resource* ptr;   // Initialized to nullptr
};

Widget w{};        // Value initialization with no default ctor
```

An empty default constructor will initialize all data members of class (user-defined) type, but will not initialize the data members of fundamental type.

```
// Ex 3: Explicit default constructor with value initialization
struct Widget {
  Widget() { }     // Explicit default constructor

  int idx;         // Uninitialized
  std::string str; // Default (empty string)
  Resource* ptr;   // Uninitialized
};

Widget w{};        // Value initialization with no default ctor
```

The `= default` allows the compiler to generate the default constructor. `= default` counts as definition, plus may provide additional benefits (include `noexcept`).

```
// Ex 4: Defaulted constructor with value initialization
struct Widget {
  Widget() = default; // Defaulted consructor

  int idx;            // Initialized to 0
  std::string str;    // Default (empty string)
  Resource* ptr;      // Initialized to nullptr
};

Widget w{};           // Value initialization with declared default ctor
```




# Destructor



```
// Ex 1: Compiler-generated destructor available
class Widget {
public:
  // ...
};

Widget w1;   // Ok! Compiler generated
Widget w2{}; // Ok! Compiler generated
```





```
// Ex 2: Explicit declaration of destructor
class Widget {
public:
  ~Widget(); // Explicit declaration of dtor
  // ...     // Compiler provides empty dtor
};

Widget w1;   // Ok! Manual destructor
Widget w2{}; // Ok! Manual destructor
```




```
// Ex 3: Explicit defintion of empty destructor
class Widget {
public:
  // ...
  ~Widget()        // The compiler generated destructor destroys the
  {                // std::string data member, but does not perform
                   // any special action for the integer and pointer...
  }                // Potential resource leak!

private:
  int idx;         // Fundamental type
  std::string str; // Class (user-defined) type
  Resource* ptr;   // Possible resource
};
```


```
// Ex 4: Explicit defintion of destructor to delete pointer
class Widget {
public:
  // ...
  ~Widget()        // ...
  {                // ...
    delete ptr;    // ...
  }                // No resource leak!

private:
  int idx;         // Fundamental type
  std::string str; // Class (user-defined) type
  Resource* ptr;   // Possible resource
};
```


# Copy Operations

## Compiler Generated

Below is the compiler-generated copy constructor and copy assignment operator. The default operations perform element-by-element copy. Note that this performs a shallow copy of our Resource.

```
// Ex 1: Compiiler generated copy operations
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr} // Shallow copy!
  { } 

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    idx = other.idx;
    str = other.str;
    ptr = other.ptr; // Shallow copy!
    return *this;
  }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```


## Manual Implementation

We explicitly copy the Resource. To ensure we do not leak our Resource, we need to explicitly delete the Resource in our copy assignment operation. However, by doing this, we are no longer safe against self-assignment.

```
// Ex 2: Manual implementation
class Widget {
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? new Resource{*other.ptr} : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    delete ptr;
    idx = other.idx;
    str = other.str;
    ptr = other.ptr ? new Resource{*other.ptr} : nullptr;
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```


## Temporary Swap Idiom

Here we use the copy-and-swap idiom in for our copy assignment operator. This is safe against self-assignment. However, this is not the most efficient implementation of this operation.

```
// Ex 3: Temporary-swap idiom
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? new Resource{*other.ptr} : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    Widget tmp{other};
    swap(tmp);
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept {
    using std::swap;
    swap(idx, other.idx);
    swap(str, other.str);
    swap(ptr, other.ptr);
  }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```

## Optimized Implementation

adf af adsf adsf ads

```
// Ex 4: Optimized implementation
class Widget {
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? new Resource{*other.ptr} : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    if (ptr and &other.ptr) {
      idx  = other.idx;
      str  = other.str;
      *ptr = *other.ptr;
    }
    else {
      Widget tmp{other};
      swap(tmp);
    }
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept {
    using std::swap;
    swap(idx, other.idx);
    swap(str, other.str);
    swap(ptr, other.ptr);
  }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```


## std::unique_ptr

Using std::unique_ptr to manage the Resource. We no longer need to explicitly define the destructor.

```
// Ex 5: std::unique_ptr
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? std::make_unique<Resource>(*other.ptr) : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    if (ptr and &other.ptr) {
      idx  = other.idx;
      str  = other.str;
      *ptr = *other.ptr;
    }
    else {
      Widget tmp{other};
      swap(tmp);
    }
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept {
    using std::swap;
    swap(idx, other.idx);
    swap(str, other.str);
    swap(ptr, other.ptr);
  }

private:
  int idx{};
  std::string str{};
  std::unique_ptr<Resource> ptr{};
};
```

## std::shared_ptr

Using std::shared_ptr to manage the Resource. We no longer need to explicitly define copy operations. However, using std::shared_ptr changes the semantics of the class. Do not use std::shared_ptr just to eliminate the need to explicitly define copy operations.

```
// Ex 6: std::shared_ptr
class Widget {
public:
  // Copy Constructor
  Widget(Widget const&) = default;

  // Copy assignment operator
  Widget& operator=(Widget const&) = default;

  // Destructor
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  std::shared_ptr<Resource> ptr{};
};
```

# Move Operations

Move semantics [eg copy ctor and copy assignment operator] were added to the C++ standard with C++11. [more background information about what move semantics are and why they are important.]

We can think of copy operations and move operations as an overload set with distinct behavioral and performance characteristics. For example, if a class does not explicitly define move operations, a class will default to copy operations when a move operation is invoked by another function. In this way, we can think of copy as a generalized move.

Also, when constructing a new object from an existing object, where the existing object is no longer needed, we may choose move construct the new object, which could be orders of magnitude faster than copy construction. While this may not always be the case (depending on the type itself), the standard does guarantee that a move operation will never be slower than a coppy operation. In this way, we can thinkg of move as an optimized copy.

## Compiler Generated



```
// Ex 1: Compiler generated
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
    : idx{std::move(other.idx)}
    , str{std::move(other.str)}
    , ptr{std::move(other.ptr)} // Shallow copy!
  { }

  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = std::move(other.ptr); // Shallow copy!
    return *this;
  }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```



## Manual Implementation



```
// Ex 2: Manual implementation
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
    : idx{std::move(other.idx)}
    , str{std::move(other.str)}
    , ptr{std::move(other.ptr)} // Shallow copy!
  { }

  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = std::move(other.ptr); // Shallow copy!
    return *this;
  }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```



## Temporary Swap Idiom

Notes on move assignment operator
* Follows the temporary-swap idiom
* Implemented in terms of the move constructor
* Guards against self-assignment -> not necessary and may be removed



```
// Ex 3: Temporary-swap idiom
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
    : idx{std::move(other.idx)}
    , str{std::move(other.str)}
    , ptr{std::exchange(other.ptr, {})}
  { }

  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
    Widget tmp{std::move(other)};
    swap(tmp);
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept {
    using std::swap;
    swap(idx, other.idx);
    swap(str, other.str);
    swap(ptr, other.ptr);
  }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```

## Optimized Implementation



```
// Ex 4: Optimized implementation
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
    : idx{std::move(other.idx)}
    , str{std::move(other.str)}
    , ptr{std::exchange(other.ptr, {})}
  { }

  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
    delete ptr;
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = other.ptr; other.ptr = nullptr;
    return *this;
  }

  void swap(Widget& other) noexcept {
    using std::swap;
    swap(idx, other.idx);
    swap(str, other.str);
    swap(ptr, other.ptr);
  }

  // Destructor
  ~Widget() { delete ptr; }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};
```


## std::unique_ptr



```
// Ex 5: std::unique_ptr
class Widget {
public:
  // Move constructor
  Widget(Widget&&) noexcept = default;

  // Move assignment operator
  Widget& operator=(Widget&&) noexcept = default;

  // Destructor
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  std::unique_ptr<Resource> ptr{};
};
```

## std::shared_ptr


```
// Ex 6: std::shared_ptr
class Widget {
public:
  // Move constructor
  Widget(Widget&&) noexcept = default;

  // Move assignment operator
  Widget& operator=(Widget&&) noexcept = default;

  // Destructor
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  std::shared_ptr<Resource> ptr{};
};
```




# Rule of Three/Five/Zero

The Rule of Three, The Rule of Five, and the Rule of Zero, are names of [idioms] that refer to the nuanced relationships between the special member functions: specifically, the destructor, copy constructor, copy assinment operator, move constructor, and move assignment operator. For example, if you explicitly define [a destructor], the compiler will [implicitly the copy constructor and copy assignment operator]. Likewise, if you explicitly define [a move constructor], the compiler will [implicitly delete the copy constructor and copy assignment operator].

The full list of ... displayed below.

[ IMAGE ]

The Rule of Three, Rule of Five, and Rule of Zero are a set of guidelines that have been been established to follow about when and under what circumstances special member functions should be explicitly defined.

## Rule of Three

If a class requires a user-defined destructor, a user-defined copy constructor, or a user-defined copy assignment operator, it almost certainly requires all three. [continued]

This guideline was established long before move semantics (e.g., move constructor and move assignment operator) we added to the standard with C++11. This rule is still observed today, but now tends to be treated as a special case of the Rule of Five.

## Rule of Five

The Rule of Five refers to the relationship between special member function, where if a class requires a user-defined copy constructor, copy assignment operator, move constructor, move assignment operator, or destructor, it almost certainly requires all five.

As mentioned above, the Rule of Five was established after move semantics were added to the language with C++11. As an extension to the Rule of Three, 

## Rule of Zero

The Rule of Zero states that "if you can avoid defining default operations, do." This class is the simplest implementation and gives the cleanest semantics. [continued]
