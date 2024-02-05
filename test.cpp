#include <gtest/gtest.h>
#include "containers/list.h"

namespace s21 {

TEST(ListTest, PushBackTest) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(ListTest, PushFrontTest) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list[0], 3);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 1);
}

TEST(ListTest, PopBackTest) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.pop_back();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 1);
}

TEST(ListTest, PopFrontTest) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.pop_front();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list[0], 1);
}

TEST(ListTest, ClearTest) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    EXPECT_EQ(list.get_size(), 0);
}

TEST(ListTest, AccessTest) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
    // Проверка на выброс исключения при доступе за пределы списка
    EXPECT_THROW(list[2], std::out_of_range);
}

} // namespace s21

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}