// VERSION #1
// COMPILER GENERATED

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

struct Resource {
  int x{5};
  int y{7};
};

struct Widget {
public:
  // Default consructor
  Widget() = default;

  // Parameterized constructor
  Widget(int i, std::string s, Resource p)
    : idx{i}, str{s}, ptr{new Resource{p}} { }

  // Copy constructor
  Widget(Widget const& other)
    : idx{other.idx}
    , str{other.str}
    , ptr{other.ptr} // Shallow copy!
  { } 

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    idx = other.idx;
    str = other.str;
    ptr = other.ptr; // Shallow copy!
    return *this;
  }

  // Move constructor
  Widget(Widget&& other) noexcept
    : idx{std::move(other.idx)}
    , str{std::move(other.str)}
    , ptr{std::move(other.ptr)} // Shallow copy!
  { }

  // Move assignment operator
  Widget& operator=(Widget&& other) noexcept {
    idx = std::move(other.idx);
    str = std::move(other.str);
    ptr = std::move(other.ptr); // Shallow copy!
    return *this;
  }

  // Destructor
  //~Widget() = default;

  int         get_idx() const { return idx; }
  std::string get_str() const { return str; }
  Resource*   get_ptr() const { return ptr; }

private:
  int idx{};
  std::string str{};
  Resource* ptr{};
};

// Formatted print function for Widget
void print_widget(std::string_view s, Widget const& w)
{
  // Display information about the Widget
  std::cout << s
            << "\nidx = " << w.get_idx()
            << "\nstr = " << w.get_str()
            << "\nptr = " << w.get_ptr();

  // If the resource is valid, get and display information about it
  if (w.get_ptr()) {
    auto* r = w.get_ptr();
    std::cout << "\nr.x = " << r->x
              << "\nr.y = " << r->y;
  }

  // Formatting only
  std::cout << std::endl;
}

int main()
{
// /*
  //--------------------------------------------------------------------------//
  // Default constructor (zero initialized)
  Widget w0{};
  print_widget("\ndefault ctor", w0);

  //--------------------------------------------------------------------------//
  // Parameterized constructor
  Widget w1{1, "yo", {0,1}};
  print_widget("\n(1) parameterized ctor", w1);

  //--------------------------------------------------------------------------//
  // Copy constructor
  Widget w2{2, "yoo", {2,3}};
  Widget w3{w2};

  print_widget("\n(2a) copy ctor (original obj)", w2);
  print_widget("(2b) copy ctor (new obj)",      w3);

  //--------------------------------------------------------------------------//
  // Copy assignment operator
  Widget w4{3, "foo", {4,5}};
  Widget w5 = w4;

  print_widget("\n(3a) copy assign (original obj)", w4);
  print_widget("(3b) copy assign (new obj)",      w5);

  //--------------------------------------------------------------------------//
  // Move constructor
  Widget w6{4, "bar", {6,7}};
  print_widget("\n(4a) move ctor (original obj)", w6);

  Widget w7{std::move(w6)};
  print_widget("(4b) move ctor (new obj)",       w7);
  print_widget("(4c) move ctor (post-move obj)", w6);

  //--------------------------------------------------------------------------//
  // Move assignment operator
  Widget w8{5, "baz", {8,9}};
  print_widget("\n(5a) move assign (original obj)", w8);

  Widget w9 = std::move(w8);
  print_widget("(5b) move assign (new obj)",       w9);
  print_widget("(5c) move assign (post-move obj)", w8);
// */
}