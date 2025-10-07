#include <iostream>
#include <vector>
#include <deque>
#include "gtest/gtest.h"
using namespace std;

// Функція для підрахунку розміру пам’яті без виділення
template <typename T>
size_t CreateArrayAtMemory(void*, size_t bs) {
    return bs * sizeof(T);
}

// Рекурсивне обчислення пам’яті та створення масиву
template <typename T, typename ... Args>
size_t CreateArrayAtMemory(void* p, size_t bs, Args ... args) {
    size_t R = 0;
    size_t PS = sizeof(void*);
    char* P = (char*)p;
    char* P0 = (char*)p;

    size_t BytesForAllPointers = bs * PS;
    R = BytesForAllPointers;

    char* pos = P0 + BytesForAllPointers;
    for (size_t i = 0; i < bs; i++) {
        char** pp = (char**)P;
        if (p)
            *pp = pos;
        size_t RLD = CreateArrayAtMemory<T>(p ? pos : nullptr, args...);
        P += PS;
        R += RLD;
        pos += RLD;
    }
    return R;
}

// Виділення пам’яті і створення масиву
template <typename T, typename ... Args>
T CreateArray(Args ... args) {
    size_t n = CreateArrayAtMemory<T>(nullptr, args...); // підрахунок потрібного розміру пам’яті
    char* p = new char[n]; // виділення пам’яті в байтах
    CreateArrayAtMemory<T>(p, args...); // створення масиву
    cout << n << " Byte used\n";
    return (T)p;
}

int main(int argc, char** argv) {
    // Приклад: 2-вимірний масив
    /*
    int j = 0x21;
    size_t n2 = CreateArrayAtMemory<short>(nullptr, 2, 3);
    vector<char> a2(n2);
    short** f2 = (short**)a2.data();
    CreateArrayAtMemory<short>(f2, 2, 3);
    for (int i1 = 0; i1 < 2; i1++) {
        for (int i2 = 0; i2 < 3; i2++) {
            f2[i1][i2] = j++;
        }
    }
    for (int i1 = 0; i1 < 2; i1++) {
        for (int i2 = 0; i2 < 3; i2++) {
            std::cout << (int)f2[i1][i2] << " ";
        }
    }
    std::cout << std::endl << n2 << " bytes used " << std::endl;
    std::cout << std::endl;
    */

    // Приклад: 5-вимірний масив
    /*
    int j = 0x21;
    size_t n5 = CreateArrayAtMemory<int>(nullptr, 2, 3, 4, 5, 6);
    vector<char> a5(n5);
    int***** f5 = (int*****)a5.data();
    CreateArrayAtMemory<int>(f5, 2, 3, 4, 5, 6);
    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            for (int i3 = 0; i3 < 4; i3++)
                for (int i4 = 0; i4 < 5; i4++)
                    for (int i5 = 0; i5 < 6; i5++)
                        f5[i1][i2][i3][i4][i5] = j++;

    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            for (int i3 = 0; i3 < 4; i3++)
                for (int i4 = 0; i4 < 5; i4++)
                    for (int i5 = 0; i5 < 6; i5++)
                        std::cout << (int)f5[i1][i2][i3][i4][i5] << " ";
    std::cout << std::endl << n5 << " bytes used " << std::endl;
    std::cout << std::endl;
    */

    // Динамічний масив
    /*
    int j = 0x21;
    size_t n2 = CreateArrayAtMemory<short>(nullptr, 2, 3);
    char* a2 = new char[n2];
    short** f2 = (short**)a2;
    CreateArrayAtMemory<short>(f2, 2, 3);
    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            f2[i1][i2] = j++;

    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            std::cout << (int)f2[i1][i2] << " ";
    std::cout << std::endl << n2 << " bytes used " << std::endl;
    std::cout << std::endl;
    */

    // СПРОБА НА DEQUE — ТУТ CRASH
    /*
    int j = 0x21;
    size_t n2 = CreateArrayAtMemory<short>(nullptr, 2, 3);
    deque<char> a2(n2);
    short** f2 = (short**)&a2[0];
    CreateArrayAtMemory<short>(f2, 2, 3);
    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            f2[i1][i2] = j++;

    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            std::cout << (int)f2[i1][i2] << " ";
    std::cout << std::endl << n2 << " bytes used " << std::endl;
    std::cout << std::endl;
    */

    // Робочий приклад із CreateArray
    // Глибоке виділення 5-вимірного масиву
    int j = 0x21;
    int***** f = CreateArray<int*****>(2, 3, 4, 5, 6);

    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            for (int i3 = 0; i3 < 4; i3++)
                for (int i4 = 0; i4 < 5; i4++)
                    for (int i5 = 0; i5 < 6; i5++)
                        f[i1][i2][i3][i4][i5] = j++;

    for (int i1 = 0; i1 < 2; i1++)
        for (int i2 = 0; i2 < 3; i2++)
            for (int i3 = 0; i3 < 4; i3++)
                for (int i4 = 0; i4 < 5; i4++)
                    for (int i5 = 0; i5 < 6; i5++)
                        std::cout << f[i1][i2][i3][i4][i5] << " ";

    std::cout << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
