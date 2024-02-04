#include "list.h" 

using namespace s21;
int main () {

    List<int> l;
    l.push_back(5);
    l.push_back(777);
    l.push_back(2);
    l.show_list();
    std::cout << "\n" << l[0] << " Huynana";
    std::cout << l.get_size(); 


    return 0;
}