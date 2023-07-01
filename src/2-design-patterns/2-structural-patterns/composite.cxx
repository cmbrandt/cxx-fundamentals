#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

struct Component
{
  virtual ~Component() = default;

  virtual void operation() const = 0;
  virtual void add(std::unique_ptr<Component> component) { }
  virtual void remove(Component* component) { }
  virtual Component* get_child(size_t index) const { return nullptr; }

};

struct Leaf : public Component
{
  void operation() const override {
    std::cout << "Leaf::operation" << std::endl;
  }
};

struct Composite : public Component
{
  void operation() const override {
    std::cout << "\nComposite::operation" << std::endl;
    for (const auto& child : children)
      child->operation();
  }

  void add(std::unique_ptr<Component> component) override {
    children.push_back(std::move(component));
  }

  void remove(Component* component) override {
    auto it = std::find_if(children.begin(), children.end(), [&](auto const& child) {
      return child.get() == component;
    });

    if (it != children.end())
      children.erase(it);
  }

  Component* get_child(size_t index) const override {
    if (index >= 0 && index < children.size())
      return children[index].get();

    return nullptr;
  }

private:
  std::vector<std::unique_ptr<Component>> children;
};

int main()
{
  // Create a composite object
  auto composite = std::make_unique<Composite>();

  // Create and add leaf objects to the composite
  composite->add(std::make_unique<Leaf>());
  composite->add(std::make_unique<Leaf>());

  // Perform the operation on the composite
  composite->operation();

  // Remove the first leaf
  Component* first_child = composite->get_child(0);
  composite->remove(first_child);

  // Perform the operation on the composite again
  composite->operation();
}