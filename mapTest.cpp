#include <iostream>
#include "Map.h" // Include your Map class

int main()
{
    // Create a Map of string keys and int values
    Map<std::string, int> myMap;

    // Test adding elements
    myMap.add("Alice", 25);
    myMap.add("Bob", 30);

    // Test has() function using if-else
    if (myMap.has("Alice"))
    {
        std::cout << "Has Alice? Yes" << std::endl;
    }
    else
    {
        std::cout << "Has Alice? No" << std::endl;
    }

    if (myMap.has("Charlie"))
    {
        std::cout << "Has Charlie? Yes" << std::endl;
    }
    else
    {
        std::cout << "Has Charlie? No" << std::endl;
    }

    // Test get() function
    if (myMap.has("Alice"))
    {
        std::cout << "Alice's value: " << myMap.get("Alice") << std::endl;
    }

    if (myMap.has("Bob"))
    {
        std::cout << "Bob's value: " << myMap.get("Bob") << std::endl;
    }

    // Test edge case: accessing a non-existent key
    if (myMap.has("Charlie"))
    {
        std::cout << "Charlie's value: " << myMap.get("Charlie") << std::endl;
    }
    else
    {
        std::cout << "Charlie does not exist in the map." << std::endl;
    }

    return 0;
}
