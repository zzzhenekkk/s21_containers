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
        EXPECT_EQ(*it, originalList[index]) << "Element at index " << index << " does not match";
        ++index;
    }
}

TEST(ListCopyConstructor, ModificationsToCopyDoNotAffectOriginal) {
    s21::list<int> originalList = {1, 2, 3};
    s21::list<int> copiedList(originalList);
    
    // Изменяем копию
    *copiedList.begin() = 10;
    
    // Проверяем, что первый элемент оригинального списка не изменился
    EXPECT_EQ(*originalList.begin(), 1);
}

TEST(Insert, InsertStart) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();
    
    // вставляем в начало
    s21::list<int>::iterator it2 = list.insert(it, 0);
    
    // Проверяем, что первый элемент теперь равен 0
    EXPECT_EQ(list[0], 0);
    // Проверяем, что итератор ссылается на втсавленный элемент
    EXPECT_EQ(*it2, 0);
    list.show_list();
}

TEST(Insert, InsertMiddle1) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();
    
    ++it;
    // вставляем меду первым и вторым
    s21::list<int>::iterator it2 = list.insert(it, 5);
    
    // Проверяем, что второй элемент теперь равен 0
    EXPECT_EQ(list[1], 5);
    // Проверяем, что итератор ссылается на втсавленный элемент
    EXPECT_EQ(*it2, 5);
    list.show_list();
}

TEST(Insert, InsertMiddle2) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.begin();
    
    ++it;
    ++it;
    // вставляем меду вторым и третьим (между предпоследним и последним)
    s21::list<int>::iterator it2 = list.insert(it, 7);
    
    // Проверяем, что второй элемент теперь равен 0
    EXPECT_EQ(list[2], 7);
    // Проверяем, что итератор ссылается на втсавленный элемент
    EXPECT_EQ(*it2, 7);
    list.show_list();
}


TEST(Insert, InsertEnd) {
    s21::list<int> list = {1, 2, 3};
    s21::list<int>::iterator it = list.end();
    
    // ++it;
    // ++it;
    // ++it;
    // вставляем в конец
    s21::list<int>::iterator it2 = list.insert(it, 9);
    
    // Проверяем, что второй элемент теперь равен 0
    EXPECT_EQ(list[3], 9);
    // Проверяем, что итератор ссылается на втсавленный элемент
    EXPECT_EQ(*it2, 9);
    list.show_list();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}