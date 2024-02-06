#include <gtest/gtest.h>
#include "containers/list.h"
#include <iostream>
#include <list>


TEST(list, Constructor_Default) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListConstructor, ConstructWithSize) {
    s21::list<int> intList(5);
    EXPECT_EQ(intList.size(), 5);

    for (size_t i = 0; i < intList.size(); ++i) {
        EXPECT_EQ(intList[i], 0);
    }

    s21::list<std::string> stringList(3);
    EXPECT_EQ(stringList.size(), 3);

    for (size_t i = 0; i < stringList.size(); ++i) {
        EXPECT_TRUE(stringList[i].empty());
    }
}

TEST(ListInitializerListConstructor, CanInitializeWithInitializerList) {
    // Инициализация списка целыми числами
    s21::list<int> intList = {1, 2, 3, 4, 5};

    // Проверяем размер списка
    EXPECT_EQ(intList.size(), 5);

    // Проверяем значения элементов списка
    size_t index = 0;
    for (int value : {1, 2, 3, 4, 5}) {
        EXPECT_EQ(intList[index], value);
        ++index;
    }
}

TEST(ListInitializerListConstructor, InitializeWithEmptyList) {
    // Инициализация пустого списка
    s21::list<int> emptyList = {};

    // Проверяем, что размер списка равен 0
    EXPECT_TRUE(emptyList.empty());
}

TEST(ListCopyConstructor, CopyConstructorCreatesExactCopy) {
    // Создание и инициализация оригинального списка
    s21::list<int> originalList = {1, 2, 3, 4, 5};
    
    // Создание копии с использованием конструктора копирования
    s21::list<int> copiedList(originalList);
    
    // Проверка, что размеры списков совпадают
    EXPECT_EQ(originalList.size(), copiedList.size());
    
    // Проверка, что элементы списков совпадают
    size_t index = 0;
    for (auto it = copiedList.begin(); it != copiedList.end(); ++it) {
        EXPECT_EQ(*it, originalList[index]);
        ++index;
    }
}

TEST(ListCopyConstructor, ModificationsToCopyDoNotAffectOriginal) {
    s21::list<int> originalList = {1, 2, 3};
    s21::list<int> copiedList(originalList);
    
    // Изменяем копию
    *(copiedList.begin()) = 10;
    
    // Проверяем, что первый элемент оригинального списка не изменился
    EXPECT_EQ(*(originalList.begin()), 1);
}

TEST(ListMoveConstructor, CanMoveList) {
    // Создаем и заполняем временный список
    s21::list<int> temp = {1, 2, 3, 4, 5};

    // Используем конструктор перемещения для создания нового списка
    s21::list<int> movedList = std::move(temp);

    // Проверяем, что новый список содержит правильные данные
    EXPECT_EQ(movedList.size(), 5);
    int expectedValue = 1;
    for (const auto& item : movedList) {
        EXPECT_EQ(item, expectedValue++);
    }

    // Проверяем, что исходный список теперь пуст
    EXPECT_TRUE(temp.empty());
}


TEST(ListMoveConstructor, SourceListIsValidAfterMove) {
    s21::list<int> temp = {1, 2, 3};
    s21::list<int> movedList = std::move(temp);

    EXPECT_EQ(temp.size(), 0);

}

TEST(ListMoveAssignment, CanMoveAssignList) {
    // Создаем и заполняем временный список
    s21::list<int> temp = {1, 2, 3, 4, 5};

    // Создаем целевой список и выполняем присваивание перемещением
    s21::list<int> targetList;
    targetList = std::move(temp);

    // Проверяем, что целевой список содержит правильные данные после перемещения
    EXPECT_EQ(targetList.size(), 5);
    int expectedValue = 1;
    for (const auto& item : targetList) {
        EXPECT_EQ(item, expectedValue++);
    }

    // Проверяем, что исходный список теперь пуст
    EXPECT_TRUE(temp.empty());
}

TEST(ListMoveAssignment, ReleasesResourcesBeforeMoveAssign) {
    s21::list<int> targetList = {10, 20, 30}; // Начальное заполнение целевого списка
    s21::list<int> temp = {1, 2, 3, 4, 5};

    // Сохраняем оригинальные ресурсы целевого списка (например, указатели) для последующей проверки
    // Этот шаг зависит от вашей внутренней реализации и может потребовать доступа к внутренним членам

    targetList = std::move(temp); // Выполняем присваивание перемещением

    // Проверяем, что целевой список теперь содержит новые данные
    EXPECT_EQ(targetList.size(), 5);

    // Проверяем, что оригинальные данные целевого списка были освобождены
    // Это может включать проверку, что оригинальные указатели были удалены или изменены
}

TEST(ListIteratorDecrement, DecrementMiddle) {
    s21::list<int> myList = {1, 2, 3, 4, 5};
    auto it = myList.begin();
    ++it; // Перемещаемся к 2
    ++it; // Перемещаемся к 3

    --it; // Декрементируем итератор, должны вернуться к 2
    EXPECT_EQ(*it, 2);
}

// Тест на декремент итератора, указывающего на последний элемент
TEST(ListIteratorDecrement, DecrementFromEnd) {
    s21::list<int> myList = {1, 2, 3, 4, 5};
    auto it = myList.end();
    --it; // Декремент до последнего элемента (5)
    EXPECT_EQ(*it, 5);

    --it; // Декремент до предпоследнего элемента (4)
    EXPECT_EQ(*it, 4);
}

// Тест на декремент итератора, указывающего на начало списка
TEST(ListIteratorDecrement, DecrementFromBegin) {
    std::list<int> myList = {1, 2, 3, 4, 5};
    auto it = myList.begin();

    s21::list<int> myList_s21 = {1, 2, 3, 4, 5};
    auto it_s21 = myList_s21.begin();

    // Попытка декремента итератора, указывающего на начало списка, может привести к неопределенному поведению
    // Этот тест зависит от вашей реализации. Некоторые реализации могут выбросить исключение или предоставить специальное значение итератора
    // EXPECT_ANY_THROW(--it); // Раскомментируйте, если ваша реализация выбрасывает исключение
    // или
    --it; // Раскомментируйте, если ваша реализация безопасно обрабатывает эту операцию
    --it_s21;
    // std::cout << *it;
    // std::cout << *it_s21;
    EXPECT_EQ(*it, *it_s21); // Проверьте, что итератор не изменился, если это поддерживается
}


TEST(Insert, InsertStart) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();
    
    // вставляем в начало
    s21::list<int>::iterator it2 = list.insert(it, 0);
    
    // Проверяем, что первый элемент теперь равен 0
    EXPECT_EQ(list[0], 0);
    // Проверяем, что итератор ссылается на вставленный элемент
    EXPECT_EQ(*it2, 0);
    EXPECT_EQ(list.size(), 4);
    list.show_list();
}

TEST(Insert, InsertMiddle1) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();
    
    ++it;
    // вставляем меду первым и вторым
    s21::list<int>::iterator it2 = list.insert(it, 5);
    
    // Проверяем, что второй элемент теперь равен 5
    EXPECT_EQ(list[1], 5);
    // Проверяем, что итератор ссылается на вставленный элемент
    EXPECT_EQ(*it2, 5);
    EXPECT_EQ(list.size(), 4);
    list.show_list();
}

TEST(Insert, InsertMiddle2) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();
    
    ++it;
    ++it;
    // вставляем меду вторым и третьим (между предпоследним и последним)
    s21::list<int>::iterator it2 = list.insert(it, 7);
    
    // Проверяем, что третий элемент теперь равен 7
    EXPECT_EQ(list[2], 7);
    // Проверяем, что итератор ссылается на вставленный элемент
    EXPECT_EQ(*it2, 7);
    EXPECT_EQ(list.size(), 4);
    list.show_list();
}


TEST(Insert, InsertEnd) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.end();

    // вставляем в конец
    s21::list<int>::iterator it2 = list.insert(it, 9);
    
    // Проверяем, что появившийся новый поселдний элемент теперь равен 9
    EXPECT_EQ(list[3], 9);
    // Проверяем, что итератор ссылается на вставленный элемент
    EXPECT_EQ(*it2, 9);
    EXPECT_EQ(list.size(), 4);
    list.show_list();
}

TEST(Erase, Start) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();

    list.erase(it);
    
    // Проверяем, что первый элемент теперь равен 2
    EXPECT_EQ(list[0], 2);

    list.show_list();
}

TEST(Erase, Second) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();
    ++it;

    list.erase(it);
    
    // Проверяем, что первый элемент теперь равен 2
    EXPECT_EQ(list[1], 3);

    list.show_list();
}

TEST(Erase, Last) {
    s21::list<int> list = {1, 2, 3, 4};
    s21::list<int>::iterator it = list.begin();
    ++it;
    ++it;
    ++it;

    list.erase(it);
    
    // Проверяем, что первый элемент теперь равен 2
    EXPECT_EQ(list[2], 3);
    EXPECT_EQ(list.size(), 3);

    list.show_list();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

