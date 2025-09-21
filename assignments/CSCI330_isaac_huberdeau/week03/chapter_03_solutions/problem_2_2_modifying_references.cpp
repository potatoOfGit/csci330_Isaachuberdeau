// Template provided (build on Problem 2.1):
#include <cstdio>
#include <cstring>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// TODO: Keep your display_student and is_honor_student functions from 2.1
void display_student(const Student& s){
    printf("Student: %s, Age: %d, GPA: %.2f\n", s.name, s.age, s.gpa);
}

bool is_honor_student(const Student& s){
    return s.gpa >= 3.5;
}
// TODO: Write a function 'update_gpa' that takes a Student reference (non-const)
// and a new GPA value, then updates the student's GPA
void update_gpa(Student& s, double new_gpa) {
    s.gpa = new_gpa;
}

// TODO: Write a function 'celebrate_birthday' that takes a Student reference
// and increments their age by 1
void celebrate_birthday(Student& s) {
    s.age += 1;
}

int main() {
    Student bob = {"Bob Smith", 19, 3.2};

    // Display Bob's initial info
    printf("Initial - ");
    display_student(bob);
    printf("Bob is an honor student: %s\n", is_honor_student(bob) ? "Yes" : "No");

    // Update Bob's GPA to 3.6
    update_gpa(bob, 3.6);

    // Celebrate Bob's birthday
    celebrate_birthday(bob);

    // Display Bob's updated info
    printf("Updated - ");
    display_student(bob);
    printf("Bob is an honor student: %s\n", is_honor_student(bob) ? "Yes" : "No");

    return 0;
}