#include "MorseTree.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream morse_in("morse.txt");

	MorseTree morse_tree(morse_in);

	try
	{
		cout << "_.. __. decoded = " << morse_tree.decode("_.. __.") << endl;
		cout << "ac = " << morse_tree.encode("ac") << endl;
	}
	catch (const logic_error e)
	{
		cerr << e.what() << endl;
		system("pause");
		exit(0);
	}
	

	system("pause");

	return 0;
}