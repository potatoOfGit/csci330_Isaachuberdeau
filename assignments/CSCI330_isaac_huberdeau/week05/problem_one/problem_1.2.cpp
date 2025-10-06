#include <iostream>

struct Animal {
  virtual ~Animal() = default;
  virtual void make_sound() const {
    std::cout << "Some generic animal sound\n";
  }
};

struct Dog : Animal {
  // Your override here
  void make_sound() const override { std::cout << "Woof woof!\n"; }
};

int main() {
  Animal* animal = new Dog();
  animal->make_sound();  // Should print "Woof!"
  delete animal;
  return 0;
}

/* ERRORS:
 error: 'void Dog::make_soud() const' marked 'override', but does not override
   12 |   void make_soud() const override { std::cout << "Woof woof!\n"; }*/