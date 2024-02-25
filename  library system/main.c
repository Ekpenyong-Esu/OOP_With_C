#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declaration of classes
typedef struct Book Book;
typedef struct Patron Patron;
typedef struct Library Library;

// Book class
struct Book {
    char title[50];
    char author[50];
    int availableCopies;
};

// Patron class
struct Patron {
    char name[50];
    int borrowedBooks;
};

// Library class
struct Library {
    Book* books;
    size_t numBooks;
    Patron* patrons;
    size_t numPatrons;
};

// Function to create a new book
Book* createBook(const char* title, const char* author, int availableCopies) {
    Book* book = (Book*)malloc(sizeof(Book));
    strncpy(book->title, title, sizeof(book->title) - 1);
    strncpy(book->author, author, sizeof(book->author) - 1);
    book->availableCopies = availableCopies;
    return book;
}

// Function to create a new patron
Patron* createPatron(const char* name) {
    Patron* patron = (Patron*)malloc(sizeof(Patron));
    strncpy(patron->name, name, sizeof(patron->name) - 1);
    patron->borrowedBooks = 0;
    return patron;
}

// Function to create a new library
Library* createLibrary() {
    Library* library = (Library*)malloc(sizeof(Library));
    library->books = NULL;
    library->numBooks = 0;
    library->patrons = NULL;
    library->numPatrons = 0;
    return library;
}

// Function to add a book to the library
void addBookToLibrary(Library* library, Book* book) {
    library->books = realloc(library->books, (library->numBooks + 1) * sizeof(Book));
    library->books[library->numBooks++] = *book;
}

// Function to add a patron to the library
void addPatronToLibrary(Library* library, Patron* patron) {
    library->patrons = realloc(library->patrons, (library->numPatrons + 1) * sizeof(Patron));
    library->patrons[library->numPatrons++] = *patron;
}

// Function to borrow a book
void borrowBook(Library* library, Patron* patron, const char* bookTitle) {
    for (size_t i = 0; i < library->numBooks; ++i) {
        if (strcmp(library->books[i].title, bookTitle) == 0 && library->books[i].availableCopies > 0) {
            library->books[i].availableCopies--;
            patron->borrowedBooks++;
            printf("%s borrowed by %s\n", bookTitle, patron->name);
            return;
        }
    }
    printf("%s not available for borrowing\n", bookTitle);
}

// Function to return a book
void returnBook(Library* library, Patron* patron, const char* bookTitle) {
    for (size_t i = 0; i < library->numBooks; ++i) {
        if (strcmp(library->books[i].title, bookTitle) == 0 && patron->borrowedBooks > 0) {
            library->books[i].availableCopies++;
            patron->borrowedBooks--;
            printf("%s returned by %s\n", bookTitle, patron->name);
            return;
        }
    }
    printf("%s not found in the list of borrowed books for %s\n", bookTitle, patron->name);
}

// Function to display information about a book
void displayBookInfo(const Book* book) {
    printf("Title: %s\nAuthor: %s\nAvailable Copies: %d\n", book->title, book->author, book->availableCopies);
}

// Function to display information about a patron
void displayPatronInfo(const Patron* patron) {
    printf("Name: %s\nBorrowed Books: %d\n", patron->name, patron->borrowedBooks);
}

// Function to display information about the library
void displayLibraryInfo(const Library* library) {
    printf("Books in the library:\n");
    for (size_t i = 0; i < library->numBooks; ++i) {
        displayBookInfo(&library->books[i]);
        printf("\n");
    }

    printf("Patrons in the library:\n");
    for (size_t i = 0; i < library->numPatrons; ++i) {
        displayPatronInfo(&library->patrons[i]);
        printf("\n");
    }
}

// Function to free the memory allocated for books, patrons, and the library
void freeLibrary(Library* library) {
    free(library->books);
    free(library->patrons);
    free(library);
}

int main() {
    // Create a library
    Library* myLibrary = createLibrary();

    // Add books to the library
    addBookToLibrary(myLibrary, createBook("The Great Gatsby", "F. Scott Fitzgerald", 3));
    addBookToLibrary(myLibrary, createBook("To Kill a Mockingbird", "Harper Lee", 5));
    addBookToLibrary(myLibrary, createBook("1984", "George Orwell", 2));

    // Add patrons to the library
    addPatronToLibrary(myLibrary, createPatron("Alice"));
    addPatronToLibrary(myLibrary, createPatron("Bob"));

    // Display initial information about the library
    printf("Library information before any transactions:\n");
    displayLibraryInfo(myLibrary);

    // Perform book transactions
    borrowBook(myLibrary, &myLibrary->patrons[0], "The Great Gatsby");
    borrowBook(myLibrary, &myLibrary->patrons[1], "To Kill a Mockingbird");
    returnBook(myLibrary, &myLibrary->patrons[0], "The Great Gatsby");

    // Display updated information about the library
    printf("\nLibrary information after transactions:\n");
    displayLibraryInfo(myLibrary);

    // Free the allocated memory
    freeLibrary(myLibrary);

    return 0;
}
