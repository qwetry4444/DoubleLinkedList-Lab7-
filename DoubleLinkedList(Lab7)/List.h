#pragma once
class List;

class Item {
protected:
	Item* next;
	Item* prev;
	List* list;

public:
	Item* Next() { return next; }
	Item* Prev() { return prev; }

	Item();
	virtual ~Item();

	void SetNext(Item* next) { this->next = next; }
	void SetPrev(Item* prev) { this->prev = prev; }
	void SetList(List* list) { this->list = list; }

	friend class List;
	friend class SubjList;
};

class List {
protected:
	Item* head;
	Item* tail;

public:
	Item* Head() { return head; }
	Item* Tail() { return tail; }

	List();
	~List();

	void SetHead(Item* head) { this->head = head; }
	void SetTail(Item* tail) { this->tail = tail; }

	void Add(Item* item);
	int Count();
	Item* GetItem(int index);
	Item* Remove(int indexToRemove);
	void Delete(int indexToDelete);
	void Insert(Item* itemToInsert, int indexToInsert);
	void Clear();
	int GetIndexOfItem(Item* item);
};



