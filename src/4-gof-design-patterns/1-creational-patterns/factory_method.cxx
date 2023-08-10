#include <iostream>
#include <memory>

enum class ProductId {ONE, TWO};

// Defines the interface of objects the factory method creates
struct Product {
  virtual ~Product() = default;
  virtual void operation() const = 0;
};

// Implements the Product interface
struct ConcreteProduct1: public Product {
  void operation() const {
    std::cout << "ConcreteProduct1" << std::endl;
  }
};

// Implements the Product interface
struct ConcreteProduct2: public Product {
  void operation() const {
    std::cout << "ConcreteProduct2" << std::endl;
  }
};

// Implements the Factory Method, which returns an object of type Product
struct Creator {
  // Factory method
  std::unique_ptr<Product> create(ProductId const& id) const {
    if (id == ProductId::ONE)
      return std::make_unique<ConcreteProduct1>();
    if (id == ProductId::TWO)
      return std::make_unique<ConcreteProduct2>();
    // repeat for remaining products...

    return nullptr;
  }
};

// Client code
void client(Creator& c, ProductId const& id)
{
  std::unique_ptr<Product> p = c.create(id);
  p->operation();
}

int main()
{
  // Create a creator instance
  std::unique_ptr<Creator> creator = std::make_unique<Creator>();

  // Client usage
  client(*creator, ProductId::ONE);
  client(*creator, ProductId::TWO);
}