#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Observer interface
struct Observer
{
  virtual ~Observer() {}

  virtual void update(int value) = 0;
};

// ConcreteObserver class
struct ConcreteObserver : public Observer
{
  void update(int value) override {
    observer_state = value;
    std::cout << "Observer state updated: " << observer_state << std::endl;
  }

private:
  int observer_state;
};

// Subject interface
struct Subject
{
  virtual ~Subject() {}

  virtual void attach(std::shared_ptr<Observer> observer) = 0;
  virtual void detach(std::shared_ptr<Observer> observer) = 0;
  virtual void notify() = 0;
};

// ConcreteSubject class
struct ConcreteSubject : public Subject
{
  void attach(std::shared_ptr<Observer> observer) override {
    observers.push_back(observer);
  }

  void detach(std::shared_ptr<Observer> observer) override {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
      observers.erase(it);
  }

  void notify() override {
    for (const auto& observer : observers)
      observer->update(subject_state);
  }

  void set_state(int value) {
    std::cout << "\nConcreteSubject::set_state()" << std::endl;
    subject_state = value;
    notify();
  }

private:
  std::vector<std::shared_ptr<Observer>> observers;
  int subject_state;
};

// Client code
void client(std::unique_ptr<ConcreteSubject>& subject, int value)
{
  subject->set_state(value);
}

// Main program
int main()
{
  // Create a concrete subject
  auto subject = std::make_unique<ConcreteSubject>();

  // Create two concrete observers
  auto observer1 = std::make_shared<ConcreteObserver>();
  auto observer2 = std::make_shared<ConcreteObserver>();

  // Attach the two observers to the subject
  subject->attach(observer1);
  subject->attach(observer2);

  // Set the subject state, which will notify the observers
  client(subject, 42);

  // Detach one observer and set the state again
  subject->detach(observer2);
  client(subject, 100);
}
