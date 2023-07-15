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
* Using std::unique_ptr
* Using std::shared_ptr

### [Move Operations](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/1_class_design.md#class-hierarchies)
* Compiler
* Temporary Swap
* Optimized
* Using std::unique_ptr
* Using std::shared_ptr

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
  ~Widget(); // explicit declaration of dtor
  // ...     // compiler does not generate dtor
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
  }                // potential resource leak!

private:
  int idx;         // fundamental type
  std::string str; // class (user-defined) type
  Resource* ptr;   // possible resource
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
  }                // potential resource leak!

private:
  int idx;         // fundamental type
  std::string str; // class (user-defined) type
  Resource* ptr;   // possible resource
};
```


# Copy Operations


# Move Operations


# Rule of Zero/Five

## Rule of Zero

## Rule of Five
