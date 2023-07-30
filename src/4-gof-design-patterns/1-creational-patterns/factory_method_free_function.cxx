#include <iostream>
#include <memory>

enum class ProductId {ONE, TWO};

// Defines the interface of objects the factory method creates
struct Product
{
  virtual ~Product() = default;

  virtual void operation() const = 0;
};

// Implements the Product interface
struct ConcreteProduct1: public Product
{
  void operation() const {
    std::cout << "ConcreteProduct1" << std::endl;
  }
};

// Implements the Product interface
struct ConcreteProduct2: public Product
{
  void operation() const {
    std::cout << "ConcreteProduct2" << std::endl;
  }
};

// Factory free function which returns an object of type Product
std::unique_ptr<Product> create(ProductId const& id)
{
  if (id == ProductId::ONE)
    return std::make_unique<ConcreteProduct1>();
  if (id == ProductId::TWO)
    return std::make_unique<ConcreteProduct2>();
  // repeat for remaining products...

  return nullptr;
}

// Client code
void client(ProductId const& id)
{
  std::unique_ptr<Product> p = create(id);
  p->operation();
}

int main()
{
  // Client usage
  client(ProductId::ONE);
  client(ProductId::TWO);
}