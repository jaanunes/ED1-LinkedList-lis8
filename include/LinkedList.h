#ifndef ED1_LINKED_LIST_CPP_LINKEDLIST_H
#define ED1_LINKED_LIST_CPP_LINKEDLIST_H

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T>
class LinkedList : public List<T> {

public:

    // Estrutura de cada nó da lista
    struct Node {
        T item;
        Node* next;

        explicit Node(const T& item)
            : item(item), next(nullptr) {}

        Node(const T& item, Node* next)
            : item(item), next(next) {}
    };

private:

    Node* head;
    Node* tail;
    int count;

    const int NOT_FOUND = -1;
    const std::string DOES_NOT_EXIST = "Position does not exist.";
    const std::string LIST_EMPTY = "List is empty.";

    bool positionDoesNotExist(int position) const {
        return !(position >= 0 && position < count);
    }

    Node* searchNode(int position) const {

        if (positionDoesNotExist(position)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }

        Node* currentNode = head;

        for (int i = 0; i < position; i++) {
            currentNode = currentNode->next;
        }

        return currentNode;
    }

public:
    // Retorna o primeiro nó da lista
    Node* getHead() const {
        return head;
    }

    Node* getTail() const {
        return tail;
    }

    // Atualiza o último nó da lista
    void setTail(Node* node) {
        tail = node;
    }

    // Diminui a quantidade de nós após uma remoção manual
    void decreaseCount() {
        count--;
    }

    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // Destructor to free dynamically allocated heap memory across all nodes
    ~LinkedList() override {
        clear();
    }

    int size() const override {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    // Inserts a new item at the beginning of the list
    void addFirst(const T& item) override {
        Node* newNode = new Node(item, head);

        if (count == 0) {
            head = newNode;
            tail = newNode;
        } else {
            head = newNode;
        }

        count++;
    }

    // Inserts a new item at the end of the list using the tail pointer
    void addLast(const T& item) override {
        Node* newNode = new Node(item);

        if (count == 0) {
            head = newNode;
        } else {
            tail->next = newNode;
        }

        tail = newNode;
        count++;
    }

    // Inserts a new item at a specific index
    void insertAt(int index, const T& item) override {
        if (index < 0 || index > count) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }

        if (index == 0) {
            addFirst(item);
        } else if (index == count) {
            addLast(item);
        } else {
            Node* previousNode = searchNode(index - 1);
            Node* newNode = new Node(item, previousNode->next);
            previousNode->next = newNode;
            count++;
        }
    }

    // Inserts a new item in ascending sorted order (requires operator '<' for type T)
    void addSorted(const T& item) override {
        if (count == 0 || !(head->item < item)) {
            addFirst(item);
        } else if (!(item < tail->item)) {
            addLast(item);
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->item < item) {
                current = current->next;
            }
            Node* newNode = new Node(item, current->next);
            current->next = newNode;
            count++;
        }
    }

    // Removes and returns the first element of the list
    T removeFirst() override {
        if (count == 0) {
            throw std::runtime_error(LIST_EMPTY);
        }

        Node* nodeToDelete = head;
        T removed = nodeToDelete->item;

        head = head->next;
        delete nodeToDelete;
        count--;

        if (count == 0) {
            tail = nullptr;
        }

        return removed;
    }

    // Removes and returns the last element of the list
    T removeLast() override {
        if (count == 0) {
            throw std::runtime_error(LIST_EMPTY);
        }

        // Single element edge case
        if (count == 1) {
            return removeFirst();
        }

        Node* penultimateNode = searchNode(count - 2);
        Node* nodeToDelete = penultimateNode->next;
        T removed = nodeToDelete->item;

        penultimateNode->next = nullptr;
        tail = penultimateNode;
        delete nodeToDelete;
        count--;

        return removed;
    }

    // Removes and returns the element at a specific index
    T removeAt(int index) override {
        if (positionDoesNotExist(index)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }

        if (index == 0) {
            return removeFirst();
        }

        if (index == count - 1) {
            return removeLast();
        }

        Node* previousNode = searchNode(index - 1);
        Node* current = previousNode->next;
        Node* nextNode = current->next;

        previousNode->next = nextNode;
        T removed = current->item;
        delete current;

        count--;
        return removed;
    }

    // Removes the first occurrence of the specified item
    bool remove(const T& item) override {
        int position = find(item);

        if (position == NOT_FOUND) {
            return false;
        }

        removeAt(position);
        return true;
    }

    // Deallocates all nodes and resets the list to an empty state
    void clear() override {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Performs a linear search and returns the index of the item, or NOT_FOUND (-1)
    int find(const T& item) const override {
        Node* current = head;
        int index = 0;

        while (current != nullptr) {
            if (current->item == item) {
                return index;
            }
            current = current->next;
            index++;
        }
        return NOT_FOUND;
    }

    // Retrieves the item stored at a specific index
    T get(int index) const override {
        return searchNode(index)->item;
    }

    // Updates the item stored at a specific index
    void set(int index, const T& item) override {
        Node* node = searchNode(index);
        node->item = item;
    }

    // Generates a string representation of the list in array format [item1, item2, ...]
    std::string toString() const {
        if (count == 0) {
            return "[]";
        }

        std::ostringstream builder;
        builder << "[";
        Node* current = head;

        while (current != nullptr) {
            builder << current->item;
            if (current->next != nullptr) {
                builder << ", ";
            }
            current = current->next;
        }

        builder << "]";
        return builder.str();
    }

    // =====================================================================
    // LISTA 08 - Técnicas avançadas em listas encadeadas
    // =====================================================================

    // Q1 - Retorna os itens do nó central até o fim, separados por espaço.
    // Fast/Slow em uma única passagem. Em tamanho par, devolve o 2º nó central.
    std::string middleToSpacedString() const {
        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return joinFrom(slow);
    }

    // Q2 - Verifica se a lista é palíndromo com O(1) de espaço extra.
    // 1) acha o meio (fast/slow); 2) inverte a 2ª metade in-place;
    // 3) compara as metades; 4) restaura a lista original.
    bool isPalindrome() {
        if (count <= 1) {
            return true;
        }

        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // slow é o início da 2ª metade; o nó anterior continua apontando para ele,
        // então depois de inverter e reinverter a ligação se restabelece sozinha.
        Node* reversedHead = reverseFrom(slow);

        bool palindrome = true;
        Node* left = head;
        Node* right = reversedHead;
        while (right != nullptr) {
            if (!(left->item == right->item)) {
                palindrome = false;
                break;
            }
            left = left->next;
            right = right->next;
        }

        reverseFrom(reversedHead); // restaura a estrutura original
        return palindrome;
    }

    // Q3 - Remove duplicatas de uma lista ORDENADA (não decrescente), com delete.
    void removeDuplicates() {
        Node* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->item == current->next->item) {
                Node* duplicate = current->next;   // nó redundante
                current->next = duplicate->next;   // 1º remapeia o ponteiro
                if (duplicate == tail) {
                    tail = current;
                }
                delete duplicate;                  // 2º libera a memória
                count--;
            } else {
                current = current->next;
            }
        }
    }

    // Q4 - Agrupa os nós de posição ímpar e depois os de posição par (in-place).
    // A posição é a ordem do nó (1º, 2º, 3º...) e não o valor armazenado.
    void oddEvenList() {
        if (count <= 2) {
            return;
        }

        Node* odd = head;
        Node* even = head->next;
        Node* evenHead = even;
        Node* lastEven = even;

        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
            if (even != nullptr) {
                lastEven = even;
            }
        }

        odd->next = evenHead;   // liga o fim dos ímpares ao início dos pares
        tail = lastEven;        // o último nó da lista agora é o último par
    }

    // Q5 - Define esta lista como a soma de duas listas de dígitos em ordem reversa
    // (head = unidades). Usa nó sentinela (dummy) e variável carry.
    void setToSumOf(const LinkedList& a, const LinkedList& b) {
        if (&a == this || &b == this) {
            throw std::invalid_argument("Destination list must be different from operands.");
        }

        clear();

        Node dummy{T()};
        Node* last = &dummy;
        const Node* p = a.head;
        const Node* q = b.head;
        int carry = 0;

        while (p != nullptr || q != nullptr || carry != 0) {
            int sum = carry;

            if (p != nullptr) {
                sum += p->item;
                p = p->next;
            }
            if (q != nullptr) {
                sum += q->item;
                q = q->next;
            }

            carry = sum / 10;
            Node* newNode = new Node(static_cast<T>(sum % 10));
            last->next = newNode;
            last = newNode;
            count++;
        }

        head = dummy.next;
        tail = (head != nullptr) ? last : nullptr;
    }

    // Itens separados por espaço (formato de saída da Lista 08)
    std::string toSpacedString() const {
        return joinFrom(head);
    }

private:
    // Inverte in-place a cadeia que começa em 'start' e devolve o novo início
    Node* reverseFrom(Node* start) {
        Node* previous = nullptr;
        Node* current = start;

        while (current != nullptr) {
            Node* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        return previous;
    }

    // Concatena os itens a partir de 'start' até o fim, separados por espaço
    std::string joinFrom(const Node* start) const {
        std::ostringstream builder;
        for (const Node* current = start; current != nullptr; current = current->next) {
            builder << current->item;
            if (current->next != nullptr) {
                builder << " ";
            }
        }
        return builder.str();
    }
};

#endif // ED1_LINKED_LIST_CPP_LINKEDLIST_H