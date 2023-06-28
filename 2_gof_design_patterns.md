# Gang of Four Design Patterns
Lorem ipsum dolor sit amet, te sit utamur pertinacia, omnium qualisque referrentur et his. Pri ad agam mutat option, te summo voluptaria qui, in simul probatus nec. Suas impetus et sit. Eum ne quas velit iisque, nec vero insolens interpretaris ei, duo magna ornatus te. In malorum corrumpit aliquando quo, in nam fugit inermis consulatu, libris minimum adolescens eos in. Nulla offendit an mei, ut nonumy aeterno pericula nam, no nec liber patrioque.

## Content

### [Creational Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_gof_design_patterns.md#creational-patterns)
* Factory Method
* Prototype
* Singleton

### [Structural Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_gof_design_patterns.md#structural-patterns)
* Adapter
* Bridge
* Decorator
* Composite
* Fascade
* Proxy

### [Behavioral Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_gof_design_patterns.md#behavioral-patterns)
* Strategy
* Template Method
* Observer
* Visitor

# Creational Patterns
Creational design patterns focus on how objects are created, aiming to find appropriate ways to create objects based on the specific situation. The conventional approach to object creation can lead to design challenges or increased complexity. Creational design patterns address this issue by providing mechanisms to manage object creation in a controlled manner.


## Factory Method

### About:
* Classification: Class Pattern
* Also Known As:  Virtual Constructor, Factory Pattern, Virtual Factory, Creation Method

### Purpose:
To provide an API for creating an object, where the factory method determines the exact class of the object that will be created

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

### About:
* Classification: Class Pattern
* Also Known As:  Clone pattern

### Purpose:
Create new objects by copying or cloning existing objects, thus avoiding the need for explicit instantiation and allowing for runtime determination of the object to be cloned

### Structure:

### Participants:

### Variations:
* N/A

### Pros:
* Reduces the need for subclassing to create new objects
* Simplifies the creation of complex objects

### Cons:
* Cloning can be complex and error-prone for objects with complex internal references
* Not suitable for scenarios where object creation involves complex logic or dependencies


## Singleton

### About:
* Classification: Object pattern
* Also Known As:  N/A

### Purpose:
To ensure that there is only a single instance of a class throughout the application, and to provide a global point of access to that instance

### Structure:

### Participants:

### Variations:
* N/A

### Pros:
* Ensures that there is only one instance of a class throughout the application
* Provides a global access point to the single instance

### Cons:
* Static initialization ordering
* Thread safety
* Hidden dependency


# Structural Patterns
Structural design patterns focus on how to compose objects and classes to form larger structures. Structural *class* patterns employ inheritance to compose interfaces or implementations. Structural *object* patterns describe approaches to compose objects to achieve new functionality.


## Adapter

## Bridge

## Decorator

## Composite

## Fascade

## Proxy


# Behavioral Patterns
Behavioral patterns are concerned with algorithms and the assignment of responsibilities between objects. They describe both the patterns of objects and classes, along with the patterns of communication between them.


## Strategy

### About:
* Classification: Object pattern
* Also Known As:  Policy (compile-time)

### Purpose:
To define a family of algorithms and encapsulate them into objects

### Structure:

### Participants:

### Variations:
* N/A

### Pros:
* Algorithms are encapsulated into objects and can be exchanged at runtime
* Adding new strategyies is as simple as implementing a new `ConcreteStrategy`
* Replaces the traditional `if/else` statements and `switch` statements

### Cons:
* Clients must know and choose the correct strategy
* The number of objects (strategies) increases heavily


## Template Method

### About:
* Classification: Object pattern
* Also Known As:  N/A

### Purpose:
To define the skeleton of an algorithm consisting of various typical steps

### Structure:

### Participants:

### Variations:
* Non-Virtual Interface (NVI)
* Hook Methods

### Pros:
* Enables inversion control
* New variations of an algorithm are easy to implement by creating new subclasses
* Common steps of the algorithm can be implemented directly in the interface class

### Cons:
* Must subclass to specialize behavior
* Even small variations of an algorithm require the creation of a new class
* The skeleton is fixed and cannot be changed (overcome by making the skeleton function virtual)


## Observer

### About:
* Classification: Object pattern
* Also Known As:  Publisher-subscriber

### Purpose:
To define 1-to-N dependencies between objects so that changes to one object cause all dependent objects to be notified

### Structure:

### Participants:

### Variations:
* Subject may send a notification, or a value
* Observer may or may not pick up the value (if necessary)

### Pros:
* New `Observers` (subscribers) can easily be added to the `Subject` (publisher)
* `Observers` can register and unregister themselves at runtime
* 3

### Cons:
* There is no guarantee of the order in which subscribers are notified
* Publishers may send a notification to a subscriber that is not alive anymore


## Visitor

### About:
* Classification: Object pattern
* Also Known As:  N/A

### Purpose:
To encapsulate an operation executed on an object within an object hierarchy

### Structure:

### Participants:

### Variations:
* N/A

### Pros:
* A new `Visitor` (operation) can easily be added to the operations hierarchy
* An operation is encapsulated in one visitor

### Cons:
* Modifying the object hierarchy with a new visitor object (eg, `ConcreteElement`) is difficult
* Widely regarded as the most complicated of the GoF patterns