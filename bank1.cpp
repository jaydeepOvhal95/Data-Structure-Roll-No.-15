#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;
    int token;

    cout << "BANK TOKEN MANAGEMENT SYSTEM\n";
    cout << "Enter token numbers for 5 customers:\n";

    // Accept token numbers
    for (int i = 1; i <= 5; i++) {
        cout << "Enter token number for customer " << i << ": ";
        cin >> token;
        q.push(token);
    }

    // Serve customers in the same order
    cout << "\nServing customers in order:\n";

    while (!q.empty()) {
        cout << "Serving customer with token number: "
             << q.front() << endl;
        q.pop();
    }

    return 0;
}
