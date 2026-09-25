#include "workerdb.hpp"

WorkerData::WorkerData() : name(), age(0), salary(0) {}

WorkerData::WorkerData(const MyString &name, int age, double salary)
    : name(name), age(age), salary(salary) {}

WorkerDb::Node::Node(const MyString &surname)
    : surname(surname), data(), next(nullptr) {}

WorkerDb::WorkerDb() : head(nullptr), tail(nullptr) {}

WorkerDb::~WorkerDb(){
    Node *p = head;
    while (p != nullptr){
        Node *next = p->next;
        delete p;
        p = next;
    }
}

WorkerData& WorkerDb::operator[](const MyString &surname){
    for (Node *p = head; p != nullptr; p = p->next){
        if (p->surname == surname){
            return p->data;
        }
    }

    Node *node = new Node(surname);
    if (head == nullptr){
        head = node;
    }
    else{
        tail->next = node;
    }
    tail = node;
    return node->data;
}

WorkerDb::Iterator WorkerDb::begin(){
    return Iterator(head);
}

WorkerDb::Iterator WorkerDb::end(){
    return Iterator(nullptr);
}

WorkerDb::Iterator::Iterator(Node *node) : node(node) {}

const MyString& WorkerDb::Iterator::key() const {
    return node->surname;
}

WorkerData& WorkerDb::Iterator::operator*() const {
    return node->data;
}

WorkerData* WorkerDb::Iterator::operator->() const {
    return &node->data;
}

WorkerDb::Iterator& WorkerDb::Iterator::operator++(){
    node = node->next;
    return *this;
}

WorkerDb::Iterator WorkerDb::Iterator::operator++(int){
    Iterator old = *this;
    node = node->next;
    return old;
}

bool WorkerDb::Iterator::operator==(const Iterator &other) const {
    return node == other.node;
}

bool WorkerDb::Iterator::operator!=(const Iterator &other) const {
    return node != other.node;
}