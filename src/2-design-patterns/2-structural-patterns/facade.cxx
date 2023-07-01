#include <iostream>
#include <memory>
#include <string>

struct SubsystemOne
{
  void subsys_one_turn_on() {
    std::cout << "Subsystem One On" << std::endl;
  }

  void subsys_one_turn_off() {
    std::cout << "Subsystem One Off" << std::endl;
  }
};

struct SubsystemTwo
{
  void subsys_two_turn_on() {
    std::cout << "Subsystem Two On" << std::endl;
  }

  void subsys_two_turn_off() {
    std::cout << "Subsystem Two Off" << std::endl;
  }
};

struct SubsystemThree
{
  void subsys_three_turn_on() {
    std::cout << "Subsystem Three On" << std::endl;
  }

  void subsys_three_turn_off() {
    std::cout << "Subsystem Three Off" << std::endl;
  }
};

struct SubsystemFour
{
  void subsys_four_turn_on() {
    std::cout << "Subsystem Four On" << std::endl;
  }

  void subsys_four_turn_off() {
    std::cout << "Subsystem Four Off" << std::endl;
  }
};

struct Facade
{
  Facade() = default;

  // Member functions simplify the usage for each
  // subsystem (class) by delegating to its members

  void turn_system_on() {
    std::cout << "\nTurn the system on:" << std::endl;
    ss1.subsys_one_turn_on();
    ss2.subsys_two_turn_on();
    ss3.subsys_three_turn_on();
    ss4.subsys_four_turn_on();
  }

  void turn_system_off() {
    std::cout << "\nTurn the system off:" << std::endl;
    ss1.subsys_one_turn_off();
    ss2.subsys_two_turn_off();
    ss3.subsys_three_turn_off();
    ss4.subsys_four_turn_off();
  }

private:
  // The facade owns an instance of each subsystem (class)
  SubsystemOne   ss1;
  SubsystemTwo   ss2;
  SubsystemThree ss3;
  SubsystemFour  ss4;
};

// Client code
void client(std::unique_ptr<Facade> const& f)
{
  f->turn_system_on();
  f->turn_system_off(); 
}

int main()
{
  auto f = std::make_unique<Facade>();
  client(f);
}