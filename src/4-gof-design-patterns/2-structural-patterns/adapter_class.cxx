#include <iostream>
#include <memory>

struct Adaptee
{
  void specific_request() const {
    std::cout << "Adaptee::specific_request" << std::endl;
  }
};

struct Target
{
  virtual ~Target() = default;

  virtual void request() const = 0;
};

// Adapter inherits from Target for the interface,
// and inherits from Adaptee for the implementation
struct Adapter : public Target, private Adaptee
{
  void request() const override {
    std::cout << "Adapter::request" << std::endl;
    specific_request();
  }
};

void client(std::unique_ptr<Target> const& target)
{
  target->request();
}

int main()
{
  std::unique_ptr<Target> adapter = std::make_unique<Adapter>();
  client(adapter);
}