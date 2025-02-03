#include <iostream>
#include <string>
using namespace std;
// base class book;
class Book {
protected:
    string title;
    string author;
    string ISBN;

public:
    Book(string t, string a, string IS) {
        title = t;
        author = a;
        ISBN = IS;
    }
    // setters and getters for title;
    void set_title(string t) { title = t; }
    string get_title() { return title; }

    // setters and getters for author;
    void set_author(string a) { author = a; }
    string get_author() { return author; }

    // setters and getters for ISBN;

    void set_ISBN(string IS) { ISBN = IS; }
    string get_ISBN() { return ISBN; }
};

//  child fiction class
class Fiction : public Book {
public:
    Fiction(string t, string a, string IS) : Book(t, a, IS) {}
};

// child non-fiction class;
class Non_Fiction : public Book {
public:
    Non_Fiction(string t, string a, string IS) : Book(t, a, IS) {}
};
// SLL to monitor fiction books i should creat the node class and the SLL classe
// :)

class sll_node {
private:
    Fiction* book;
    sll_node* next;
    sll_node* fictionhead;

public:
    // contrructor to intialize the values

    sll_node(Fiction* fiction_book) {
        book = fiction_book;
        next = NULL;
    }


    Fiction* get_book() { return book; }
    sll_node* get_next() { return next; }
    void set_next(sll_node* nextnode) { next = nextnode; }
};

class dll_nodes {
private:
    Non_Fiction* books;
    dll_nodes* Dnext;
    dll_nodes* prev;
    dll_nodes* nonfictionhead;
    dll_nodes* ninfictiontail;

public:
    dll_nodes(Non_Fiction* nonfiction_book) {
        books = nonfiction_book;
        Dnext = NULL;
        prev = NULL;
    }

    Non_Fiction* get_book() { return books; }
    dll_nodes* get_next() { return Dnext; }
    void set_next(dll_nodes* dnextnode) { Dnext = dnextnode; }

    void set_prev(dll_nodes* prevNode) { prev = prevNode; }
    dll_nodes* get_prev() { return prev; }
};

class RecentlyAddedStack {
private:
    Book* stack[5];
    int count;

public:
    RecentlyAddedStack() { count = 0; }
    void pushBook(Book* book) {
        if (count == 5) {
            cout << "Stack full. Removing oldest book.\n";
            popBook();
        }
        stack[count++] = book;
        cout << "Book \"" << book->get_title() << "\" added to stack.\n";
    }

    void popBook() {
        if (count == 0) {
            cout << "No recently added books to remove.\n";
            return;
        }

        for (int i = 1; i < count; i++) {
            stack[i - 1] = stack[i];
        }
        count--;
    }

    void displaybooks() {
        if (count == 0) {
            cout << "No recently added books.\n";
            return;
        }
        cout << "Most recently added books are:\n";
        for (int i = count - 1; i >= 0; i--) {
            cout << stack[i]->get_title() << endl;
        }
    }
};

class Borrow_queue {
private:
    Book* queue[10];
    int front, rear, count;

public:
    Borrow_queue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    void enqueueBook(Book* book) {
        if (count == 10) {
            dequeueBook();
        }
        rear = (rear + 1) % 10;
        queue[rear] = book;
        count++;
        cout << "Book \"" << book->get_title() << "\" added to borrowing history."
            << endl;
    }
    void dequeueBook() {
        if (count == 0) {
            cout << "borrowing history is empty! " << endl;
        }
        cout << "Book \"" << queue[front]->get_title()
            << "\" removed from borrowing history." << endl;
        front = (front + 1) % 10;
        count--;
    }
    void display_BorrowedBooks() {
        if (count == 0) {
            cout << "empty borrowing history" << endl;
            return;
        }
        cout << "borrowing history: " << endl;
        for (int i = 0; i < count; i++) {
            int index = (front + i) % 10;
            cout << queue[index]->get_title() << " by " << queue[index]->get_author()
                << endl;
        }
    }
};

class library {
private:
    sll_node* fictionhead;
    dll_nodes* nonfictionhead;
    dll_nodes* nonfictiontail;
    RecentlyAddedStack stack;
    Borrow_queue queue;

public:
    library() {
        fictionhead = NULL;
        nonfictionhead = NULL;
        nonfictiontail = NULL;
    }
    void addbook() {
        string type;
        cout << "Enter book type (fiction/nonfiction): ";
        cin >> type;
        if (type != "fiction" && type != "nonfiction") {
            cout << "Invalid book type! Please enter either 'fiction' or "
                "'nonfiction'.\n";
            return;
        }
        string title, author, ISBN;
        cout << "Enter title: ";
        cin >> title;
        cout << "Enter author: ";
        cin >> author;
        cout << "Enter ISBN: ";
        cin >> ISBN;

        if (type == "fiction") {
            Fiction* new_book = new Fiction(title, author, ISBN);
            sll_node* new_node = new sll_node(new_book);
            new_node->set_next(fictionhead);
            fictionhead = new_node;
            stack.pushBook(new_book);
        }
        else if (type == "nonfiction") {
            Non_Fiction* new_book = new Non_Fiction(title, author, ISBN);
            dll_nodes* new_node = new dll_nodes(new_book);
            if (nonfictionhead == nullptr) {
                nonfictionhead = nonfictiontail = new_node;
            }
            else {
                new_node->set_next(nonfictionhead);
                nonfictionhead->set_prev(new_node);
                nonfictionhead = new_node;
            }


            stack.pushBook(new_book);

        }
        else {
            cout << "Invalid book type. Please enter 'fiction' or 'nonfiction'.\n";
        }
    }

    void removebook() {
        string type, ISBN;
        cout << "Enter book type (fiction/nonfiction): ";
        cin >> type;
        if (type != "fiction" && type != "nonfiction") {
            cout << "Invalid book type! Please enter either 'fiction' or 'nonfiction'.\n";
            return;
        }

        cout << "Enter ISBN: ";
        cin >> ISBN;
        cin.ignore();  // Clear newline character left in the input buffer

        // Handling Fiction Books
        if (type == "fiction") {
            if (fictionhead == NULL) {
                cout << "There are no fiction books to remove!" << endl;
                return;
            }

            // Removing from the head of the list
            if (fictionhead->get_book()->get_ISBN() == ISBN) {
                sll_node* temp = fictionhead;
                fictionhead = fictionhead->get_next();
                delete temp->get_book();  // Delete book data
                delete temp;              // Delete node
                cout << "Book removed successfully." << endl;
                return;
            }

            // Removing from the middle or end of the list
            sll_node* current = fictionhead;
            while (current->get_next() != NULL) {
                if (current->get_next()->get_book()->get_ISBN() == ISBN) {
                    sll_node* to_delete = current->get_next();
                    current->set_next(to_delete->get_next());  // Link past the node
                    delete to_delete->get_book();
                    delete to_delete;
                    cout << "Book removed successfully." << endl;
                    return;
                }
                current = current->get_next();
            }

            // If book was not found
            cout << "The book with ISBN: " << ISBN << " was not found." << endl;
        }

        // Handling Non-Fiction Books
        else if (type == "nonfiction") {
            if (nonfictionhead == NULL) {
                cout << "There are no nonfiction books to remove!" << endl;
                return;
            }

            // Removing from the head of the list
            if (nonfictionhead->get_book()->get_ISBN() == ISBN) {
                dll_nodes* temp = nonfictionhead;
                nonfictionhead = nonfictionhead->get_next();
                if (nonfictionhead) nonfictionhead->set_prev(NULL);
                delete temp->get_book();
                delete temp;
                cout << "Book removed successfully." << endl;
                return;
            }

            // Searching for book in the middle or end
            dll_nodes* current = nonfictionhead;
            while (current != NULL) {
                if (current->get_book()->get_ISBN() == ISBN) {
                    // Adjust pointers
                    if (current->get_next()) {
                        current->get_next()->set_prev(current->get_prev());
                    }
                    if (current->get_prev()) {
                        current->get_prev()->set_next(current->get_next());
                    }

                    delete current->get_book();
                    delete current;
                    cout << "Book removed successfully." << endl;
                    return;
                }
                current = current->get_next();
            }

            // If book was not found
            cout << "The book with ISBN: " << ISBN << " was not found." << endl;
        }
    }

    void searchbook() {
        string type, ISBN_title;
        cout << "Enter book type (fiction/nonfiction): ";
        cin >> type;
        if (type != "fiction" && type != "nonfiction") {
            cout << "Invalid book type! Please enter either 'fiction' or "
                "'nonfiction'.\n";
            return;  // Exit the function
        }
        cout << "Enter ISBN or title: ";
        cin >> ISBN_title;
        if (type == "fiction") {
            if (fictionhead == NULL) {
                cout << "there are no books to search from !" << endl;
            }
            sll_node* temp = fictionhead;

            // if the book is at the begining of the list

            if (temp->get_book()->get_ISBN() == ISBN_title ||
                temp->get_book()->get_title() == ISBN_title) {
                cout << "the book :" << temp->get_book()->get_title() << " exists "
                    << endl;
                return;
            }
            // if book is in the middle of the list
            while (temp != NULL) {
                if (temp->get_book()->get_ISBN() == ISBN_title ||
                    temp->get_book()->get_title() == ISBN_title) {
                    cout << " the book" << temp->get_book() << " exists !" << endl;
                    return;
                }
                temp = temp->get_next();

                cout << "book not found " << endl;
            }
        }

        else if (type == "nonfiction") {
            if (nonfictionhead == NULL) {
                cout << "There are no books to search from! " << endl;
                return;
            }
            dll_nodes* temp = nonfictionhead;
            while (temp != NULL) {
                if (temp->get_book()->get_ISBN() == ISBN_title ||
                    temp->get_book()->get_title() == ISBN_title) {
                    cout << " the Book : " << temp->get_book()->get_title() << " is found"
                        << endl;
                    return;
                }
                temp = temp->get_next();
            }

            cout << "Book not found " << endl;
        }

        else {
            cout << "Invalid book type." << endl;
        }
    }
    void borrowBook() {
        string type, ISBN;
        cout << "Enter book type (fiction/nonfiction): ";
        cin >> type;
        if (type != "fiction" && type != "nonfiction") {
            cout << "Invalid book type! Please enter either 'fiction' or "
                "'nonfiction'.\n";
            return;  // Exit the function
        }
        cout << "Enter ISBN: ";
        cin >> ISBN;

        if (type == "fiction") {
            sll_node* temp = fictionhead;
            while (temp) {
                if (temp->get_book()->get_ISBN() == ISBN) {
                    queue.enqueueBook(temp->get_book());
                    cout << "You borrowed: " << temp->get_book()->get_title() << endl;
                    return;
                }
                temp = temp->get_next();
            }
        }
        else if (type == "nonfiction") {
            dll_nodes* temp = nonfictionhead;
            while (temp) {
                if (temp->get_book()->get_ISBN() == ISBN) {
                    queue.enqueueBook(temp->get_book());
                    cout << "You borrowed: " << temp->get_book()->get_title() << endl;
                    return;
                }
                temp = temp->get_next();
            }
        }
        else {
            cout << "Book not found." << endl;
        }
    }

    void displayRecentlyAddedBooks() {
        stack.displaybooks();
    }

    void displayBorrowingHistory() { queue.display_BorrowedBooks(); }
};
int main() {
    library library;
    int choice;
    do {
        cout << "1. Add Book." << endl
            << " 2.Remove Book." << endl
            << "3.Search Book" << endl
            << "4.Borrow Book" << endl;
        cout << "5. View Recently Added Books" << endl
            << "6. View Borrowing History" << endl
            << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            library.addbook();
            break;
        case 2:
            library.removebook();
            break;
        case 3:
            library.searchbook();
            break;
        case 4:
            library.borrowBook();
            break;
        case 5:
            library.displayRecentlyAddedBooks();
            break;
        case 6:
            library.displayBorrowingHistory();
            break;
        case 7:
            cout << "have a great day &see you soon :)" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 7);

    return 0;
}
