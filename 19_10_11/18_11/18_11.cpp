#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

const short SIZE = 50;

struct Source {
    char type[SIZE]{};
    char title[SIZE]{};
    char author[SIZE]{};
    char publisher[SIZE]{};
    char category[SIZE]{};
    int year{};
};

void printSource(const Source& source) {
    cout << "Type: " << source.type << endl;
    cout << "Title: " << source.title << endl;
    cout << "Author: " << source.author << endl;
    cout << "Publisher: " << source.publisher << endl;
    cout << "Category: " << source.category << endl;
    cout << "Year: " << source.year << endl;
    cout << "-----------------------------\n";
}

void displayLibrary(Source* library, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printSource(library[i]);
    }
}

void addSource(Source*& library, size_t& size) {
    Source newSource;

    cout << "Enter type (Book, Magazine, Newspaper): ";
    cin.ignore();
    cin.getline(newSource.type, SIZE);

    cout << "Enter title: ";
    cin.getline(newSource.title, SIZE);

    if (strcmp(newSource.type, "Book") == 0 || strcmp(newSource.type, "Magazine") == 0) {
        cout << "Enter author: ";
        cin.getline(newSource.author, SIZE);
    }

    cout << "Enter publisher: ";
    cin.getline(newSource.publisher, SIZE);

    if (strcmp(newSource.type, "Book") == 0) {
        cout << "Enter category: ";
        cin.getline(newSource.category, SIZE);
    }

    if (strcmp(newSource.type, "Magazine") == 0 || strcmp(newSource.type, "Newspaper") == 0) {
        cout << "Enter year: ";
        cin >> newSource.year;
    }

    Source* newLibrary = new Source[size + 1];
    for (size_t i = 0; i < size; i++) {
        newLibrary[i] = library[i];  
    }

    newLibrary[size] = newSource;

    delete[] library;
    library = newLibrary;
    size++;

    cout << "Source added successfully!\n";
}


void searchBook(Source* library, size_t size) {
    char author[SIZE];
    char title[SIZE];

    cout << "Enter author: ";
    cin >> author;
    cout << "Enter title: ";
    cin >> title;

    for (size_t i = 0; i < size; i++) {
        if (strcmp(library[i].author, author) == 0 && strcmp(library[i].title, title) == 0) {
            printSource(library[i]);
            return;
        }
    }
    cout << "Book not found.\n";
}

void deleteSource(Source*& library, size_t& size) {
    char title[SIZE];
    cout << "Enter title of source to delete: ";
    cin >> title;

    size_t indexToDelete = size;
    for (size_t i = 0; i < size; i++) {
        if (strcmp(library[i].title, title) == 0) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == size) {
        cout << "Source not found.\n";
        return;
    }

    Source* newLibrary = new Source[size - 1];
    for (size_t i = 0, j = 0; i < size; i++) {
        if (i != indexToDelete) {
            newLibrary[j++] = library[i];
        }
    }

    delete[] library;
    library = newLibrary;
    size--;
    cout << "Source deleted successfully.\n";
}

int main() {
    size_t size = 3;
    Source* library = new Source[size]{
        {"Book", "Harry Potter and the Chamber of Secrets", "J.K. Rowling", "Pottermore Publishing", "Children's Fantasy", 0},
        {"Magazine", "National Geographic", "", "National Geographic Partners", "", 2021},
        {"Newspaper", "The New York Times", "", "New York Times Company", "", 2023}
    };

    int choice;
    do {
        cout << "\nLibrary System Menu:\n";
        cout << "1. Display all sources\n";
        cout << "2. Add a new source\n";
        cout << "3. Search for a book by author and title\n";
        cout << "4. Delete a source\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayLibrary(library, size);
            break;
        case 2:
            addSource(library, size);
            break;
        case 3:
            searchBook(library, size);
            break;
        case 4:
            deleteSource(library, size);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    delete[] library;
    return 0;
}
