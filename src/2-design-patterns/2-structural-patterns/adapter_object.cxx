#include <iostream>
#include <memory>

struct Target
{
  virtual ~Target() = default;
  
  virtual void request() const = 0;
};

struct Adaptee
{
  void specific_request() const {
    std::cout << "Adaptee::specific_request" << std::endl;
  }
};

// Adapter class may own a pointer to Adaptee
// or a concrete instance of Adaptee
struct Adapter : public Target
{
  Adapter() = default;
  //Adapter() : adaptee(std::make_unique<Adaptee>()) { }

  void request() const override {
    std::cout << "Adapter::request" << std::endl;
    adaptee.specific_request();
    //adaptee.specific_request();
  }

protected:
  Adaptee adaptee;
  //std::unique_ptr<Adaptee> adaptee;
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
