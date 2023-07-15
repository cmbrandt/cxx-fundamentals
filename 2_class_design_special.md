# Class Design: Special Member Functions

The *special member functions* are class member functions that, in certain cases, the compiler automatically generates for you. These functions include the default constructor, destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator. If a class does not define one or more of the special member functions, then the compiler may implicitly declare and define them. The compiler-generated implementations are called the *default* member functions, and are not generated if they are not needed.

Default special member functions can be explicitly declared using `= default`. The compiler will define the function only if needed, in the same way as if the function was not declared at all.

In some cases, the compiler may generate *delete* special member functions, where they will not be defined and therefore not callable. These cases vary for each function, and are illustrated below. To prevent the automatic generation of a special member function, it can be declared using `= delete`.

## Content

### [Default Constructor](https://github.com/cmbrandt/cxx-fundamentals/blob/master/2_class_design_special.md#default-constructor-1)
* Availability
* Initialization

### [Destructor](https://github.com/cmbrandt/cxx-fundamentals/blob/master/2_class_design_special.md#destructor-1)
* Default Destructor
* Custom Destructor

### [Copy Operations](https://github.com/cmbrandt/cxx-fundamentals/blob/master/2_class_design_special.md#copy-operations-1)
* Compiler Generated
* Manual Implementation
* Temporary Swap Implementation
* Optimized Implementation
* std::unique_ptr Implementation
* std::shared_ptr Implementation

### [Move Operations](https://github.com/cmbrandt/cxx-fundamentals/blob/master/2_class_design_special.md#move-operations-1)
* Compiler Generated
* Manual Implementation
* Temporary Swap Implementation
* Optimized Implementation
* std::unique_ptr Implementation
* std::shared_ptr Implementation

### [Rule of Three/Five/Zero](https://github.com/cmbrandt/cxx-fundamentals/blob/master/2_class_design_special.md#rule-of-threefivezero-1)
* Rule of Three
* Rule of Five
* Rule of Zero


# Default Constructor

In C++, the standard describes the default constructor for a class as a constructor that can be called with no arguments (this includes a constructor whose parameters all have default arguments). Default constructors are significant because they are invoked in certain circumstances; and therefore, in these circumstances, it is an error for a class to not have a default constructor.

## Availability

If a class has no other explicitly defined constructors, the compiler will implicitly declare and define a default constructor for it. This implicitly defined default constructor is (nearly) equivalent to an explicitly defined defined one (differing only in certain cases of initialization).

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

## Initialization

The task of the compiler generated default constructor is to initialize an instance of its class with default values. When no explicit data member initializer is provided, the compiler will default initialize all data member of class type, but will not initialize the data members of fundamental type.

In the example below, `int` is representative of a fundamental type, `std::string` is representative of a class type, and the pointer the class type `Resource` is treated by the compiler as a fundamental type. Using default initialization, we see that the `std::string` is initialized (to an empty string), while the `int` and the pointer are uninitialized.

```
// Ex 1: Default initialization
struct Widget {
  int idx;         // Uninitialized
  std::string str; // Default (empty string)
  Resource* ptr;   // Uninitialized
};

Widget w;          // Default initialization using the default ctor
```

Value initialization chanages the fundamental behavior of the class, value initializing every fundamental type and default constructing each class type. Still using the compiler generated default constructor below, the `int` is initialized to zero, the `std::string` remains an empty string, and the pointer is initialized to `nullptr`.

```
// Ex 2: Value initialization
struct Widget {
  int idx;         // Initialized to 0
  std::string str; // Default (empty string)
  Resource* ptr;   // Initialized to nullptr
};

Widget w{};        // Value initialization using the default ctor
```

By providing an explicit default constructor, the default constructor becomes responsible for initializing all data members of the class. Therefore, an empty default constructor will default initialize all data member of class type, but will not initialize the data members of fundamental type.

```
// Ex 3: Explicit empty default constructor with value initialization
struct Widget {
  Widget() { }     // Explicit empty default constructor

  int idx;         // Uninitialized
  std::string str; // Default (empty string)
  Resource* ptr;   // Uninitialized
};

Widget w{};        // Value initialization with explicit empty default ctor
```

A better option is to ask the compiler to generate the default constuctor by declaring it with `= default`. In doing so, fundamental type data members are value initialized and class type data members are default initialized. Asking for the compiler generated default constructor using `= default` may also provide bonus effects (e.g., `noexcept`).

```
// Ex 4: Defaulted constructor with value initialization
struct Widget {
  Widget() = default; // Defaulted consructor

  int idx;            // Initialized to 0
  std::string str;    // Default (empty string)
  Resource* ptr;      // Initialized to nullptr
};

Widget w{};           // Value initialization with defaulted ctor
```


# Destructor

The primary responsibility of a destructor is to ensure proper cleanup and deallocation of resources held by an object. It is a member function that is invoked automatically when the object goes out of scope or it explicitly destroyed by a call to `delete`.

The destructor for a class first executes all statements and expressions in its body, then calls the destructor for each non-static data members of class type, for all non-virtual direct base classes, and (if the class is the most derived class in a hierarchy), for each virtual base class. The default destructor does not perform any action for fundamental types. 

When a destructor is not explicitly declared or defined, the compiler will provide a default constructor, which is sufficient for many classes. A custom destructor is only necessary when the class stores a handle to system resources that need to be released, or pointers that own the memory they point to.

## Default Destructor

The default constructor consists of an empty body, meaning it does not contain any explicit code. In the example below, the compiler generated default destructor calls the destructor for the `std::string` data member, and performs no action on the `int` data member.

```
// Ex 1: Compiler-generated destructor available
class Widget {
public:
  // ...

private:
  int idx;         // Fundamental type
  std::string str; // Class type
};
```

When a destructor is explicitly declared but not defined, the compiler will provide a default destructor for the class.

```
// Ex 2: Explicit declaration of destructor
class Widget {
public:
  ~Widget();       // Explicit declaration of dtor
  // ...           // Compiler provides default dtor

private:
  int idx;         // Fundamental type
  std::string str; // Class type
};
```

## Custom Destructor

In the example below, the `Resource` pointer could be either owning or non-owning. In this situation, the default destructor (either compiler generator or explicitly defined) performs no action on the pointer, which could lead to a resource leak.

```
// Ex 3: Explicit defintion of default destructor
class Widget {
public:
  // ...
  ~Widget()        // Default destructor destroys the std::string
  {                // member but does performs no action on the
                   // int and pointer members...
  }                // Potential resource leak!

private:
  int idx;         // Fundamental type
  std::string str; // Class type
  Resource* ptr;   // Possible resource
};
```

For this case, a custom destructor will be required to prevent a potential resource leak. In the example below, `delete` is called on the `Resource` pointer in the body of the destructor, releasing any memory associated with it and eliminating any chance of a resource leak.

After exiting the body of the destructor, the destructor for the `std::string` data member is called, and no action is performed on the `int` data member.

```
// Ex 4: Explicit defintion of destructor to delete pointer
class Widget {
public:
  // ...
  ~Widget()        // Custom destructor deletes the pointer member
  {                // before destroying the std::string member,
    delete ptr;    // no action performed on the int member...
  }                // No resource leak!

private:
  int idx;         // Fundamental type
  std::string str; // Class type
  Resource* ptr;   // Possible resource
};
```

Typically, destructors do not pose a problem. However, they are a sign that other special member functions need to be explicitly defined, such as copy operations and move operations.


# Copy Operations

asdf asdf  asdf as fasd fas 

## Compiler Generated

Below is the compiler-generated copy constructor and copy assignment operator. The default operations perform element-by-element copy. Note that this performs a shallow copy of our `Resource` pointer.

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
