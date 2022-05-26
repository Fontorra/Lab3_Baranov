#pragma once

#include "BinaryTreeSearch.h"

template <class T>

class Set {
private:
	BinaryTreeSearch<T>* items = new BinaryTreeSearch<T>;
public:

	Set(T* items, int count) {
		this->items = new BinaryTreeSearch<T>(items, count);
	}

	Set() {
		items = new BinaryTreeSearch<T>;
	}

	Set(const Set<T>& set) {
		*(this->items) = *(set.items);
	}

	Set<T>& operator = (const Set<T>& set) {
		*(this->items) = *(set.items);
		return *this;
	}

	~Set() {
		delete items;
	}

	T* GetSet() {
		return this->items->GetArr();
	}

	Set<T>* Map(T(*foo) (T)) {
		Set<T>* newSet = new Set<T>;
		newSet->items = this->items->Map(foo);
		return newSet;
	}

	Set<T>* Where(T(*foo)(T)) {
		Set<T>* newSet = new Set<T>;
		newSet->items = this->items->Where(foo);
		return newSet;
	}

	Set<T>* Reduce(T(*foo) (T, T), T Const) {
		Set<T>* newSet = new Set<T>;
		newSet->items = this->items->Reduce(foo, Const);
		return newSet;
	}

	void Insert(T item) {
		this->items->Insert(item);
	}

	void Remove(T item) {
		this->items->deleteKey(item);
	}

	int GetSize() {
		return this->items->GetSize();
	}

	bool Find(T Key) {
		return this->items->Find(Key);
	}

	void Show() {
		return this->items->Show();
	}

	bool FindSub(const Set<T> set) {
		return this->items->FindSub(set.items);
	}

	bool operator ==(Set<T> set) {
		if (this->items->GetSize() == set.items->GetSize()) {
			T* thisArr = this->items->GetArr();
			int thisSize = this->GetSize();
			T* setArr = set.items->GetArr();
			int setSize = set.GetSize();
			if ((thisArr == nullptr && thisSize > 0) || (setArr == nullptr && setSize > 0)) throw std::exception("NotEnoughMemory");
			if (thisSize < setSize) {
				for (int i = 0; i < thisSize; i++) {
					if (!set.Find(thisArr[i])) {
						delete[] thisArr;
						delete[] setArr;
						return false;
					}
				}
			}
			else {
				for (int i = 0; i < setSize; i++) {
					if (!this->Find(setArr[i])) {
						delete[] thisArr;
						delete[] setArr;
						return false;
					}
				}
			}
			delete[] thisArr;
			delete[] setArr;
			return true;
		}
		return false;
	}

	Set<T>* Union(Set<T>* set) { //Merge
		Set<T>* newSet = new Set<T>;
		newSet->items = this->items->Merge(set->items);
		return newSet;
	}

	Set<T>* Intersection(Set<T>* set) {
		Set<T>* newSet = new Set<T>;
		T* thisArr = this->items->GetArr();
		int thisSize = this->GetSize();
		T* setArr = set->items->GetArr();
		int setSize = set->GetSize();
		if ((thisArr == nullptr && thisSize > 0) || (setArr == nullptr && setSize > 0)) throw std::exception("NotEnoughMemory");
		if (thisSize < setSize) {
			for (int i = 0; i < thisSize; i++) {
				if (set->Find(thisArr[i])) newSet->Insert(thisArr[i]);
			}
		}
		else {
			for (int i = 0; i < setSize; i++) {
				if (this->Find(setArr[i])) newSet->Insert(setArr[i]);
			}
		}
		delete[] thisArr;
		delete[] setArr;
		return newSet;
	}

	Set<T>* Subtraction(Set<T>* set) {
		Set<T>* newSet = new Set<T>(*this);
		T* setArr = set->items->GetArr();
		int setSize = set->GetSize();
		if ((setArr == nullptr && setSize > 0)) throw std::exception("NotEnoughMemory");
		for (int i = 0; i < setSize; i++) {
			newSet->Remove(setArr[i]);
		}
		delete[] setArr;
		return newSet;
	}
};