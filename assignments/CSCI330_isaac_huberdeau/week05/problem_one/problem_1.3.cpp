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

struct Cat : Animal {
  void make_sound() const override { std::cout << "meow"; }
};

int main() {
  Animal* animal = new Dog();
  animal->make_sound();  // Should print "Woof!"
  delete animal;

  Animal* zoo[3] = {
      new Dog(), new Animal(), new Cat()
      // Add a Cat class that meows
  };

  for (int i = 0; i <= 2; i++) {
    zoo[i]->make_sound();
  }

  for (int j = 0; j <= 2; j++) {
    delete zoo[j];
  }

  return 0;
}