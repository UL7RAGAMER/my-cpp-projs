#include <iostream>
#include <string>
using namespace std;
#define log(x) cout << x << endl
#include "M_vector.h"
#include <vector>
#include <list>
#include <utility>
template <class T>
int Hash(T key,int capacity){}
template<>
int Hash(int key, int capacity)
{
	return (key ^ ( key >> 4)) % capacity;
}
template<>
int Hash(string key, int capacity)
{
	int l = key.length();
	int r = 0;
	for (int i = 0; i < l; i++)
	{
		r = r * 37 + (int)(key[i]);
	}
	return r % capacity;
}



template<typename K,typename V> 
class unordered_map
{
private:
	int bucket_size;
	vector<vector<pair<K, V>>> buckets;



public:
	class Iterator
	{
	private:
		using B_iterator = typename vector<pair<K, V>> ::iterator;

		unordered_map* map;
		B_iterator current;
		int index;
		
		void next()
		{
			while (index < map->bucket_size && current == map->buckets[index].end())
			{
				index++;
				if (index < map->bucket_size)
				{
					current = map->buckets[index].begin();
				}
			}
		}
	
	public:
		Iterator(unordered_map* map, B_iterator current, int index)
			:map{map}, current{current},index(index)
		{
			if (index < map->bucket_size && current == map->buckets[index].end())
				next();

		}

		pair<K, V>& operator*()
		{
			return *current;
		}

		Iterator& operator++()
		{
			current++;
			next();
			return *this;

		}
	bool operator==(const Iterator& other) const
	{
		return map == other.map && index == other.index && current == other.current;
	}
	bool operator!=(const Iterator& other) const
	{
		return !(*this == other);
	}


	};



	unordered_map(int size = 10)
		:bucket_size(size)
	{
		buckets.resize(size);
	}

	~unordered_map(){buckets.~vector();}

	void del(K key)
	{
		int hashi = Hash(key, bucket_size);
		auto& bucket = buckets[hashi];
		for (auto it = bucket.begin(); it != bucket.end(); ++it) 
		{
			if (it->first == key)
			{
				bucket.erase(it);
				return;
			}
		}
	}
	V& operator[](const K& key)
	{
		int hashIndex = Hash(key, bucket_size);
		
		for (auto& p : buckets[hashIndex])
		{
			if (p.first == key)
			{	
				return p.second;
			}
		}

		buckets[hashIndex].emplace_back(key, V());
		return buckets[hashIndex].back().second;
	}

	Iterator begin() {
		return Iterator(this, buckets[0].begin(), 0);
	}

	Iterator end() {
		int lastBucket = bucket_size - 1;
		while (lastBucket >= 0 && buckets[lastBucket].empty()) {
			--lastBucket;
		}
		return lastBucket >= 0 ? Iterator(this, buckets[lastBucket].end(), lastBucket) : Iterator(this, buckets[0].end(), 0);
	}
	auto find(K key)
	{
		int hashIndex = Hash(key, bucket_size);
		for (auto it = buckets[hashIndex].begin(); it != buckets[hashIndex].end(); ++it)
		{
			if (it->first == key)
			{
				return Iterator(this, it, hashIndex);
			}
		}
		return end();
	}
};




int main()
{	
	unordered_map<int, int> o{};
	log(Hash(321,10));
	log(Hash(133,10));
	o[133] = 1;
	o[321] = 2;
	
	o.del(133);
	for (auto& p : o)
	{
		log(p.first);
	}

}
