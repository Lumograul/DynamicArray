#include "Array.h"
#include <iostream>

int main() {
    Array<int> arr;

    // Вставляем элементы в массив
    arr.insert(10);
    arr.insert(20);
    arr.insert(30);

    // Используем обычный итератор, чтобы изменить значения
    for (auto it = arr.iterator(); it.hasNext(); it.next()) {
        std::cout << "Before change: " << it.get() << std::endl;
        it.get() += 5; // Изменяем значения через обычный итератор
    }

    // Используем константный итератор для чтения значений (изменять нельзя)
    for (auto cit = arr.const_iterator(); cit.hasNext(); cit.next()) {
        std::cout << "ConstIterator: " << cit.get() << std::endl;
        // cit.get() += 5; // Это вызовет ошибку компиляции, так как get() константный
    }
    return 0;
}
