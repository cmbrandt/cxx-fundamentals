#include <iostream>
#include <memory>

struct Implementor
{
  virtual ~Implementor() = default;

  virtual void operation_impl() = 0;
};

struct ConcreteImplementorA : public Implementor
{
  void operation_impl() override {
    std::cout << "ImplementatorA::operation_impl" << std::endl;
  }
};

struct ConcreteImplementorB : public Implementor
{
  void operation_impl() override {
    std::cout << "ImplementatorB::operation_impl" << std::endl;
  }
};

struct Abstraction
{
  Abstraction(std::unique_ptr<Implementor> impl)
  : pimpl{std::move(impl)} { }

  virtual void operation() = 0;

protected:
  std::unique_ptr<Implementor> pimpl; // Bridge
};

struct RefinedAbstractionA : public Abstraction
{
  RefinedAbstractionA(std::unique_ptr<Implementor> impl)
  : Abstraction(std::move(impl)) { }

  void operation() override {
    std::cout << "\nRefinedAbstractionB::operation" << std::endl;
    pimpl->operation_impl();
  }
};

struct RefinedAbstractionB : public Abstraction
{
  RefinedAbstractionB(std::unique_ptr<Implementor> impl)
  : Abstraction(std::move(impl)) { }

  void operation() override {
    std::cout << "\nRefinedAbstractionB::operation" << std::endl;
    pimpl->operation_impl();
  }
};

void client(std::unique_ptr<Abstraction> const& abstraction)
{
  abstraction->operation();
}

int main()
{
  // Implementors
  std::unique_ptr<Implementor> implA = std::make_unique<ConcreteImplementorA>();
  std::unique_ptr<Implementor> implB = std::make_unique<ConcreteImplementorB>();

  implA->operation_impl();
  implB->operation_impl();

  // Abstractions
  std::unique_ptr<Abstraction> abstraction1
    = std::make_unique<RefinedAbstractionA>(std::move(implA));
  std::unique_ptr<Abstraction> abstraction2
    = std::make_unique<RefinedAbstractionB>(std::move(implB));

  // Client usage
  client(abstraction1);
  client(abstraction2);
}