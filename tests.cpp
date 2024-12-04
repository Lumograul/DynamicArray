#include <gtest/gtest.h>
#include "Array.h"

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, InsertAndAccessElements) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, InsertAtSpecificIndex) {
    Array<int> arr;
    arr.insert(0);
    arr.insert(1);
    arr.insert(2);
    arr.insert(1, 10);

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 1);
    EXPECT_EQ(arr[3], 2);
    EXPECT_EQ(arr.size(), 4);
}

TEST(ArrayTest, InsertWithReallocation) {
    Array<int> arr;
    for (int i = 0; i < 20; ++i) {
        arr.insert(i);
    }

    EXPECT_EQ(arr.size(), 20);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[19], 19);
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    arr.insert(0);
    arr.insert(1);
    arr.insert(2);
    arr.remove(1);

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr.size(), 2);
}

TEST(ArrayTest, RemoveElementOutOfBounds) {
    Array<int> arr;
    arr.insert(0);
    arr.insert(1);
    arr.insert(2);

    EXPECT_THROW(arr.remove(3), std::out_of_range);
    EXPECT_THROW(arr.remove(-1), std::out_of_range);
}

TEST(ArrayTest, AccessOutOfBounds) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    EXPECT_THROW(arr[2], std::out_of_range);
    EXPECT_THROW(arr[-1], std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);

    Array<int> copiedArr = arr;

    EXPECT_EQ(copiedArr[0], 1);
    EXPECT_EQ(copiedArr[1], 2);
    EXPECT_EQ(copiedArr.size(), 2);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);

    Array<int> movedArr = std::move(arr);

    EXPECT_EQ(movedArr[0], 1);
    EXPECT_EQ(movedArr[1], 2);
    EXPECT_EQ(movedArr.size(), 2);
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, CopyAssignment) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);

    Array<int> copiedArr;
    copiedArr = arr;

    EXPECT_EQ(copiedArr[0], 1);
    EXPECT_EQ(copiedArr[1], 2);
    EXPECT_EQ(copiedArr.size(), 2);
}

TEST(ArrayTest, MoveAssignment) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);

    Array<int> movedArr;
    movedArr = std::move(arr);

    EXPECT_EQ(movedArr[0], 1);
    EXPECT_EQ(movedArr[1], 2);
    EXPECT_EQ(movedArr.size(), 2);
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, IteratorForward) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    auto it = arr.iterator();
    EXPECT_EQ(it.get(), 1);
    it.next();
    EXPECT_EQ(it.get(), 2);
    it.next();
    EXPECT_EQ(it.get(), 3);
    it.next();
    EXPECT_FALSE(it.hasNext());
}

TEST(ArrayTest, IteratorReverse) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    auto rit = arr.reverseIterator();
    EXPECT_EQ(rit.get(), 3);
    rit.next();
    EXPECT_EQ(rit.get(), 2);
    rit.next();
    EXPECT_EQ(rit.get(), 1);
    rit.next();
    EXPECT_FALSE(rit.hasNext());
}

TEST(ArrayTest, EmptyArray) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(ArrayTest, ClearArray) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    // Очистим массив
    arr.remove(0);
    arr.remove(0);
    arr.remove(0);

    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, ConstIterator) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    auto cit = arr.const_iterator();
    EXPECT_EQ(cit.get(), 1);
    cit.next();
    EXPECT_EQ(cit.get(), 2);
    cit.next();
    EXPECT_EQ(cit.get(), 3);
    cit.next();
    EXPECT_FALSE(cit.hasNext());
}

TEST(ArrayTest, ConstReverseIterator) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    auto cit = arr.const_reverseIterator();
    EXPECT_EQ(cit.get(), 3);
    cit.next();
    EXPECT_EQ(cit.get(), 2);
    cit.next();
    EXPECT_EQ(cit.get(), 1);
    cit.next();
    EXPECT_FALSE(cit.hasNext());
}

TEST(ArrayTest, IteratorSetValue) {
    Array<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    auto it = arr.iterator();
    it.set(10);
    EXPECT_EQ(arr[0], 10);

    auto rit = arr.reverseIterator();
    rit.set(20);
    EXPECT_EQ(arr[2], 20);
}
