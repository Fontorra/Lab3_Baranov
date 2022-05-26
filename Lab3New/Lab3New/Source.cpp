#include <iostream>
#include <string>
#include "BinaryTreeSearch.h"
#include "Set.h"

template <typename T>
/*int SetMenu() {
	int i = 0;
	std::cout << "choose Type:\n1.int\n2.double\n3.string\n4.char\n";
	std::cin >> i;
	switch (i)
	{
	case 1:
		T = int;
		break;
	case 2:
		T = double;
		break;
	case 3:
		T = std::string;
		break;
	case 4:
		T = char;
		break;
	default:
		return 0;
	}
	std::cout << "Set Menu: \n0.Exit\n" << "Input\n" << "Output\n" << "Processing\n" << "map-where\n" << "Operations\n";
	std::cin >> i;

	Set<T> firstSet;
	Set<T> secondSet;
	Set<T> resultSet;
	T item = T();
	int count = 0;
	switch (i)
	{
	case 0:
		return 0;
	case 1:
		std::cout << "Input first Set:\nInput number of elements: ";
		std::cin >> count;
		T* firstArr = new T[count];
		for (int i = 0; i < count; i++) {
			std::cin >> firstArr[i];
		}
		firstSet = new Set<T>(firstArr, count);
		std::cout << "Input secon Set:\nInput number of items and then items: ";
		std::cin >> count;
		T* secondArr = new T[count];
		for (int i = 0; i < count; i++) {
			std::cin >> secondtArr[i];
		}
		secondSet = new Set<T>(secondArr, count);
	default:
		break;
	}

}

int TreeNemu() {
	
}
*/

int foo1(int key) {
	return key * key;
}

bool foo2(int key) {
	if (key > 100) return true;
	return false;
}

int foo3(int x, int c) {
	return x + c;
}

int main2() {
	int* mas = new int[100];
	int k = 2;
	for (int i = 0; i < 10; i++) {
		mas[i] = i * k;
		k *= -1;
	}

	for (int i = 0; i < 10; i++) std::cout << mas[i] << " ";
	std::cout << std::endl;
	BinaryTreeSearch<int> tree(mas, 10);
	/*
	tree.Insert(4);
	tree.Insert(5);
	tree.Insert(10);
	tree.Insert(25);
	tree.Insert(50);
	tree.Insert(100);
	tree.Insert(100);*/
	std::cout << tree.GetSize() << std::endl;
	/*tree.deleteKey(30);
	tree.deleteKey(50);
	tree.deleteKey(29);
	tree.deleteKey(15);
	tree.deleteKey(25);
	tree.deleteKey(100);
	/*tree.Show();
	tree.deleteKey(120);
	tree.Show();
	tree.deleteKey(130);
	tree.Show();
	tree.deleteKey(170);
	tree.Show();
	tree.deleteKey(140);
	tree.Show();
	tree.deleteKey(190);
	tree.Show();
	tree.deleteKey(150);
	tree.Show();
	tree.deleteKey(160);
	tree.Show();
	tree.deleteKey(110);
	tree.Show();
	tree.deleteKey(180);
	tree.Show();
	tree.deleteKey(100);
	tree.Show();*/
	/*int(*foo)(int) = foo1;
	bool(*Foo)(int) = foo2;
	int(*Foo2)(int, int) = foo3;
	BinaryTreeSearch<int>* newTree = tree.Map(foo);
	BinaryTreeSearch<int> new1Tree(tree);
	tree.Show();
	new1Tree.Show();
	BinaryTreeSearch<int>* new2Tree = newTree->Where(Foo);
	newTree->Show();
	new2Tree->Show();*/
	//std::cout << newTree->Reduce(Foo2, 10);
	/*BinaryTreeSearch<int>* new3Tree = newTree->GetSub(196);
	new3Tree->Show();
	std::cout << newTree->FindSub(new3Tree) << " " << newTree->FindSub(&tree) << std::endl;
	BinaryTreeSearch<int>* new11Tree = tree.Merge(newTree);
	new11Tree->Show();
	delete newTree;
	delete new2Tree;
	Set<int> firstSet(mas, 10);
	k = 10;
	for (int i = 0; i < 10; i++) {
		mas[i] = i * k;
		k *= -1;
	}
	Set<int> secondSet(mas, 10);
	Set<int> result = firstSet + secondSet;
	std::cout << std::endl;
	firstSet.Show();
	secondSet.Show();
	result.Show();*/

	k = 10;
	for (int i = 0; i < 100; i++) {
		mas[i] = i * k;
		k *= -1;
	}
	Set<int> firstSet(mas, 10);
	firstSet.Show();
	k = 5;
	for (int i = 0; i < 100; i++) {
		mas[i] = i * k;
		k *= -1;
	}
	Set<int> secondSet(mas, 10);
	secondSet.Show();
	std::cout << "\n\n\n";
	Set<int> resultSet = *(firstSet.Union(&secondSet));
	resultSet.Show();
	std::cout << "\n\n\n";
	resultSet = *(firstSet.Intersection(&secondSet));
	resultSet.Show();
	std::cout << "\n\n\n";
	resultSet = *(firstSet.Subtraction(&secondSet));
	resultSet.Show();
	std::cout << "\n\n\n";
	delete[] mas;
	return 0;
}

int FunctionMap(int item) {
	return item * item;
}

bool FunctionWhereFirst(int item) {
	if (item > 3) return true;
	else return false;
}

int main() {
	int* Array = new int[10];
	for (int i = 0; i < 10; i++) Array[i] = i + 1;
	BinaryTreeSearch<int> Tree(Array, 10);
	BinaryTreeSearch<int> newTree = *(Tree.Where(&FunctionWhereFirst));
	int* arr = newTree.GetArr();
	int* resultArr = new int[7]{ 7, 5, 4, 6, 9, 8, 10 };
	for (int i = 0; i < 7; i++) {
		std::cout << arr[i] << " " << resultArr[i] << "\n";
	}
	return 0;
}