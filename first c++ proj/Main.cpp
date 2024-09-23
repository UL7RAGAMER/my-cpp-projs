#include <iostream>
#include <string>
using namespace std;
#define log(x) cout << x << endl;

template <typename T> class M_vector
{
private:
	T* arr;
	int size;
	int capacity;
public:

	M_vector(int ini_size)
		: arr{ static_cast<T*>(::operator new(ini_size * sizeof(T) * 2)) },
		  capacity{ini_size * 2},
		  size{0}
	{
	}
	~M_vector()
	{
		delete[] arr;
	}
	int len()
	{
		return capacity;
	}
	void push(T element)
	{
		if (size < capacity)
		{
			arr[size] = element;
			size++;
		}

		else
		{
			T* new_arr;
			capacity = capacity * 2;
			new_arr = static_cast<T*>(::operator new(capacity * sizeof(T)));
			for (int i = 0; i < size; i++)
			{
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			arr[size] = element;
			size++;
		}



	}
	friend ostream& operator<<(ostream& stream, const M_vector<T>& a)
	{
		for (int i = 0; i < a.size; i++)
		{
			stream << a.arr[i]<<' ';
			
		}
		return stream;
	}
};

int main()
{
	M_vector<int> v(1);
	v.push(12);
	log(v.len());

	v.push(22);
	log(v.len());
	v.push(32);
	log(v.len());

	v.push(42);
	log(v.len());

	v.push(52);
	log(v.len());

	v.push(62);

	log(v.len());
	

}

