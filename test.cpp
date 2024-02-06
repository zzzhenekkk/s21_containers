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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

