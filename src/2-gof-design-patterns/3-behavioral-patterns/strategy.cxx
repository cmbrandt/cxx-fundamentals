#include <iostream>
#include <memory>
#include <utility>

// Interface for the Strategy family of algorithms
struct Strategy
{
  virtual ~Strategy() = default;

  virtual void algorithm() const = 0;
};

// The Context owns a Strategy
struct Context
{
  void operation() const {
    if (strat != nullptr)
      strat->algorithm();
  }

  void set_strategy(std::unique_ptr<Strategy> s) {
    strat = std::move(s);
  }

private:
  std::unique_ptr<Strategy> strat{nullptr};
};

struct ConcreteStrategy1 : public Strategy
{
  void algorithm() const {
    std::cout << "ConcreteStrategy1 executed" << std::endl;
  }
};

struct ConcreteStrategy2 : public Strategy
{
  void algorithm() const {
    std::cout << "ConcreteStrategy2 executed" << std::endl;
  }
};

// Client code
void client(Context const& c)
{
  c.operation();
}

int main()
{
  Context context;

  context.set_strategy(std::make_unique<ConcreteStrategy1>());
  client(context);

  context.set_strategy(std::make_unique<ConcreteStrategy2>());
  client(context);
}