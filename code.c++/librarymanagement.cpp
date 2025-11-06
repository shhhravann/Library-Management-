#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // Required for stringstream and proper data parsing
using namespace std;

// CLASS: Book
// Represents a single book with basic information.
class Book {
protected:
    int bookId;
    string title;
    string author;

public:
    // Default constructor
    Book() {
        bookId = 0;
        title = "";
        author = "";
    }

    // Parameterized constructor
    Book(int id, string t, string a) {
        bookId = id;
        title = t;
        author = a;
    }

    // Method to get book details from the user
    void getBookData() {
        cout << "Enter Book ID: ";
        // Basic input validation to handle non-integer input gracefully
        while (!(cin >> bookId)) {
            cout << "Invalid input. Please enter a numerical Book ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(); // Consume the newline character left by cin >> bookId
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
    }

    // Method to display book details
    void showBookData() const {
        cout << "\nBook ID: " << bookId;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author << endl;
    }

    // Getter for Book ID
    int getId() const {
        return bookId;
    }

    // Getters for Title and Author (Required for file writing due to access specifiers)
    string getTitle() const {
        return title;
    }
    string getAuthor() const {
        return author;
    }

    // Operator Overloading for comparing book IDs
    bool operator==(const Book &b) const {
        return this->bookId == b.bookId;
    }
};

// CLASS: Library
// Inherits from Book and provides management functionalities,
// demonstrating the concept of Inheritance.
class Library : public Book {
public:
    void addBook();
    void displayBooks();
    void searchBook(int id);
};

// Function to add a new book record to the file 'library.txt'
void Library::addBook() {
    Book b;
    b.getBookData();

    // Check if the file exists and open in append mode
    ofstream fout("library.txt", ios::app);
    if (!fout.is_open()) {
        cout << "\nError: Could not open file for writing!\n";
        return;
    }

    // Data is stored in a comma-separated format (CSV)
    fout << b.getId() << "," << b.getTitle() << "," << b.getAuthor() << endl;
    fout.close();

    cout << "\nBook added successfully!\n";
}

// Function to display all book records from 'library.txt'
void Library::displayBooks() {
    // Open file for reading
    ifstream fin("library.txt");
    if (!fin.is_open()) {
        cout << "\nNo books found or file could not be opened!\n";
        return;
    }

    string line;
    cout << "\n------ Library Books (ID, Title, Author) ------\n";
    // Read the file line by line
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

// Function to search for a book by ID in 'library.txt'
void Library::searchBook(int id) {
    ifstream fin("library.txt");
    if (!fin.is_open()) {
        cout << "\nNo data found or file could not be opened!\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(fin, line)) {
        stringstream ss(line);
        string segment;
        int storedId = 0;
        
        // Extract the ID (first segment before the comma)
        if (getline(ss, segment, ',')) {
            try {
                storedId = stoi(segment);
            } catch (const std::exception& e) {
                // Ignore lines where the ID is not a valid integer
                continue;
            }
        }

        if (storedId == id) {
            cout << "\nBook Found:\n" << line << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nBook not found!\n";

    fin.close();
}

// FUNCTION OVERLOADING EXAMPLE
// First overloaded function: a simple welcome message
void showMessage() {
    cout << "\n--- Welcome to Library Management System! ---\n";
}

// Second overloaded function: a personalized welcome message
void showMessage(const string& name) {
    cout << "\nHello, " << name << "! Welcome to the Library System.\n";
}

// TEMPLATE EXAMPLE
// A function template that works with any data type T that supports the '+' operator
template <class T>
T addValues(T a, T b) {
    return a + b;
}

// MAIN FUNCTION
int main() {
    // Set the locale for consistent output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Library lib;
    int choice;

    // Demonstration of Function Overloading
    showMessage(); 
    showMessage("C++ Enthusiast");

    do {
        cout << "\n---------------------------------------";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book (by ID)";
        cout << "\n4. Use Template Function Example";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        
        // Input validation for menu choice
        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            lib.addBook();
            break;
        case 2:
            lib.displayBooks();
            break;
        case 3: {
            int id;
            cout << "\nEnter Book ID to search: ";
            if (cin >> id) {
                lib.searchBook(id);
            } else {
                cout << "\nInvalid ID entered.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            break;
        }
        case 4:
            // Demonstration of the Template function with different types
            cout << "\n--- Template Function Demo ---";
            cout << "\naddValues(3, 4) [int] = " << addValues(3, 4);
            cout << "\naddValues(2.5, 4.7) [double] = " << addValues(2.5, 4.7) << endl;
            break;
        case 5:
            cout << "\nExiting program... Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}