#include <cassert>
#include <iostream>
#include <memory>
#include <string_view>
#include <utility>

struct Resource {
  Resource() = default;
  Resource(int ii) : i{ii} { }
  int i{};
};

class Widget {
public:
  Widget() = default;
  Widget(int ii, std::string const& ss, int rr)
  : i{ii}, s{ss}, r{std::make_shared<Resource>(rr)} { }

  int         get_i() const { return i; }
  std::string get_s() const { return s; }
  Resource*   get_r() const { return r.get(); }

private:
  int i{};
  std::string s{"Foo"};
  std::shared_ptr<Resource> r{};
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

  Widget w2{5, "Bar", 33};
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