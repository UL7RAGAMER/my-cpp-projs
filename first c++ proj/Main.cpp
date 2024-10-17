#include <iostream>
#include <string>
using namespace std;
#define log(x) cout << x << endl

template <typename T> class M_vector
{
private:
	T* arr;
	int size;
	int capacity;
public:
	M_vector(const M_vector& other) 
		:capacity(1),
		size(0),
		arr((T*)(::operator new(1 * sizeof(T) * 2)))
	{
		log("Copied");
		for (int i = 0;i < other.size;i++)
		{
			push(other.get(i));
		}
	}
	M_vector(int ini_size)
		: arr{ (T*)(::operator new(ini_size * sizeof(T) * 2)) },
		  capacity{ini_size * 2},
		  size{0}
	{
	}
	~M_vector()
	{
		operator delete(arr);
	}
	int len()
	{
		return capacity;
	}
	void push(T element)
	{
		if (size < capacity)
		{
			new (arr+ size) T{element};
			size++;
		}

		else
		{
			T* new_arr;
			capacity = capacity * 2;
			new_arr = (T*)(::operator new(capacity * sizeof(T)));
			for (int i = 0; i < size; i++)
			{
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			new (arr + size) T{ element };
			size++;
		}

	}
	T get(int index) const
	{
		return arr[index];
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
	v.push(23);
	M_vector<int> s = v;
	log(s);

}

