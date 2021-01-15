#include <iostream>
using namespace std;



class linkedlistNode {
public:

	char value;
	linkedlistNode* next;
	linkedlistNode** child;

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

	SuffixTrie(){}

	SuffixTrie(string input) {
		if (arr.root == NULL) {
			arr.root = new linkedlistNode*;
		}

		for (int i = 1; i <= input.size(); i++) {
			firstInsert(input, i);
		}
	}

	//Check if Initial Char in the sub string exists and if not it creates a node that starts with it
	void firstInsert(string input, int index) {
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

		
	}


	void insert(linkedlistNode* Node, string input, int index) {
		//Base Case to stop the reccursive function
		if (index == 0) {
			return;
		}

		if (Node == NULL) {
			Node = new linkedlistNode;
			Node->value = input[input.size() - index];
			insert(Node->next, input, index - 1);
		}
		else if (Node->value == input[input.length() - index]) {
			insert(Node->next, input, index - 1);
		}
		else if (Node->next == NULL && Node->value != input[input.length() - index]) {
			Node->next = new linkedlistNode;
			Node->next->value = input[input.size() - index];
			insert(Node->next, input, index - 1);
		}
		else if (Node->child == NULL) {
			
			Node->child = new linkedlistNode*;
			Node->child[0] = new linkedlistNode;
			Node->child[0]->value = input[input.length() - index];
			Node->child[0]->next = NULL;
			Node->child[0]->child = NULL;
			Node->child[1] = NULL;
			insert(Node->child[0], input, index - 1);
		}
		else {
			linkedlistNode* temp = checkChild(Node->child, input, index);
			insert(temp, input, index - 1);
			
		}
		
	}

	linkedlistNode* checkChild(linkedlistNode** Node, string input, int index) {

		int i = 0;

		while (true) {

			if (Node[i] == NULL) {
				return Node[i];
			}
			else if (Node[i]->value == input[input.size() - index]) {
				return Node[i];
			}
			i++;
		}


		//return Node[i];

	}

	void print() {
		linkedlistNode* temp;
		for (int i = 0; i < arr.size; i++) {
			cout << arr.root[i]->value;
			temp = arr.root[i]->next;
			while (temp != NULL) {
				cout << temp->value;
				temp = temp->next;
			}
			cout << endl;
			
		}
		cout << arr.root[1]->child[0]->value  << endl;
		
	}
};



int main()
{
    // Construct a suffix trie containing all suffixes of "bananabanaba$"

    //            0123456789012
    SuffixTrie t("bananaba$");
	t.print();

   // t.Search("ana"); // Prints: 1 3 7
    //t.Search("naba"); // Prints: 4 8

    return 0;
}



