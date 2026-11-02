
#include <iostream>
#include <sstream>
#include <string>
#include "LinkedList.h"

using namespace std;

void addTwoNumbers(
    LinkedList<int>& list1,
    LinkedList<int>& list2,
    LinkedList<int>& result
) {
    LinkedList<int>::Node* first = list1.getHead();
    LinkedList<int>::Node* second = list2.getHead();

    int carry = 0;

    while (first != nullptr || second != nullptr || carry > 0) {

        int num1 = 0;
        int num2 = 0;

        // Obtém o dígito da primeira lista
        if (first != nullptr) {
            num1 = first->item;
            first = first->next;
        }

        // Obtém o dígito da segunda lista
        if (second != nullptr) {
            num2 = second->item;
            second = second->next;
        }

        // Soma os dígitos e o transporte
        int soma = num1 + num2 + carry;

        int digito = soma % 10;
        carry = soma / 10;

        // Insere o resultado na nova lista
        result.addLast(digito);
    }
}

int main() {
    LinkedList<int> list1;
    LinkedList<int> list2;
    LinkedList<int> result;

    string line;
    int number;

    // Lê a primeira lista
    getline(cin, line);
    stringstream ss1(line);

    while (ss1 >> number) {
        list1.addLast(number);
    }

    // Lê a segunda lista
    getline(cin, line);
    stringstream ss2(line);

    while (ss2 >> number) {
        list2.addLast(number);
    }

    // Realiza a soma
    addTwoNumbers(list1, list2, result);

    // Imprime o resultado
    LinkedList<int>::Node* current = result.getHead();

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
