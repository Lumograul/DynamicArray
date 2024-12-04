#pragma once
#include <iostream>
#include <stdexcept>
#include <cassert>  // Для использования assert в отладочной версии

template<typename T>
class Array {
private:
    T* data;
    int capacity;
    int currentSize;

    void clear() {
        for (int i = 0; i < currentSize; ++i) {
            data[i].~T();
        }
        currentSize = 0;
    }

    void reallocate() {
        capacity = static_cast<int>(capacity * 1.6);
        T* newData = new T[capacity];
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
    }

public:
    Array(int cap = 8) : capacity(cap), currentSize(0) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }

    // Конструктор копирования
    Array(const Array& other) : capacity(other.capacity), currentSize(other.currentSize) {
        data = new T[capacity];
        for (int i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];  // Копируем элементы
        }
    }

    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;  // Освобождаем текущую память
            capacity = other.capacity;
            currentSize = other.currentSize;
            data = new T[capacity];
            for (int i = 0; i < currentSize; ++i) {
                data[i] = other.data[i];  // Копируем элементы
            }
        }
        return *this;
    }

    // Оператор перемещения
    Array(Array&& other) noexcept : data(other.data), capacity(other.capacity), currentSize(other.currentSize) {
        other.data = nullptr;
        other.capacity = 0;
        other.currentSize = 0;
    }

    // Оператор перемещения присваивания
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            currentSize = other.currentSize;
            other.data = nullptr;
            other.capacity = 0;
            other.currentSize = 0;
        }
        return *this;
    }

    // Вставка элемента в конец
    int insert(const T& value) {
        if (currentSize == capacity) {
            reallocate();
        }
        data[currentSize++] = value;
        return currentSize - 1;
    }

    // Вставка элемента в заданную позицию
    int insert(int index, const T& value) {
        if (index < 0 || index > currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        if (currentSize == capacity) {
            reallocate();
        }
        for (int i = currentSize; i > index; --i) {
            data[i] = std::move(data[i - 1]);  // Сдвигаем элементы вправо
        }
        data[index] = value;
        ++currentSize;
        return index;
    }

    // Удаление элемента по индексу
    void remove(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        for (int i = index; i < currentSize - 1; ++i) {
            data[i] = std::move(data[i + 1]);  // Сдвигаем элементы влево
        }
        --currentSize;
    }

    // Получение элемента по индексу
    const T& operator[](int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    T& operator[](int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Получение текущего размера
    int size() const {
        return currentSize;
    }

    class Iterator {
    private:
        T* ptr;
        Array<T>& array;

    public:
        Iterator(T* p, Array<T>& arr) : ptr(p), array(arr) {}

        T& get() const { return *ptr; }

        void set(const T& value) { *ptr = value; }

        void next() { if (hasNext()) ++ptr; }

        bool hasNext() const { return ptr < (array.data + array.currentSize); }
    };

    Iterator iterator() {
        return Iterator(data, *this);
    }

    class ConstIterator {
    private:
        const T* ptr;
        const Array<T>& array;

    public:
        ConstIterator(const T* p, const Array<T>& arr) : ptr(p), array(arr) {}

        const T& get() const { return *ptr; }

        void next() { if(hasNext()) ++ptr; }

        bool hasNext() const { return ptr < (array.data + array.currentSize); }
    };

    ConstIterator const_iterator() const {
        return ConstIterator(data, *this);  // Константный итератор для прямого обхода
    }

    class ReverseIterator {
    private:
        T* ptr;
        Array<T>& array;

    public:
        ReverseIterator(T* p, Array<T>& arr) : ptr(p), array(arr) {}

        T& get() const { return *ptr; }

        void set(const T& value) { *ptr = value; }

        void next() { if(hasNext()) --ptr; }

        bool hasNext() const { return ptr >= (array.data); }
    };

    ReverseIterator reverseIterator() {
        return ReverseIterator(data + currentSize - 1, *this);
    }

    class ConstReverseIterator {
    private:
        const T* ptr;
        const Array<T>& array;

    public:
        ConstReverseIterator(const T* p, const Array<T>& arr) : ptr(p), array(arr) {}

        const T& get() const { return *ptr; }

        void next() { if(hasNext()) --ptr; }

        bool hasNext() const { return ptr >= (array.data); }
    };

    ConstReverseIterator const_reverseIterator() const {
        return ConstReverseIterator(data + currentSize - 1, *this);
    }

};
