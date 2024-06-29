#include <iostream>
#include <string>
using namespace std;
#define log(x) cout << x << endl;
struct node {
	int value{};
	node* ptr{};
	node(int v, node* p) 
	{ 
		value = v;
		ptr = p;
	}
	node() {};
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

};
class ll {

	node* head{};
	node* current{};
	node* x{};
public:
	~ll() 
	{
		node* c = head;
		while (c->ptr) {
			node* next = c->ptr;
			delete c;
			c = next;
		}
	}

	void append(int v)
	{
		if (!head) 
		{
			node* n= new node(v, nullptr);
			head = n;
			current = head;
			return;
		}
		node* n = new node(v, nullptr);
		x = n;
		current->ptr = n;
		current = n;
	}
	int get(int index){
		int v = -1;
		node* c = head;
		
		for (int i=0;i <= index;i++) 
		{
			v = c->value;
			c = c->ptr;
		}
		return v;
	}
	int pop(int index)
	{
		node* c = head;
		if (index != 0) 
		{	
			node* pp=nullptr;
			for (int i = 0;i < index;i++)
			{
				if (index - 1 == i)
				{
					pp = c;
				}
				c = c->ptr;
				
			}
			int v = c->value;
			node* np = c->ptr;
			pp->ptr = np;
			delete c;
			return v;
		}
		else
		{
			int v = head->value;
			node *np = head->ptr;
			delete head;
			head = np;
			return v;
		}
				
	}
	void insert(int index, int value)
	{
		node* c = head;
		node* pp{};
		for (int i = 0;i < index;i++)
		{
			if (index - 1 == i)
			{
				pp = c;
			}
			c = c->ptr;

		}
		node* nn = new node(value, c);
		pp->ptr = nn;


	}
	void print()
	{
		log(*head);
	}

	ll operator+(ll& n )
	{
		ll* sum = new ll;
		current->ptr = n.head;
		sum->head = head;
		sum->current = n.current;
		return *sum;
	}


};

//*((int*)((char*)pointer_array + byte_location))= new_val;
int main()
{
	ll a;
	a.append(1);
	a.append(2);
	a.append(32);
	a.print();
	a.insert(2, 23);
	a.print();

}
	
