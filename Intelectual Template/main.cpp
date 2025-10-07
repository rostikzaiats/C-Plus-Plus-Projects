#include <iostream>
#include <typeinfo>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <Windows.h>
#include <gtest/gtest.h>
using namespace std;

// Завдання 1.
template<typename Cont>
void printContainer(const Cont& C, ostream& out)
{
	if (typeid(C).name() == typeid(vector<typename Cont::value_type>).name())
	{
		if (!C.empty())
		{
			for (auto it = C.begin(); it != C.end(); it++)
			{
				out << "[" << *it << "]" << ' ';
			}
		}
		else
		{
			out << '[' << "empty" << ']';
		}
	}
}

template<typename T>
class Unique_Cont
{
};

template<typename T>
class Unique_Cont<vector<T>>
{
public:
	inline static const string view = "*** Вектор ***";
	inline static const string start = "[";
	inline static const string end = "]";
	inline static const string empty = "порожній";
};

template<typename T>
class Unique_Cont<list<T>>
{
public:
	inline static const string view = "*** Двобічний список ***";
	inline static const string start = "<";
	inline static const string end = ">";
	inline static const string empty = "порожній";
};

template<typename T>
class Unique_Cont<set<T>>
{
public:
	inline static const string view = "*** Множина ***";
	inline static const string start = "{";
	inline static const string end = "}";
	inline static const string empty = "порожня";
};

template<typename Container>
void printCont(const Container& C, ostream& out)
{
	Unique_Cont<Container> temp;
	out << temp.view << '\n';
	if (!C.empty())
	{
		for (auto it = C.begin(); it != C.end(); ++it)
		{
			out << temp.start << *it << temp.end << ' ';
		}
	}
	else
	{
		out << temp.start << temp.empty << temp.end;
	}
}

int main(int argc, char** argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<int> v1{};
	printContainer(v1, cout);
	cout << endl;

	printCont(v1, cout);
	cout << endl;

	set s1{ 10, 20, 30 };
	printCont(s1, cout);
	cout << endl;

	list<string> l1;
	printCont(l1, cout);
	cout << endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(PrintContainerTest, EmptyVector) {
	ostringstream out;
	vector<int> v;
	printContainer(v, out);
	EXPECT_EQ(out.str(), "[empty]");
}

TEST(PrintContainerTest, NonEmptyVector) {
	ostringstream out;
	vector<int> v = { 1, 2, 3 };
	printContainer(v, out);
	EXPECT_EQ(out.str(), "[1] [2] [3] ");
}

TEST(PrintContTest, VectorOutput) {
	ostringstream out;
	vector<int> v = { 5, 10 };
	printCont(v, out);
	EXPECT_EQ(out.str(), "*** Вектор ***\n[5] [10] ");
}

TEST(PrintContTest, EmptyListOutput) {
	ostringstream out;
	list<string> l;
	printCont(l, out);
	EXPECT_EQ(out.str(), "*** Двобічний список ***\n<порожній>");
}

TEST(PrintContTest, SetOutput) {
	ostringstream out;
	set<int> s = { 100, 200 };
	printCont(s, out);
	EXPECT_EQ(out.str(), "*** Множина ***\n{100} {200} ");
}
