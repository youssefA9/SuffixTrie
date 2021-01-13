#include <iostream>
using namespace std;

class trieNode {
public:
	linkedList list;
};

class linkedlistNode {
public:
	char value;
	linkedlistNode* next;
	trieNode* child;

};

class linkedList {
public:
	linkedlistNode* root;
};



int main()
{
    // Construct a suffix trie containing all suffixes of "bananabanaba$"

    //            0123456789012
   // SuffixTrie t("bananabanaba$");

   // t.Search("ana"); // Prints: 1 3 7
    //t.Search("naba"); // Prints: 4 8

    return 0;
}



