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
	//constructor that reads in all characters to correct position in binary tree
	MorseTree(ifstream& morse_in) 
	{ 
		//set root to avoid error
		root = new BTNode<char>(NULL);
		char letter;
		string code;

		//while there are more letter to read into tree
		while (morse_in >> letter)
		{
			//read in the code corresponding to the letter
			morse_in >> code;
			encode_map[letter] = code; //building encoding map

			stringstream code_in(code);
			char curr_code;
			BTNode<char>* local_root = root;
			//while there are more characters in the code string, traverse tree
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
			//put letter into position traversed to in binary tree
			local_root->data = letter;
		}
	}
	
	string encode(const string& msg);
	string decode(const string& code);

private:
	map<char, string> encode_map;
};

string MorseTree::encode(const string& msg)
{
	stringstream msg_in(msg);
	char letter;
	string code;

	//while there are more letters, add code of letter and space character to return code
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
	string coded_letter;
	string msg;
	char curr_code;
	BTNode<char>* local_root = root;

	//read in first coded letter
	while (code_in >> coded_letter)
	{
		stringstream code_seg(coded_letter);
		//traverse tree: left for '.' right for '_'
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
			//catch invalid characters (those that are not '.' or '_')
			else
			{
				string inv;
				inv.push_back(curr_code);
				throw logic_error("Invalid character: '" + inv + "'.");
			}
		}
		//when coded letter has been found, add it to the return string
		msg += local_root->data;
		//reset local_root to start of binary tree
		local_root = root;
	}
	return msg;
}
