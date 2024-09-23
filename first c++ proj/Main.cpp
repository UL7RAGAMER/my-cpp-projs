#include <iostream>
#include <string>
using namespace std;
#define log(x) cout << x << endl;

template <typename T> class M_vector
{
private:
	T* arr;
	int size;
	int curr_mem;
	int max_mem;
public:

	M_vector(int ini_size)
		: arr{ new T(ini_size * 2) },
		  max_mem{ ini_size * 2 * (int)sizeof(T) },
		  size{0}
	{
	}
	~M_vector()
	{
		delete[] arr;
	}
	int len()
	{
		return size
	}
	void push(T element)
	{
		if (curr_mem + (int)sizeof(T) < max_mem)
		{
			arr[size] = element;
			size++;
			curr_mem = curr_mem + ((int)sizeof(T));
		}

		else
		{
			T* new_arr;
			max_mem = max_mem * 2;
			new_arr = new T[max_mem];
			for (int i = 0; i < size; i++)
			{
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			arr[size] = element;
			size++;
			curr_mem = curr_mem + ((int)sizeof(T));
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
	v.len();
	v.push(22);
	v.len();
	v.push(32);
	v.len();
	v.push(42);
	v.len();
	v.push(52);
	v.len();
	v.push(62);
	v.len();
	

}

