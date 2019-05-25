#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "HuffTree.h"
using namespace std;

int main()
{
	auto str = get_string();
	auto treeRoot = HuffLeaf::HuffAlgo(str);
	auto encodedStr =  EncodeString(str, treeRoot);
	auto mapCode = HuffLeaf::Get_codes(treeRoot);
	DecodeString(mapCode, encodedStr);
	return 0;
}