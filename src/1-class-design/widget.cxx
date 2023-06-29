#include <cassert>
#include <iostream>
#include <string_view>
#include <utility>

struct Resource {
  int i{};
};

class Widget {
public:
  Widget() = default;
  Widget(int ii, std::string const& ss)
  : i{ii}, s{ss}, r{new Resource} { }

  // Copy constructor
  Widget(Widget const& other)
  : i{other.i}
  , s{other.s}
  , r{other.r ? new Resource{*other.r} : nullptr}
  { }

  // Copy assignment operator
  Widget& operator=(Widget const& other) {
    if (r and other.r) {
      i  = other.i;
      s  = other.s;
      *r = *other.r;
    }
    else {
      Widget tmp{other};
      swap(tmp);
    }
    return *this;
  }

  // Move constructor
  Widget(Widget&& other)
  : i{std::move(other.i)}
  , s{std::move(other.s)}
  , r{std::exchange(other.r, {})}
  { }

  // Move assignment operator
  Widget& operator=(Widget&& other) {
    delete r;
    i = other.i;
    s = other.s;
    r = other.r; other.r = nullptr;
    return *this; 
  }

  ~Widget() { delete r; }

  void swap(Widget& other) {
    using std::swap;
    swap(i, other.i);
    swap(s, other.s);
    swap(r, other.r);
  }

  int         get_i() const { return i; }
  std::string get_s() const { return s; }
  Resource*   get_r() const { return r; }

private:
  int i{};
  std::string s{"Foo"};
  Resource* r{};
};

void print_widget(std::string_view sv, Widget const& w) {
  std::cout << sv
            << "\nw.i = " << w.get_i()
            << "\nw.s = " << w.get_s()
            << "\nw.r = " << w.get_r() << std::endl;
}

int main()
{
  Widget w1;
  print_widget("\nDefault constructor", w1);

  Widget w2{5, "Bar"};
  print_widget("\nParameterized constructor", w2);

  Widget w3{w2};
  print_widget("\nCopy constructor", w3);

  Widget w4 = w2;
  print_widget("\nCopy assignment operator", w4);

  Widget w5{std::move(w2)};
  print_widget("\nMove constructor", w5);
  print_widget("Moved from value", w2);

  Widget w6 = std::move(w3);
  print_widget("\nMove assignment operator", w6);
  print_widget("Moved from value", w3);
}