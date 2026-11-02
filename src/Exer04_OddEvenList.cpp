
#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"

using namespace std;

void oddEvenList(LinkedList<int>& list) {
    LinkedList<int>::Node* head = list.getHead();

    if (head == nullptr || head->next == nullptr) {
        return;
    }

    // Ponteiros para as posições ímpares e pares
    LinkedList<int>::Node* odd = head;
    LinkedList<int>::Node* even = head->next;

    // Guarda o início da parte par
    LinkedList<int>::Node* evenHead = even;

    while (even != nullptr && even->next != nullptr) {

        // Conecta o próximo nó ímpar
        odd->next = even->next;
        odd = odd->next;

        // Conecta o próximo nó par
        even->next = odd->next;
        even = even->next;
    }

    // Junta a parte ímpar com a parte par
    odd->next = evenHead;

    // Atualiza a cauda da lista
    if (even != nullptr) {
        list.setTail(even);
    } else {
        list.setTail(odd);
    }
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

    oddEvenList(list);

    LinkedList<int>::Node* current = list.getHead();

    while (current != nullptr) {
        cout << current->item;

        if (current->next != nullptr) {
            cout << " ";
        }

        current = current->next;
    }

    cout << endl;

    return 0;
}
