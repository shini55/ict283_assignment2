#include <iostream>
#include "Vector.h"
#include <string>



int main()
{
    Vector<int> numbers1(8);
    numbers1.Insert(10, 0);
    numbers1.Insert(55, 1);
    numbers1.Insert(17, 2);
    numbers1.Insert(99, 3);

    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 1     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Size: " << numbers1.GetSize() << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < numbers1.GetSize(); i++)
    {
        std::cout << "numbers[" << i << "]: " << numbers1[i] << std::endl;
    }
    std::cout << std::endl;


    Vector<int> numbers2(-100);
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 2     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Size: " << numbers2.GetSize() << std::endl;
    std::cout << std::endl;


    Vector<std::string> words(20);
    words.Insert("Test", 0);
    words.Insert("String", 1);
    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 3     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Size: " << words.GetSize() << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < words.GetSize(); i++)
    {
        std::cout << "numbers[" << i << "]: " << words[i] << std::endl;
    }
    std::cout << std::endl;



    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 4     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    std::cout << "Size before inserting elements: " << numbers1.GetSize() << std::endl;
    numbers1.Insert(123, 4);
    numbers1.Insert(456, 5);
    std::cout << "Size after inserting more elements: " << numbers1.GetSize() << std::endl;
    std::cout << std::endl;


    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 5     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    Vector<int> numbers3 = numbers1;

    std::cout << "Original vector: "<< std::endl;
    for (int i = 0; i < numbers1.GetSize(); i++)
    {
        std::cout << "numbers[" << i << "]: " << numbers1[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Copied vector: "<< std::endl;
    for (int i = 0; i < numbers3.GetSize(); i++)
    {
        std::cout << "numbers[" << i << "]: " << numbers3[i] << std::endl;
    }
    std::cout << std::endl;


    numbers3.Insert(789, 6);  // Modifying copied vector


    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 6     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    for (int i = 0; i < numbers3.GetSize(); i++)
    {
        std::cout << "numbers[" << i << "]: " << numbers3[i] << std::endl;
    }
    std::cout << std::endl;



    numbers3.Delete(6);

    std::cout << "-------------------"<< std::endl;
    std::cout << "     Test ID 7     "<< std::endl;
    std::cout << "-------------------"<< std::endl;
    for (int i = 0; i < numbers3.GetSize(); i++)
    {
        std::cout << "numbers[" << i << "]: " << numbers3[i] << std::endl;
    }
    std::cout << std::endl;



    return 0;
}
