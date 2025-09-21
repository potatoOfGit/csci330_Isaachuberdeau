// Template provided:
#include <cstdio>

int main() {
    // TODO: Create an integer variable 'score' with value 85
    // TODO: Create a reference 'score_ref' that refers to 'score'
    // TODO: Print both score and score_ref
    // TODO: Modify score through score_ref to 92
    // TODO: Print both values again to show they're the same
    
    //Problem One
    int score = 85;
    int& score_ref = score;
    printf("Original: %d, Reference: %d\n", score, score_ref);
    
    score_ref = 92;
    
    printf("Motified score: %d,Refrence: %d\n", score, score_ref);

    return 0;
}