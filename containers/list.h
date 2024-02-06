#include <iostream>
#include <stdexcept> // для std::out_of_range
#include <limits> // для max_size()

namespace s21 {

template <typename T>
class list {
public:
    // -------------------  обьявление итератора -------------------
    class ListIterator;
    class ListConstIterator;
    
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;
    using size_type = size_t;

    // -------------------  конструкторы и деструкторы -------------------
    list();
    list(size_type n);
    list(std::initializer_list<value_type> const &items); // инициализация с помощью списка инициализации
    list(const list &l); // copy constructor
    list(list &&l); // move constructor
    ~list();

    list& operator=(list &&l);


    // -------------------  методы для работы со списком -------------------
    bool empty() {return !size_;} // checks whether the container is empty
    size_type size() {return size_;} // returns the number of elements
    size_type max_size() { return std::numeric_limits<size_type>::max();} // returns the maximum possible number of elements

    void push_back(const value_type& data);
    void show_list();
    reference operator[](size_type index);
    void pop_front();
    void pop_back();
    void push_front(const value_type& data);
    void clear();
    iterator insert(iterator pos, const_reference value); // inserts element into concrete pos and returns the iterator that points to the new element
    void erase(iterator pos); //erases element at pos
    reference front() noexcept { return *begin(); }; //access the first element
    const_reference front() const noexcept { return *begin(); }
    // reference back() { return *std::prev(end()); }
    // ------------------- методы для работы с итератором -------------------
    iterator begin();
    iterator end();
    ListConstIterator begin() const;
    ListConstIterator end() const;


private:

    class Node;

    size_type size_{};
    Node* head_{};
    Node* tail_{};
};

// --------------------------------------- классы ------------------------------------------
template <typename T>
class list<T>::Node {
    public:
        value_type data;
        Node* pNext;
        Node* pPrev;

        Node(const value_type& data = value_type(), Node* pNext = nullptr, Node* pPrev = nullptr) : data(data), pNext(pNext), pPrev(pPrev) {}
        // Node(const Node & node);
        // Node(Node && node);
};


template <typename T>
class list<T>::ListIterator {
private:
    Node * current; // Текущий узел, на который указывает итератор
    list<T>& pList;

public:
    ListIterator(Node * node = nullptr, list<T>& pList = nullptr) : current(node), pList(pList) {}

    // Оператор разыменования
    T& operator*() { return current->data; }

    // Оператор инкремента для перехода к следующему элементу
    ListIterator& operator++() {
        current = current->pNext;
        return *this;
    }

    // Оператор инкремента (постфиксный)
    ListIterator operator++(int) {
        ListIterator temp = *this;
        ++(*this);
        return temp;
    }

    // Оператор декримента для перехода к следующему элементу
    ListIterator& operator--() {
        if (current == pList.head_)
            current = pList.tail_;
        else if (current!=nullptr)
            current = current->pPrev;
        else 
            current = pList.tail_;
        return *this;
    }
    
    // Оператор декримента для перехода к следующему элементу
    ListIterator& operator--(int) {
        ListIterator temp = *this;
        --(*this);
        return temp;
    }

    // Операторы сравнения
    bool operator==(const ListIterator& other) const { return current == other.current; }
    bool operator!=(const ListIterator& other) const { return !(current == other.current); }

};

template <typename T>
class list<T>::ListConstIterator {
private:
    const Node * current; // Текущий узел, на который указывает итератор
    const list<T>& pList;

public:
    ListConstIterator(const Node* node, const list<T>& pList) : current(node), pList(pList) {}

    // Оператор разыменования
    const T& operator*() const { return current->data; }

    // Оператор инкремента для перехода к следующему элементу
    ListConstIterator& operator++() {
        current = current->pNext;
        return *this;
    }

    // Оператор инкремента (постфиксный)
    ListConstIterator operator++(int) {
        ListConstIterator temp = *this;
        ++(*this);
        return temp;
    }

        // Оператор декримента для перехода к следующему элементу
    ListConstIterator& operator--() {
        if (current == pList.head_)
            current = pList.tail_;
        else if (current!=nullptr)
            current = current->pPrev;
        else 
            current = pList.tail_;
        return *this;
    }
    
    // Оператор декримента для перехода к следующему элементу
    ListConstIterator& operator--(int) {
        ListConstIterator temp = *this;
        --(*this);
        return temp;
    }

    // Операторы сравнения
    bool operator==(const ListConstIterator& other) const { return current == other.current; }
    bool operator!=(const ListConstIterator& other) const { return !(*this == other); }
    // ListConstIterator operator=(ListConstIterator& other) {return ListConstIterator(other.current, other.pList); };
    // bool operator!=(const ListConstIterator& other) const { return current != other.current; }


};


// ------------------------------------- для node -------------------------------------
    // template <typename T>
    // list<T>Node(const Node & node) {

    // }

    // template <typename T>    
    // list<T>Node(Node && node) {

    // }
// ------------------------------------- для итератора -------------------------------------

template <typename T>
typename list<T>::ListIterator list<T>::begin() {
    return ListIterator(head_, *this);
}


template <typename T>
typename list<T>::ListIterator list<T>::end() {
    return ListIterator(nullptr, *this);
}

template <typename T>
typename list<T>::ListConstIterator list<T>::begin() const{
    return ListConstIterator(head_, *this);
}


template <typename T>
typename list<T>::ListConstIterator list<T>::end() const{
    return ListConstIterator(nullptr, *this);
}



// ------------------------------------- конструкторы и деструкторы list -------------------------------------

template <typename T>
list<T>::list() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
list<T>::~list() {
    clear();
}

template <typename T>
list<T>::list(size_type n) : size_(0), head_(nullptr), tail_(nullptr) {
    for (size_type i = 0; i < n; ++i) {
        push_back(T{}); // Добавляем элементы со значением по умолчанию
    }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : size_(0), head_(nullptr), tail_(nullptr) {
    
    for (const T& item : items) {
        push_back(item);
    }
}

template <typename T>
list<T>::list(const list &l) {
    size_ = 0;
    
    for (auto it = l.begin(); it != l.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
list<T>::list(list &&l) {
    size_ = l.size_;
    head_ = l.head_;
    tail_ = l.tail_;
    l.size_ = 0;
    l.head_ = nullptr;
    l.tail_ = nullptr;
}

// --------------------------------------- методы -------------------------------------


template <typename T>
void list<T>::erase(iterator pos) {
    iterator it = this->begin();
    iterator last = this->end();
    --last;
    if (it == pos)
        pop_front();
    else if (pos == last) 
        pop_back();
    else {
        Node *current = head_;
        Node *tmp;
        --pos;
        while (it != pos) {
            current = current->pNext;
            ++it;
        }
        tmp = current->pNext;
        tmp->pNext->pPrev = current;
        current->pNext = tmp->pNext;
        delete tmp;
        size_--;
    }
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListIterator pos, const_reference value) {
    Node* newNode = new Node(value);
    Node* current = head_;
    iterator it = this->begin();
    // если вначале 
    if (it == pos) {
        push_front(value);
        --it;
    } // если в конце
    else if (pos == this->end()) {
        push_back(value);
        --it;
    } // если по середине
    else {
        --pos;
        while (it != pos){
            ++it;
            current = current->pNext;
        }
        newNode->pNext = current->pNext;
        current->pNext = newNode;
        newNode->pPrev = current;
        newNode->pNext->pPrev = newNode;
        ++it;
        size_++;
    }
    return it;
}

template <typename T>
list<T>& list<T>::operator=(list &&l)  {
    clear();
    size_ = l.size_;
    head_ = l.head_;
    tail_ = l.tail_;
    l.size_ = 0;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    return *this;
}

template <typename T>
void list<T>::push_back(const value_type& data) {
    Node* newNode = new Node(data);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        tail_->pNext = newNode;
        newNode->pPrev=tail_;
        tail_ = newNode;
    }
    size_++;
}

template <typename T>
void list<T>::show_list() {
    Node* current = head_;
    if (current == nullptr)
        std::cout << "empty list\n";
    while (current != nullptr) {
        std::cout << current->data << std::endl;
        current = current->pNext;
    }
}



template <typename T>
void list<T>::pop_front() {
    if (head_ != nullptr) {
        Node * temp = head_;
        if (head_->pNext != nullptr)
            head_ = head_->pNext;
        head_->pPrev = nullptr;
        delete temp;
    } else {
        throw std::out_of_range("List is empty");
    }
    size_--;
}

template <typename T>
void list<T>::pop_back() {
    if (tail_ != nullptr) {
        Node * temp = tail_;
        if (tail_->pPrev != nullptr)
            tail_ = tail_->pPrev;
        tail_->pNext = nullptr;
        delete temp;
    } else {
        throw std::out_of_range("List is empty");
    }
    size_--;
}

template <typename T>
void list<T>::push_front(const value_type& data) {
    Node* newNode = new Node(data);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    } else {
        newNode->pNext = head_;
        head_->pPrev = newNode;
        head_ = newNode;
    }
    size_++;
}


template <typename T>
void list<T>::clear() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->pNext;
        delete current;
        current = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

// --------------------------------- определение операторов ------------------------------------
template <typename T>
T& list<T>::operator[](size_type index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head_;
    while (index-- > 0) {
        current = current->pNext;
    }
    return current->data;
}

} // namespace s21
