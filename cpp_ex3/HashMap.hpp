//
// Created by mattan on 9/11/19.
//
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>
#include <iostream>
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
	HashMap(const std::vector<KeyT> &keys, const std::vector<ValueT> &values): HashMap()
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

	/**
	 * copy ctor
	 * @param other HashMap
	 */
	HashMap(const HashMap<KeyT, ValueT> &other):
			_capacity(other._capacity), _size(other._size),
			_minLoadFactor(other._minLoadFactor), _maxLoadFactor(other._maxLoadFactor),
			_data(new bucket[_capacity])
	{
		std::copy(other._data.get(), other._data.get() + _capacity, _data.get());
	}

	/**
	 * @param minLoadFactor
	 * @param maxLoadFactor
	 */
	HashMap(double minLoadFactor, double maxLoadFactor):
			_capacity(INITIAL_CAPACITY), _size(INITIAL_SIZE),
			_minLoadFactor(minLoadFactor), _maxLoadFactor(maxLoadFactor), _data(new bucket[_capacity])
	{
		if (!(0 < minLoadFactor && minLoadFactor < maxLoadFactor && maxLoadFactor < 1))
		{
			throw std::domain_error(LOAD_FACTOR_DOMAIN);
		}

	}

	HashMap(HashMap && other) noexcept:
	_capacity(other._capacity),
	_size(other._size), _maxLoadFactor(other._maxLoadFactor),
	_minLoadFactor(other._size)
	{
		_data.reset();
		_data = std::move(other._data);
		other._minLoadFactor = 0;
		other._maxLoadFactor = 0;
		other._size = 0;
		other._capacity = 0;
	}

	/**
	 * dtor
	 */

	~HashMap(){}

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

	/**
	 * @param key
	 * @return
	 */
    ValueT& at(const KeyT& key)
    {
		if (_data != nullptr)
        {
            size_t index = getHash(key);
            auto it = getIterator(key, index);
            if (it != _data[index].end())
            {
                return it->second;
            }
        }
        throw std::out_of_range(OUT_OF_RANGE);
    }

    /**
     * @param key
     * @return
     */
    const ValueT& at(const KeyT& key) const
	{
        if (_data != nullptr)
        {
            size_t index = getHash(key);
            auto it = getIterator(key, index);
            if (it != _data[index].end())
            {
                return it->second;
            }
        }
        throw std::out_of_range(OUT_OF_RANGE);
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

	/**
	 *
	 */
	void clear()
	{
        _size = 0;
        _data.reset();
        _data = std::make_unique<bucket[]>(_capacity);
	}

	/**
	 * @param key
	 * @return
	 */
	bool containsKey(KeyT key) const
	{
		if (_size == 0 || _capacity == 0)
		{
			return false;
		}
		size_t bucketIndex = getHash(key);
		return (bucketContainsKey(key, bucketIndex));
	}

	/**
	 * @param key
	 * @param value
	 * @return
	 */
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

	/**
	 * @param key
	 * @param index
	 * @return
	 */
	bool bucketContainsKey(KeyT key, size_t index) const
	{
		return any_of(_data[index].begin(), _data[index].end(),
		              [&key](const std::pair<KeyT, ValueT>& p) { return p.first == key;});
	}

	/**
	 * @param key
	 * @return
	 */
	bool erase(KeyT key)
	{
		size_t index = getHash(key);
		auto it = getIterator(key, index);
		if (it != _data[index].end())
		{
			--_size;
			_data[index].erase(it);
            refreshMap(false);
            return true;
		}
		return false;
	}

	/**
	 *
	 */
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
		inline const std::pair<KeyT, ValueT> *operator->() const { return &(*_pair); }

		/**
		 * @return incremented iterator
		 */
        const const_iterator& operator++()
		{
            int index = _hashMap.getHash(_pair->first), lastIndex = _hashMap._capacity - 1;
            if (++_pair == _hashMap._data[index].end() && index != lastIndex)
            {
                while (++index < lastIndex && _hashMap._data[index].empty()) {}
                _pair = _hashMap._data[index].begin();
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
		typename bucket::const_iterator _pair;
        const HashMap& _hashMap;

        const_iterator(const HashMap& hashMap,
                 const typename bucket::const_iterator pair):
                _pair(pair), _hashMap(hashMap)
        {}
    };

    /**
     * @return
     */
    const const_iterator begin() const noexcept
    {
        size_t i = 0;
        for (size_t & j = i; j <_capacity && _data[j].empty(); ++j) {}
        return const_iterator(*this, _data[i].begin());
    }

	/**
	 * @return
	 */
	const const_iterator end() const noexcept
	{
	    typename bucket::const_iterator it = _data[_capacity - 1].end();
		return const_iterator(*this, it);
	}

	/**
	 * @return
	 */
	const const_iterator cbegin() const noexcept
	{
        size_t i = 0;
        for (size_t & j = i; j <_capacity && _data[j].empty(); ++j) {}
        return const_iterator(*this, _data[i].begin());
	}

	/**
	 * @return
	 */
	const const_iterator cend() const noexcept
	{
        typename bucket::iterator it = _data[_capacity - 1].end();
        return const_iterator(*this, it);
	}

	/**
	 * @param other
	 * @return
	 */
	HashMap &operator=(const HashMap &other)
	{
		if (this != &other)
		{
			_capacity = other._capacity;
			clear();
			std::copy(other._data.get(), other._data.get() + other._capacity, _data.get());
			_size = other._size;
			_minLoadFactor = other._minLoadFactor;
			_maxLoadFactor = other._maxLoadFactor;
		}
		return *this;
	}

	/**
	 * @param key
	 * @return
	 */
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

    /**
 * @param key
 * @return
 */
    const ValueT &operator[](const KeyT &key) const noexcept
    {
        size_t index = getHash(key);
        auto it = std::find_if(_data[index].begin(), _data[index].end(),
                               [&key](const std::pair<KeyT, ValueT> &p)
                               { return p.first == key; });
        return it->second;
    }

	/**
	 * @param other
	 * @return
	 */
	HashMap &operator=(HashMap && other) noexcept = default;

	/**
	 * @param other
	 * @return
	 */
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

	/**
	 * @param other
	 * @return
	 */
	bool operator!=(const HashMap &other)
	{
		return (!operator==(other));
	}

private:
	size_t _capacity, _size;
	double _minLoadFactor, _maxLoadFactor;
	std::unique_ptr<bucket[]> _data;

	/**
	 * @param key
	 * @param index
	 * @return
	 */
	const typename bucket::iterator getIterator(const KeyT &key, size_t index) const
	{

		return std::find_if(_data[index].begin(), _data[index].end(),
		                    [&key](const std::pair<KeyT, ValueT> &p)
		                    { return p.first == key; });
	}

	/**
	 * @param key
	 * @param index
	 * @return
	 */
	const typename bucket::const_iterator getConstIterator(const KeyT &key, size_t index) const
	{

		return std::find_if(_data[index].begin(), _data[index].end(),
		                    [&key](const std::pair<KeyT, ValueT> &p)
		                    { return p.first == key; });
	}

	/**
	 * @param key
	 * @return
	 */
	size_t getHash(KeyT key) const
	{
		return std::hash<KeyT>{}(key) & (_capacity - 1);
	}

	/**
	 * @param enlarge
	 */
	void updateContainer(bool enlarge)
	{
		size_t old_capacity = (enlarge) ? _capacity / 2 : _capacity * 2;
		auto temp = std::make_unique<bucket[]>(_capacity);
		for (size_t i = 0; i < old_capacity; i++)
        {
            for (auto pair : _data[i])
            {
                size_t index = getHash(pair.first);
                temp[index].push_back(pair);
            }
        }
		_data.reset();
		_data = std::move(temp);
	}

	/**
	 * @param insert
	 */
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
};