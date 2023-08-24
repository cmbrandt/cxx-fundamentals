# Class Design: Special Member Functions

The special member functions are class member functions that, in certain cases, the compiler automatically generates for you. These functions include the default constructor, destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator. If a class does not define one or more of the special member functions, then the compiler may implicitly declare and define them. The compiler-generated implementations are called the default member functions, and are not generated if they are not needed.

Default special member functions can be explicitly declared using `= default`. The compiler will define the function only if needed, in the same way as if the function was not declared at all.

In some cases, the compiler may generate *delete* special member functions, where they will not be defined and therefore not callable. These cases vary for each function, and are illustrated below. To prevent the automatic generation of a special member function, it can be declared using `= delete`.

# Content

### [Rule of Three/Five/Zero](https://github.com/cmbrandt/cxx-fundamentals/blob/master/02_class_design_special.md#rule-of-threefivezero-1)
* Rule of Three
* Rule of Five
* Rule of Zero

### [Default Constructor](https://github.com/cmbrandt/cxx-fundamentals/blob/master/02_class_design_special.md#default-constructor-1)
* Availability
* Initialization

### [Destructor](https://github.com/cmbrandt/cxx-fundamentals/blob/master/02_class_design_special.md#destructor-1)
* Default Destructor
* Custom Destructor

### [Copy Operations](https://github.com/cmbrandt/cxx-fundamentals/blob/master/02_class_design_special.md#copy-operations-1)
* Compiler Generated
* Manual Implementation
* Copy-and-Swap Implementation
* Optimized Implementation
* std::unique_ptr Implementation
* std::shared_ptr Implementation

### [Move Operations](https://github.com/cmbrandt/cxx-fundamentals/blob/master/02_class_design_special.md#move-operations-1)
* Compiler Generated
* Manual Implementation
* Copy-and-Swap Implementation
* Optimized Implementation
* std::unique_ptr Implementation
* std::shared_ptr Implementation

### [Additional Resources](https://github.com/cmbrandt/cxx-fundamentals/blob/master/02_class_design_special.md#additional-resources-1)


# Rule of Three/Five/Zero

The Rule of Three, Rule of Five, and Rule of Zero are well-known conventions that refer to the dependencies between special member functions: specifically, the destructor, copy constructor, copy assinment operator, move constructor, and move assignment operator.

For example, if a class explicitly defines a copy constructor, the compiler will implicitly delete the move constructor and move assignment operator. Likewise, if a class explicitly defines a move constructor, the compiler will not declare a destructor, copy constructor, copy assignment operator, or move assignment operator.

The table below illustrates the full list of dependencies among special member functions.

<p align="center">
    <img src="https://github.com/cmbrandt/cxx-fundamentals/blob/master/img/special_member_functions_howard_hinnant2.png" alt="Image" />
</p>

The Rule of Three, Rule of Five, and Rule of Zero server as a set of guidelines to follow about when and under what circumstances special member functions should be explicitly defined.

## Rule of Three

If a class requires a user-defined destructor, a user-defined copy constructor, or a user-defined copy assignment operator, it mostly likely requires all three.

When objects of class type are copied or copy-assigned in various situations (passing/returning by value, manipulating a container, etc.), these special member functions will be called. If they are not explicitly defined by the user, they are implicitly defined by the compiler.

The implicitly-defined special member functions are typically incorrect if the class manages a resource whose handle is an object of non-class type (raw pointer, POSIX file descriptor, etc.), whose destructor does nothing, and whose copy constructor and copy assignment operator perform a shallow copy.

The Rule of Three states that if a class explicitly defines any of the destructor, copy constructor, or copy assignment operator, then it should explicitly define all three.

## Rule of Five

With the advent of C++11, the Rule of Three can be broadened to the Rule of Five. C++11 provides move semantics, which enable the efficient transfer of resources from one object to another by reducing unnecessary copies and memory allocations. These operations are performed using rvalue references with move constructors and move assignment operators.

More formally, the Rule of Five states that if a class explicitly define any of the destructor, copy constructor, copy assignment operator, move constructor, or move assignment operator, then it should explicitly define all five.

The Rule of Five can be thought of as an extension to the Rule of Three for modern C++.

## Rule of Zero

The Rule of Zero states that, when possible, classes should avoid explicitly defining any special member functions.

The fundamental concept is that a class should only define special member fuctions if it is solely dedicated to resource management. This stems from the single responsibility principle, where a class should be focused on a single concern. If a class consists solely of fundamental types (excluding raw pointers) and any resources maintained within are managed by a specialized resource mangement class, then all special member functions can be defaulted.

Overall, the Rule of Zero promotes safer, more efficient, and less error-prone code, contributing to better software quality and developer productivity. It leverages the C++ language features to handle resource management automatically, leaving developers to focus on the logic and design of their classes rather than getting bogged down with low-level resource management details.


# Default Constructor

In C++, the standard describes the default constructor for a class as a constructor that can be called with no arguments (this includes a constructor whose parameters all have default arguments). Default constructors are significant because they are invoked in certain circumstances; and therefore, in these circumstances, it is an error for a class to not have a default constructor.

## Availability

If a class has no other explicitly defined constructors, the compiler will implicitly declare and define a default constructor for it. This implicitly defined default constructor is (nearly) equivalent to an explicitly defined defined one (differing only in certain cases of initialization).

```cpp
// Ex 1: Compiler-generated default constructor available
class Widget {
public:
  // ...
};

Widget w1;   // Ok! Compiler generated
Widget w2{}; // Ok! Compiler generated
```

If constructors are explicitly defined for a class, but they are all non-default, the compiler will not implicitly define a default construcctor, leading to a situation where the class does not have a default constructor. This is the reason for a typical error, as demonstrated below.

```cpp
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

```cpp
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

```cpp
// Ex 1: Default initialization
struct Widget {
  int idx;         // Uninitialized
  std::string str; // Default (empty string)
  Resource* ptr;   // Uninitialized
};

Widget w;          // Default initialization using the default ctor
```

Value initialization chanages the [fundamental] behavior of the class, value initializing every fundamental type and default constructing each class type. Still using the compiler generated default constructor below, the `int` is initialized to zero, the `std::string` remains an empty string, and the pointer is initialized to `nullptr`.

```cpp
// Ex 2: Value initialization
struct Widget {
  int idx;         // Initialized to 0
  std::string str; // Default (empty string)
  Resource* ptr;   // Initialized to nullptr
};

Widget w{};        // Value initialization using the default ctor
```

By providing an explicit default constructor, the default constructor becomes responsible for initializing all data members of the class. Therefore, an empty default constructor will default initialize all data member of class type, but will not initialize the data members of fundamental type.

```cpp
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

```cpp
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

```cpp
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

```cpp
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

In the example below, the `Resource` pointer could be either owning or non-owning. The default destructor (either compiler generator or explicitly defined) performs no action on the pointer, which could lead to a resource leak.

```cpp
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

For this case, a custom destructor will be required to prevent a potential resource leak. Below, `delete` is called on the `Resource` pointer in the body of the custom destructor, releasing any memory associated with it and eliminating any chance of a resource leak.

After exiting the body of the destructor, the destructor for the `std::string` data member is called, and no action is performed on the `int` data member.

```cpp
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

Every class has a copy constructor and a copy assignment operator: either they are available, or they are (implicitly) deleted.

The compiler generates copy operations if (1) they are not explicitly declared, (2) no move operation is declared, and (3) all base classes and data members can be copy constructed and copy assigned. In the case that (2) and (3) are not met, the compiler implicitly deletes the copy operations.

## Compiler Generated

Below is the compiler-generated copy constructor and copy assignment operator. Both operations accept a `Widget` by reference-to-const and perform a member-wise copy operation. This is a very basic way to generate the operations, and works well for most types. However, the element-wise copy operation performs a shallow copy on the resource, meaning that the pointer is copied rather than copying the underlying object.

Note that we have included a manual destructor to to delete our resource, per our examples above.

```cpp
// Ex 1: Compiiler generated
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr} // Shallow copy!
  { } 

  // Copy assignment operator
  Widget& operator=(Widget const& other)
  {
    idx = other.idx;
    str = other.str;
    ptr = other.ptr; // Shallow copy!
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

By performing a shallow copy on the resource, multiple `Widget` instances will hold the same pointer. The implication of this is that the destructor for each instance will call delete on the same pointer, leading to undefined behavior.

## Manual Implementation

To improve upon this implementation, both the copy constructor and the copy assignment operator perform a deep copy of the resource. This eliminates the potential shared resource, and the undefined behavior associated with it.

In the copy assignment operator, before creating the deep copy to assign to the member pointer, the existing resource must be deleted before the assignment to ensure the existing resource is not leaked. This poses a problem in the case of self-assignment, where the object is copy assigned to itself. If the copy assignment operator attempts to copy the deleted resource, undefined behavior occurs and the program becomes invalid.

```cpp
// Ex 2: Manual implementation
class Widget {
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? new Resource{*other.ptr} : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other)
  {
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

Observe the number of details that need to be addressed as a result of the class explicitly managing the pointer data member. The copy constructor and copy assignment operator need to deal with `new`, `delete`, dangling pointers, and `nullpt`s.

## Copy-and-Swap Implementation

The copy assignment operator utilizes the copy-and-swap idiom. Initially, the parameter other is passed to the copy constructor, and the resultant object is stored in the local variable `tmp`. Then, the `swap` member function is invoked to efficiently exchange the current state with the contents of `tmp`. As the copy assignment operator scope concludes, the local variable `tmp` is automatically destructed.

The `swap` member function itself performs a member-wise swap for each data member. By bringing `std::swap` into scope, argument-dependent lookup (ADL) enables the appropriate implementation of `swap` for each data member, ensuring the most efficient swapping of the underlying data.

```cpp
// Ex 3: Copy-and-swap implementation
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? new Resource{*other.ptr} : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other)
  {
    Widget tmp{other};
    swap(tmp);
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept
  {
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

This implementation builds on existing functions that we already know and trust, specifically the copy constructor and the destructor. This implementation is short, safe against self-assigment, and also provides a strong exception guarantee. However, this is not the fastest possible implementation of the copy assignment operator, and could be further improved upon.

## Optimized Implementation

If both `Widget` objects, `this` and `other`, have valid pointers, then each member can be exlicitly copied. This includes the explicit copy of the resource, where each pointer is dereferenced and a copy assignment is performed. This case does not need to be checked for self-assignment, the data members resolve that themselves.

However, if one of pointers is not valid, then the `else` branch will use the copy-and-swap idiom.

```cpp
// Ex 4: Optimized implementation
class Widget {
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? new Resource{*other.ptr} : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other)
  {
    if (ptr and &other.ptr) {
      idx  = other.idx;
      str  = other.str;
      *ptr = *other.ptr; // Copy assignment of the resource
    }
    else {
      Widget tmp{other};
      swap(tmp);
    }
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept
  {
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

Note that we have been working with the Rule of Three, explicitly defining the destructor, as well as the copy constructor and copy assignment operator.

## std::unique_ptr Implementation

Per the C++ Core Guidelines, classes should not have owning pointers as data members. By switching ownership of the resource from a raw pointer to a `std::unique_ptr`, the class no longer need to worry about cleanup and the destructor can be defaulted. The copy operations must still be explicitly defined, since `std::unique_ptr` itself cannot be copied.

```cpp
// Ex 5: std::unique_ptr implementation
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr ? std::make_unique<Resource>(*other.ptr) : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other)
  {
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
  ~Widget() = default;

  void swap(Widget& other) noexcept
  {
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

## std::shared_ptr Implementation

Another option for managing the resouce is to use `std::shared_ptr`. Note that this fundamentally changes the semantics of the class, as up to this point each instance of `Widget` has owned its own resource. By using `std::shared_ptr`, instances of the class would all share the same resource, which is a significant change in behavior.

However, by using `std::shared_ptr` to own the resource, the copy constructor and copy assignment operator may be defaulted as well.

```cpp
// Ex 6: std::shared_ptr implementation
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

This is the Rule of Zero. Classes that do not require an explicit destructor, copy constructor, and copy assignment operator are much easier to work with.


# Move Operations

C++11 introduced move semantics, which encompass move constructors and move assignment operators, to enhance the language's resource management and performance. Move semantics allow efficient transfer of resources from one object to another, improving the efficiency of operations involving temporary or expiring objects.

Copy and move operations can be regarded as separate behaviors with distinct performance characteristics. If a class doesn't explicitly define move operations, it defaults to using copy operations when invoked by other functions. Consequently, copy serves as a more general form of move.

Furthermore, in scenarios where an existing object is no longer needed and a new object is being constructed, move construction can be significantly faster than copy construction, though its performance may vary depending on the object's type. Thus, move operations can be seen as an optimized form of copy, enhancing efficiency in specific contexts.

The compiler will provide default move operations if (1) they are not explicitly declared, (2) move copy operation is declared, and (3) no destructor is declared, and (4) all base classes and data members can be move constructed and move assigned. In the case that any of those conditions are not met, the compiler will explicitly delete the move operations altogether.

## Compiler Generated

Below is the compiler generated move constructor and move assignment operator. Both operations accept an rvalue reference to a non-const `Widget` and perform a member-wise move operation. This basic operation works well for most types; however, the shallow copy on the resource will prove to be problematic.

A manual destructor to delete the resource is included, inline with the examples above.

```cpp
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
  Widget& operator=(Widget&& other) noexcept
  {
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = std::move(other.ptr); // Shallow copy!
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

An similar observation about the default move operations can be made about the default copy operations. The shallow copy of the resource will lead to the destructor of each instance calling delete on the same pointer, again leading to undefined behavior.

## Manual Implementation

These issues can be resolved in both operations by exchanging the existing resource (along with deleting the original resource in the move assignment operator). However, this implementation of the move assignment operator is still not safe for the case of self-assignment.

```cpp
// Ex 2: Manual implementation
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
    : idx{std::move(other.idx)}
    , str{std::move(other.str)}
    , ptr{std::exchange(other.ptr, {})}
  { }

  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept
  {
    delete ptr;
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = std::exchange(other.ptr, {}); // Problem with self-assignment
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

By calling delete on `ptr` and deallocating the memory associated with it, then assigning it to the value of `other.ptr` ... dangling pointer.



## Temporary Swap Implementation

The temporary swap idiom implementation for the move assignment operator is safe against self-assignment. However, this implementation does not have optimal performance.

```cpp
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
  Widget& operator=(Widget&& other) noexcept
  {
    Widget tmp{std::move(other)};
    swap(tmp);
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept
  {
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

To provide a move assignment operation that has optimal performance and is safe against self-assignment, the exchange operation is replaced with a new set of operations to alleviate the dangling pointer. 

```cpp
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
  Widget& operator=(Widget&& other) noexcept
  {
    delete ptr;
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = other.ptr; other.ptr = nullptr;
    return *this;
  }

  // Destructor
  ~Widget() { delete ptr; }

  void swap(Widget& other) noexcept
  {
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

Even though this implementation may not be preferred by some since it calls delete outside of the destructor, it is both safe against self-assignment and optimized for performance.

Note that for this implementation, we have provided a manual destructor with optimized move operations and optimized copy operations. This is what we refer to as the Rule of Five.

## std::unique_ptr Implementation

By shifting ownership of the resource from a raw pointer to a `std::unique_ptr`, the manual destructor is no longer necessary (since the unique_ptr takes care of deleting things). Additionally, `std::unique_ptr` implements both move operations, so the move constructor and move assignment operator can now be defaulted along with the destructor.

```cpp
// Ex 5: std::unique_ptr
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) = default;

  // Move assignment operator
  Widget& operator=(Widget&& other) = default;

  // Destructor
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  std::unique_ptr<Resource> ptr{};
};
```

## std::shared_ptr Implementation

If the resource is now owned by a `std::shared_ptr`, the manual destructor again is no longer necessary, and both the move constructor and move assignment operator may be default.

```cpp
// Ex 6: std::shared_ptr
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) = default;

  // Move assignment operator
  Widget& operator=(Widget&& other) = default;

  // Destructor
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  std::shared_ptr<Resource> ptr{};
};
```

As was shown previously, when the resource is owned by `std::shared_ptr` the copy constructor and copy assignment operator may be defaulted as well. This effectively eliminates the need to explicitly define any of the move operations, copy operations, or destructor.

This is referred to as the Rule of Zero.

# Additional Resources

* Hinnant, H. [Inside Bloomberg]. (2016, Month Day). *Title*. [Video]. [www.youtube.com/watch?v=vLinb2fgkHk](https://www.youtube.com/watch?v=vLinb2fgkHk)
* Iglberger, K. [CppCon]. (2021, September xx). *Back To Basics: The Special Member Functions*. [Video]. [www.youtube.com/watch?v=9BM5LAvNtus](https://www.youtube.com/watch?v=9BM5LAvNtus)
* https://en.cppreference.com/w/cpp/language/rule_of_three
* 4


