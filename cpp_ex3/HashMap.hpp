//
// Created by mattan on 9/11/19.
//
#include <vector>
#include <cmath>
#include <unordered_map>

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

	HashMap(std::vector<KeyT> keys, std::vector<ValueT> values);

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

	const ValueT& at(const KeyT& key) const
	{
	    size_t index = getHash(key);
        auto it = std::find_if(_data[index].begin(), _data[index].end(),
                               [&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
        if (it == _data[index].end())
        {
            throw std::exception();
        }
        return it->second;
	}



	int bucketSize(const KeyT& key) const
    {
	    if (!containsKey(key))
        {
	        throw std::exception();
        }
	    size_t index = getHash(key);
        return _data[index];

    }

	bool empty() const
	{
		return _size == 0;
	}

	void clear() const
	{
        delete[] _data;
        _size = 0;
        _data = nullptr;
        _data = new bucket[_capacity];
	}

	bool containsKey(KeyT key) const
	{
		size_t bucketIndex = getHash(key);
		return bucketContainsKey(key, bucketIndex);
	}

	bool insert(KeyT key, ValueT value)
	{
		size_t bucketIndex = getHash(key);
		bool contained = bucketContainsKey(key, bucketIndex);
		if (!contained)
		{

			_data[bucketIndex].emplace_back(key, value);
            ++_size;
			refreshMap();
			return true;
		}
		return false;
	}

	bool bucketContainsKey(KeyT key, size_t index) const
	{

		return any_of(_data[index].begin(), _data[index].end(),
		              [&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
	}

	bool erase(KeyT key)
	{
		size_t index = getHash(key);
		auto it = std::find_if(_data[index].begin(), _data[index].end(),
				[&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
		if (it != _data[index].end())
		{
			--_size;
			_data[index].erase(it);
			refreshMap();
		}
		return false;
	}

private:
	size_t _capacity, _size;
	double _minLoadFactor, _maxLoadFactor;
	using bucket = std::vector<std::pair<KeyT, ValueT> >;
	bucket* _data;

	size_t getHash(KeyT key) const
	{
		return std::hash<KeyT>{}(key) & _capacity - 1;
	}

	void updateContainer(bool enlarge)
	{
        size_t old_capacity = (enlarge) ? _capacity / 2 : _capacity * 2;
		auto temp = new bucket[_capacity]();
		for (size_t i = 0; i < old_capacity; i++)
		{
			for (auto pair : _data[i])
			{
				size_t index = getHash(pair.first);
				temp[index].push_back(pair);
			}
		}
        delete[] _data;
        _data = temp;
	}

	void refreshMap()
	{
		if (getLoadFactor() < _minLoadFactor && _capacity > 1)
		{

			_capacity /= 2;
			return updateContainer(false);
		}
		if (getLoadFactor() > _maxLoadFactor)
		{
			_capacity *= 2;
			return updateContainer(true);
		}
	}

	HashMap& operator=(const HashMap& other)
    {
        if (this != &other)
        {
            _capacity = other._capacity();
            clear();
            std::copy(other._data, other._data + other._capacity, _data);
            _size = other._size;
            _minLoadFactor = other._minLoadFactor;
            _maxLoadFactor = other._maxLoadFactor;
        }
        return *this;
    }

    const ValueT& operator[](const KeyT& key) const noexcept
    {
        return _data[getHash(key)];
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
	_data = new bucket[_capacity];
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(std::vector<KeyT> keys, std::vector<ValueT> values):
        _minLoadFactor(DEFAULT_MIN_LOAD_FACTOR), _maxLoadFactor(DEFAULT_MAX_LOAD_FACTOR),
        _size(keys.size())
{
    assert(keys.size() == values.size());
    _capacity = (size_t) pow(2,ceil(log(_size)));
    _data = new bucket[_capacity]();
    while (getLoadFactor() < _minLoadFactor || getLoadFactor() > _maxLoadFactor)
    {
        refreshMap();
    }
    for (int i = 0; i < keys.size(); i++)
    {
        size_t bucketIndex = getHash(keys[i]);
        _data[bucketIndex].emplace_back(keys[i], values[i]);
    }
}
