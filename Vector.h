#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept>

const int INITIAL_CAPACITY =9; /// To define the initial capacity of the vector object


/**
 * @class Vector
 * @brief To help in defining a dynamic array
 *
 * This template class implements a Vector class that allows to
 * insert, delete, resize, and deep copy.
 *
 * @tparam T The type of element that is stored in the vector.
 */
template <class T>
class Vector
{

public:
    /**
    * @brief Default constructor for the Vector class.
    *
    * Initializes an empty vector with a default capacity.
    */
    Vector();

    /**
    * @brief Constructor to initialize the vector.
    *
    * @param n is the capacity of the vector.
    */
    Vector(int n); //Gather resources
    /**
     * @brief Destructor for the Vector class.
     *
     * Releases any allocated memory for the vector.
     */
    ~Vector();     //Release or remove memory


    /**
    * @brief Copy constructor for the Vector.
    *
    * Creates a deep copy of another vector.
    *
    * @param rhs is the vector to copy from.
    */
    Vector(const Vector<T>& rhs);

    /**
     * @brief Overloaded operator for the Vector.
     *
     * Copies data from one vector to another using deep copy.
     *
     * @param rhs The vector to assign from.
     * @return A reference to the current vector.
     */
    Vector<T>& operator=(const Vector<T>& rhs);

    /**
     * @brief Copies the data from another vector.
     *
     * Performs a deep copy of the given vector's data.
     *
     * @param rhs The vector to copy from.
     */
    void Copy(const Vector<T>& rhs);


    /**
    * @brief Inserts an element at a specific index in the vector.
    *
    * If the index is valid, the element is inserted and the vector is resized if required.
    *
    * @param data The data to insert.
    * @param index The index where the element should be inserted.
    * @return True if insertion is successful, otherwise false.
    */

    bool Insert(const T& data, int index);

    /**
    * @brief Deletes an element at a specific index in the vector
    *
    * If the index is valid, the element is removed and the vector is resized if required
    *
    * @param index The index of the element to delete.
    * @return True if deletion is successful, otherwise false
    */
    bool Delete(int index);

    /**
     * @brief Gets the current size of the vector.
     *
     * @return The number of elements in the vector.
     */
    int GetSize() const;

    /**
    * @brief Accesses an element at a specific index for reading.
    *
    * This method allows to read elements of the vector.
    *
    * @param index The index of the element to access.
    * @return A constant reference to the element.
    */

    const T& operator[](int index) const; //Access /Read e.g. cout << vec [0] << endl;

    /**
    * @brief Accesses an element at a specific index for modifying.
    *
    * This operator allows tp modify the elements in the vector
    *
    * @param index The index of the element to access.
    * @return A reference to the element
    */

    T& operator[](int index);             //Modify / Assign e.g. vec[10] =999;



private:
    T *m_vector;    ///A pointer to dynamic array
    int m_size;     /// The number of elements in a array
    int m_capacity;  ///The number of allocated spaces on the heap

    void Resize(int newCapacity); /// Private method to resize the vector


    int GetCapacity() const; /// Private method to get capacity of the vector

};

//**==****==****==****==****==****==****==****==****==**
//IMPLEMENTATION
//**==****==****==****==****==****==****==****==****==**
template <class T>
Vector<T>::Vector()
{
    m_size = 0;
    m_capacity = 0;
    m_capacity = INITIAL_CAPACITY;
    m_vector = new T[m_capacity];
}

template <class T>
Vector<T>::Vector(int n)
{
    if(n <= 0)
    {
        n=INITIAL_CAPACITY ;  //default to initial capacity if n is invalid
    }
    m_size=0;               // vector is initially empty
    m_capacity=n;
    m_vector=new T[n];
    if(m_vector != nullptr) //only when heap is successfully allocated
    {
        m_capacity =n;      //update the capacity
    }

}

template <class T>
Vector<T>::~Vector()
{
    if(m_vector != nullptr)
    {
        delete[] m_vector; // Release memory
    }
    m_vector = nullptr;

}
template <class T>
bool Vector<T>::Insert(const T& data, int index)
{

    if (m_size > m_capacity/2)
    {
        // Resize the array if necessary
        Resize(m_capacity * 2);  // Ensure the Resize function adjusts the capacity
    }

    // Shift elements to the right to make room for the new value
    for (int i = m_size; i > index; --i)
    {
        m_vector[i] = m_vector[i - 1];  // Shift elements right
    }

    // Insert the new value at the specified index
    m_vector[index] = data;
    m_size++;  // Increment size

    return true;  // Return true on success

}
template <class T>
bool Vector<T>::Delete(int index)
{

    if (index < 0 || index >= m_size) //Check that vector is not negative or out of range
    {
        return false;  // Invalid index
    }

    // Shift elements left from the given index
    for (int i = index; i < m_size - 1; ++i)
    {
        m_vector[i] = m_vector[i + 1];
    }

    --m_size;  // Reduce size
    return true;

}

template <class T>
int Vector<T>::GetSize() const
{
    return m_size;

}
//This should be private
template <class T>
int Vector<T>::GetCapacity() const
{
    return m_capacity;

}
template <class T>
const T& Vector<T>::operator[](int index) const
{

    if (index >= 0 && index < m_size) // Check if the index is within the valid range of the vector
    {
        return m_vector[index]; // Return the item at the given position. Reading
    }
    else
    {
        throw std::out_of_range("Index out of range"); //throw error
    }


}
template <class T>
T& Vector<T>::operator[](int index)
{

    if (index >= 0 && index < m_size)
    {
        return m_vector[index]; // Return the item at the given position so it can be changed. For Modifying
    }
    else
    {
        throw std::out_of_range("Index out of range");//throw error
    }


}

template <class T>
Vector<T>::Vector(const Vector<T>& rhs) //create a duplicate of another vector
{
    m_vector = nullptr;  // Ensure no dangling pointer
    Copy(rhs);  // Call Copy method to perform the actual copying

}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{


    Copy(rhs);// Copy the data from the other vector to make sure its deep copy so its independent
    return *this; // Return this vector after copying


}

template <class T>
void Vector<T>::Copy(const Vector<T>& rhs)
{

    if (rhs.m_vector != nullptr) // If m_vector is not null
    {
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_vector = new T[m_capacity];  // Allocate new memory

        // Deep copy elements
        for (int i = 0; i < m_size; ++i)
        {
            m_vector[i] = rhs.m_vector[i];
        }
    }
    else
    {
        m_vector = nullptr;  // Empty vector
        m_size = 0;
        m_capacity = 0;
    }
}

template <class T>
void Vector<T>::Resize(int newCapacity)
{
    // Only resize if new capacity is greater than the current capacity
    if (newCapacity <= m_capacity)
    {
        return;
    }

    T* newVector = new T[newCapacity];  // Allocate new array with new capacity

    // Copy elements from old array to the new one
    for (int i = 0; i < m_size; ++i)
    {
        newVector[i] = m_vector[i];
    }

    // Release old array memory
    delete[] m_vector;

    // Point to the new array
    m_vector = newVector;

    // Update the capacity
    m_capacity = newCapacity;


}


#endif // VECTOR_H_INCLUDED
