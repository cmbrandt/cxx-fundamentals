#include <iostream>
#include <memory>

struct Component
{
  virtual ~Component() = default;

  virtual void operation() const = 0;
};

struct ConcreteComponent : public Component
{
  void operation() const override {
    std::cout << "\nConcreteComponent::operation" << std::endl;
  }
};

struct Decorator : public Component
{
public:
  Decorator(std::unique_ptr<Component> component)
  : component(std::move(component)) { }

  template <class T>
  Decorator(ConcreteComponent const& component)
  : component{std::make_unique<T>(component)} { }

  void operation() const override {
    if (component)
      component->operation();
  }

protected:
  std::unique_ptr<Component> component;
};

struct ConcreteDecorator : public Decorator
{
  ConcreteDecorator(std::unique_ptr<Component> component)
  : Decorator(std::move(component)) { }

  void operation() const override {
    Decorator::operation();
    additional_operation();
    }

  void additional_operation() const {
    std::cout << "ConcreteDecorator::additional_operation" << std::endl;
  }
};

void client(std::unique_ptr<Component> const& c)
{
  c->operation();
}

int main()
{
  // Construct a ConcreteDecorator using a local a ConcreteComponent instance
  std::unique_ptr<Component> component
    = std::make_unique<ConcreteComponent>();
  std::unique_ptr<Component> decorator1
    = std::make_unique<ConcreteDecorator>(std::move(component));

  // Construct a ConcreteDecorator directly from a ConcreteComponent
  std::unique_ptr<Component> decorator2
    = std::make_unique<ConcreteDecorator>(std::make_unique<ConcreteComponent>());

  // Execute the operations
  client(decorator1);
  client(decorator2);  
}