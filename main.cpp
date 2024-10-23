#include <iostream>
#include <algorithm>

class MyArray {
private:
    int* arr;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];

        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    MyArray(int numElements) : size(0), capacity(numElements) {
        arr = new int[capacity];
    }

    MyArray(const MyArray& other) : size(other.size), capacity(other.capacity) {
        arr = new int[capacity];
        std::copy(other.arr, other.arr + size, arr);
    }

    MyArray& operator=(const MyArray& other) {
        if (this != &other) {
            delete[] arr;

            size = other.size;
            capacity = other.capacity;
            arr = new int[capacity];
            std::copy(other.arr, other.arr + size, arr);
        }
        return *this;
    }

    MyArray(MyArray&& other) noexcept : arr(other.arr), size(other.size), capacity(other.capacity) {
        other.arr = nullptr; // Обнуляем указатель другого объекта
        other.size = 0;
        other.capacity = 0;
    }

    MyArray& operator=(MyArray&& other) noexcept {
        if (this != &other) {
            delete[] arr;

            arr = other.arr;
            size = other.size;
            capacity = other.capacity;

            other.arr = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    ~MyArray() {
        delete[] arr;
    }

    void add(int value) {
        if (size >= capacity) {
            resize();
        }
        arr[size++] = value;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MyArray myArray(5);
    myArray.add(10);
    myArray.add(20);
    myArray.add(30);
    myArray.add(40);
    myArray.add(50);
    myArray.print();

    MyArray newArray(2);
    newArray.add(44);
    newArray.add(34);

    myArray = newArray;
    myArray.print();

    return 0;
}
