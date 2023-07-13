# Class Design: Essentials
Lorem ipsum dolor sit amet, semper accumsan adolescens eum eu, ea pri modo primis volumus, dico commodo aliquip ex vim. Ad vix minim corpora patrioque, pro enim referrentur no. No quo affert oratio definitionem, sit ut enim consulatu. Eu sit reque causae.

## Content

### [Preliminaries](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#preliminaries-1)

* Access Specifiers
* Value Types
* Regular

### [Data Members](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#data-members-1)

* Representation
* Invariants

### [Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#member-functions-1)

* Constructors
* Destructor
* Accessors
* Mutators
* Implementation

### [Non-Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#non-member-functions-1)

* Equality
* Distinction
* Ordering

# Preliminaries



# Data Members

```
struct Rational {
  int num;
  int den;
};
```


```
class Rational {
public:
  int num;
  int den;
};
```



# Member Functions


## Constructors


### Parameterized Constructor

```
class Rational {
public:
  Rational(int n, int d) {
    num = n;
    den = d;
  }

private:
  int num;
  int den;
};
```

```
class Rational {
public:
  Rational(int n, int d) : num{n}, den{d} { }

private:
  int num;
  int den;
};
```

### Default Constructor

```
class Rational {
public:
  Rational() : num{0}, den{1} { }
  Rational(int n, int d) : num{n}, den{d} { }

private:
  int num;
  int den;
};
```

```
class Rational {
public:
  Rational() = default;
  Rational(int n, int d) : num{n}, den{d} { }

private:
  int num{0};
  int den{1};
};
```

## Destructor


## Copy Operations

### Copy Constructor

### Copy Assignment Operator


## Move Operations

### Move Constructor

### Move Assignment Operator


## Accessors and Mutators

### Accessors

### Mutators


## Implementation Functions

### Greatest Common Factor

### Normalize


# Non-Member Functions

## Equality

## Distinction

## Ordering
