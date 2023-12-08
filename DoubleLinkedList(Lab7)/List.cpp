#include "List.h"
#include <iostream>

Item::Item()
	: next(nullptr),
	prev(nullptr),
	list(nullptr)
{}

Item::~Item() {
	list->Delete(list->GetIndexOfItem(this));
}

List::List()
	: head(nullptr),
	tail(nullptr)
{}

List::~List() {
	Clear();
}


void List::Add(Item* item)
{
	item->list = this;
	if (head == nullptr)
	{
		head = item;
		tail = item;
		head->prev = nullptr;
	}
	else
	{
		tail->next = item;
		item->prev = tail;
		tail = item;
	}
	tail->next = nullptr;
}

int List::Count()
{
	Item* itemTmp = head;
	int countItems = 0;
	while (itemTmp != nullptr)
	{
		countItems++;
		itemTmp = itemTmp->next;
	}
	return countItems;
}

Item* List::GetItem(int index)
{
	int indexTmp = 0;
	Item* itemTmp = head;
	while (indexTmp != index && itemTmp)
	{
		itemTmp = itemTmp->next;
		indexTmp++;
	}
	return itemTmp;
}

Item* List::Remove(int indexToRemove)
{
	Item* itemToRemove = GetItem(indexToRemove);
	if (itemToRemove)
	{
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
		}

		else if (itemToRemove == head)
		{
			head->next->prev = nullptr;
			head = head->next;
		}
		else if (itemToRemove == tail)
		{
			tail = tail->prev;
			tail->next = nullptr;
		}
		else
		{
			itemToRemove->prev->next = itemToRemove->next;
			itemToRemove->next->prev = itemToRemove->prev;
		}
	}
	return itemToRemove;
}

void List::Delete(int indexToDelete)
{
	Item* itemToDelete = Remove(indexToDelete);
	if (itemToDelete != nullptr)
	{
		delete(itemToDelete);
	}
}

void List::Insert(Item* itemToInsert, int indexToInsert)
{
	itemToInsert->list = this;
	Item* itemToShift = GetItem(indexToInsert);
	if (itemToShift == nullptr)
	{
		Add(itemToInsert);
		return;
	}
	if (indexToInsert == 0)
	{
		head->prev = itemToInsert;
		head->prev->next = (itemToShift);
		head = itemToInsert;
		head->prev = nullptr;
		return;
	}
	if (itemToShift != nullptr && indexToInsert != 0)
	{
		itemToShift->prev->next = itemToInsert;
		itemToInsert->prev = itemToShift->prev;
		itemToShift->prev = itemToInsert;
		itemToInsert->next = itemToShift;
	}
}

void List::Clear()
{
	Item* itemTmp = head;
	while (head)
	{
		Delete(0);
	}
}

int List::GetIndexOfItem(Item* item)
{
	int index = 0;
	Item* itemTmp = head;
	while (true)
	{
		if (itemTmp != item && itemTmp != nullptr)
		{
			itemTmp = itemTmp->next;
			index++;
		}
		else
			return index;
	}
	return -1;
}


