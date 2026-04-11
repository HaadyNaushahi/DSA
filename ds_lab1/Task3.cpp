#include <iostream>
#include <vector>
using namespace std;

class Book {
    string book_name;
    string author;
    int pages;
public:
    Book(string book_name, string author, int pages) {
        cout << "Book parameterized cocstructor called " << endl;
        this->book_name = book_name;
        this->author = author;
        this->pages = pages; 
    }
    int getPages() {
        return pages;
    }
    string getName() {
        return book_name;
    }
    void display() {
        cout << "book name : " << book_name<< ", ";
        cout << "book author : " << author << ", ";
        cout << "book pages : " << pages << endl;
    }
   
};

class Newspaper {
    string title;
    string date;
    string edition;
public:
    Newspaper(string title, string date, string edition) {
        cout << "Newspaper parameterized constructor called " << endl;
        this->title = title;
        this->date = date;
        this->edition = edition;
    }
    string getEdition() {
        return edition;
    }
    string retrunTitle() {
        return title;
    }
    void display() {
        cout << "Newspaper title : " << title << ", ";
        cout << "Newspaper date : " << date << ", ";
        cout << "Newspaper edition : " << edition << endl;
    }
};

class Library {
    vector<Book> books;
    vector<Newspaper> newspapers;
public:
    void addBook(const Book& b) {
        books.push_back(b);
    }
    void addNewspaper(const Newspaper& p) {
        newspapers.push_back(p);
    }
    void displayCollection() {
        cout << "Books collection" << endl;
        for (auto b : books) {
            b.display();
        }
        cout << "Newspaper collection" << endl;
        for (auto n : newspapers) {
            n.display();
        }
    }

    void sortBooksByPages() {
        for (int i = 0; i < books.size(); ++i) {
            for (int j = 0; j < books.size() - 1; ++j) {
                if (books[j].getPages() < books[j + 1].getPages()) {
                    Book temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }
    void sortNewspapersByEdition() {
        for (int i = 0; i < newspapers.size(); ++i) {
            for (int j = 0; j < newspapers.size() - 1; ++j) {
                if (newspapers[j].getEdition() > newspapers[j + 1].getEdition()) {
                    Newspaper temp = newspapers[j];
                    newspapers[j] = newspapers[j + 1];
                    newspapers[j + 1] = temp;
                }
            }
        }
    }
    Book* searchBookByTitle(string title) {
        for (auto &b : books) {
            if (b.getName() == title) {
                return &b;
            }
        }
        return nullptr;
    }
    Newspaper* searchNewspaperByName(string title) {
        for (auto &n : newspapers) {
            if (n.retrunTitle() == title) {
                return &n;
            }
        }
        return nullptr;
    }
};

int main() {
    // Create book objects
    Book book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book book2("To Kill a Mockingbird", "Harper Lee", 324);

    // Create newspaper objects
    Newspaper newspaper1("Washington Post", "2024-10-13", "Morning Edition");
    Newspaper newspaper2("The Times", "2024-10-12", "Weekend Edition");

    // Create a library object
    Library library;

    // Add books and newspapers to the library
    library.addBook(book1);
    library.addBook(book2);
    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);
    cout << endl;
    // Display the entire collection
    cout << "Before Sorting:\n";
    library.displayCollection();

    // Sort books by pages and newspapers by edition
    library.sortBooksByPages();
    library.sortNewspapersByEdition();
    cout << endl;
    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    
    // Search for a book by title
    Book* foundBook = library.searchBookByTitle("The Catcher in the Rye");
    if (foundBook) {
        cout << "\nFound Book:\n";
        foundBook->display();
    }
    else {
        cout << "\nBook not found.\n";
    }

    // Search for a newspaper by name
    Newspaper* foundNewspaper = library.searchNewspaperByName("The Times");
    if (foundNewspaper) {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    }
    else {
        cout << "\nNewspaper not found.\n";
    }
    

    return 0;
}
