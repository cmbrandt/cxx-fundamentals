# Class Design: Special Member Functions
Lorem ipsum dolor sit amet, semper accumsan adolescens eum eu, ea pri modo primis volumus, dico commodo aliquip ex vim. Ad vix minim corpora patrioque, pro enim referrentur no. No quo affert oratio definitionem, sit ut enim consulatu. Eu sit reque causae.

## Content

### [Default Constructor](https://github.com/cmbrandt/modern-cxx-seminar/edit/master/1_class_design.md#fundamentals-1)
* Data Member Initialization
* Default Constructor Availability

### [Destructor](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#special-member-functions)
* Compiler Generated
* ...

### [Copy Operations](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#additional-class-operations)
* Compiler Generated
* Temporary Swap
* Optimized
* std::unique_ptr
* std::shared_ptr

### [Move Operations](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#class-hierarchies)
* Compiler Generated
* Temporary Swap
* Optimized
* std::unique_ptr
* std::shared_ptr

### [Rule of Zero/Five](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#rule-of-zerofive)
* Rule of Zero
* Rule of Five


# Default Constructor


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
  Widget() { }
  int idx;         // Uninitialized
  std::string str; // Default (empty string)
  Resource* ptr;   // Uninitialized
};

Widget w{};        // Value initialization with no default ctor
```

The `= default` allows the compiler to generate the default constructor. `= default` counts as definition, plus may provide additional benefits (include `noexcept`).

```
// Ex 4: Declared default constructor with value initialization
struct Widget {
  Widget() = default;
  int idx;         // Initialized to 0
  std::string str; // Default (empty string)
  Resource* ptr;   // Initialized to nullptr
};

Widget w{};        // Value initialization with declared default ctor
```


## Default Constructor Availability

[*description of the default constructor*]

The compiler generates a default constructor if you have no other constructor in your class.

```
// Ex 1: Compiler-generated default constructor available
class Widget {
public:
  // ...
};

Widget w1;   // Ok! Compiler generated
Widget w2{}; // Ok! Compiler generated
```

However, if you have any other constructor defined in your class, then the compiler does not generate a default constructor.

```
// Ex 2: No compiler-generated default constructor available
class Widget {
public:
  Widget(Widget const&); // explicit declaration of copy ctor
  // ...                 // default ctor no longer available
};

Widget w1;   // Error! No default constructor
Widget w2{}; // Error! No default constructor
```

Additionally, the compiler is not able to generate a default constructor if any data member or any base class is not default constructable.

```
// Ex 3: No compiler-generated default constructor available
class Widget {
public:
  // ...
private:
  NotDefaultConstructable member; // Data member without default ctor
};

Widget w1;   // Error! No default constructor
Widget w2{}; // Error! No default constructor
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
  ~Widget()        // The compiler generated destructor destroys the
  {                // std::string data member, but does not perform
    delete ptr;    // any special action for the integer and pointer...
  }                // Potential resource leak!

private:
  int idx;         // Fundamental type
  std::string str; // Class (user-defined) type
  Resource* ptr;   // Possible resource
};
```


# Copy Operations

## Compiler Generated

```
// Ex 1: ...
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
  : idx{other.idx}
  , str{other.str}
  , ptr{other.ptr} { }                     // Shallow copy!

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    idx = other.idx;
    str = other.str;
    ptr = other.ptr;                       // Shallow copy!
    return *this;
  }

  // Note: default dtor -> possible resource leak!

private:
  int idx{};
  std::string str{};
  Resource* ptr{nullptr};
};
```

## Temporary Swap Idiom


Notes on copy assignment operator
* Follows the temporary-swap idiom
* Implemented in terms of the copy constructor
* Guards against self-assignment -> not necessary and may be removed


```
// Ex 2: ...
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
  : idx{other.idx}
  , str{other.str}
  , ptr{other.ptr ? new Resource{*other.ptr} : nullptr} { }

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    if (this == &other)
      return *this;
    Widget tmp{other};
    swap(tmp);
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
  Resource* ptr{nullptr};
};
```

## Optimized Implementation

```
// Ex 3: ...
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
  : idx{other.idx}
  , str{other.str}
  , ptr{other.ptr ? new Resource{*other.ptr} : nullptr} { }

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

private:
  int idx{};
  std::string str{};
  Resource* ptr{nullptr};
};
```


## std::unique_ptr

```
// Ex 4: ...
class Widget {
public:
  // Copy constructor
  Widget(Widget const& other)
  : idx{other.idx}
  , str{other.str}
  , ptr{other.ptr ? std::make_unique<Resource>(*other.ptr) : nullptr} { }

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
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  Resource* ptr{nullptr};
};
```

## std::shared_ptr


```
// Ex 5: ...
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
  Resource* ptr{nullptr};
};
```

# Move Operations

## Compiler Generated

```
// Ex 1: ...
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
  : idx{std::move(other.idx)}
  , str{std::move(other.str)}
  , ptr{std::move(other.ptr)} { } // Shallow copy!
  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
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
  Resource* ptr{nullptr};
};
```

## Temporary Swap Idiom

Notes on move assignment operator
* Follows the temporary-swap idiom
* Implemented in terms of the move constructor
* Guards against self-assignment -> not necessary and may be removed

```
// Ex 2: ...
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
  : idx{std::move(other.idx)}
  , str{std::move(other.str)}
  , ptr{std::exchange(other.ptr, {})} { }
  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
    if (this == &other)
      return *this;
    Widget tmp{std::move(other)};
    swap(tmp);
    return *this;
  }
  // Destructor
  ~Widget() { delete ptr; }

private:
  int idx{};
  std::string str{};
  Resource* ptr{nullptr};
};
```

## Optimized Implementation

```
// Ex 3: ...
class Widget {
public:
  // Move constructor
  Widget(Widget&& other) noexcept
  : idx{std::move(other.idx)}
  , str{std::move(other.str)}
  , ptr{std::exchange(other.ptr, {})} { }
  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
    delete ptr;
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = other.ptr; other.ptr = nullptr;
    return *this;
  }
  // Destructor
  ~Widget() { delete ptr; }

private:
  int idx{};
  std::string str{};
  Resource* ptr{nullptr};
};
```


## std::unique_ptr

```
// Ex 4: ...
class Widget {
public:
  // Move Constructor
  Widget(Widget&&) = default;
  // Move assignment operator
  Widget& operator=(Widget&&) = default;
  // Destructor
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  std::unique_ptr<Resource> ptr{nullptr};
};
```

## std::shared_ptr


```
// Ex 5: ...
class Widget {
public:
  // Move Constructor
  Widget(Widget&&) = default;
  // Move assignment operator
  Widget& operator=(Widget&&) = default;
  // Destructor
  ~Widget() = default;

private:
  int idx{};
  std::string str{};
  std::shared_ptr<Resource> ptr{nullptr};
};
```




# Rule of Zero/Five

## Rule of Zero

## Rule of Five
