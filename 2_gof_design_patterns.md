# Gang of Four Design Patterns

## Subsections:
* Creational Patterns
* Structural Patterns
* Behavioral Patterns


# Creational Patterns
Pro clita aliquid tibique ut, sed porro apeirian in, libris efficiendi contentiones an qui. Nullam causae partiendo te eos, porro labitur signiferumque ut nam. Ad sit quaerendum conclusionemque, in labore oportere voluptatibus pri. Idque molestiae pri ad.


## Factory Method

### About:
* Form: Class Pattern
* AKA:  Virtual Constructor, Factory Pattern, Virtual Factory, Creation Method

### Purpose:
To provide an API for creating an object, where the factory method detemrines the exact class of the object that will be created

### Structure:

### Participants:

### Variations:
* Distinct class that implements that factory method
* Free function (parameterized via `enum`, `std::string`, or `int`)
* Class member function (typically via `std::shared_ptr`)

### Pros:
* Familiarity (used in pretty much every well-designed OO system)
* Enables us to create differnt subclasses in a uniform way
* Decouples object creation and their subsequent use

### Cons:
* Increased complexity
* Lack of extensibility
* Runtime overhead

## Prototype

## Singleton


# Structural Patterns


## Adapter

## Bridge

## Decorator

## Composite

## Fascade

## Proxy


# Behavioral Patterns


## Observer

## Visitor

## Template Method

## Strategy
