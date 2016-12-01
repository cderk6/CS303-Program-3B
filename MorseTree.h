#pragma once
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Binary_Tree.h"

using namespace std;

class MorseTree : public Binary_Tree<char>
{
public:
	MorseTree(ifstream& morse_in) 
	{ 
		root = new BTNode<char>(NULL);
		char letter;
		string code;

		while (morse_in >> letter)
		{
			morse_in >> code;
			//decode_map[code] = letter;
			encode_map[letter] = code;
			stringstream code_in(code);
			char curr_code;
			BTNode<char>* local_root = root;
			while (code_in >> curr_code)
			{
				if (curr_code == '.')	//left
				{
					if (local_root->left == nullptr)
						local_root->left = new BTNode<char>(NULL);
					local_root = local_root->left;
				}
				else if (curr_code == '_')	//right
				{
					if (local_root->right == nullptr)
						local_root->right = new BTNode<char>(NULL);
					local_root = local_root->right;
				}
			}
			local_root->data = letter;
		}
	}
	
	string encode(const string& msg);
	string decode(const string& code);

private:
	//map<string, char> decode_map;
	map<char, string> encode_map;

};

string MorseTree::encode(const string& msg)
{
	stringstream msg_in(msg);
	char letter;
	string code;

	while (msg_in >> letter)
	{
		map<char, string>::iterator itr = encode_map.find(letter);
		if (itr == encode_map.end())
			throw logic_error("Invalid character: Character not found in Morse Tree.");
		code += itr->second;
		code += " ";
	}
	return code;
}

string MorseTree::decode(const string& code)
{
	stringstream code_in(code);
	string temp;
	string msg;
	char curr_code;
	BTNode<char>* local_root = root;

	while (code_in >> temp)
	{
		stringstream code_seg(temp);
		while (code_seg >> curr_code)
		{
			if (curr_code == '.')
			{
				if (local_root->left == nullptr)
					throw logic_error("Invalid code: Code segment not found in Morse Tree.");
				local_root = local_root->left;
			}
			else if (curr_code == '_')
			{
				if (local_root->right == nullptr)
					throw logic_error("Invalid code: Code segment not found in Morse Tree.");
				local_root = local_root->right;
			}
			else
			{
				string inv;
				inv.push_back(curr_code);
				throw logic_error("Invalid character: '" + inv + "'.");
			}
		}
		msg += local_root->data;
		local_root = root;
	}
	return msg;
}
