#include <iostream>
using namespace std;

string rmws (string str)
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

struct Character
{
	string name;
	int age;
	string bio;
};

string gml (istream &i)
{
	string accumulator = "";
	while (true)
	{
		string line;
		getline(i, line);
		if (rmws(line).empty())
		{
			if (!accumulator.empty())
				return accumulator;
		}
		else accumulator += line += string("\n");
	}
}

Character menu_character ()
{
	Character cr;
	cout << "Let's settle up with your character.\n" << "Enter The name : \n";
	cin >> cr.name;
	cout << "Your age equals : \n";
	cin >> cr.age;
	cout << "How will people remember you? \n";
	cr.bio = gml(cin);
	cout << cr.bio;
	return cr;
}


void menu_main ()
{
	string choice;
	cout << "Main menu.\n" << "1. Start game\n" << "2. Exit\n";
	bool isdone = false;
	while ( ! isdone)
	{
		getline(cin, choice);
		choice = rmws(choice);
		cout << "You entered: " << choice << endl;
		if (choice == "1")
		{
			menu_character();
			isdone = true;
		}
		else if (choice == "2")
		{
			isdone = true;
		}
		else cout << "Wrong.\n";
	}
}

int main()
{
	menu_main();
	cout << "\n\nThe end\n";
	return 0;
}


