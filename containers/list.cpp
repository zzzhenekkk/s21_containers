#include "list.h" 

using namespace s21;
int main () {

    list<int> l;
    l.push_back(5);
    l.push_back(777);
    l.push_back(2);

    l.push_front(999);
    l.push_front(999);
    l.pop_front();

    
    l.show_list();
    list<int> l2;
    l2.push_front(1);
    // std::cout << "\n" << l[0] << " Huynana";
    std::cout << "\n" << l.size() << "\n\n"; 
    // l.clear();
    // l.show_list();
    // l.pop_back();
    l2.show_list();
    std::cout << "\n" << l2.size() << "\n\n"; 
    l.swap(l2);
    l.show_list();
    l2.show_list();
    return 0;
}