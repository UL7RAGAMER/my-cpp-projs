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
	int size = 0;
	 
public:
	
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
			node* n= new node(v, nullptr);
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
		if (index < size)
		{
			node* c = head;
			if (index > 0)
			{
				node* pp = nullptr;
				for (int i = 0; i <= index - 1; i++)
				{

					pp = c;
					c = c->ptr;

				}
				int v = c->value;
				node* np = c->ptr;
				pp->ptr = np;
				delete c;
				return v;
			}
			else if (index == 0)
			{
				int v = head->value;
				node* np = head->ptr;
				delete head;
				head = np;
				return v;
			}
			else log("Out of bounds");
		}

		else log("Out of bounds");
				
	}
	void insert(int index, int value)
	{	
		if (index<size)
		{
			node* c = head;
			node* pp{};
			for (int i = 0; i <= index - 1; i++)
			{

				pp = c;
				c = c->ptr;

			}
			node* nn = new node(value, c);
			pp->ptr = nn;
			size++;
		}
		else log("Out of bounds");
	}
	void print()
	{	
		if (head) { log(*head); }
		else log("Cannot print (nullptr)")
	}

	ll operator+(ll& n )
	{
		ll* sum = new ll();
		ll* temp = this;
		for (int i = 0; i< this->size;i++)
		{
			int no = temp->get(i);
			sum->append(no);
		}
		for (int i = 0; i < n.size;i++)
		{
			int no = n.get(i);
			sum->append(no);
		}
		return *sum;
	}


};

//*((int*)((char*)pointer_array + byte_location))= new_val;
int main()
{
	ll a;
	a.append(1);
	a.append(2);
	a.append(3);
	a.print();
	ll b;
	b.append(4);
	b.append(5);
	b.append(6);
	b.print();
	ll c = a + b;
	c.print();

	

}
	
