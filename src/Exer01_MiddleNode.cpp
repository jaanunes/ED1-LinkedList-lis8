
#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"

using namespace std;

void middleNode(LinkedList<int>& list) {
    LinkedList<int>::Node* slow = list.getHead();
    LinkedList<int>::Node* fast = list.getHead();

    // Encontra o nó central
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Imprime a partir do nó central
    LinkedList<int>::Node* current = slow;

    while (current != nullptr) {
        cout << current->item;

        if (current->next != nullptr) {
            cout << " ";
        }

        current = current->next;
    }

    cout << endl;
}

int main() {
    LinkedList<int> list;

    string line;
    getline(cin, line);

    stringstream ss(line);
    int number;

    while (ss >> number) {
        list.addLast(number);
    }

    middleNode(list);

    return 0;
}
