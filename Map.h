#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <map>
using std::map;

template <class Key, class Value>
class Map
{

public:


    // Constructor
    Map();

    // Destructor
    ~Map();

    // Function 1: Add a key-value pair (renamed from insert)
    void add(const Key& key, const Value& value);

    // Function 2: Check if a key exists
    bool has(const Key& key) const;

    // Function 3: Get the value associated with a key
    Value& get(const Key& key);
    const Value& get(const Key& key) const;



    // Function 4: Get the number of elements
    size_t Count() const;

private:

    std::map<Key, Value> data;

};
// Constructor
template <class Key, class Value>
Map<Key, Value>::Map() {}

// Destructor
template <class Key, class Value>
Map<Key, Value>::~Map() {}

// Add a key-value pair (renamed from insert)
template <class Key, class Value>
void Map<Key, Value>::add(const Key& key, const Value& value)
{
    data[key] = value;
}

// Check if a key exists (renamed from contains)
template <class Key, class Value>
bool Map<Key, Value>::has(const Key& key) const
{
    return data.find(key) != data.end();
}

// Get the value associated with a key
template <class Key, class Value>
Value& Map<Key, Value>::get(const Key& key)
{
    return data.at(key);
}

// Get the value associated with a key (const version)
template <class Key, class Value>
const Value& Map<Key, Value>::get(const Key& key) const
{
    return data.at(key);
}
// Get the number of elements
template <class Key, class Value>
size_t Map<Key, Value>::Count() const
{
    return data.size();
}

#endif // MAP_H_INCLUDED
