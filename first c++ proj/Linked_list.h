#pragma once
#include<vector>
#include <iostream>
using namespace std;
#define log(x) cout << x << endl;

struct node {

	int value;
	node* ptr;
	node() {}
	node(int v, node* p)
	{
		value = v;
		ptr = p;
	}
	friend ostream& operator<<(ostream& os, const node obj) {
		os << obj.value;
		if (obj.ptr) {
			os << " -> " << *obj.ptr;
		}
		else {
			os << " -> nullptr";
		}
		return os;
	}
	node(const node& other) : value(other.value), ptr(other.ptr ? new node(*other.ptr) : nullptr) {}
};

class ll {

	node* head{};
	node* current{};
	int size = 0;

public:
	ll() {}

	ll(const ll& other)
	{

		for (int i = 0; i < other.size; i++)
		{
			int no = other.get(i);
			this->append(no);
		}
		this->size = other.size;

	}
	~ll()
	{
		node* c = head;
		while (c) {
			node* next = c->ptr;
			delete c;
			c = next;
		}
	}
	void append(int v)
	{

		if (!head)
		{
			node* n = new node(v, nullptr);
			head = n;
			current = head;
			size++;
			return;
		}
		node* n = new node(v, nullptr);
		current->ptr = n;
		current = n;
		size++;
	}
	int get(int index)const
	{
		int v = -1;
		node* c = head;

		for (int i = 0; i <= index; i++)
		{
			v = c->value;
			c = c->ptr;
		}
		return v;
	}
	int pop(int index)
	{
		if (index < size)
		{
			node* c = head;
			if (index > 0)
			{
				node* previous_pointer = nullptr;
				for (int i = 0; i <= index - 1; i++)
				{

					previous_pointer = c;
					c = c->ptr;

				}
				int v = c->value;
				node* new_pointer = c->ptr;
				previous_pointer->ptr = new_pointer;
				delete c;
				return v;
			}
			else if (index == 0)
			{
				int v = head->value;
				node* new_pointer = head->ptr;
				delete head;
				head = new_pointer;
				return v;
			}
			else log("Out of bounds");
		}

		else log("Out of bounds");

	}
	void insert(int index, int value)
	{
		if (index < size)
		{
			node* c = head;
			node* previous_pointer{};
			for (int i = 0; i <= index - 1; i++)
			{

				previous_pointer = c;
				c = c->ptr;

			}
			node* nn = new node(value, c);
			previous_pointer->ptr = nn;
			size++;
		}
		else log("Out of bounds");
	}
	void print()
	{
		if (head) { log(*head); }
		else log("Cannot print (nullptr)")
	}

	ll operator+(ll& n)
	{
		ll* sum = new ll();
		ll* temp = this;
		for (int i = 0; i < this->size; i++)
		{
			int no = temp->get(i);
			sum->append(no);
		}
		for (int i = 0; i < n.size; i++)
		{
			int no = n.get(i);
			sum->append(no);
		}
		return *sum;
	}


};


