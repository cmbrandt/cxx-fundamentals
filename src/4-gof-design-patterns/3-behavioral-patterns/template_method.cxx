#include <iostream>
#include <memory>

struct AbstractClass
{
  virtual ~AbstractClass() = default;

  // Implement the template method by
  // defining the skeleton of the algorithm
  void virtual template_method() {
    std::cout << "AbstractClass::template_method" << std::endl;
    primitive_operation1();
    primitive_operation2();
  }

protected:
  // Define the abstract primitive operations
  virtual void primitive_operation1() = 0;
  virtual void primitive_operation2() = 0;
};

// ConcreteClass implements the primitive operations
struct ConcreteClass : public AbstractClass
{
protected:
  void primitive_operation1() override {
    std::cout << "ConcreteClass::primitive_operation1" << std::endl;
  }

  void primitive_operation2() override {
    std::cout << "ConcreteClass::primitive_operation2" << std::endl;
  }
};

// Client code
void client(std::unique_ptr<AbstractClass> const& obj)
{
  obj->template_method();
}

int main()
{
  std::unique_ptr<AbstractClass> object = std::make_unique<ConcreteClass>();
  client(object);
}
