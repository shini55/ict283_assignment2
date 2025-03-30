#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

using std::map;

template <class K, class V>
class Map
{


private:
    std::map<K, V> data;  // Internal storage

public:
    Map();  // Constructor
    void add(K key, V value);  // Add key-value pair
    V find(K key);  // Find value by key
    void remove(K key);  // Remove key-value pair
    size_t getHash(K key);  // Hash function

private:

};
template <class K, class V>
Map<K, V>::Map() {}

// Add key-value pair
template <class K, class V>
void Map<K, V>::add(K key, V value)
{
    data[key] = value;
}

// Find value by key (returns default value if not found)
template <class K, class V>
V Map<K, V>::find(K key)
{
    if (data.count(key) > 0)
    {
        return data[key];
    }
    return V();  // Return default-constructed U if key not found
}

// Remove a key-value pair
template <class K, class V>
void Map<K, V>::remove(K key)
{
    data.erase(key);
}

// Hash function to generate an index (for BST distribution)
template <class K, class V>
size_t Map<K, V>::getHash(K key)
{
    return std::hash<K>()(key);
}

#endif // MAP_H_INCLUDED
