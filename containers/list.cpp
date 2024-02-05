#include "list.h" 

using namespace s21;
int main () {

    List<int> l;
    l.push_back(5);
    l.push_back(777);
    l.push_back(2);

    l.push_front(999);
    l.push_front(999);
    l.pop_front();

    
    l.show_list();
    // std::cout << "\n" << l[0] << " Huynana";
    std::cout << "\n" << l.get_size() << "\n\n"; 
    // l.clear();
    // l.show_list();
    l.pop_back();
    l.show_list();
    std::cout << "\n" << l.get_size() << "\n\n"; 
    return 0;
}