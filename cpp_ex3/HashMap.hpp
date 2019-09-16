//
// Created by mattan on 9/11/19.
//
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#ifndef CPP_EX3_HASHMAP_HPP
#define CPP_EX3_HASHMAP_HPP

static const double DEFAULT_MIN_LOAD_FACTOR = 0.25;
static const int INITIAL_CAPACITY = 16;
static const double DEFAULT_MAX_LOAD_FACTOR = 0.75;
static const int INITIAL_SIZE = 0;
static const char *const OUT_OF_RANGE = "Key does not exist";
static const char *const NON_EQUAL_LENGTH = "Keys and Values are not of equal length.";
static const char *const LOAD_FACTOR_DOMAIN = "Load Factors should be between 0 and 1 and lower"
                                              " load factor must be lower than higher load factor.";
#endif //CPP_EX3_HASHMAP_HPP

/**
 * vector length exception
 */
struct NonEqualLengthException : std::exception
{
	const char *what() const noexcept override
	{
		return NON_EQUAL_LENGTH;
	}
};

/**
 * HashMap template class
 * @tparam KeyT key type
 * @tparam ValueT value type
 */
template<typename KeyT, typename ValueT>
class HashMap
{
public:
	using bucket = std::vector<std::pair<KeyT, ValueT> >;

	/**
	 * default ctor
	 */
	HashMap() : HashMap(DEFAULT_MIN_LOAD_FACTOR, DEFAULT_MAX_LOAD_FACTOR)
	{}

	/**
	 * @param keys vector
	 * @param values vector
	 */
	HashMap(const std::vector<KeyT> &keys, const std::vector<ValueT> &values);

	/**
	 * copy ctor
	 * @param other HashMap
	 */
	HashMap(const HashMap<KeyT, ValueT> &other);

	/**
	 * @param minLoadFactor
	 * @param maxLoadFactor
	 */
	HashMap(double minLoadFactor, double maxLoadFactor);

	HashMap(HashMap && other) noexcept:
	_capacity(other._capacity),
	_size(other._size), _maxLoadFactor(other._maxLoadFactor),
	_minLoadFactor(other._size)
	{
		_data = other._data;
		other._minLoadFactor = 0;
		other._maxLoadFactor =0;
		other._size = 0;
		other._capacity = 0;
		other._data = nullptr;
	}

	/**
	 * dtor
	 */

	~HashMap()
	{
	    delete[] _data;
        _data = nullptr;
	}

	/**
	 * @return number of elements
	 */
	inline int size() const
	{ return (int) _size; }

	/**
	 * @return container capacity
	 */
	inline int capacity() const
	{ return (int) _capacity; }

	/**
	 * @return load factor
	 */
	inline double getLoadFactor() const
	{ return (double) _size / _capacity; }

	ValueT& at(const KeyT& key)
    {
		if (_size == 0 || _capacity == 0)
		{
			throw std::out_of_range(OUT_OF_RANGE);
		}
        size_t index = getHash(key);
        auto it = getIterator(key, index);
        if (it == _data[index].end())
        {
            throw std::out_of_range(OUT_OF_RANGE);
        }
        return it->second;
    }

    const ValueT& at(const KeyT& key) const
	{
        size_t index = getHash(key);
        auto it = getConstIterator(key, index);
        if (it == _data[index].end())
        {
            throw std::out_of_range(OUT_OF_RANGE);
        }
        return it->second;
	}

	/**
	 * @param key
	 * @return
	 */
	int bucketSize(const KeyT &key) const
	{
		if (!containsKey(key))
		{
			throw std::out_of_range(OUT_OF_RANGE);
		}
		size_t index = getHash(key);
		return _data[index].size();

	}

	/**
	 * @return true iff no elements
	 */
	inline bool empty() const { return _size == 0; }

	void clear()
	{
        delete[] _data;
        _size = 0;
        _data = nullptr;
        _data = new bucket[_capacity];
	}

	bool containsKey(KeyT key) const
	{
		if (_size == 0 || _capacity == 0)
		{
			return false;
		}
		size_t bucketIndex = getHash(key);
		return (bucketContainsKey(key, bucketIndex));
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

    class const_iterator
    {
    public:

    	const_iterator()
    	{
    		_hashMap(HashMap());
		    _pair(std::make_pair(KeyT(),ValueT()));
    	}


		/**
		 * @return dereferenced pair
		 */
		inline const std::pair<KeyT, ValueT> &operator*() const { return *_pair; }

		/**
		 * @return pointer to pair
		 */
		inline const std::pair<KeyT, ValueT> *operator->() const { return _pair; }

		/**
		 * @return incremented iterator
		 */
        const const_iterator& operator++()
        {
            size_t index = _hashMap.getHash(_pair->first);
            bucket b = _hashMap._data[index];
	        size_t i = 0;
            for (; i < b.size(); i++)
            {
            	if (b[i].first == _pair->first)
	            {
                    break;
	            }
            }
//	        const typename bucket::iterator it = _hashMap.getIterator(_pair->first, index);
//	        typename bucket::iterator next = it + 1;
	        if (++i == b.size())
	        {
	        	index++;
		        while (index < _hashMap._capacity && _hashMap._data[index].empty())
		        {
			        ++index;
		        }
		        _pair = (index == _hashMap._capacity) ? nullptr : &(_hashMap._data[index][0]);
	        }
	        else
	        {
	        	_pair = &(_hashMap._data[index][i]);
	        }
	        return *this;
        }

	    const const_iterator operator++(int)
	    {
		    const_iterator tmp = *this;
		    operator++();
		    return tmp;
	    }


	    /**
		 * @param other
		 * @return true iff equal
		 */
		inline bool operator==(const_iterator const &other) const
		{ return (_pair == other._pair); }

		/**
		 * @param other
		 * @return true iff equal
		 */
		inline bool operator!=(const_iterator const &other) const
		{ return (!operator==(other)); }


    private:
        friend class HashMap<KeyT, ValueT>;
        const std::pair<KeyT,ValueT> * _pair;
        const HashMap& _hashMap;

        const_iterator(const HashMap& hashMap,
                 const std::pair<KeyT,ValueT>* pair, bool endptr=false):
                _pair(pair), _hashMap(hashMap)
        {
            size_t index = 0;
            if (!pair && !endptr && _hashMap._size > 0)
            {
                while(index < _hashMap._capacity && _hashMap._data[index].empty())
                {
                    index++;
                }
                _pair = &(_hashMap._data[index][0]);
            }

        }
    };

    const const_iterator begin() const noexcept
    {
        return const_iterator(*this, nullptr);
    }

	/**

	 * @return
	 */
	const const_iterator end() const noexcept
	{
		return const_iterator(*this, nullptr, true);
	}

	const const_iterator cbegin() const noexcept
	{
		return const_iterator(*this, nullptr);
	}

	const const_iterator cend() const noexcept
	{
		return const_iterator(*this, nullptr, true);
	}

	HashMap &operator=(const HashMap &other)
	{
		if (this != &other)
		{
			_capacity = other._capacity;
			clear();
			std::copy(other._data, other._data + other._capacity, _data);
			_size = other._size;
			_minLoadFactor = other._minLoadFactor;
			_maxLoadFactor = other._maxLoadFactor;
		}
		return *this;
	}

	ValueT &operator[](const KeyT &key) noexcept
	{
		size_t index = getHash(key);
		auto it = getIterator(key, index);
		if (it == _data[index].end())
		{
			insert(key, ValueT());
			it = getIterator(key, getHash(key));
		}
		return it->second;

	}

	HashMap &operator=(HashMap other) noexcept
	{
		swap(*this, other);
		return *this;
	}

	friend void swap(HashMap &first, HashMap &second) noexcept
	{
		std::swap(first._size, second._size);
		std::swap(first._capacity, second._capacity);
		std::swap(first._minLoadFactor, second._minLoadFactor);
		std::swap(first._maxLoadFactor, second._maxLoadFactor);
		std::swap(first._data, second._data);
	}

	const ValueT &operator[](const KeyT &key) const noexcept
	{
		size_t index = getHash(key);
		auto it = std::find_if(_data[index].begin(), _data[index].end(),
		                       [&key](const std::pair<KeyT, ValueT> &p)
		                       { return p.first == key; });
		return it->second;
	}

	bool operator==(const HashMap &other) const
	{
		if (_size != other._size || _capacity != other._capacity ||
		    _minLoadFactor != other._minLoadFactor ||
		    _maxLoadFactor != other._maxLoadFactor)
		{
			return false;
		}
		for (auto pair : *this)
		{
			KeyT key = pair.first;
			if (!other.containsKey(key) || other.at(key) != at(key))
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const HashMap &other)
	{
		return (!operator==(other));
	}

private:
	size_t _capacity, _size;
	double _minLoadFactor, _maxLoadFactor;
	bucket *_data;

	const typename bucket::iterator getIterator(const KeyT &key, size_t index) const
	{

		return std::find_if(_data[index].begin(), _data[index].end(),
		                    [&key](const std::pair<KeyT, ValueT> &p)
		                    { return p.first == key; });
	}

	const typename bucket::const_iterator getConstIterator(const KeyT &key, size_t index) const
	{

		return std::find_if(_data[index].begin(), _data[index].end(),
		                    [&key](const std::pair<KeyT, ValueT> &p)
		                    { return p.first == key; });
	}

	size_t getHash(KeyT key) const
	{
		return std::hash<KeyT>{}(key) & (_capacity - 1);
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

	void removeDuplicates(const std::vector<KeyT> &keys, const std::vector<ValueT> &values,
	                      bucket &pairs) const;
};

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::const_iterator::const_iterator()
{
	_hashMap(HashMap());
	_pair(std::make_pair(KeyT(), ValueT()));
}

template<typename KeyT, typename ValueT>
const HashMap::const_iterator &HashMap<KeyT, ValueT>::const_iterator::operator++()
{
	size_t index = _hashMap.getHash(_pair->first);
	bucket b = _hashMap._data[index];
	size_t i = 0;
	for (; i < b.size(); i++)
	{
		if (b[i].first == _pair->first)
		{
			break;
		}
	}
	if (++i == b.size())
	{
		index++;
		while (index < _hashMap._capacity && _hashMap._data[index].empty())
		{
			++index;
		}
		_pair = (index == _hashMap._capacity) ? nullptr : &(_hashMap._data[index][0]);
	}
	else
	{
		_pair = &(_hashMap._data[index][i]);
	}
	return *this;
}

template<typename KeyT, typename ValueT>
const HashMap::const_iterator HashMap<KeyT, ValueT>::const_iterator::operator++(int)
{
	const_iterator tmp = *this;
	operator++();
	return tmp;
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::const_iterator::const_iterator(const HashMap &hashMap,
                                                      const std::pair<KeyT, ValueT> *pair,
                                                      bool endptr) :
		_pair(pair), _hashMap(hashMap)
{
	size_t index = 0;
	if (!pair && !endptr && _hashMap._size > 0)
	{
		while (index < _hashMap._capacity && _hashMap._data[index].empty())
		{
			index++;
		}
		_pair = &(_hashMap._data[index][0]);
	}

}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT> &other):
		_capacity(other._capacity), _size(other._size),
		_minLoadFactor(other._minLoadFactor), _maxLoadFactor(other._maxLoadFactor)
{
	_data = new bucket[_capacity];
	std::copy(other._data, other._data + _capacity, _data);
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(double minLoadFactor, double maxLoadFactor):
		_capacity(INITIAL_CAPACITY), _size(INITIAL_SIZE),
		_minLoadFactor(minLoadFactor), _maxLoadFactor(maxLoadFactor)
{
	if (!(0 < minLoadFactor && minLoadFactor < maxLoadFactor && maxLoadFactor < 1))
	{
		throw std::domain_error(LOAD_FACTOR_DOMAIN);
	}
	_data = new bucket[_capacity];
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(const std::vector<KeyT> &keys, const std::vector<ValueT> &values):
		HashMap()
{
	if (keys.size() != values.size())
	{
		throw NonEqualLengthException();
	}
	for (size_t i = 0; i < keys.size(); i++)
	{
		(*this)[keys[i]] = values[i];
	}
}

template<typename KeyT, typename ValueT>
void HashMap<KeyT, ValueT>::removeDuplicates(const std::vector<KeyT> &keys,
                                             const std::vector<ValueT> &values,
                                             std::vector<std::pair<KeyT, ValueT> > &pairs) const
{

	for (int i = 0; i < keys.size(); i++)
	{
		KeyT key = keys[i];
		ValueT value = values[i];
		auto it = std::find_if(pairs.begin(), pairs.end(),
		                       [&key](const std::pair<KeyT, ValueT> &p)
		                       { return p.first == key; });
		if (it == pairs.end())
		{
			pairs.emplace_back(key, value);
		}
		else
		{
			it->second = value;
		}
	}
}



