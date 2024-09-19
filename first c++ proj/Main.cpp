#include <iostream>
#include <string>
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


class str
{
private:
	char* buff;
	unsigned int size_buff;
public:
	str(const char* s)
	{
		size_buff = strlen(s);
		buff = new char[size_buff + 1];
		memcpy(buff, s, size_buff);
		buff[size_buff] = 0;
	}
	str(const str& other)
		: size_buff(other.size_buff + 1)
	{
		buff = new char[size_buff];
		memcpy(buff, other.buff, size_buff + 1);

	}
	~str()
	{
		delete[] buff;
	}
	friend ostream& operator<<(ostream& stream, const str& string);
};

ostream& operator<<(ostream& stream, const str& string)
{
	stream << string.buff;
	return stream;
}

template <typename T> class M_vector
{
private:
	T* arr;
	int size;
	int curr_mem;
	int max_mem;
public:
	M_vector(int ini_size)
		: arr = ::operator new(ini_size * 2 * (int)sizeof(T)),
		  max_mem = ini_size,
		  size = 0
	{

	}

	void push(T element)
	{
		if (curr_mem + (int)sizeof(T) < max_mem)
		{
			arr[size] = element;
			size++;
		}

		else
		{
			T* new_arr;
			max_mem *= 2;
			new_arr = new T[max_mem];
			for (int i = 0; i < size; i++)
			{
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
		}



	}

};

int main()
{
	log(sizeof(int))
		M_vector<int> v(1);
	v.push(12);
	v.push(22);
	v.push(32);
}

