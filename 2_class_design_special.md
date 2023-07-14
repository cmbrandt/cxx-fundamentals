# Class Design: Special Member Functions
Lorem ipsum dolor sit amet, semper accumsan adolescens eum eu, ea pri modo primis volumus, dico commodo aliquip ex vim. Ad vix minim corpora patrioque, pro enim referrentur no. No quo affert oratio definitionem, sit ut enim consulatu. Eu sit reque causae.

## Content

### [Default Constructor](https://github.com/cmbrandt/modern-cxx-seminar/edit/master/1_class_design.md#fundamentals-1)
* Compiler Generated
* ...

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

[description of the default constructor]

The compiler generates a default constructor if you have no other construcctor in your class.

```
// Compiler-generated default constructor available
class Widget {
public:
  // ...
};

Widget w1;   // Ok! Compiler generated
Widget w2{}; // Ok! Compiler generated
```

However, if you have any other construtor defined in your class, then the compiler does not generate a default constructor.

```
// No compiler-generated default constructor available
class Widget {
public:
  Widget(Widget const&); // explicit declaration of copy ctor
  // ...                 // default ctor no longer available
};

Widget w1;   // Error! No default constructor
Widget w2{}; // Error! No default constructor
```

The compiler is not able to generate a default constructor if any data member or any base class is not default constructable

```
// No compiler-generated default constructor available
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


# Copy Operations


# Move Operations


# Rule of Zero/Five

## Rule of Zero

## Rule of Five
