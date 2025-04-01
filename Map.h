#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <map>
using std::map;


/**
 * @brief A simple map-like class to store key and the value.
 *
 * This class allows to store data in the form of key and the value
 *
 * @tparam Key The type of the key.
 * @tparam Value The type of the value associated with the key.
 */

template <class Key, class Value>
class Map
{

public:


    /**
     * @brief Creates an empty map.
     *
     * Initializes the map to be empty and ready to store key and the value
     */
    Map();

    /**
     * @brief Destroys the map.
     *
     * Cleans up resources used by the map when it is no longer needed.
     */
    ~Map();


    /**
     * @brief Adds a new key and the value to the map.
     *
     * This function stores the key and the value in the map. If the key already exists,
     * it updates the value.
     *
     * @param key The key to store.
     * @param value The value to the key.
     */
    void add(const Key& key, const Value& value);

    /**
     * @brief Checks if the map contains a specific key.
     *
     * This function returns true if the key is already in the map, otherwise false.
     *
     * @param key The key to look for.
     * @return true if the key is found, false if not.
     */
    bool has(const Key& key) const;

   /**
     * @brief Retrieves the value associated with a given key.
     *
     * This function gives access to the value
     *
     * @param key The key whose value to be retrieve.
     * @return A reference to the value of the key.
     */
    Value& get(const Key& key);



      /**
     * @brief Retrieves the value for  a key for reading
     *
     * This function helps access the value of a key without modifying it.
     *
     * @param key The key whose value to be retrieve.
     * @return A constant reference to the value of the key.
     */
    const Value& get(const Key& key) const;




private:

    std::map<Key, Value> data; ///Stores the key and the value

};

template <class Key, class Value>
Map<Key, Value>::Map() {}


template <class Key, class Value>
Map<Key, Value>::~Map() {}


template <class Key, class Value>
void Map<Key, Value>::add(const Key& key, const Value& value)
{
    data[key] = value;// Add a key and the value
}


template <class Key, class Value>
bool Map<Key, Value>::has(const Key& key) const
{
    return data.find(key) != data.end();// Check if a key exists
}


template <class Key, class Value>
Value& Map<Key, Value>::get(const Key& key)
{
    return data.at(key);// Get the value associated with a key for modifying
}


template <class Key, class Value>
const Value& Map<Key, Value>::get(const Key& key) const
{
    return data.at(key);// Get the value associated with a key for reading
}


#endif // MAP_H_INCLUDED
