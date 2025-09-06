#include <iostream>
#include <string>

using namespace std;

// Maximum size of history stack
const int MAX_HISTORY = 100;

// Stack Implementation for Browser History
class BrowserHistory {
private:
    string history[MAX_HISTORY];
    int top;

public:
    BrowserHistory() {
        top = -1;
    }

    // Push URL to history
    void visitPage(const string& url) {
        if (top >= MAX_HISTORY - 1) {
            cout << "History full. Cannot visit new page.\n";
            return;
        }
        history[++top] = url;
        cout << "Visited: " << url << endl;
    }

    // Go back in history
    void goBack() {
        if (top <= 0) {
            cout << "No previous page to go back to.\n";
            return;
        }
        top--;
        cout << "Went back to: " << history[top] << endl;
    }

    // Show current page
    void currentPage() {
        if (top == -1) {
            cout << "No pages visited yet.\n";
        } else {
            cout << "Current page: " << history[top] << endl;
        }
    }
};

int main() {
    BrowserHistory bh;
    int choice;
    string url;

    do {
        cout << "\n--- Browser History Manager ---\n";
        cout << "1. Visit New Page\n";
        cout << "2. Go Back\n";
        cout << "3. Show Current Page\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter URL: ";
                cin >> url;
                bh.visitPage(url);
                break;
            case 2:
                bh.goBack();
                break;
            case 3:
                bh.currentPage();
                break;
            case 4:
                cout << "Exiting Browser History Manager.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}