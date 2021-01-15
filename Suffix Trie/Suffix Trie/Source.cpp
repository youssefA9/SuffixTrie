#include <iostream>
using namespace std;



class linkedlistNode {
public:

	char value;
	linkedlistNode* next;
	linkedlistNode** child;
	int childSize = 0;
	int branchNum = -1;

	linkedlistNode() {
		this->next = NULL;
		this->child = new linkedlistNode*;
	}

};

class linkedList {

public:
	linkedlistNode** root;
	int size = 0;
};


class SuffixTrie {
	linkedList arr;

public:

	SuffixTrie() {}

	SuffixTrie(string input) {
		if (arr.root == NULL) {
			arr.root = new linkedlistNode*;
		}

		for (int i = 1; i <= input.size(); i++) {
			split(arr.root, input, i, arr.size, i);
		}
	}

	//Check if Initial Char in the sub string exists and if not it creates a node that starts with it
	/*void firstInsert(string input, int index) {
		bool exists = false;
		int at = 0;

		for (int i = 0; i < arr.size; i++) {
			if (arr.root[i]->value == input[input.size() - index]) {
				exists = true;
				at = i;
				break;
			}
		}

		if (exists == false) {
			arr.root[arr.size] = new linkedlistNode;
			arr.root[arr.size]->value = input[input.length() - index];
			arr.root[arr.size]->child = NULL;
			arr.root[arr.size]->next = NULL;
			insert(arr.root[arr.size], input, index - 1);
			arr.size++;
		}
		else if (exists == true) {
			insert(arr.root[at], input, index - 1);
		}


	}*/


	void insert(linkedlistNode* Node, string input, int index, int orgIndex) {
		//Base Case to stop the reccursive function
		if (index == 0) {
			return;
		}

		if (Node->next == NULL) {

			Node->next = new linkedlistNode;
			Node->next->value = input[input.size() - index];
			if (input[input.size() - index] == '$') {
				Node->next->branchNum = orgIndex - 1;
			}
			insert(Node->next, input, index - 1, orgIndex);
		}
		else if (Node->next->value != input[input.length() - index]) {

			if (Node->child == NULL) {
				Node->child = new linkedlistNode*;
			}
			split(Node->child, input, index, Node->childSize, orgIndex);

		}
		else if (Node->next->value == input[input.length() - index]) {
			insert(Node->next, input, index - 1, orgIndex);
		}


	}

	void split(linkedlistNode** Node, string input, int index, int& nodeSize, int orgIndex) {

		bool exists = false;
		int at = 0;

		for (int i = 0; i < nodeSize; i++) {
			if (Node[i]->value == input[input.size() - index]) {
				exists = true;
				at = i;
				break;
			}
		}

		if (exists == false) {
			Node[nodeSize] = new linkedlistNode;
			Node[nodeSize]->value = input[input.length() - index];
			if (input[input.length() - index] == '$') {
				Node[nodeSize]->branchNum = orgIndex - 1;
			}
			Node[nodeSize]->child = NULL;
			Node[nodeSize]->next = NULL;
			insert(Node[nodeSize], input, index - 1, index);
			nodeSize++;
		}
		else if (exists == true) {
			insert(Node[at], input, index - 1, orgIndex - at + 1);
		}

	}

	linkedlistNode* searchExistance(linkedlistNode* Node, string input, int index) {

		if (index + 1 == input.size()) {
			return Node;
		}
		else {

			if (Node->value == input[index]) {
				if (Node->next == NULL) {
					return NULL;
				}
				if (Node->next->value == input[index + 1]) {
					return searchExistance(Node->next, input, index + 1);
				}
				else {
					int j = 0;
					for (j = 0; j < Node->childSize; j++) {
						if (Node->child[j]->value == input[index]) {
							return searchExistance(Node->child[j], input, index + 1);
							break;
						}
					}
					
					return NULL;
					
				}

			}
		}

	}



	void Search(string input) {
		bool flag = false;
		int i = 0;

		while (i < arr.size) {
			if (arr.root[i]->value == input[0]) {
				flag = true;
				break;
			}
			i++;
		}

	
		linkedlistNode* Node;

		if (i == arr.size) {
			Node = NULL;
		}
		else {
			Node = searchExistance(arr.root[i], input, 0);
		}

		if (Node == NULL) {
			cout << "Pattern Not Found" << endl;
			return;
		}

		int* carry = new int[1];
		int size = 0;
		//carry = getIndex(Node, carry, size);

		for (int i = 0; i < size; i++) {
			cout << carry[i];
		}

	}

	int* getIndex(linkedlistNode* Node, int* carry, int& size) {

		if (Node->value == '$') {
			int* temp = new int[size];
			for (int i = 0; i < size; i++) {
				temp[i] = carry[i];
			}
			delete[] carry;
			carry = temp;
			carry[size] = Node->branchNum;
			size++;
			return carry;
		}
		else {
			if (Node->childSize > 0) {
				for (int i = 0; i < Node->childSize; i++) {
					carry = getChildIndex(Node->child[i], carry, size);
				}
			}

			return getIndex(Node->next, carry, size);
		}


	}

	int* getChildIndex(linkedlistNode* Node, int* carry, int& size) {
		carry = getIndex(Node, carry, size);
		return carry;
	}

	void print() {
		linkedlistNode* temp;
		for (int i = 0; i < arr.size; i++) {
			cout << arr.root[i]->value;
			temp = arr.root[i]->next;
			while (temp != NULL) {
				cout << temp->value;
				if (temp->childSize > 0) {
					for (int j = 0; j < temp->childSize; j++) {
						//printchild(temp->child[j]);
					}
				}
				if (temp->next == NULL) {
					cout << temp->branchNum;
				}
				temp = temp->next;
			}
			
			cout << endl;
			
		}

		//cout << arr.root[3]->next->next->next->child[0]->value << endl;
		//cout << arr.root[2]->child[0]->next->next->branchNum;
	}

	void printchild(linkedlistNode* Node) {
			
		while (Node != NULL) {
			cout << Node->value;
			if (Node->childSize > 0) {
				for (int i = 0; i < Node->childSize; i++) {
					printchild(Node->child[i]);
				}
				Node = Node->next;
			}
			cout << endl;

		}
	}
};



int main()
{
    // Construct a suffix trie containing all suffixes of "nabanaba$"

    //            0123456789012
    SuffixTrie t("ggh$");
	t.print();

	//	Counter a = 6
	//	Counter b = 3
	//	Counter n = 3
	//	Counter $ = 1

		t.Search("g"); // Prints: 1 3 7
    //	t.Search("naba"); // Prints: 4 8

    return 0;
}