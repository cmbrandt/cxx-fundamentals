# Design Patterns
[Design Patterns: Elements of Reusable Object-Oriented Software](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612) is an extremely well-known and highly influential book that describes software design patterns. First published in 1994, the book was written by Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides, who together are often referred to as the *Gang of Four (GoF)*.

The book illustrates 23 classic software design patterns, categorized into three types: creational patterns, structural patterns, and behavioral patterns. Of those original 23 patterns, many remain widely used today, while others have somewhat fallen out of favor. Below we will explore 13 of the original 23 patterns that are most likely to appear in modern code bases.


## Content

### [Creational Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_design_patterns.md#creational-patterns)
* Factory Method
* Prototype
* Singleton

### [Structural Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_design_patterns.md#structural-patterns)
* Adapter
* Decorator
* Proxy
* Bridge
* Fascade
* Composite

### [Behavioral Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_design_patterns.md#behavioral-patterns)
* Strategy
* Template Method
* Observer
* Visitor

# Creational Patterns
Creational design patterns focus on how objects are created, aiming to find appropriate ways to create objects based on the specific situation. The conventional approach to object creation can lead to design challenges or increased complexity. Creational design patterns address this issue by providing mechanisms to manage object creation in a controlled manner.


## Factory Method

### About:
* **Classification:** Class pattern
* **Also Known As:**  Virtual Constructor, Factory Pattern, Virtual Factory, Creation Method

### Purpose:
To provide an API for creating objects, where the factory method determines the exact class of the objects that will be created

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/factory_method.png" alt="Image" />
</p>

### Participants:
`Product`
* Defines the interface of objects the factory method creates

`ConcreteProduct`
* Implements the Product interface

`Creator`
* Defines the factory method, which returns an object of type Product

### Variations:
* Class hierarchy where subclasses implement factory method overrides
* Concrete class that implements a parameterized factory method
* Parameterized free function factory method

### Pros:
* Familiarity (used in most well-designed OO systems)
* Create different subclasses in a uniform way
* Decouples object creation and their subsequent use

### Cons:
* Class proliferation (when using a class hierarchy)
* Runtime overhead


## Prototype

### About:
* **Classification:** Class pattern
* **Also Known As:**  Clone Pattern

### Purpose:
Create new objects by cloning existing objects, providing a way to create instances without explicitly specifying their classes

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/prototype.png" alt="Image" />
</p>

### Participants:
`Prototype`
* Declares an interface for cloning itself

`ConcretePrototype`
* Implements an operation for cloning itself

`Client`
* Creates a new object by asking a prototype to clone itself

### Pros:
* Reduces the need for subclassing to create new objects
* Simplifies the creation of complex objects

### Cons:
* Cloning can be complex and error-prone for objects with complex internal references
* Not suitable for scenarios where object creation involves complex logic or dependencies


## Singleton

### About:
* **Classification:** Object pattern
* **Also Known As:** N/A

### Purpose:
To ensure that there is only a single instance of a class throughout the application, and to provide a global point of access to that instance

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/singleton.png" alt="Image" />
</p>

### Participants:
`Singleton`
* Defines a static get_instance operation that allows clients to access its unique instance

### Pros:
* Providing global access to shared resources or services
* Centralized control

### Cons:
* Static initialization ordering
* Thread safety
* Global state


# Structural Patterns
Structural design patterns focus on how to compose objects and classes to form larger structures. Structural *class* patterns employ inheritance to compose interfaces or implementations. Structural *object* patterns describe approaches to compose objects to achieve new functionality.


## Adapter


### About:
* **Classification:** xxx pattern
* **Also Known As:** 

### Purpose:
qewr

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/adapter_class.png" alt="Image" />
</p>

### Participants:
`xxx`
* asdf

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Decorator


### About:
* **Classification:** xxx pattern
* **Also Known As:** 

### Purpose:
qewr

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/bridge.png" alt="Image" />
</p>

### Participants:
`xxx`
* asdf

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Proxy


### About:
* **Classification:** xxx pattern
* **Also Known As:** 

### Purpose:
qewr

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/proxy.png" alt="Image" />
</p>

### Participants:
`xxx`
* asdf

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Bridge


### About:
* **Classification:** xxx pattern
* **Also Known As:** 

### Purpose:
qewr

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/bridge.png" alt="Image" />
</p>

### Participants:
`xxx`
* asdf

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Fascade


### About:
* **Classification:** xxx pattern
* **Also Known As:** 

### Purpose:
qewr

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/fascade.png" alt="Image" />
</p>

### Participants:
`xxx`
* asdf

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Composite


### About:
* **Classification:** xxx pattern
* **Also Known As:** 

### Purpose:
qewr

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/composite.png" alt="Image" />
</p>

### Participants:
`xxx`
* asdf

### Pros:
* 1
* 2

### Cons:
* 1
* 2


# Behavioral Patterns
Behavioral patterns are concerned with algorithms and the assignment of responsibilities between objects. They describe both the patterns of objects and classes, along with the patterns of communication between them.


## Strategy

### About:
* **Classification:** Object pattern
* **Also Known As:**  Policy

### Purpose:
Define a family of algorithms, encapsulate each one with a class, and make them interchangeable

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/strategy.png" alt="Image" />
</p>

### Participants:
`Strategy`
* Declares an interface common to all concrete stategies

`ConcreteStrategy`
* Implements the algorithm using the Strategy interface

`Context`
* Configured with a ConcreteStrategy object
* Maintains a reference to a Strategy object

### Variations:
* Policy (using templates)

### Pros:
* Algorithms are encapsulated into objects and can be exchanged at runtime
* Adding new strategies is as simple as implementing a new ConcreteStrategy
* Replaces the traditional if/else and switch statements

### Cons:
* Clients must know and choose the correct strategy
* Increased number of classes
* Increased runtime overhead


## Template Method

### About:
* **Classification:** Object pattern
* **Also Known As:**  N/A

### Purpose:
Define the skeleton of an algorithm in an operation, deferring some steps to subclasses

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/template_method.png" alt="Image" />
</p>

### Participants:
`AbstractClass`
* Implements the template method defining the skeleton of an algorithm
* Declares abstract primitive operations that concrete subsclasses define to implement steps of an algorihtm

`ConcreteClass`
* Implements the primitive operations to carry out subclass-specific steps of the algorithm

### Variations:
* Non-Virtual Interface (NVI)

### Pros:
* Promotes code reuse by providing a common skeleton or template for algorithms
* New variations of an algorithm are easy to implement by creating new subclasses
* Common steps of the algorithm can be implemented directly in the interface class

### Cons:
* Relies on inheritance to reuse and customize behavior
* Even small variations of an algorithm require the creation of a new class
* The skeleton is fixed and cannot be changed (overcome by making the skeleton function virtual)


## Observer

### About:
* **Classification:** Object pattern
* **Also Known As:**  Publisher-Subscriber

### Purpose:
Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/observer.png" alt="Image" />
</p>

### Participants:
`Subject`
* Provides an interface for attaching and detaching Observer objects
* Any number of Observers may observer a subject

`ConcreteSubject`
* Stores state of interest to ConcreteObserver objects
* Sends a notification to its observers when its state changes

`Observer`
* Defines an updating inteface for objects that should be notified of changes in a subject

`ConcreteObserver`
* Maintains a reference to a ConcreteSubject object
* Stores state that should stay consistent with the subject's
* Implements the Observer updating interface to keep its state consistenent with the subject's

### Variations:
* Subject may send a notification or a value
* Observer may or may not pick up the value

### Pros:
* New Observers (subscribers) can easily be added to the Subject (publisher)
* Observers can register and unregister themselves at runtime

### Cons:
* There is no guarantee of the order in which subscribers are notified
* Publishers may send a notification to a subscriber that is not alive anymore


## Visitor

### About:
* **Classification:** Object pattern
* **Also Known As:**  N/A

### Purpose:
Separates algorithms from the objects on which they operatate, where new operations can be added to the existing object structures without modifying the structures

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/visitor.png" alt="Image" />
</p>

### Participants:
`Visitor` (NodeVisitor)
* Declares a visit operation for each class of ConcreteElement in the object structure
* The operation name and signature identifies the class that sends the visit request to the visitor
* The visitor then determines the concrete class of the element being visited
* The visitor can access the element directly through its particular interface

`ConcreteVisitor` (TypeCheckingVisitor)
* Implements each operation declared by Visitor
* Provides the context for the algorithm and stores its local state, which often accumulates results during the traversal of the structure

`Element` (Node)
* Defines an accept operation that takes a visitor as an argument

`ConcreteElement` (AssignmentNode, VariableRefNode)
* Implements an accept operation that takes a visitor as an argument

### Variations:
* std::variant with std::visit
* std::variant with Overload pattern

### Pros:
* Operations hierarchy and object hierarchy are (relatively) independent
* A new ConcreteVisitor can easily be added to the operations hierarchy

### Cons:
* Widely regarded as the most complicated of the GoF patterns
* Modifying the object hierarchy with a new ConcreteElement is difficult
