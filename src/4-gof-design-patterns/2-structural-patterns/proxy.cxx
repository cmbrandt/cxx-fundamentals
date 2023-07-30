#include <iostream>
#include <memory>

struct Subject
{
  virtual ~Subject() = default;

  virtual void request() = 0;
};

struct RealSubject : public Subject
{
  // Implementing the interface of Subject
  void request() override {
    std::cout << "RealSubject::request" << std::endl;
  }
};

// Proxy class may own a pointer to RealSubject
// or a concrete instance of RealSubject
struct Proxy : public Subject
{
  Proxy() = default;
  //Proxy() : real_subject(std::make_shared<RealSubject>()) { }

  // Implementing the interface of Subject,
  // while also delegating to RealSubject
  void request() override {
    // Additional operations before forwarding the request
    std::cout << "Proxy::request enter" << std::endl;

    // Forward the request to the RealSubject
    real_subject.request();
    //real_subject->request();

    // Additional operations after forwarding the request
    std::cout << "Proxy::request exit" << std::endl;
  }

private:
  RealSubject real_subject;
  //std::shared_ptr<RealSubject> real_subject;
};

void client(std::unique_ptr<Subject> const& s)
{
  s->request();
}

int main()
{
  std::unique_ptr<Subject> subject = std::make_unique<Proxy>();
  client(subject);
}