#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3New/Set.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SetTests
{
	TEST_CLASS(SetTests)
	{
	public:
		TEST_METHOD(UniqueOperations) //Intersection and Subtraction
		{
			int* firstArr = new int[20]{ 1, 2, 3, 4, 5, 11, 12, 13, 14, 15, 21, 22, 23, 24, 25, -1, -2, -3, -4, -5 };
			int* secondArr = new int[10]{ 0, 2, 4, 6, 8, 10, -2, -4, -6, 14 };
			Set<int> firstSet(firstArr, 20);
			Set<int> secondSet(secondArr, 10);
			Assert::IsTrue(firstSet.GetSize() == 20);
			Assert::IsTrue(secondSet.GetSize() == 10);
			Set<int> resultSet = *(firstSet.Intersection(&secondSet));
			Assert::IsTrue(resultSet.GetSize() == 5);
			int* exceptArr = new int[5]{ 2, 4, -2, -4, 14 };
			Set<int> exceptSet(exceptArr, 5);
			Assert::IsTrue(exceptSet == resultSet);
			resultSet = *(secondSet.Subtraction(&firstSet));
			delete[] exceptArr;
			exceptArr = new int[5]{ 0, 6, 8, 10, -6};
			Set<int> exceptSet2(exceptArr, 5);
			Assert::IsTrue(exceptSet2 == resultSet);
			resultSet = *(secondSet.Subtraction(&secondSet));
			Set<int> exceptSet3;
			Assert::IsTrue(exceptSet3 == resultSet);
		}
	};
}
