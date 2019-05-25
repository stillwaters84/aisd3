#include <iostream>
#include <string>
#include "RedBlackTree.h"
#include "mylist.h"


/*
	1) enter the string - ok
	2) make a map of symbols - ok
	3) make a list of free nodes - ok
	4) code every symbol
	5) make a new map

	i have a list of free nodes with symbols - now huffman algorithm to code it
*/
using namespace std;

int main()
{
	Map<char, int> HTree;

	//yList<Map<char,int>> *NodeTree = new MyList<Map<char,int>>();
	string sample_str;
	getline(cin, sample_str);
	cout << sample_str.length() << endl;
	for (int i = 0; i < sample_str.length(); i++) {
		if (HTree.FindNode(sample_str[i]) != nullptr) {
			HTree.FindNode(sample_str[i])->value++;
		}
		else {
			HTree.insertnode(sample_str[i], 1);
		}
	} ///doing well
	//HTree.get_keys();
	auto HList = HTree.TravelMap(HTree.getRoot());
	auto MinNode = HList->findMin();
	return 0;
}