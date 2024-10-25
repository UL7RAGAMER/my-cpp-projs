#include <iostream>
#include <string>
using namespace std;
#define log(x) cout << x << endl

template<typename K,typename V> class unordered_map
{
private:
	K key;
	V value;

public:
	int Hash(int key, int capacity)
	{
		return key % capacity;
	}

	int Hash(string key, int capacity)
	{
		int l = key.length();
		string r;
		for (int i = 0; i < l; i++)
		{
			r += to_string((int)(key[i]));
		}
		return (stoi(r)) % capacity;
	}



};




int main()
{	
	unordered_map<int,int> o;
	log(o.Hash("Ad", 4));
}
