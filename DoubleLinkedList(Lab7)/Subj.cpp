#include "Subj.h"
#include <iostream>
using namespace std;

class Planet : public Base {
private:
	string systemOfStar;
	int orbitalDiameter;

public:
	Planet();
	void Print() const override;
	void Input() override;
	ItemType Type() const override { return itPlanet; };

	bool operator > (Base&) override;

	bool operator >= (int) override {
		return false;
	}
	bool operator <= (int) override {
		return false;
	}

	bool operator == (Base&) override;

	friend class Star;
	friend class SubjList;
};

class Star : public Base {
private:
	double surfaceTemperature;
	double apparentMagnitude;
	int distanceFromEarth;

public:
	Star();
	void Print() const override;
	void Input() override;
	ItemType Type() const override { return itStar; };

	bool operator > (Base&) override;

	bool operator >= (int) override;
	bool operator <= (int) override;
	bool operator == (Base&) override;

	friend class Planet;
	friend class SubjList;
};

bool Planet::operator > (Base& objNext)
{
	switch (objNext.Type()) 
	{
	case itStar:
		return true;
	case itPlanet:
		return (this->orbitalDiameter > ((Planet&)objNext).orbitalDiameter);
	}
}

bool Planet::operator == (Base& objNext) 
{
	switch (objNext.Type())
	{
	case itPlanet:
		return false;
	case itStar:
		return (this->systemOfStar == ((Star&)objNext).name);
	}
}

Planet::Planet()
	: Base()
	, systemOfStar("")
	, orbitalDiameter(0)
{}

void Planet::Print() const
{
	cout << "Planet:" << endl;
	cout << "\tName: " << name << endl << "\tWeight: " << weight << "\tDiameter: " << diameter << endl;
	cout << "\tThe planet belongs to the planetary system of " << systemOfStar << endl;
	cout << "\tOrbit diameter: " << orbitalDiameter << endl;
}

void Planet::Input()
{
	cout << "Input planet." << endl;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter weight: ";
	cin >> weight;
	cout << "Enter diameter: ";
	cin >> diameter;
	cout << "Enter the star to the planetary system to which the planet belongs: ";
	cin >> systemOfStar;
	cout << "Enter orbital diameter: ";
	cin >> orbitalDiameter;
}


Star::Star()
	: Base()
	, surfaceTemperature(0)
	, apparentMagnitude(0)
	, distanceFromEarth(0)
{}

bool Star::operator > (Base& objNext)
{
	switch (objNext.Type()) {
	case itPlanet:
		return false;
	case itStar:
		return (name > ((Star&)objNext).name);
	}
}

bool Star::operator >= (int num) {
	return distanceFromEarth >= num;
}

bool Star::operator <= (int num) {
	return distanceFromEarth <= num;
}

bool Star::operator == (Base& baseNext) {
	switch (baseNext.Type())
	{
	case itStar:
		return false;
	case itPlanet:
		return name == ((Planet&)baseNext).systemOfStar;
	}
}

void Star::Print() const
{
	cout << "Star:" << endl;
	cout << "\tName: " << name << endl << "\tWeight: " << weight << "\tDiameter: " << diameter << endl;
	cout << "\tSurface temperature: " << surfaceTemperature << "\tApparent magnitude: " << apparentMagnitude << "\tDistance from Earth :" << distanceFromEarth << endl;
}

void Star::Input()
{
	cout << "Input star." << endl;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter weight: ";
	cin >> weight;
	cout << "Enter diameter: ";
	cin >> diameter;
	cout << "Enter surface temperature";
	cin >> surfaceTemperature;
	cout << "Enter apparent magnitude: ";
	cin >> apparentMagnitude;
	cout << "Enter distance from Earth: ";
	cin >> distanceFromEarth;
}

Base::Base()
	: name("")
	, weight(0)
	, diameter(0)
{}

Base::Base(ItemType _type)
	: name("")
	, weight(0)
	, diameter(0)
{}

Base::~Base() {}


Base* Base::Create(enum ItemType _type) {
	Base* base = nullptr;
	switch (_type) {
	case itStar:
		base = new Star();
		break;
	case itPlanet:
		base = new Planet();
		break;
	}
	return base;
}

bool Base::operator == (string _name) {
	return name == _name;
}

void SubjList::PrintList() {
	SubjList& L = *this;
	if (this) {
		if (Head()) {
			for (int i = 0; i < Count(); i++) {
				L[i].Print();
			}
		}
		else
			cout << "List is empty." << endl;
	}
	else
		cout << "ERROR: wrong list!" << endl;
}

void SubjList::PrintByType(enum ItemType type) {
	if (this) {
		if (Head()) {
			for (Base* p = (Base*)Head(); p; p = (Base*)p->next) {
				if (p->Type() == type)
					p->Print();
			}
		}
		else
			cout << "List is empty." << endl;
	}
	else
		cout << "ERROR: wrong list!" << endl;
}

void SubjList::SearchByName(string _name) {
	if (this) {
		if (Head()) {
			Base* p = (Base*)Head();
			while (p) {
				if (*p == _name) {
					p->Print();
				}
				p = (Base*)p->next;
			}
		}
		else
			cout << "List is empty." << endl;
	}
	else
		cout << "ERROR: wrong list!" << endl;
}

void SubjList::SearchByDiapasone(int diapasoneStart, int diapasoneEnd) {
	if (this) {
		if (Head()) {
			Base* p = (Base*)Head();
			while (p) {
				if (*p >= diapasoneStart && *p <= diapasoneEnd)
					p->Print();
				p = (Base*)p->next;
			}
		}
	}
}

void SubjList::Swap(int i, int j) {
	int MAX = i > j ? i : j;
	int MIN = i < j ? i : j;
	Item* it = this->Remove(MAX);
	this->Insert(it, MIN);
	it = this->Remove(MIN + 1);
	this->Insert(it, MAX);
}

void SubjList::SortByTypes(int listLen) {
	int i;
	int flag = 1;
	do {
		Base* p = (Base*)head;
		flag = 0;
		for (i = 0; i < listLen - 1; i++) {
			Base* obj2 = (Base*)p->next;
			if (*p > *obj2) {
				Swap(i, i + 1);
				flag = 1;
			}
			else
				p = (Base*)p->next;
		}
	} while (flag == 1);
}


void SubjList::Sort() {
	SubjList& L = *this;
	int i, j;
	int countPlanetsInSystem;
	Planet* planetToMove;
	int listLen = Count();
	SortByTypes(listLen);
	for (i = 0; i < listLen; i++) {
		if (L[i].Type() == itStar) {
			countPlanetsInSystem = 0;
			for (j = i + 1; j < listLen; j++) {
				if (L[j].Type() == itStar)
					continue;
				if (L[i] == L[j])
				{
					planetToMove = (Planet*)Remove(j);
					Insert(planetToMove, i + 1 + countPlanetsInSystem);
					countPlanetsInSystem++;
				}
			}
		}
	}
}
