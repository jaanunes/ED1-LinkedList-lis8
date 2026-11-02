
#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"

using namespace std;

bool isPalindrome(LinkedList<int>& list) {
    if (list.getHead() == nullptr || list.getHead()->next == nullptr) {
        return true;
    }

    // Encontra a metade da lista
    LinkedList<int>::Node* slow = list.getHead();
    LinkedList<int>::Node* fast = list.getHead();

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Inverte a segunda metade
    LinkedList<int>::Node* previous = nullptr;
    LinkedList<int>::Node* current = slow->next;

    while (current != nullptr) {
        LinkedList<int>::Node* nextNode = current->next;

        current->next = previous;
        previous = current;
        current = nextNode;
    }

    slow->next = previous;

    // Compara a primeira metade com a segunda invertida
    LinkedList<int>::Node* first = list.getHead();
    LinkedList<int>::Node* second = slow->next;

    bool palindrome = true;

    while (second != nullptr) {
        if (first->item != second->item) {
            palindrome = false;
            break;
        }

        first = first->next;
        second = second->next;
    }

    // Restaura a segunda metade
    previous = nullptr;
    current = slow->next;

    while (current != nullptr) {
        LinkedList<int>::Node* nextNode = current->next;

        current->next = previous;
        previous = current;
        current = nextNode;
    }

    slow->next = previous;

    return palindrome;
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

    if (isPalindrome(list)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
