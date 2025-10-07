#include "pch.h"
#include"C:\Users\rosti\source\repos\DJ KAVUN\DJ KAVUN\main.cpp"

TEST(CreateArrayAtMemory, Creating) {
	size_t n = CreateArrayAtMemory<int>(nullptr, 2, 3, 4, 5);
	EXPECT_EQ(n, sizeof(int) * 2 * 3 * 4 * 5);

}
TEST(CreateArrayAtMemory, CreatingButTypes)
{
	size_t double_n = CreateArrayAtMemory<double>(nullptr, 2, 3, 4, 5, 6);
	EXPECT_EQ(double_n, sizeof(double) * 2 * 3 * 4 * 5 * 6);

	size_t char_n = CreateArrayAtMemory<char>(nullptr, 2, 3, 4);
	EXPECT_EQ(char_n, sizeof(char) * 2 * 3 * 4);

	size_t short_n = CreateArrayAtMemory<short>(nullptr, 2, 3);
	EXPECT_EQ(short_n, sizeof(short) * 2 * 3);
}
TEST(CreateArrayAtMemory, CreatingZero)
{
	size_t n = CreateArrayAtMemory<int>(nullptr, 0);
	EXPECT_EQ(n, 0);
}
TEST(CreateArray, IntValuesFillTest) {
    int*** arr = CreateArray<int***>(2, 3, 4);
    int val = 100;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 4; ++k)
                arr[i][j][k] = val++;

    val = 100;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 4; ++k)
                EXPECT_EQ(arr[i][j][k], val++);
}

TEST(CreateArray, ShortArrayTest) {
    short** arr = CreateArray<short**>(2, 3);
    short x = 50;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            arr[i][j] = x++;

    x = 50;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_EQ(arr[i][j], x++);
}
