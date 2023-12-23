#pragma once
#include "List.h"
#include <string>
using namespace std;

class SubjList;

enum ItemType
{
	itNone = 0,
	itStar = 1,
	itPlanet = 2
};

class Base : public Item {
protected:
	string name;
	double weight;
	double diameter;
public:
	Base();
	Base(ItemType _type);
	~Base();

	virtual void Print() const = 0;
	virtual void Input() = 0;

	virtual ItemType Type() const { return itNone; };

	static Base* Create(enum ItemType type);

	virtual bool operator > (Base& obj2) = 0;

	virtual bool operator >= (int) = 0;
	virtual bool operator <= (int) = 0;
	virtual bool operator == (Base& obj2) = 0;
	bool operator == (string name);

	friend class SubjList;
};


class SubjList : public List {
public:
	void PrintList();
	void PrintByType(enum ItemType type);
	void SearchByName(string name);
	void SearchByDiapasone(int distanceStart, int distanceEnd);
	void Swap(int i, int j);
	void SortByTypes(int listLen);
	void Sort();

	Base& operator [] (int index) {
		return *(Base *)this->GetItem(index);
	}
};

