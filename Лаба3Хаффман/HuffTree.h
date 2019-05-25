#pragma once
#include <iostream>
#include <string>
#include "RedBlackTree.h"
#include "mylist.h"

using namespace std;

class HuffLeaf {
public:
	std::string character;
	unsigned frequency;
	std::string code = {};
	HuffLeaf* left = nullptr;
	HuffLeaf* right = nullptr;
	HuffLeaf() = default;
	HuffLeaf(std::string ch, unsigned freq) : character(ch), frequency(freq) {};
	~HuffLeaf() {}; 
	static HuffLeaf* mergeLeaves(HuffLeaf * lhs, HuffLeaf * rhs);
	
	static Map<string, string>* Get_codes(HuffLeaf* node);
	static void Get_codes_node(HuffLeaf* node, Map<string, string>* result);
	
	static HuffLeaf* HuffAlgo(string sample_str);
	static void go(HuffLeaf* root);

	friend bool operator<(const HuffLeaf& left, const HuffLeaf& right);
	//friend std::ostream& operator<< (std::ostream &out, const HuffLeaf &leaf);
};

bool operator<(const HuffLeaf& left, const HuffLeaf& right) {
	return left.frequency < right.frequency;
}

/*std::ostream& operator<< (std::ostream &out, const HuffLeaf &leaf){
	std::cout << leaf.character << ": " << leaf.frequency;
	return out;
}*/

//make new list with merged characters and merged frequences 
HuffLeaf* HuffLeaf::mergeLeaves(HuffLeaf * lhs, HuffLeaf  * rhs){
	HuffLeaf* newLeaf = new HuffLeaf(lhs->character+rhs->character, lhs->frequency+rhs->frequency);
	newLeaf->left = lhs;
	newLeaf->right = rhs;
	return newLeaf;
}

void HuffLeaf::Get_codes_node(HuffLeaf* node, Map<string,string> *result) {
	if (node != nullptr) {
		Get_codes_node(node->left, result);
		if (node->character.length() <= 1) {
			result->insertnode(node->character, node->code);
		}
		Get_codes_node(node->right, result);
	}
}

Map<string,string>* HuffLeaf::Get_codes(HuffLeaf* node) { ///recursive traveling
	Map<string, string>* result = new Map<string, string>;
	Get_codes_node(node, result);
	return result;
}

void HuffLeaf::go(HuffLeaf* leaf) { ///code huffman's tree symbol 
	//i made it like: left child is 1, right is 0 and symbols merging while traveling
	if (!leaf) return;
	if (leaf->left)
		leaf->left->code = leaf->code + "1";
	if (leaf->right)
		leaf->right->code = leaf->code + "0";
	go(leaf->left);
	go(leaf->right);
}

string get_string() {
	string sample_str;
	getline(cin, sample_str);
	return sample_str;
}

HuffLeaf* HuffLeaf::HuffAlgo(string sample_str) {
	Map<char, int> HTree;
	//make a map of symbols (dumb stuff but ok)
	for (int i = 0; i < sample_str.length(); i++) {
		auto placeToInsert = HTree.FindNode(sample_str[i]);
		if (placeToInsert != nullptr) {
			placeToInsert->value++;
		}
		else {
			HTree.insertnode(sample_str[i], 1);
		}
	} 

	auto HList = HTree.TravelMap(); ///put elements of map in list (seems legit)

	//find two minimal elements, make new list element with merged frequency and characters
	while (true) {
		auto minIndex_1 = HList.findMin();
		auto min_1 = HList.at(minIndex_1);
		HList.remove(minIndex_1);

		auto minIndex_2 = HList.findMin();
		if (minIndex_2 == -1) { //if there's only one elem in list
			HList.push_back(min_1);
			break;
		}
		auto min_2 = HList.at(minIndex_2);
		HList.remove(minIndex_2);

		auto newLeaf = HuffLeaf::mergeLeaves(min_1, min_2);
		HList.push_back(newLeaf);
	}

	auto root = HList.first->number;
	go(root);
	return root;
}

string EncodeString(string sample_str, HuffLeaf *root) {
	auto MapOfCodes = HuffLeaf::Get_codes(root);
	string encoded_string;
	int cnt = 0;
	for (int i = 0; i < sample_str.length(); i++) {
		Node<string, string>* MapCode = MapOfCodes->FindNode(string(1, sample_str[i]));
		for (int j = 0; j < MapCode->value.length(); j++) {
			cnt++;
			encoded_string += MapCode->value[j];
		}
	}
	cout << "Encoded String: " << encoded_string << endl;
	return encoded_string;
}

string DecodeString(Map<string,string>*MapOfCodes, string encoded_string) {
	string decoded_string;
	auto CodeList = MapOfCodes->get_values();
	auto CodeListFirst = CodeList->first;
	auto SymbolsList = MapOfCodes->get_keys();
	auto SymbolListFirst = SymbolsList->first;
	cout << *SymbolsList << endl;
	cout << *CodeList << endl;
	int codelength = 0;
	string code;
	for (int i = 0; i < encoded_string.length(); i++) {
		code += encoded_string[i];
		CodeListFirst = CodeList->first;
		SymbolListFirst = SymbolsList->first;
		while (CodeListFirst != nullptr && SymbolListFirst != nullptr) {
			if (code == CodeListFirst->number) {
				decoded_string += SymbolListFirst->number;
				code.clear();
			}
			CodeListFirst = CodeListFirst->next;
			SymbolListFirst = SymbolListFirst->next;
		}
	}
	cout << "Decoded String: " << decoded_string << endl;
	delete CodeList;
	delete SymbolsList;
	return decoded_string;
}