#include <iostream>
#include <string>

namespace s21 {

template <typename T>
class List {
public:
    List();
    ~List();
    // Добавление элемента в конец листа
    void push_back(T data);
    void show_list();
    int get_size() {return Size;};
    T& operator[](int index);

private:
    class Node { // Убрано повторное объявление шаблона
    public:
        Node* pNext;
        T data;

        // Конструктор для узла
        Node(T data = T(), Node* pNext = nullptr) : data(data), pNext(pNext) {}
    };

    int Size; // Длина списка
    Node* head; // Указатель на первый элемент
};

template <typename T>
List<T>::List() : Size(0), head(nullptr) {} // Инициализация в списке инициализации

template <typename T>
List<T>::~List() {
    // Здесь должен быть код для очистки списка, чтобы не было утечек памяти
}

// Добавление элемента в конец листа
template <typename T>
void List<T>::push_back(T data) {
    if (head == nullptr) {
        head = new Node(data);
    } else {
        Node* current = head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }
    Size++;
}

template <typename T>
void List<T>::show_list() {
    Node* current = head;
    while (current != nullptr) { // Изменено условие для корректного вывода последнего элемента
        std::cout << current->data << std::endl;
        current = current->pNext;
    }
}

template <typename T>
T& List<T>::operator[](int index) {
    Node* current = head;
    if (index >= Size) {
        throw std::invalid_argument("Incorrect index"); 
    } else {
        while (current != nullptr && index > 0) { // Изменено условие для корректного вывода последнего элемента
            current = current->pNext;
            index--;
        }

    }
    
    return current->data;
}


} // namespace s21
