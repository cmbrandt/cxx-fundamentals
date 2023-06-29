#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forwards declarations
class ConcreteElementA;
class ConcreteElementB;

struct Visitor
{
  virtual ~Visitor() = default;

  virtual void visit(ConcreteElementA const& a) const = 0;
  virtual void visit(ConcreteElementB const& b) const = 0;
};

struct Element
{
  virtual ~Element() = default;

  virtual void accept(Visitor const& v) = 0;
};

struct ConcreteElementA : public Element
{
  void accept(Visitor const& v) override {
    v.visit(*this);
  }

  std::string operation_a() const {
    return "ConcreteElementA";
  }
};

struct ConcreteElementB : public Element
{
  void accept(Visitor const& v) override {
    v.visit(*this);
  }

  std::string operation_b() const {
    return "ConcreteElementB";
  }
};

struct ConcreteVisitor : public Visitor
{
  void visit(ConcreteElementA const& a) const override {
    std::cout << "ConcreteVisitor::visit(ConcreteElementA)"
              << "\na.operation_a(): " << a.operation_a() << std::endl;
  }

  void visit(ConcreteElementB const& b) const override {
    std::cout << "ConcreteVisitor::visit(ConcreteElementB)"
              << "\nb.operation_b(): " << b.operation_b() << std::endl;
  }
};

// Client code that visits all elements
void client(std::vector<std::unique_ptr<Element>> const& elems,
            Visitor const& v)
{
  for (auto const& e : elems)
    e->accept(v);
}

int main()
{
  using Elements_t = std::vector<std::unique_ptr<Element>>;

  Elements_t elems{};

  // Create elements
  elems.emplace_back(std::make_unique<ConcreteElementA>());
  elems.emplace_back(std::make_unique<ConcreteElementB>());
  elems.emplace_back(std::make_unique<ConcreteElementA>());

  // Create visitor
  ConcreteVisitor visitor{};

  // Client usage
  client(elems, visitor);
}
