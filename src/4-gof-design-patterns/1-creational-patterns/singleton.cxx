#include <iostream>

// This is the Scotty Meyers implementation of the Singleton Pattern
struct Singleton {
  // Delete copy operations
  Singleton(Singleton const&)            = delete;
  Singleton& operator=(Singleton const&) = delete;

  // Initializes and returns the single instance
  static Singleton& get_instance()
  {
    static Singleton instance;
    return instance;
  }

  // Methods
  int  get_value() const { return value; }
  void set_value(int v)  { value = v;    }

private:
  // Private ctor and dtor
  Singleton()  = default;
  ~Singleton() = default;

  int value{0};
};

// Client code
void client1(Singleton& singleton)
{
  std::cout << "singleton.get_value() = "
            <<  singleton.get_value()
            << std::endl;

  // Update the singleton object with a new value
  singleton.set_value(5);
  std::cout << "singleton.get_value() = "
            <<  singleton.get_value()
            << std::endl;
}

int main()
{
  Singleton& singleton = Singleton::get_instance();

  // Client usage
  client1(singleton);
}