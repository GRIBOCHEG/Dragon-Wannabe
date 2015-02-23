#include <iostream>
using namespace std;

string trim (string str)
{
	int n = 0;
	while (n < str.length())
	{
		if (str[n] == ' ') { 
			str.erase(n,1); }
		else n++;
	}
	return str;
}

int main()
{
	string choice;
	cout << "Main menu.\n" << "1. Start game\n" << "2. Exit\n";
	int i = 0;
	while (i < 1)
	{
		getline(cin, choice);
		choice = trim(choice);
		cout << "You entered: " << choice << endl;
		if (choice == "1")
		{
			cout << "Let's settle up with your character.\n";
			i++;
		}
		else if (choice == "2")
		{
			i++;
		}
		else cout << "Wrong.\n";
	}
	cout << "The end\n";
	return 0;
}


