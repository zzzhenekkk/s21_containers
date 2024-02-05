#include <iostream>
#include <stdexcept> // Для std::out_of_range

namespace s21 {

template <typename T>
class List {
public:
    // обьявление итератора
    class iterator;

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    

    List();
    ~List();

    // методы для работы со списком
    void push_back(const value_type& data); // Используем const_reference для данных
    void show_list();
    size_type get_size() { return Size; }
    reference operator[](size_type index);
    void pop_front();
    void pop_back();
    void push_front(const value_type& data);
    void clear();

    // методы для работы с итератором
    iterator begin();
    iterator end();


private:

    class Node;

    size_type Size; // Используем size_type для размера списка
    Node* head_;
    Node* tail_;
};

// --------------------------------------- классы ------------------------------------------
template <typename T>
class List<T>::Node {
    public:
        value_type data;
        Node* pNext;
        Node* pPrev;

        Node(const value_type& data = value_type(), Node* pNext = nullptr, Node* pPrev = nullptr) : data(data), pNext(pNext), pPrev(pPrev) {}
};


template <typename T>
class List<T>::iterator {
private:
    Node * current; // Текущий узел, на который указывает итератор

public:
    iterator(Node * node) : current(node) {}

    // Оператор разыменования
    T& operator*() { return current->data; }

    // Оператор инкремента для перехода к следующему элементу
    iterator& operator++() {
        current = current->next;
        return *this;
    }

    // Оператор инкремента (постфиксный)
    iterator operator++(int) {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    // Операторы сравнения
    bool operator==(const iterator& other) const { return current == other.current; }
    bool operator!=(const iterator& other) const { return !(*this == other); }
    
};


// ------------------------------------- для итератора -------------------------------------

template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head_);
}




template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(nullptr);
}



// ------------------------------------- конструкторы и деструкторы list -------------------------------------

template <typename T>
List<T>::List() : Size(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
List<T>::~List() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->pNext;
        delete current;
        current = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    Size = 0;
}

// --------------------------------------- методы -------------------------------------

template <typename T>
void List<T>::push_back(const value_type& data) {
    Node* newNode = new Node(data);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        tail_->pNext = newNode;
        newNode->pPrev=tail_;
        tail_ = newNode;
    }
    Size++;
}

template <typename T>
void List<T>::show_list() {
    Node* current = head_;
    if (current == nullptr)
        std::cout << "empty list\n";
    while (current != nullptr) {
        std::cout << current->data << std::endl;
        current = current->pNext;
    }
}



template <typename T>
void List<T>::pop_front() {
    if (head_ != nullptr) {
        Node * temp = head_;
        head_ = head_->pNext;
        head_->pPrev = nullptr;
        delete temp;
    } else {
        throw std::out_of_range("List is empty");
    }
    Size--;
}

template <typename T>
void List<T>::pop_back() {
    if (tail_ != nullptr) {
        Node * temp = tail_;
        tail_ = tail_->pPrev;
        tail_->pNext = nullptr;
        delete temp;
    } else {
        throw std::out_of_range("List is empty");
    }
    Size--;
}

template <typename T>
void List<T>::push_front(const value_type& data) {
    Node* newNode = new Node(data);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        newNode->pNext = head_;
        head_->pPrev = newNode;
        head_ = newNode;
    }
    Size++;
}


template <typename T>
void List<T>::clear() {
    this->~List();
}

// --------------------------------- определение операторов ------------------------------------
template <typename T>
T& List<T>::operator[](size_type index) {
    if (index >= Size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head_;
    while (index-- > 0) {
        current = current->pNext;
    }
    return current->data;
}

} // namespace s21
