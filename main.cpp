#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

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

string rtrim (string str)
{
	while (!str.empty() && str[str.length() - 1] == ' ')
	{
		str.pop_back();
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
	if (!temp.empty())
		result.push(temp);
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

bool parse_int (string str, int &n)
{
	istringstream ss (rtrim(str));
	ss >> n;
	return !ss.fail() && ss.eof();
}

template <typename T>
class Parser
{
public:
	virtual bool operator()(string str, T &n) = 0;
};

class SimpleIntParser : public Parser<int>
{
public:
	virtual bool operator()(string str, int &n)
	{
		return parse_int(str, n);
	}	
};

class ComparingIntParser : public Parser<int>
{
public:
	ComparingIntParser(int num)
	{
		this->num = num;
	}
	virtual bool operator()(string str, int &n)
	{
		return parse_int(str, n) && n < this->num;
	}
private:
	int num;
};

bool parse_nonempty_string(string str, string &resstr)
{
	resstr = purify_string(str);
	return !resstr.empty();
}

class NoneEmptyStringParser : public Parser<string>
{
public:
	virtual bool operator()(string str, string &resstr)	
	{
		return parse_nonempty_string(str, resstr);
	}
};

template<typename T>
T cycle_input (Parser<T> &p)
{
	T result;
	string input;
	while (true)
	{
		cerr << "Enter it!\n";
		getline(cin, input);
		if (p(input,result)) 
			return result;
		else cout << "Wrong\n";
	}
}

string getmultiline (istream &i)
{
	string accumulator = "";
	while (true)
	{
		string line;
		getline(i, line);
		if (rtrim(line).empty())
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
	int in;
	cout << "Let's settle up with your character.\n" << "Enter The name : \n";
	{
		NoneEmptyStringParser nesp;
		cr.name = cycle_input(nesp);
	}
	cout << "Your name is: " << cr.name << endl;
	input = "";
	cout << "Your age equals : \n";
	{
		SimpleIntParser sp;
		cr.age = cycle_input(sp);
	}
	cout << "Your age is: " << cr.age << endl;
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

struct MenuNavigationState
{
	Room *room;
	int *inroom;
};

typedef void (*MenuNavigationFunc)(MenuNavigationState);

struct MenuNavigationOption
{
	string name;
	MenuNavigationFunc func;
};

void menu_moveto (MenuNavigationState mnavs)
{
	int choice;
	string input;
	int n =0;
	cout << "Where'd ya want to go: \n";
	while (n < mnavs.room->doors.size())
	{
		cout << n << ". To room " << mnavs.room->doors[n] << " \n";
		n++;
	}
	{
		ComparingIntParser cp(mnavs.room->doors.size());
		choice = cycle_input(cp);
	}
	*mnavs.inroom = mnavs.room->doors[choice];
}

void menu_search (MenuNavigationState mnavs)
{
	int n = 0;
	while (n < mnavs.room->objects.size())
	{
		cout << "You see a " << mnavs.room->objects[n].name << ".\nIt is " << mnavs.room->objects[n].descr << ".\n";
		n++;
	}
}

void menu_navigation (Character chr)
{
	int choice;
	string input;
	vector<MenuNavigationOption> optns =
		{
			{ name : "Search", func : menu_search },
			{ name : "Move", func : menu_moveto }
		};
	Level world = creator_level();
	while (true)
	{
		cout << "You're in room " << chr.inroom << endl;
		cout << "What do you want to do?\n";
		for (int i = 0; i < optns.size(); i++)
		{
			cout << i << ". " << optns[i].name << endl;
		}
		{
			ComparingIntParser cp(optns.size());
			choice = cycle_input(cp);
		}
		MenuNavigationState mnavs = { room : &world.rooms[chr.inroom], inroom : &chr.inroom };
		optns[choice].func(mnavs);
	}
}

void menu_main ()
{
	int choice;
	cout << "Main menu.\n" << "0. Start game\n" << "1. Exit\n";
	while (true)
	{
		{
			ComparingIntParser cp(2);
			choice = cycle_input(cp);
		}
		if (choice == 0)
		{
			menu_navigation(menu_character());
			break;
		}
		else if (choice == 1)
		{
			break;
		}
	}
}

int main()
{
	menu_main();
	cout << "\n\nThe end\n";
	return 0;
}


