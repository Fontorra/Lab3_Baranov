#pragma once
template <class T>

class BinaryTreeSearch {
private:
	enum choose {
		Left,
		Right,
		Root
	};

	typedef struct Node {
		T key;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
		int balance = 0; // h(left) - h(right)

			Node() {
				key = T();
			}

			Node(T item) {
				key = item;
		}

		Node(T item, int Balance) {
			key = item;
			balance = Balance;
		}

	}Node;

	Node* root = nullptr;

	void rotateLeft(Node* node) {
		Node* nextNode = node->right;
		if (nextNode == nullptr) {
			int i = 0;
		}
		node->right = nextNode->left;
		if (nextNode->left != nullptr) nextNode->left->parent = node;
		nextNode->left = node;
		nextNode->parent = node->parent;
		if (node->parent != nullptr) {
			if (node->parent->left == node) {
				node->parent->left = nextNode;
			}
			else {
				node->parent->right = nextNode;
			}
		}
		node->parent = nextNode;
		if (/*node->balance == -2 &&*/ nextNode->balance == -1) {
			node->balance = 0;
			nextNode->balance = 0;
		}
		else {
			if (/*node->balance == -2 &&*/ nextNode->balance == 0) {
				node->balance = -1;
				nextNode->balance = 1;
			}
		}
		if (node == root) root = nextNode;
	}

	void rotateRight(Node* node) {
		Node* nextNode = node->left;
		node->left = nextNode->right;
		if (nextNode->right != nullptr) nextNode->right->parent = node;
		nextNode->right = node;
		nextNode->parent = node->parent;
		if (node->parent != nullptr) {
			if (node->parent->left == node) {
				node->parent->left = nextNode;
			}
			else {
				node->parent->right = nextNode;
			}
		}
		node->parent = nextNode;
		if (/*node->balance == 2 && */ nextNode->balance == 1) {
			node->balance = 0;
			nextNode->balance = 0;
		}
		else {
			if (/*node->balance == 2 && */nextNode->balance == 0) {
				node->balance = 1;
				nextNode->balance = -1;
			}
		}
		if (node == root) root = nextNode;
	}

	void bigRotateLeft(Node* node) {
 		Node* rNode = node->right;
		Node* rlNode = node->right->left;
		rotateRight(node->right);
		rotateLeft(node);
		if (rlNode->balance == 1) {
			node->balance = 0;
			rNode->balance = -1;
			rlNode->balance = 0;
		}
		if (rlNode->balance == -1) {
			node->balance = 1;
			rNode->balance = 0;
			rlNode->balance = 0;
		}
		if (rlNode->balance == 0) {
			node->balance = 0;
			rNode->balance = 0;
			rlNode->balance = 0;
		}
	}

	void bigRotateRight(Node* node) {
		Node* lNode = node->left;
		Node* lrNode = node->left->right;
		rotateLeft(node->left);
		rotateRight(node);
		if (lrNode->balance == -1) {
			node->balance = 0;
			lNode->balance = 1;
			lrNode->balance = 0;
		}
		if (lrNode->balance == 1) {
			node->balance = -1;
			lNode->balance = 0;
			lrNode->balance = 0;
		}
		if (lrNode->balance == 0) {
			node->balance = 0;
			lNode->balance = 0;
			lrNode->balance = 0;
		}
	}

	void Rotate(Node* node) {
		if (node->balance == -2) {
			if (node->right->balance == -1 || node->right->balance == 0) {
				rotateLeft(node);
			}
			else {
				bigRotateLeft(node);
			}
		}
		if (node->balance == 2) {
			if (node->left->balance == 1 || node->left->balance == 0) {
				rotateRight(node);
			}
			else {
				bigRotateRight(node);
			}
		}
	}


public:

	//
	void Show() {
		ShowNode(root);
		std::cout << std::endl;
	}
	//
	BinaryTreeSearch() {

	}

	BinaryTreeSearch(T* items, int count) {
		for (int i = 0; i < count; i++) {
			Insert(items[i]);
		}
	}

	BinaryTreeSearch(const BinaryTreeSearch<T>& Tree) {
		if (Tree.root != nullptr) {
			root = new Node(Tree.root->key, Tree.root->balance);
			CopyNode(root, Tree.root->left, Left);
			CopyNode(root, Tree.root->right, Right);
		}
		else {
			root == nullptr;
		}
	}

	BinaryTreeSearch<T>& operator = (const BinaryTreeSearch<T>& Tree) {
		deleteTree(root);
		if (Tree.root != nullptr) {
			root = new Node(Tree.root->key, Tree.root->balance);
			CopyNode(root, Tree.root->left, Left);
			CopyNode(root, Tree.root->right, Right);
		}
		else {
			root = nullptr;
		}
		return *this;
	}

	~BinaryTreeSearch() {
		deleteTree(root);
	}

	bool operator == (BinaryTreeSearch<T>& tree) {
		if (this->GetSize() == tree.GetSize()) {
			return this->FindSub(&tree);
		}
	}

	int GetSize() {
		int count = 0;
		doGetSize(root, count);
		return count;
	}

	void Insert(T Key) {
		if (root == nullptr) {
			root = new Node(Key);
		}
		else {
			doInsert(root, nullptr, Key, Root);
		}
	}

	bool Find(T Key) {
		if (doFind(root, Key) != nullptr) return true;
		return false;
	}

	int deleteKey(T Key) {
		doDeleteKey(root, Key);
		return 0;
	}

	BinaryTreeSearch<T>* Map(T(*foo)(T)) {
		BinaryTreeSearch<T>* newTree = new BinaryTreeSearch<T>;
		if (root == nullptr) return newTree;
		doMap(*newTree, root, foo);
		return newTree;
	}

	BinaryTreeSearch<T>* Where(bool(*foo)(T)) {
		BinaryTreeSearch<T>* newTree = new BinaryTreeSearch<T>;
		if (root == nullptr) return newTree;
		doWhere(*newTree, root, foo);
		return newTree;
	}

	T Reduce(T(*foo)(T, T), T Const) {
		T result = Const;
		if (root == nullptr) return result;
		doReduce(root, foo, result);
		return result;
	}

	BinaryTreeSearch<T>* Merge(BinaryTreeSearch<T>* Tree) { //this funcion create a new Tree
		BinaryTreeSearch<T>* newTree = new BinaryTreeSearch<T>(*this);
		doMerge(newTree, Tree->root);
		return newTree;
	}

	void Concat(BinaryTreeSearch<T>* Tree) { //this function is changing existing Tree
		doMerge(*this, Tree->root);
	}

	BinaryTreeSearch<T>* GetSub(T Key) {
		Node* node = doFind(root, Key);
		BinaryTreeSearch<T>* newTree = new BinaryTreeSearch<T>;
		if (node == nullptr) return newTree;
		newTree->root = new Node(Key, node->balance);
		CopyNode(newTree->root, node->left, Left);
		CopyNode(newTree->root, node->right, Right);
		return newTree;
	}	  
	
	bool FindSub(BinaryTreeSearch<T>* Tree) {
		if (root == nullptr) return true;
		Node* node = doFind(root, Tree->root->key);
		return doFindSub(node, Tree->root);
	}

	T* GetArr() {
		int size = GetSize();
		try {
			T* arr = new T[size];
			int index = 0;
			doArr(arr, root, index);
			return arr;
		}
		catch (...) {
			return nullptr;
		}
	}

private:

	void doArr(T* arr, Node* node, int& index) {
		if (node != nullptr) {
			arr[index] = node->key;
			index++;
			doArr(arr, node->left, index);
			doArr(arr, node->right, index);
		}
	}

	void doGetSize(Node* node, int& count) {
		if (node != nullptr) {
			count++;
			doGetSize(node->left, count);
			doGetSize(node->right, count);
		}
	}

	void doMerge(BinaryTreeSearch<T>* newTree, Node* node) {
		if (node != nullptr) {
			newTree->Insert(node->key);
			doMerge(newTree, node->left);
			doMerge(newTree, node->right);
		}
	}

	bool doFindSub(Node* thisNode, Node* treeNode) {
		if (treeNode == nullptr) return true;
		if (thisNode == nullptr) return false;
		if (thisNode->key != treeNode->key) return false;
		return (doFindSub(thisNode->left, treeNode->left) &&
			doFindSub(thisNode->right, treeNode->right));
	}

	Node* doFind(Node* node, T Key) {
		if (node == nullptr) return nullptr;
		if (node->key == Key) return node;
		if (Key > node->key) doFind(node->right, Key);
		else doFind(node->left, Key);
	}

	void CopyNode(Node* prevNode, Node* node, choose ident) {
		if (node != nullptr) {
			Node* newNode = new Node(node->key, node->balance);
			newNode->parent = prevNode;
			if (ident == Left) prevNode->left = newNode;
			else prevNode->right = newNode;
			CopyNode(newNode, node->left, Left);
			CopyNode(newNode, node->right, Right);
		}
	}

	void doMap(BinaryTreeSearch<T>& newTree, Node* node, T(*foo)(T)) {
		if (node != nullptr) {
			newTree.Insert(foo(node->key));
			doMap(newTree, node->left, foo);
			doMap(newTree, node->right, foo);
		}
	}

	void doWhere(BinaryTreeSearch<T>& newTree, Node* node, bool(*foo)(T)) {
		if (node != nullptr) {
			if (foo(node->key)) newTree.Insert(node->key);
			doWhere(newTree, node->left, foo);
			doWhere(newTree, node->right, foo);
		}
	}

	void doReduce(Node* node, T(*foo)(T, T), T& result) {
		if (node != nullptr) {
			result = foo(node->key, result);
			doReduce(node->left, foo, result);
			doReduce(node->right, foo, result);
		}
	}

	void ShowNode(Node* node) {
		if (node != nullptr) {
			std::cout << node->key << " ";
			ShowNode(node->left);
			ShowNode(node->right);
		}
	}

	choose findParent(Node* node) {
		if (node->parent == nullptr) return Root;
		if (node->parent->left == node) return Left;
		return Right;
	}

	int doInsert(Node* node, Node* prevNode, T Key, choose ident) {
		if (node == nullptr) {
			node = new Node(Key);
			node->parent = prevNode;
			if (prevNode == nullptr) return 0;
			if (ident == Left) prevNode->left = node;
			if (ident == Right) prevNode->right = node;
			while (node != nullptr) { 
				choose ident = findParent(node);
				if (ident == Left) {
					node = node->parent;
					node->balance++;
					if (node->balance == 2) Rotate(node);
					if (node->balance == 0) return 0;
				}
				if (ident == Right) {
					node = node->parent;
					node->balance--;
					if (node->balance == -2) Rotate(node);
					if (node->balance == 0) return 0;
				}
				if (ident == Root) {
					return 0;
				}
			}
		}

		if (Key < node->key) {
			return doInsert(node->left, node, Key, Left);
		}

		if (Key > node->key) {
			return doInsert(node->right, node, Key, Right);
		}

		if (Key == node->key) return -1;
	}

	int doDeleteKey(Node* node, T Key) {
		Node* delNode = doFind(root, Key);
		if (delNode == nullptr) return 0;
		return deleteNode(delNode);
	}

	int deleteNode(Node* node) {
		Node* nowNode = nullptr;
		choose ident = Root;
		if (node->right != nullptr) {
			Node* minNode = node->right;
			ident = Right;
			while (minNode->left != nullptr) {
				minNode = minNode->left;
				ident = Left;
			}
			node->key = minNode->key;
			nowNode = minNode->parent;
			if (ident == Left) {
				minNode->parent->left = minNode->right;
				if (minNode->right != nullptr) minNode->right->parent = minNode->parent;
			}
			if (ident == Right) {
				minNode->parent->right = minNode->right;
				if (minNode->right != nullptr) minNode->right->parent = minNode->parent;
			}
			delete minNode;
		}
		else {
			if (node->left != nullptr) {
				Node* maxNode = node->left;
				ident = Left;
				while (maxNode->right != nullptr) {
					maxNode = maxNode->right;
					ident = Right;
				}
				node->key = maxNode->key;
				nowNode = maxNode->parent;
				if (ident == Right) {
					maxNode->parent->right = maxNode->left;
					if (maxNode->left != nullptr) maxNode->left->parent = maxNode->parent;
				}
				if (ident == Left) {
					maxNode->parent->left = maxNode->left;
					if (maxNode->left != nullptr) maxNode->left->parent = maxNode->parent;
				}
				delete maxNode;
			}
			else {
				ident = findParent(node);
				if (ident == Root) {
					delete root;
					root = nullptr;
					return 1;
				}

				if (ident == Left) {
					node->parent->left = nullptr;
					nowNode = node->parent;
					delete node;
				}
				if (ident == Right) {
					node->parent->right = nullptr;
					nowNode = node->parent;
					delete node;
				}
			}
		}
		//ident - откуда пришли
		while (nowNode != nullptr) {
			if (ident == Left) {
				nowNode->balance--;
				if (nowNode->balance == -2) Rotate(nowNode);
				if (nowNode->balance == -1) return 1;
				ident = findParent(nowNode);
				nowNode = nowNode->parent;
			}

			if (ident == Right) {
				nowNode->balance++;
				if (nowNode->balance == 2) Rotate(nowNode);
				if (nowNode->balance == 1) return 1;
				ident = findParent(nowNode);
				nowNode = nowNode->parent;
			}

		}
		return 1;
	}

	void deleteTree(Node* node) {
		if (node != nullptr) {
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}
};