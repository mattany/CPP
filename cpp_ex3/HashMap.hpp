//
// Created by mattan on 9/11/19.
//
#include <vector>
#include <cmath>
#ifndef CPP_EX3_HASHMAP_HPP
#define CPP_EX3_HASHMAP_HPP

static const double DEFAULT_MIN_LOAD_FACTOR = 0.25;
static const int INITIAL_CAPACITY = 16;
static const double DEFAULT_MAX_LOAD_FACTOR = 0.75;
static const int INITIAL_SIZE = 0;
#endif //CPP_EX3_HASHMAP_HPP

template<typename KeyT, typename ValueT> class HashMap
{
public:
	HashMap(): HashMap(DEFAULT_MIN_LOAD_FACTOR, DEFAULT_MAX_LOAD_FACTOR) {}

	HashMap(std::vector<KeyT> keys, std::vector<ValueT> values)
	{
		assert(keys.size() == values.size());
	}

	HashMap(const HashMap<KeyT, ValueT>& other);

	HashMap(double minLoadFactor, double maxLoadFactor);

	~HashMap() = default;

	int size() const
	{
		return (int) _size;
	}

	int capacity() const
	{
		return (int) _capacity;
	}

	double getLoadFactor() const
	{
		return (double) _size / (double) _capacity;
	}

	bool empty() const
	{
		return _size == 0;
	}

	bool containsKey(KeyT key) const
	{
		size_t index = getHash(key);
		return _data[index].contains(key);
	}

	bool insert(KeyT key, ValueT value)
	{
		size_t index = getHash(key);
		if (!_data[index].contains(key))
		{
			++_size;

		}
	}
private:
	size_t _capacity, _size;
	double _minLoadFactor, _maxLoadFactor;
	typedef std::vector<std::vector<std::pair<KeyT, ValueT> > > container;
	container _data;

	size_t getHash(KeyT key)
	{
		return std::hash<KeyT>{}(key) & _capacity - 1;
	}

	void updateContainer()
	{

		container updated(_capacity);
		for (auto bucket : _data)
		{
			for (auto pair : bucket)
			{
				size_t index = getHash(pair.first());
				updated[index].push_back(pair);
			}
		}
		_data = updated;
	}

	void remap()
	{
		switch (getLoadFactor()):

		case
		if ( < _minLoadFactor)
		{
			_capacity /= 2;
		}
		if (getLoadFactor() > _maxLoadFactor)
		{
			_capacity *= 2;
		}
	}
};

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT> &other):
		_capacity(other._capacity), _size(other._size),
		_minLoadFactor(other._minLoadFactor), _maxLoadFactor(other._maxLoadFactor),
		_data(other._data)
{}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(double minLoadFactor, double maxLoadFactor):
		_capacity(INITIAL_CAPACITY), _size(INITIAL_SIZE),
		_minLoadFactor(minLoadFactor), _maxLoadFactor(maxLoadFactor)
{
	assert(0 <= minLoadFactor && minLoadFactor < maxLoadFactor && maxLoadFactor <= 1);
	_data.resize(_capacity);
}
