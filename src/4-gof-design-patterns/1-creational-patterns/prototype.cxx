#include <iostream>
#include <memory>
#include <string>

struct Prototype {
  virtual ~Prototype() = default;

  virtual std::unique_ptr<Prototype> clone() const = 0;
  virtual void display() const = 0;
};

struct ConcretePrototype1 : public Prototype {
  ConcretePrototype1(std::string const& d) : data(d) { }

  std::unique_ptr<Prototype> clone() const override {
    return std::make_unique<ConcretePrototype1>(*this);
  }

  void display() const override {
    std::cout << "Data: " << data << std::endl;
  }

private:
  std::string data;
};

struct ConcretePrototype2 : public Prototype {
  ConcretePrototype2(std::string const& d) : data(d) { }

  std::unique_ptr<Prototype> clone() const override {
    return std::make_unique<ConcretePrototype2>(*this);
  }

  void display() const override {
    std::cout << "Data: " << data << std::endl;
  }

private:
  std::string data;
};

// Client code
void client(Prototype& p)
{
  std::unique_ptr<Prototype> c = p.clone();

  p.display();
  c->display();
}

int main()
{
  std::unique_ptr<Prototype> prototype1
    = std::make_unique<ConcretePrototype1>("PrototypeOne");

  std::unique_ptr<Prototype> prototype2
    = std::make_unique<ConcretePrototype2>("PrototypeTwo");

  // Client usage
  client(*prototype1);
  client(*prototype2);
}
