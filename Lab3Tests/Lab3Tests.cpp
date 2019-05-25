#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "../Лаба3Хаффман/HuffTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3Tests
{
	TEST_CLASS(Huffman)
	{
	public:
		
		TEST_METHOD(EncodeString1)
		{
			string test = "it is test string";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			string check = "000100010001100110011111100011110010000001010110";
			Assert::AreEqual(encodedStr, check);
		}

		TEST_METHOD(EncodeString2)
		{
			string test = "aaaaaaaaaaabbbbbbccccccgggggeeef";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			string check = "00000000000000000000001111111111111010101010100100100100100100110011001100111";
			Assert::AreEqual(encodedStr, check);
		}

		TEST_METHOD(EncodeString3)
		{
			string test = "123";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			string check = "01001";
			Assert::AreEqual(encodedStr, check);
		}

		TEST_METHOD(DecodeString1)
		{
			string test = "it is test string";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			auto mapCode = HuffLeaf::Get_codes(treeRoot);
			string decoded_string = DecodeString(mapCode, encodedStr);
			Assert::AreEqual(test, decoded_string);
		}

		TEST_METHOD(DecodeString2)
		{
			string test = "what are you looking at it is a very nice doggo";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			auto mapCode = HuffLeaf::Get_codes(treeRoot);
			string decoded_string = DecodeString(mapCode, encodedStr);
			Assert::AreEqual(test, decoded_string);
		}

		TEST_METHOD(DecodeString3)
		{
			string test = "123";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			auto mapCode = HuffLeaf::Get_codes(treeRoot);
			string decoded_string = DecodeString(mapCode, encodedStr);
			Assert::AreEqual(test, decoded_string);
		}

		TEST_METHOD(GetCodes1)
		{
			string test = "it is test string";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			auto mapCode = HuffLeaf::Get_codes(treeRoot);
			auto CodeList = mapCode->get_values();
			auto CodeListFirst = CodeList->first;

			string check[8] = { "001", "0111","0110","000","0101","0100","11","10" };
			for (int i = 0; i < 8; i++) {
				Assert::AreEqual(check[i], CodeListFirst->number);
				CodeListFirst = CodeListFirst->next;
			}
		}

		TEST_METHOD(GetCodes2)
		{
			string test = "aaaaaabbbbccg";
			auto treeRoot = HuffLeaf::HuffAlgo(test);
			auto encodedStr = EncodeString(test, treeRoot);
			auto mapCode = HuffLeaf::Get_codes(treeRoot);
			auto CodeList = mapCode->get_values();
			auto CodeListFirst = CodeList->first;

			string check[4] = { "1", "00","010","011"};
			for (int i = 0; i < 4; i++) {
				Assert::AreEqual(check[i], CodeListFirst->number);
				CodeListFirst = CodeListFirst->next;
			}
		}
	};
}
