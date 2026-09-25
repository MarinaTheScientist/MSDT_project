#include "list.hpp"
#include <iomanip>
#include <limits>

using namespace std;

List::Node::Node() : pPrev(nullptr), pNext(nullptr), m_Data() {}

List::Node::Node(Node *prev, const Circle *pc) : pPrev(prev), pNext(prev->pNext), m_Data(*pc) {
    prev->pNext->pPrev = this;
    prev->pNext = this;
}

List::Node::~Node(){
    if (pPrev != nullptr){
        pPrev->pNext = pNext;
    }
    if (pNext != nullptr){
        pNext->pPrev = pPrev;
    }
}

List::List() : Head(), Tail(), m_size(0) {
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}

List::List(const List &other) : List() {
    for (Node *p = other.Head.pNext; p != &other.Tail; p = p->pNext){
        push_back(p->m_Data);
    }
}

List& List::operator=(const List &other){
    if (this == &other){
        return *this;
    }
    clear();
    for (Node *p = other.Head.pNext; p != &other.Tail; p = p->pNext){
        push_back(p->m_Data);
    }
    return *this;
}

List::~List(){
    clear();
}

void List::push_front(const Circle &c){
    new Node(&Head, &c);
    m_size++;
}

void List::push_back(const Circle &c){
    new Node(Tail.pPrev, &c);
    m_size++;
}

bool List::remove_first(const Circle &c){
    for (Node *p = Head.pNext; p != &Tail; p = p->pNext){
        if (p->m_Data == c){
            delete p;
            m_size--;
            return true;
        }
    }
    return false;
}

size_t List::remove_all(const Circle &c){
    size_t removed = 0;
    Node *p = Head.pNext;
    while (p != &Tail){
        Node *next = p->pNext;
        if (p->m_Data == c){
            delete p;
            m_size--;
            removed++;
        }
        p = next;
    }
    return removed;
}

void List::clear(){
    while (Head.pNext != &Tail){
        delete Head.pNext;
    }
    m_size = 0;
}

size_t List::size() const {
    return m_size;
}

bool List::empty() const {
    return m_size == 0;
}

void List::sort_by_area(){
    for (Node *i = Head.pNext; i != &Tail; i = i->pNext){
        Node *min = i;
        for (Node *j = i->pNext; j != &Tail; j = j->pNext){
            if (j->m_Data.area() < min->m_Data.area()){
                min = j;
            }
        }
        if (min != i){
            Circle tmp = i->m_Data;
            i->m_Data = min->m_Data;
            min->m_Data = tmp;
        }
    }
}

ostream& operator<<(ostream &os, const List &list){
    os << "Count: " << list.m_size << "\n";
    os << setw(4) << "#"
       << setw(10) << "X"
       << setw(10) << "Y"
       << setw(10) << "Radius"
       << setw(10) << "Area" << "\n";

    ios::fmtflags old_flags = os.flags();
    streamsize old_precision = os.precision();
    os << fixed << setprecision(3);

    int number = 1;
    for (List::Node *p = list.Head.pNext; p != &list.Tail; p = p->pNext){
        const Circle &c = p->m_Data;
        os << setw(4) << number
           << setw(10) << c.get_center().get_x()
           << setw(10) << c.get_center().get_y()
           << setw(10) << c.get_radius()
           << setw(10) << c.area() << "\n";
        number++;
    }

    os.flags(old_flags);
    os.precision(old_precision);
    return os;
}

istream& operator>>(istream &is, List &list){
    list.clear();

    char word[16];
    size_t count;
    is >> setw(16) >> word >> count;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < count; i++){
        int number;
        double x, y, radius, area;
        if (!(is >> number >> x >> y >> radius >> area)){
            break;
        }
        list.push_back(Circle(x, y, radius));
    }
    return is;
}
