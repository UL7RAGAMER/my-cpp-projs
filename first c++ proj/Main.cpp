#include <iostream>
#include <string>
using namespace std;
#define log(x) cout << x << endl
#include "M_vector.h"
#include <list>
#include <algorithm>
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
	list<pair<K, V>>* buckets;
	int elements = 0;
	const double load_factor = 0.85;
	void rehash()
	{
		log("rehash");
		int new_bucket_size = bucket_size * 2;
		list<pair<K, V>>* new_bucket = new list<pair<K, V>>[new_bucket_size];
		for (int i= 0 ;i<bucket_size;i++)
		{
			for (const auto& p : buckets[i])

			{

				int new_hash_index = Hash(p.first, new_bucket_size);
				new_bucket[new_hash_index].push_back(p);
			}
		}
		delete[] buckets;
		buckets = move(new_bucket);
		bucket_size = new_bucket_size;
	}



public:
	class Iterator
	{
	private:
		using B_iterator = typename list<pair<K, V>> ::iterator;

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
		buckets = new list<pair<K, V>>[bucket_size];
	}
	~unordered_map()
	{
		delete[] buckets;
	}

	void del(K key)
	{
		int hashi = Hash(key, bucket_size);
		auto& bucket = buckets[hashi];
		for (auto it = bucket.begin(); it != bucket.end(); ++it) 
		{
			if (it->first == key)
			{	
				elements--;
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
		elements++;
		buckets[hashIndex].emplace_back(key, V());
		if ((elements / bucket_size) > load_factor)
			rehash();
		
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
		return Iterator(this, buckets[bucket_size - 1].end(), bucket_size - 1);

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

	unordered_map& operator=(const unordered_map& o) noexcept
	{
		log("Copied");
		
		if (this == &o) return *this;

		delete[] buckets;

		bucket_size = o.bucket_size;
		elements = o.elements;
		buckets = new list<pair<K, V>>[bucket_size];
		for (int i = 0; i < bucket_size; ++i) {
			buckets[i] = o.buckets[i];
		}
		return *this;
	}
	unordered_map& operator=(unordered_map&& o) noexcept {
		log("Moved");

		if (this != &o) {
			delete[] buckets; 

			buckets = o.buckets;
			bucket_size = o.bucket_size;
			elements = o.elements;

			o.buckets = nullptr;
			o.bucket_size = 0;
			o.elements = 0;
		}

		return *this;
	}
};




int main()
{	
	
	unordered_map<int,int> o;
	o[1] = 2;
	o[2] = 41;
	o[123] = 1;

	for (auto& i : o)
	{
		log((i).first);
	}

}
