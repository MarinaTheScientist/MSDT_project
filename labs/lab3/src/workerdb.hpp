#pragma once
#include "mystring.hpp"

struct WorkerData
{
    MyString name;
    int age;
    double salary;

    WorkerData();
    WorkerData(const MyString &name, int age, double salary);
};

class WorkerDb
{
private:
    struct Node
    {
        MyString surname;
        WorkerData data;
        Node *next;

        Node(const MyString &surname);
    };

    Node *head;
    Node *tail;

public:
    class Iterator
    {
    private:
        Node *node;

        Iterator(Node *node);
        friend class WorkerDb;

    public:
        const MyString& key() const;

        WorkerData& operator*() const;
        WorkerData* operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;
    };

    WorkerDb();
    ~WorkerDb();

    WorkerData& operator[](const MyString &surname);

    Iterator begin();
    Iterator end();
};