#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Book {
  string title;
  string author;
  string category;

  Book() {}
  Book(const string& t, const string& a, const string& c)
      : title(t), author(a), category(c) {}
};

class Library {
 private:
  map<string, Book> books;
  unordered_set<string> authors;
  set<string> categories;
  unordered_map<string, string> checkedOut;

 public:
  void addBook(const string& isbn, const string& title, const string& author,
               const string& category) {
    books[isbn] = Book(title, author, category);
    authors.insert(author);
    categories.insert(category);
    cout << "Added: " << title << " by " << author << endl;
  }

  void checkoutBook(const string& isbn, const string& borrower) {
    if (books.find(isbn) == books.end()) {
      cout << "Book not found!" << endl;
      return;
    }

    if (checkedOut.find(isbn) != checkedOut.end()) {
      cout << "Book already checked out!" << endl;
      return;
    }

    checkedOut[isbn] = borrower;
    cout << books[isbn].title << " checked out to " << borrower << endl;
  }

  void returnBook(const string& isbn) {
    if (checkedOut.find(isbn) != checkedOut.end()) {
      cout << books[isbn].title << " returned by " << checkedOut[isbn] << endl;
      checkedOut.erase(isbn);
    } else {
      cout << "Book was not checked out!" << endl;
    }
  }

  void displayAllBooks() {
    cout << "\n=== All Books ===" << endl;
    for (const auto& pair : books) {
      string isbn = pair.first;
      Book book = pair.second;
      string status = (checkedOut.find(isbn) != checkedOut.end())
                          ? "Checked out to " + checkedOut[isbn]
                          : "Available";
      cout << "ISBN: " << isbn << " | " << book.title << " by " << book.author
           << " | " << status << endl;
    }
  }

  void displayAuthors() {
    cout << "\n=== All Authors ===" << endl;
    for (const string& author : authors) {
      cout << author << endl;
    }
  }

  void displayCategories() {
    cout << "\n=== All Categories (sorted) ===" << endl;
    for (const string& category : categories) {
      cout << category << endl;
    }
  }

  void displayCheckedOut() {
    cout << "\n=== Checked Out Books ===" << endl;
    if (checkedOut.empty()) {
      cout << "No books currently checked out." << endl;
      return;
    }
    for (const auto& pair : checkedOut) {
      string isbn = pair.first;
      string borrower = pair.second;
      cout << books[isbn].title << " -> " << borrower << endl;
    }
  }
};

int main() {
  Library library;

  library.addBook("978-0134685991", "Effective Modern C++", "Scott Meyers",
                  "Programming");
  library.addBook("978-0321563842", "The C++ Programming Language",
                  "Bjarne Stroustrup", "Programming");
  library.addBook("978-0596809485", "97 Things Every Programmer Should Know",
                  "Kevlin Henney", "Software Engineering");
  library.addBook("978-0134494166", "Clean Code", "Robert Martin",
                  "Software Engineering");
  library.addBook("978-0201633610", "Design Patterns", "Gang of Four",
                  "Architecture");

  library.displayAllBooks();
  library.displayAuthors();
  library.displayCategories();

  cout << "\n=== Checking out books ===" << endl;
  library.checkoutBook("978-0134685991", "Alice Johnson");
  library.checkoutBook("978-0321563842", "Bob Smith");
  library.checkoutBook("978-0134685991", "Charlie Brown");

  library.displayCheckedOut();

  cout << "\n=== Returning books ===" << endl;
  library.returnBook("978-0134685991");

  library.displayAllBooks();

  return 0;
}