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
	int elements = 0;
	const double load_factor = 0.85;
	void rehash()
	{
		log("rehash");
		int new_bucket_size = bucket_size * 2;
		vector<vector<pair<K, V>>> new_bucket(new_bucket_size) ;
		for (const auto& b : buckets)
		{
			for (const auto& p : b)

			{

				int new_hash_index = Hash(p.first, new_bucket_size);
				new_bucket[new_hash_index].emplace_back(p);
			}
		}
		buckets = move(new_bucket);
		bucket_size = new_bucket_size;
	}



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

	unordered_map& operator=(unordered_map& o) noexcept
	{
		log("Copy");
		buckets.clear();
		buckets = o.buckets;
		bucket_size = o.bucket_size;
		return *this;
	}
	unordered_map& operator=(unordered_map&& o) noexcept
	{
		log("Moved");
		buckets.clear();
		buckets = o.buckets;
		bucket_size = o.bucket_size;
		o.buckets.clear();
		o.bucket_size = 0;
		return *this;
	}
};




int main()
{	
	unordered_map<int, int> o{};
	log(Hash(321,10));
	o[133] = 1;
	o[321] = 2;
	o[113] = 1;
	o[321] = 2;
	o[1323] = 1;
	o[3214] = 2;
	o[1334] = 1;
	o[3252] = 2;
	o[123] = 1;
	o[322341] = 2;
	o[1333] = 1;
	log(Hash(133, 10));
	o[3251] = 2;


}
