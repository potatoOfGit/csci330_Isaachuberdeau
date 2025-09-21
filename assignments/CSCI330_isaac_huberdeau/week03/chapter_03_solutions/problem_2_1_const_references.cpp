#include <cstdio>

struct Student {
    char name[50];
    int age;
    double gpa;
};

// TODO: Write a function 'display_student' that takes a const Student reference
// and prints the student's information
void display_student(const Student& s){
    printf("Student: %s, Age: %d, GPA: %.2f\n", s.name, s.age, s.gpa);
}

// TODO: Write a function 'is_honor_student' that takes a const Student reference
// and returns true if GPA >= 3.5
bool is_honor_student(const Student& s){
    return s.gpa >= 3.5;
}

int main() {
    Student alice = {"Alice Johnson", 20, 3.8};
    
    // TODO: Call both functions with alice
    display_student(alice);
    printf("%s is honor student: %s\n", alice.name, is_honor_student(alice) ? "Yes" : "No");
    return 0;
}