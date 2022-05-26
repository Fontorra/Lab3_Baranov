#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3New/BinaryTreeSearch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int FunctionMap(int item) {
	return item * item;
}

bool FunctionWhereFirst(int item) {
	if (item > 3) return true;
	else return false;
}

bool FunctionWhereSecond(int item) {
	return false;
}

int FunctionReduce(int item, int c) {
	return item + c;
}

namespace TreeTests
{
	TEST_CLASS(TreeTests)
	{
	public:
		
		TEST_METHOD(BaseOperations)
		{
			BinaryTreeSearch<int> firstTree;
			firstTree.Insert(10);
			firstTree.Insert(5);
			firstTree.Insert(4);
			firstTree.Insert(2);
			firstTree.Insert(12);
			firstTree.Insert(9);
			firstTree.Insert(0);
			int* arr = firstTree.GetArr();
			int* resultArr = new int[7]{5, 2, 0, 4, 10, 9, 12};
			for (int i = 0; i < 7; i++) {
				Assert::IsTrue(arr[i] == resultArr[i]);
			}
			Assert::IsFalse(firstTree.Find(120));
			Assert::IsTrue(firstTree.Find(10));
			firstTree.deleteKey(100);
			delete[] arr;
			arr = firstTree.GetArr();
			for (int i = 0; i < 7; i++) {
				Assert::IsTrue(arr[i] == resultArr[i]);
			}
			firstTree.deleteKey(2);
			firstTree.deleteKey(0);
			firstTree.deleteKey(4);
			firstTree.deleteKey(9);
			delete[] resultArr;
			resultArr = new int[3]{ 10, 5, 12 };
			delete[] arr;
			arr = firstTree.GetArr();
			for (int i = 0; i < 3; i++) {
				Assert::IsTrue(arr[i] == resultArr[i]);
			}
		}
		TEST_METHOD(MapTest) {
			int* Array = new int[7];
			for (int i = 0; i < 7; i++) Array[i] = i + 1;
			BinaryTreeSearch<int> Tree(Array, 7);
			BinaryTreeSearch<int> resultTree = *(Tree.Map(&FunctionMap));
			int* arr = resultTree.GetArr();
			int* resultArr = new int[7]{ 16, 4, 1, 9, 36, 25, 49 };
			for (int i = 0; i < 7; i++) {
				Assert::IsTrue(arr[i] == resultArr[i]);
			}
		}
		TEST_METHOD(WhereTest) {
			int* Array = new int[10];
			for (int i = 0; i < 10; i++) Array[i] = i + 1;
			BinaryTreeSearch<int> Tree(Array, 10);
			BinaryTreeSearch<int> newTree = *(Tree.Where(&FunctionWhereFirst));
			int* arr = newTree.GetArr();
			int* resultArr = new int[7]{6, 4, 5, 8, 7, 9, 10 };
			for (int i = 0; i < 7; i++) {
				Assert::IsTrue(arr[i] == resultArr[i]);
			}
			newTree = *Tree.Where(&FunctionWhereFirst);
			BinaryTreeSearch<int> resultTree;
			Assert::IsTrue(resultTree == newTree);
		}

		TEST_METHOD(Get_FindSub) {
			int* Array = new int[10];
			for (int i = 0; i < 10; i++) Array[i] = i + 1;
			BinaryTreeSearch<int> Tree(Array, 10);
			BinaryTreeSearch<int> newTree = *(Tree.GetSub(3));
			Assert::IsTrue(Tree.FindSub(&newTree));
			newTree = *(Tree.GetSub(-1));
			BinaryTreeSearch<int> EmptyTree;
			Assert::IsTrue(newTree == EmptyTree);
		}
	};
}
