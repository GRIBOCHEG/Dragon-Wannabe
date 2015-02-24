#include <iostream>
#include <vector>
#include <string>
#include <queue>
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
		else if (str[n] == ' ' && !temp.empty())
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

struct Room
{
	vector<int> doors;
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
	cout << "Let's settle up with your character.\n" << "Enter The name : \n";
	getline(cin, cr.name);
	cr.name = purify_string(cr.name);
	cout << "Your name is: " << cr.name << endl;
	cout << "Your age equals : \n";
	cin >> cr.age;
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
	return level1;
}

void menu_navigation (Character chr)
{
	int n = 0, m = 0;
	string choice;
	Level world = creator_level();
	while (true)
	{
		n = 0;
		m = chr.inroom;
		cout << "You're in room " << chr.inroom << endl;
		cout << "In this world present " << world.rooms.size() << " rooms\n";
		cout << "In this room present " << world.rooms[m].doors.size() << " doors\n";
		cout << "Where'd ya want to go: \n";
		while (n < world.rooms[m].doors.size())
		{
			cout << "To room " << world.rooms[m].doors[n] << " ?[y/n]\n";
			cin >> choice;
			if (choice == "y")
			{
				chr.inroom = world.rooms[m].doors[n] ;
				break;
			} 
			n++;
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


