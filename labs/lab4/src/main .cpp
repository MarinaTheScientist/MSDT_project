#include <iostream>
#include <fstream>
#include "list.hpp"

using namespace std;

Circle global_circle(0, 0, 3);

int main(){
    Circle local(1, 1, 1);
    Circle *dynamic = new Circle(2, -2, 2);

    List l;
    l.push_back(global_circle);
    l.push_back(local);
    l.push_back(*dynamic);
    l.push_front(Circle(5, 5, 0.5));
    l.push_back(local);
    delete dynamic;

    cout << "Initial list:\n" << l << "\n";

    cout << "remove_first(Circle(9, 9, 9)) = " << l.remove_first(Circle(9, 9, 9)) << "\n";
    cout << "remove_first(global_circle)   = " << l.remove_first(global_circle) << "\n";
    cout << "remove_all(local)             = " << l.remove_all(local) << "\n";
    cout << "\nAfter removing:\n" << l << "\n";

    l.push_back(Circle(0, 0, 10));
    l.push_front(Circle(3, 4, 0.1));
    l.push_back(Circle(-1, 7, 1.5));
    cout << "Before sorting:\n" << l << "\n";
    l.sort_by_area();
    cout << "Sorted by area:\n" << l << "\n";

    List copy = l;
    l.clear();
    cout << "After clear: original size = " << l.size()
         << ", copy size = " << copy.size() << "\n\n";

    cout << "Enter Output File Name - ";
    char ar[80];
    cin >> ar;
    ofstream fout(ar);
    if (!fout){
        cout << "Cannot open file " << ar << "\n";
        return 1;
    }
    fout << copy;
    fout.close();

    List from_file;
    ifstream fin(ar);
    fin >> from_file;
    fin.close();
    cout << "\nRead from file " << ar << ":\n" << from_file;

    return 0;
}
