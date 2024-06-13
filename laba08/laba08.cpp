#include <iostream>

template<class T>
class MyUnique {
    T* p;
public:
    MyUnique(T* p) : p(p) {}
    ~MyUnique() { delete p; }

    T* get() const { return p; }
    T& operator*() { return *p; }
    T* operator->() { return p; }

    // Запрет копирования
    MyUnique(const MyUnique&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;

    // Оператор перемещения
    MyUnique(MyUnique&& other) noexcept : p(other.p) {
        other.p = nullptr;
    }
    MyUnique& operator=(MyUnique&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        return *this;
    }
};

// Глобальная шаблонная функция Make_MyUnique
template<typename T, typename... Args>
MyUnique<T> Make_MyUnique(Args&&... args) {
    return MyUnique<T>(new T(std::forward<Args>(args)...));
}

// Пример класса для демонстрации
class MyPoint {
    int x, y;
public:
    MyPoint(int x, int y) : x(x), y(y) {
        std::cout << "MyPoint(" << x << ", " << y << ")\n";
    }
};

int main() {
    auto point = Make_MyUnique<MyPoint>(1, 2);
    return 0;
}