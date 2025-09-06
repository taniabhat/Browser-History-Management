#include <iostream>
#include <string>

// The BrowserHistory class encapsulates the logic for managing the navigation history.
class BrowserHistory {
private:
    // The Node struct represents a single page in the history.
    // It contains the URL data and two pointers for navigation:
    // 'prev' points to the previous page, and 'next' points to the next page.
    struct Node {
        std::string url;
        Node* prev;
        Node* next;
        // Constructor for the Node to simplify creation.
        Node(const std::string& u) : url(u), prev(nullptr), next(nullptr) {}
    };

    Node* head;         // Head of the list (first visited page).
    Node* currentPage;  // Pointer to the current page in the history.

public:
    // Constructor to initialize an empty history. Both pointers are set to null.
    BrowserHistory() : head(nullptr), currentPage(nullptr) {}

    // Destructor to free all dynamically allocated memory.
    ~BrowserHistory() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    // Visits a new page. This method handles memory management and updates the history.
    // If a new page is visited, any existing 'forward' history is cleared.
    void visit(const std::string& url) {
        // If the user is not at the end of the history, we delete any forward pages.
        if (currentPage && currentPage->next) {
            Node* temp = currentPage->next;
            while (temp) {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
            currentPage->next = nullptr;
        }

        Node* newNode = new Node(url);
        if (currentPage) {
            // Link the new node to the current page.
            currentPage->next = newNode;
            newNode->prev = currentPage;
        } else {
            // If the history is empty, the new node becomes the head.
            head = newNode;
        }
        currentPage = newNode; // Update the current page pointer.
        std::cout << "Visited: " << url << std::endl;
    }

    // Navigates backward in history by moving the currentPage pointer.
    void back() {
        if (currentPage && currentPage->prev) {
            currentPage = currentPage->prev;
            std::cout << "Went back to: " << currentPage->url << std::endl;
        } else {
            std::cout << "No previous page to go back to." << std::endl;
        }
    }

    // Navigates forward in history by moving the currentPage pointer.
    void forward() {
        if (currentPage && currentPage->next) {
            currentPage = currentPage->next;
            std::cout << "Went forward to: " << currentPage->url << std::endl;
        } else {
            std::cout << "No next page to go forward to." << std::endl;
        }
    }

    // Displays the current page to the user.
    void showCurrent() {
        if (currentPage) {
            std::cout << "Current page: " << currentPage->url << std::endl;
        } else {
            std::cout << "No pages visited yet." << std::endl;
        }
    }

    // Displays the full browsing history from the head to the end of the list.
    void showHistory() {
        if (!head) {
            std::cout << "History is empty." << std::endl;
            return;
        }
        std::cout << "\n--- Full History ---\n";
        Node* temp = head;
        while (temp) {
            std::cout << temp->url;
            if (temp == currentPage) {
                std::cout << " <-- Current Page";
            }
            std::cout << std::endl;
            temp = temp->next;
        }
    }
};

// Main function to demonstrate the functionality with a user menu.
int main() {
    BrowserHistory history;
    int choice;
    std::string url;

    do {
        std::cout << "\n--- Browser History Manager ---\n";
        std::cout << "1. Visit New Page\n";
        std::cout << "2. Go Back\n";
        std::cout << "3. Go Forward\n";
        std::cout << "4. Show Current Page\n";
        std::cout << "5. Show Full History\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter URL: ";
                std::cin >> url;
                history.visit(url);
                break;
            case 2:
                history.back();
                break;
            case 3:
                history.forward();
                break;
            case 4:
                history.showCurrent();
                break;
            case 5:
                history.showHistory();
                break;
            case 6:
                std::cout << "Exiting Browser History Manager." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}