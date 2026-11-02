
#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"

using namespace std;

void removeDuplicates(LinkedList<int>& list) {
    LinkedList<int>::Node* current = list.getHead();

    while (current != nullptr && current->next != nullptr) {

        if (current->item == current->next->item) {

            // Guarda o nó que será removido
            LinkedList<int>::Node* duplicate = current->next;

            // Atualiza a ligação antes de excluir
            current->next = duplicate->next;

            // Atualiza a cauda se o último nó foi removido
            if (duplicate->next == nullptr) {
                list.setTail(current);
            }

            // Libera a memória do nó duplicado
            delete duplicate;

            // Atualiza a quantidade de elementos
            list.decreaseCount();

        } else {
            current = current->next;
        }
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

    removeDuplicates(list);

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
