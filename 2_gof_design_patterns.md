# Gang of Four Design Patterns
Lorem ipsum dolor sit amet, te sit utamur pertinacia, omnium qualisque referrentur et his. Pri ad agam mutat option, te summo voluptaria qui, in simul probatus nec. Suas impetus et sit. Eum ne quas velit iisque, nec vero insolens interpretaris ei, duo magna ornatus te. In malorum corrumpit aliquando quo, in nam fugit inermis consulatu, libris minimum adolescens eos in. Nulla offendit an mei, ut nonumy aeterno pericula nam, no nec liber patrioque.

## Content
* [Creational Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_gof_design_patterns.md#creational-patterns)
* [Structural Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_gof_design_patterns.md#structural-patterns)
* [Behavioral Patterns](https://github.com/cmbrandt/modern-cxx-seminar/blob/master/2_gof_design_patterns.md#behavioral-patterns)


# Creational Patterns
Ei diam eros verterem his, sit veri clita deleniti ei. Est an probo adhuc euripidis, alia vulputate mei ut. Sea at phaedrum laboramus, ea vim ipsum insolens mnesarchum, usu ex malis habemus. Soluta ridens causae ei sea, per porro postea inciderint ea, nisl debitis erroribus ea his.


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
Duis fierent sit in. Sanctus argumentum complectitur et duo, ocurreret deseruisse an vim. Consetetur quaerendum sit cu. Ad exerci facilisi dignissim his. Reque saperet cu vis, ei sit errem iriure.

## Adapter

## Bridge

## Decorator

## Composite

## Fascade

## Proxy


# Behavioral Patterns
Nam malis corpora repudiandae id, tale utamur accusamus te vim, cu mei vidisse quaestio. Aliquip eripuit albucius ne cum, ne summo verear officiis usu, mollis eirmod no mea. Ad facer veniam tibique pri, timeam indoctum sed ne. Purto natum soluta sea id, errem accusamus assentior his id. Eos aperiri evertitur cu, ad augue reprimique duo, detracto facilisi aliquando sit ut.

## Strategy

### About:
* Form: Object pattern
* AKA:  Policy (compile-time)

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
* Form: Object pattern
* AKA:  N/A

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
* Form: Object pattern
* AKA:  Publisher-subscriber

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
* Form: Object pattern
* AKA:  N/A

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
