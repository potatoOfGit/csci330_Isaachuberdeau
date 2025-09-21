// Template provided:
#include <cstdio>

int main() {
    int shared_value = 50;
    int& ref_one = shared_value;
    int& ref_two = shared_value;
    
    ref_one = 100;
    printf("Ref Two: %d\n", ref_two);
    
    // TODO: Create two different references to shared_value
    // TODO: Modify shared_value through the first reference
    // TODO: Print the value using the second reference
    // TODO: Show that all three (original + 2 references) have the same value
    
    return 0;
}