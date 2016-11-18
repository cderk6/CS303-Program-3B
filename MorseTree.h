#pragma once
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class MorseTree
{
public:
	MorseTree(ifstream& morse_in) 
	{ 
		char letter;
		string code;

		while (morse_in >> letter)
		{
			morse_in >> code;
			decode_map[code] = letter;
			encode_map[letter] = code;
		}
	}
	
	string encode(const string& msg);
	string decode(const string& code);

private:
	map<string, char> decode_map;
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
	string code_seg;
	string msg;

	while (code_in >> code_seg)
	{
		map<string, char>::iterator itr = decode_map.find(code_seg);
		if (itr == decode_map.end())
			throw logic_error("Invalid code: Code segment not found in Morse Tree.");
		msg += itr->second;
	}
	return msg;
}
