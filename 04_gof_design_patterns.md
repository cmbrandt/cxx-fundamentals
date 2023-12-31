# Design Patterns
[Design Patterns: Elements of Reusable Object-Oriented Software](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612) is an extremely well-known and highly influential book that describes software design patterns. First published in 1994, the book was written by Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides, who together are often referred to as the *Gang of Four (GoF)*.

The book illustrates 23 classic software design patterns, categorized into three types: creational patterns, structural patterns, and behavioral patterns. Of those original 23 patterns, many remain widely used today, while others have somewhat fallen out of favor. Below we will explore 13 of the original 23 patterns that are most likely to appear in modern code bases.


## Content

### [Creational Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/4_design_patterns.md#creational-patterns-1)
* Factory Method
* Prototype
* Singleton

### [Structural Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/4_design_patterns.md#structural-patterns-1)
* Adapter
* Decorator
* Proxy
* Bridge
* Facade
* Composite

### [Behavioral Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/4_design_patterns.md#behavioral-patterns-1)
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
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_factory_method.png" alt="Image" />
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
* **Classification:** Object pattern
* **Also Known As:**  Clone Pattern

### Purpose:
Create new objects by cloning existing objects, providing a way to create instances without explicitly specifying their classes

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_prototype.png" alt="Image" />
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
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_singleton.png" alt="Image" />
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
* **Classification:** Both Class and Object pattern
* **Also Known As:** Wrapper

### Purpose:
Converts the interface of one class into another interface that clients expect, enabling them to interact seamlessly 

### Structure:
Adapter Class
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_adapter_class.png" alt="Image" />
</p>

Adapter Object
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_adapter_object.png" alt="Image" />
</p>

### Participants:
`Target`
* Defines the domain-specific interface that Client uses

`Client`
* Collaborates with objets conforming to the Target interface

`Adaptee`
* Defines an existing interface that needs adapting

`Adapter`
* Adapts the interface of Adaptee to the Target interface

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Decorator


### About:
* **Classification:** Object pattern
* **Also Known As:** Wrapper

### Purpose:
Dynamically extend or modify an object with responsibilities

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_decorator.png" alt="Image" />
</p>

### Participants:
`Component`
* Defines the interface for objects that can have responsibilities added to them dynamically

`ConcreteComponent`
* Defines an object to which additional responsibilities can be attached

`Decorator`
* Maintains a reference to a Component object and defines an interface that conforms to Component's itnerface

`ConcreteDecorator`
* Adds responsibilities to the component

### Pros:
* Provides a flexible alternative to subclassing for extending functionality
* 2

### Cons:
* 1
* 2


## Proxy


### About:
* **Classification:** Object pattern
* **Also Known As:** Surrogate

### Purpose:
Provide a surrogate, or placeholder, for another object to control access to it

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_proxy.png" alt="Image" />
</p>

### Participants:
`Proxy`
* qwert qewr qewt 

`Subject`
* Defines the common interface for RealSubject and Proxy so that a Proxy can be used anywhere a RealSubject is expected

`RealSubject`
* Defines the real object that the proxy represents

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Bridge


### About:
* **Classification:** Object pattern
* **Also Known As:** Handle/Body

### Purpose:
Decouples the interface from the implementation, separating them into two hierarchies and enabling them to vary independently

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_bridge.png" alt="Image" />
</p>

### Participants:
`Abstraction`
* Defines the abstraction's interface
* Maintains a reference to an object of type Impementor

`RefinedAbstraction`
* Extends the interface defined by Abstraction

`Implementor`
* Defines the inteface for implementation classes (note that this interface doesn't have to conrrespond exactly to Abstraction's interface)

`ConcreteImplementor`
* Implements the Implementor interface and defines its concrete implementation

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Facade


### About:
* **Classification:** Object pattern
* **Also Known As:** N/A

### Purpose:
Provide a simplified interface to a library, a framework, or any other complex set of classes, making them easier to use

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_facade.png" alt="Image" />
</p>

### Participants:
`Facade`
* Knows which subsystem classes are responsible for a request
* Delegates client requests to appropriate subsytem objects

Subsystem classes
* Implement subsystem functionality
* Handle work assigned by the Facade object
* Have no knowledge of the facade; that is (e.g., they maintain no references to it)

### Pros:
* 1
* 2

### Cons:
* 1
* 2


## Composite


### About:
* **Classification:** Object pattern
* **Also Known As:** N/A

### Purpose:
Provide a way to represent complex structures of objects in a unified manner, so that clients can treat individual objects and groups of objects the same without having to distinguish between them

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_composite.png" alt="Image" />
</p>

### Participants:
`Component`
* Declares the interface for objects in the composition
* Implements default behavior for the interface common to all classes, as appropriate
* Declaring an interface for accessing and managing its child components

`Leaf`
* Represents leaf objects in the composition
* Has no children
* Defines behavior for primitive objects in the composition

`Composite`
* Defines behavior for components having children
* Stores child components
* Implements child-releated operations in the Component interface

`Client`
* Manipulates objects in the composition through the Component interface

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
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_strategy.png" alt="Image" />
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
* **Classification:** Class pattern
* **Also Known As:**  N/A

### Purpose:
Define the skeleton of an algorithm in an operation, deferring some steps to subclasses

### Structure:
<p align="center">
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_template_method.png" alt="Image" />
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
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_observer.png" alt="Image" />
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
    <img src="https://github.com/cmbrandt/modern-cxx-seminar/blob/master/img/design_patterns_visitor.png" alt="Image" />
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
