// Template provided:
#include <cstdio>

int main() {
    int original = 100;
    
    // TODO: Create a copy of original called 'copy_val'
    // TODO: Create a reference to original called 'ref_val'
    
    // TODO: Modify original to 200
    
    // TODO: Print all three values to show the difference
    int copy_value = original;
    int& original_ref = original;
    original_ref = 200;
    
    printf("Original: %d, Copy: %d, Reference: %d\n", original, copy_value, original_ref);
    
    
    return 0;
}