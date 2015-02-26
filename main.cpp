#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
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

string purify_string (string str)
{
	string temp = "";
	queue <string> result;
	int n = 0;
	while (n < str.length())
	{
		if (str[n] != ' ')
		{
			temp.push_back(str[n]);
		}
		else if (!temp.empty())
		{
			result.push(temp);
			temp = "";
		}
		n++;
	}
	temp = "";
	while (!result.empty())
	{
		temp += result.front();
		result.pop();
		if (!result.empty()) 
			{
				temp += " ";
			}
	}
	return temp;
}

struct Character
{
	string name;
	int age;
	string bio;
	int inroom = 0;
};

struct Object
{
	string name;
	string descr;
};

struct Room
{
	vector<int> doors;
	vector<Object> objects;
};

struct Level
{
	vector<Room> rooms;
};

string getmultiline (istream &i)
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
	string input;
	cout << "Let's settle up with your character.\n" << "Enter The name : \n";
	getline(cin, input);
	cr.name = purify_string(input);
	cout << "Your name is: " << cr.name << endl;
	cout << "Your input was " << input << endl;
	input = "";
	cout << "Your age equals : \n";
	while (true)
	{
		cout << "Enter it! \n";
		getline(cin, input);
		input = rmws(input);
		istringstream ss(input);
		if (!ss.fail() && !ss.bad())
		{
			ss >> cr.age;
			break;
		}
		else cout << "Wrong\n";
	}
	cout << "bitch " << cr.age << endl;
	cout << "input was " << input << endl
	cout << "How will people remember you? \n";
	cr.bio = getmultiline(cin);
	return cr;
}

Level creator_level ()
{
	Level level1;
	Room room0, room1, room2, room3, room4;
	level1.rooms.push_back(room0);
	level1.rooms.push_back(room1);
	level1.rooms.push_back(room2);
	level1.rooms.push_back(room3);
	level1.rooms.push_back(room4);
	level1.rooms[0].doors.push_back(1);
	level1.rooms[1].doors.push_back(0);
	level1.rooms[1].doors.push_back(2);
	level1.rooms[1].doors.push_back(4);
	level1.rooms[2].doors.push_back(1);
	level1.rooms[2].doors.push_back(3);
	level1.rooms[3].doors.push_back(2);
	level1.rooms[3].doors.push_back(4);
	level1.rooms[4].doors.push_back(1);
	level1.rooms[4].doors.push_back(3);
	level1.rooms[4].doors.push_back(0); 
	Object obj0, obj1, obj2;
	level1.rooms[0].objects.push_back(obj0);
	level1.rooms[2].objects.push_back(obj1);
	level1.rooms[3].objects.push_back(obj2);
	level1.rooms[0].objects[0].name = "table";
	level1.rooms[0].objects[0].descr = "plain pine table";
	level1.rooms[2].objects[0].name = "chair";
	level1.rooms[2].objects[0].descr = "pretty stone chair";
	level1.rooms[3].objects[0].name = "rock";
	level1.rooms[3].objects[0].descr = "ordinary grey rock";
	return level1;
}

void menu_navigation (Character chr)
{
	int n = 0, m = 0;
	int choice;
	Level world = creator_level();
	while (true)
	{
		n = 0;
		m = chr.inroom;
		cout << "You're in room " << chr.inroom << endl;
		cout << "What do you want to do?\n";
		cout << "0. Search\n";
		cout << "1. Move\n";
		cin >> choice;
		if (choice == 1)
		{
			cout << "Where'd ya want to go: \n";
			n = 0;
			while (n < world.rooms[m].doors.size())
			{
				cout << n << ". To room " << world.rooms[m].doors[n] << " ?\n"; 
				n++;
			}
			cin >> choice;
			n = 0;
			while (n < world.rooms[m].doors.size())
			{
				if (choice == n) chr.inroom = world.rooms[m].doors[n];
				n++;
			}
		}
		else if (choice == 0)
		{
			int k = 0;
			while (k < world.rooms[m].objects.size())
			{
				cout << "You see a " << world.rooms[m].objects[k].name << ".\nIt is " << world.rooms[m].objects[k].descr << ".\n";
				k++;
			}
		}
	}
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
		if (choice == "1")
		{
			menu_navigation(menu_character());
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


