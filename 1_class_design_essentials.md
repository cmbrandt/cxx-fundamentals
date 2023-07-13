# Class Design: Essentials
Lorem ipsum dolor sit amet, semper accumsan adolescens eum eu, ea pri modo primis volumus, dico commodo aliquip ex vim. Ad vix minim corpora patrioque, pro enim referrentur no. No quo affert oratio definitionem, sit ut enim consulatu. Eu sit reque causae.

## Content

### [Preliminaries](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#preliminaries-1)

* Access Specifiers
* Value Types
* Regular Types

### [Data Members](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#data-members-1)

* Representation
* Invariants

### [Member Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#member-functions-1)

* [Constructors](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#constructors)
* [Destructor](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#destructor)
* [Copy Operations](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#copy-operations)
* [Move Operations](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#move-operations)
* [Accessors and Mutators](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#accessors-and-mutators)
* [Implementation Functions](https://github.com/cmbrandt/cxx-fundamentals/blob/master/1_class_design_essentials.md#implementation-functions)

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

### Default Constructor

```
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

```
class Rational {
public:
  Rational() : num{0}, den{1} { }

private:
  int num;
  int den;
};
```

```
class Rational {
public:
  Rational() = default;

private:
  int num{0};
  int den{1};
};
```

### Parameterized Constructors

```
Rational::Rational(int n, int d) : num{n}, den{d} { }
```

```
explicit Rational::Rational(int n) : num{n} { }
```


## Destructor

```
~Rational::Rational() { };
```

```
~Rational() = default;
```

## Copy Operations


### Copy Constructor

```
Rational::Rational(Rational const& other) {
  num = other.num;
  den = other.den;
}
```

```
Rational::Rational(Rational const& other) {
: num{other.num}, den{other.den} { }
```

### Copy Assignment Operator

```
Rational& Rational::operator=(Rational const& other) {
  num = other.num;
  den = other.den;
}
```


## Move Operations

### Move Constructor

```
Rational::Rational(Rational&& other) {
: num{std::move(other.num)} , den{std::move(other.den)} { }
```

### Move Assignment Operator

```
Rational& Rational::operator=(Rational&& other) {
  num = std::move(other.num);
  den = std::move(other.den);
}
```


## Accessors and Mutators

### Accessors

```
int Rational::get_num() const { return num; }
int Rational::get_den() const { return den; }
```

### Mutators

```
void Rational::set_num(int n) { num = n; }
void Rational::set_den(int d) { den = d; }
```


## Implementation Functions

### Greatest Common Factor

```
int Rational::gcf() {
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

```
void Rational::normalize() {
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

```
bool operator==(Rational const& lhs, Rational const& rhs) {
  //
  // implementation details
  //
}
```


## Distinction

```
bool operator!=(Rational const& lhs, Rational const& rhs) {
  return !operator==(lhs, rhs);
}
```


## Ordering

```
bool operator<(Rational const& lhs, Rational const& rhs) {
  return !operator<(lhs, rhs);
}
```

```
bool operator>(Rational const& lhs, Rational const& rhs) {
  return operator<(rhs, lhs);
}
```

```
bool operator<=(Rational const& lhs, Rational const& rhs) {
  return !operator>(lhs, rhs);
}
```

```
bool operator>=(Rational const& lhs, Rational const& rhs) {
  return !operator<(lhs, rhs);
}
```

TODO: `operator<=>`
