#include <cstdio>
#include <cstring>

struct Book {
    char title[100];
    char author[50];
    int pages;
    double price;
};

// Function to create a Book by value
Book create_book(const char* title, const char* author, int pages, double price) {
    Book b;
    strncpy(b.title, title, sizeof(b.title));
    strncpy(b.author, author, sizeof(b.author));
    b.pages = pages;
    b.price = price;
    return b;
}

// Function to print book information
void print_book_info(const Book& b) {
    printf("Title: %s\nAuthor: %s\nPages: %d\nPrice: $%.2f\n", b.title, b.author, b.pages, b.price);
}

// Function to apply discount to a Book
void apply_discount(Book& b, double discount_percent) {
    b.price -= b.price * (discount_percent / 100.0);
}

// Function to copy a Book and prefix "Copy of " to the title
Book copy_book(const Book& original) {
    Book copy = original;
    char new_title[100] = "Copy of ";
    strncat(new_title, original.title, sizeof(new_title) - strlen(new_title) - 1);
    strncpy(copy.title, new_title, sizeof(copy.title));
    return copy;
}

int main() {
    printf("=== Creating original book ===\n");
    Book original = create_book("The C++ Journey", "Jane Programmer", 300, 49.99);

    printf("\n=== Original book info ===\n");
    print_book_info(original);

    printf("\n=== Applying 20%% discount ===\n");
    apply_discount(original, 20.0);
    print_book_info(original);

    printf("\n=== Creating a copy ===\n");
    Book copy = copy_book(original);
    print_book_info(copy);

    printf("\n=== Modifying copy only ===\n");
    apply_discount(copy, 10.0);
    printf("Original - Title: %s, Price: $%.2f\n", original.title, original.price);
    printf("Copy - Title: %s, Price: $%.2f\n", copy.title, copy.price);

    return 0;
}
