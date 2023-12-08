#include <iostream>
#include "List.h"
#include "subj.h"
using namespace std;

const string menu[14] =
{ "(none)", "Add", "Insert", "Delete", "Get item by index", "List length", "Print list", "Print pointers", "Search body by name", "Search star by distance to Earth", "Sorting", "Print bodies of the same type", "Clear", "Exit" };

const string TypeName[3] =
{ "(unknown)", "Star", "Planet" };

void GetIndex(int* index)
{
	cout << "Enter index" << endl;
	cout << ">";
	while (!(cin >> *index))
	{
		cout << ("Input error!. Enter index: ");
		fflush(stdin);
	}
}

void GetName(string* name)
{
	cout << "Enter the body name: ";
	cin >> *name;
}

void GetDiapasone(int* distanceStart, int* distanceEnd)
{
	cout << "Enter the left border of the range: ";
	cin >> *distanceStart;
	cout << "Enter the right border of the range: ";
	cin >> *distanceEnd;
}

int DoMenu(const string menu[], int max)
{
	cout << endl;
	int i = 0;
	for (i = 1; i < max; i++)
		cout << i << ". " << menu[i] << endl;
	cout << ">";
	fflush(stdin);
	cin >> i;
	return i < 1 || i > max ? 0 : i;
}



class DebugList : public SubjList
{
public:
	void PrintPointers();
	int Menu();
};

void DebugList::PrintPointers()
{
	cout << "List: " << this << "\tHead: " << Head() << "\tTail : " << Tail() << endl;
	cout << "  #\tp\t\t\tprev\t\t\tnext" << endl;
	int i = 0;
	Item* itemTmp = Head();
	while (itemTmp != nullptr)
	{
		cout << "  " << i << "\t" << itemTmp << "\t" << itemTmp->Prev() << "\t" << itemTmp->Next() << endl;
		itemTmp = itemTmp->Next();
		i++;
	}
}

int DebugList::Menu()
{
	return DoMenu(menu, 14);
}


int main(void)
{
	int command;
	Base* p;
	enum ItemType t;
	DebugList L;
	int index;
	string name;

	do
	{
		command = L.Menu();
		switch (command)
		{
		case 1:
			t = (ItemType)DoMenu(TypeName, 3);
			p = Base::Create(t);
			p->Input();
			L.Add(p);
			break;

		case 2:
			GetIndex(&index);
			t = (ItemType)DoMenu(TypeName, 3);
			p = Base::Create(t);
			p->Input();
			L.Insert(p, index);
			break;

		case 3:
			GetIndex(&index);
			L.Delete(index);
			break;

		case 4:
			GetIndex(&index);
			p = (Base*)L.GetItem(index);
			cout << "Founded object" << endl;
			p->Print();
			break;

		case 5:
			cout << "List lenght = " << L.Count() << endl;
			break;

		case 6:
			L.PrintList();
			break;

		case 7:
			L.PrintPointers();
			break;

		case 8:
			GetName(&name);
			L.SearchByName(name);
			break;

		case 9:
			int diapasoneStart, diapasoneEnd;
			GetDiapasone(&diapasoneStart, &diapasoneEnd);
			L.SearchByDiapasone(diapasoneStart, diapasoneEnd);
			break;

		case 10:
			L.Sort();
			break;

		case 11:
			t = (enum ItemType)DoMenu(TypeName, 3);
			L.PrintByType(t);
			break;

		case 12:
		{
			L.Clear();
			break;
		}
		}
	} while (command != 13);
	return 0;
}



