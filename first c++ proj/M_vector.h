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
	void resize()
	{
		T* new_arr;
		capacity = capacity * 2;
		new_arr = (T*)(::operator new(capacity * sizeof(T)));
		for (int i = 0; i < size; i++)
		{
			new (new_arr + i) T{ move(arr[i]) };
			arr[i].~T();
		}
		::operator delete(arr);
		arr = new_arr;
	}
public:
	M_vector(const M_vector& other)
		:capacity(1),
		size(0),
		arr((T*)(::operator new(1 * sizeof(T))))
	{
		log("Copied");
		for (int i = 0; i < other.size; i++)
		{
			push(other[i]);
		}
	}
	M_vector& operator=(const M_vector& other)
	{
		if (arr != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				arr[i].~T();
			}
			::operator delete(arr);
		}

		capacity = other.capacity;
		size = 0;
		arr = (T*)(::operator new(capacity * sizeof(T)));
		if (this != &other)
		{
			log("Copied");
			for (int i = 0; i < other.size; i++)
			{
				push(other[i]);
			}
		}

		return *this;
	}

	M_vector& operator=(M_vector&& other)
	{
		if (arr != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				arr[i].~T();
			}
			::operator delete(arr);
		}

		capacity = other.capacity;
		size = 0;
		arr = (T*)(::operator new(capacity * sizeof(T)));
		if (this != &other)
		{
			log("Moved");
			for (int i = 0; i < other.size; i++)
			{
				push((T&&)(other[i]));
			}
		}
		other.arr = nullptr;
		other.arr = 0;
		other.size = 0;
		return *this;
	}
	M_vector(M_vector&& other) noexcept
		:capacity(other.capacity),
		size(other.size),
		arr(other.arr)
	{
		log("Moved");
		other.arr = nullptr;
		other.capacity = 0;
		other.size = 0;
	}

	M_vector(int ini_size)
		: arr{ (T*)(::operator new(ini_size * sizeof(T))) },
		capacity{ ini_size },
		size{ 0 }
	{
	}

	~M_vector()
	{
		for (int i = 0; i < size; i++)
		{
			arr[i].~T();
		}
		::operator delete(arr);
	}
	int len()
	{
		return capacity;
	}

	void push(T& element)
	{
		log("Copied");
		emplace_back(element);


	}


	void push(T&& element)
	{
		log("Moved");
		emplace_back(move(element));


	}
	template <typename... Args>
	void emplace_back(Args&&... args)
	{
		log("Moved");
		if (size >= capacity)
		{
			resize();
		}
		new (arr + size) T{forward<Args>(args)...};
		size++;
	}
	const T& operator[](int index) const
	{
		if (index < 0 || index >= size)
			throw out_of_range("Index out of bounds");
		return arr[index];
	}
	friend ostream& operator<<(ostream& stream, const M_vector<T>& a)
	{
		for (int i = 0; i < a.size; i++)
		{
			stream << a.arr[i] << ' ';

		}
		return stream;
	}
};
