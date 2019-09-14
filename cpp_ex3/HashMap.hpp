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
    using bucket = std::vector<std::pair<KeyT, ValueT> >;

	HashMap(): HashMap(DEFAULT_MIN_LOAD_FACTOR, DEFAULT_MAX_LOAD_FACTOR) {}

	HashMap(const std::vector<KeyT>& keys, const std::vector<ValueT>& values);

	HashMap(const HashMap<KeyT, ValueT>& other);

	HashMap(double minLoadFactor, double maxLoadFactor);

	~HashMap()
	{
	    delete[] _data;
        _data = nullptr;
	}

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
		return (double) _size / _capacity;
	}

	ValueT& at(const KeyT& key)
    {
        size_t index = getHash(key);
        auto it = getIterator(key, index);
        if (it == _data[index].end())
        {
            throw std::exception();
        }
        return it->second;
    }

    const ValueT& at(const KeyT& key) const
	{
        size_t index = getHash(key);
        auto it = getConstIterator(key, index);
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
        return _data[index].size();

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
            refreshMap(true);
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
            refreshMap(false);
            return true;
		}
		return false;
	}

    class iterator
    {
    public:

        iterator(const HashMap& hashMap,
                 const std::pair<KeyT,ValueT>& pair):
                _hashMap(hashMap), _pair(pair)
        {
        	int index = 0;
        	auto next =  _hashMap.getData()[0].begin();
        	if (!_hashMap.containsKey(pair.first))
	        {
		        while(index < _hashMap._capacity && next == _hashMap.getData()[index].end())
		        {
			        index++;
			        next = _hashMap.getData()[index].begin();
		        }
		        _pair = *next;
	        }

        }

        const std::pair<KeyT,ValueT>& operator*() const { return _pair;}

        std::pair<KeyT,ValueT>*operator->() const { return &_pair;}

        iterator& operator++()
        {
            size_t index = _hashMap.getHash(_pair.first);
	        const typename bucket::const_iterator it = _hashMap.getConstIterator(_pair.first, index);
	        typename bucket::const_iterator next = it + 1;
	        while(index < _hashMap._capacity && next == _hashMap.getData()[index].end())
	        {
		        index++;
		        const typename bucket::const_iterator b = _hashMap.getData()[index].begin();
		        next = b;
	        }
            _pair = *next;
	        return *this;
        }

        void setPair(const std::pair<KeyT, ValueT>&  pair)
        {
            _pair = pair;
        }

        const std::pair<KeyT, ValueT>& getNextElement(size_t index, typename bucket::iterator& next) const
        {
            while(index < _hashMap._capacity && next == _hashMap.getData()[index].end())
            {
                index++;
                next = _hashMap.getData()[index].begin();
            }
            return *next;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            operator++();
            return tmp;
        }

        bool operator==(iterator const& other) const
        {
            return (_pair == other._pair && _hashMap == other._hashMap);
        }

        bool operator!=(iterator const& other) const
        {
            return (!operator==(other));
        }

    private:
        std::pair<KeyT,ValueT> _pair;
        HashMap _hashMap;
    };


    const iterator begin() const noexcept
    {
        return iterator(*this, std::make_pair(KeyT(), ValueT()));
    }

    const iterator end() const noexcept
    {
        return iterator(*this, *_data[_size - 1].end());
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

    ValueT& operator[](const KeyT& key) noexcept
    {
        size_t index = getHash(key);
        auto it = getIterator(key, index);
        if (it == _data[index].end())
        {
            ValueT value;
            insert(key, value);
            return at(key);
        }
        else
        {
            return it->second;
        }
    }

    const ValueT& operator[](const KeyT& key) const noexcept
    {
        size_t index = getHash(key);
        auto it = std::find_if(_data[index].begin(), _data[index].end(),
                               [&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
        return it->second;
    }

    bool operator==(const HashMap& other) const
    {
        if (_size != other._size || _capacity != other._capacity)
        {
            return false;
        }
        for (std::pair<KeyT,ValueT> pair : *this)
        {
        	KeyT key = pair.first;
            if (!other.containsKey(key) || other.at(key) != at(key))
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const HashMap& other)
    {
        return (!operator==(other));
    }

private:
	size_t _capacity, _size;
	double _minLoadFactor, _maxLoadFactor;
	bucket* _data;

	const bucket* getData() const
    {
        return _data;
    }

	const typename bucket::iterator getIterator(const KeyT &key, size_t index) const
	{

		return std::find_if(_data[index].begin(), _data[index].end(),
		                    [&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
	}

    const typename bucket::const_iterator getConstIterator(const KeyT &key, size_t index) const
    {

        return std::find_if(_data[index].begin(), _data[index].end(),
                            [&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
    }

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

	void refreshMap(bool insert)
	{
		if (!insert && getLoadFactor() < _minLoadFactor && _capacity > 1)
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
    void removeDuplicates(const std::vector<KeyT> &keys, const std::vector<ValueT> &values, bucket& pairs) const;
};

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT> &other):
		_capacity(other._capacity), _size(other._size),
		_minLoadFactor(other._minLoadFactor), _maxLoadFactor(other._maxLoadFactor)
{
    _data = new bucket[_capacity];
    std::copy(other._data, other._data+_capacity, _data);
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(double minLoadFactor, double maxLoadFactor):
		_capacity(INITIAL_CAPACITY), _size(INITIAL_SIZE),
		_minLoadFactor(minLoadFactor), _maxLoadFactor(maxLoadFactor)
{
	assert(0 <= minLoadFactor && minLoadFactor < maxLoadFactor && maxLoadFactor <= 1);
	_data = new bucket[_capacity];
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(const std::vector<KeyT>& keys, const std::vector<ValueT>& values):
        _minLoadFactor(DEFAULT_MIN_LOAD_FACTOR), _maxLoadFactor(DEFAULT_MAX_LOAD_FACTOR)
{
    assert(keys.size() == values.size());
    bucket pairs;
    removeDuplicates(keys, values, pairs);
    _size = pairs.size();
    _capacity = (size_t) pow(2,ceil(log2(_size)));
    if (_capacity < INITIAL_CAPACITY)
    {
        _capacity = INITIAL_CAPACITY;
    }
    if  (getLoadFactor() > _maxLoadFactor)
    {
        _capacity *= 2;
    }
    _data = new bucket[_capacity];
    for (auto pair : pairs)
    {
        size_t bucketIndex = getHash(pair.first);
        _data[bucketIndex].push_back(pair);
    }
}

template<typename KeyT, typename ValueT>
void HashMap<KeyT, ValueT>::removeDuplicates(const std::vector<KeyT> &keys,
        const std::vector<ValueT> &values, std::vector<std::pair<KeyT, ValueT> >& pairs) const
{

    for (int i = 0; i <keys.size(); i++)
    {
        KeyT key = keys[i];
        ValueT value = values[i];
        auto it = std::find_if(pairs.begin(), pairs.end(),
                               [&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
        if(it == pairs.end())
        {
            pairs.emplace_back(key, value);
        }
        else
        {
            it->second = value;
        }
    }
}


