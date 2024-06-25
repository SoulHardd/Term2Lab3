#include <iostream>
template <class T>
class DynamicArray
{
private:
    T *elements;
    int size;

public:
    ~DynamicArray();
    DynamicArray();
    DynamicArray(int size);
    DynamicArray(T *elements, int size);
    DynamicArray(const DynamicArray<T> &dynamicArray);

    int GetSize();
    T Get(int index);
    DynamicArray<T> *GetSubArray(int startIndex, int endIndex);

    void Set(int index, T value);
    void Resize(int newSize);
    DynamicArray<T> *Concat(DynamicArray<T> *array);
};

template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] elements;
};

template <class T>
DynamicArray<T>::DynamicArray()
{
    elements = nullptr;
    size = 0;
};

template <class T>
DynamicArray<T>::DynamicArray(int size)
{
    elements = new T[size];
    this->size = size;
};

template <class T>
DynamicArray<T>::DynamicArray(T *elements, int size)
{
    this->elements = new T[size];
    for (int i = 0; i < size; i++)
    {
        this->elements[i] = elements[i];
    }
    this->size = size;
};

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray)
{
    size = dynamicArray.size;
    elements = new T[size];
    for (int i = 0; i < size; i++)
    {
        elements[i] = dynamicArray.elements[i];
    }
};

template <class T>
int DynamicArray<T>::GetSize()
{
    return size;
};

template <class T>
T DynamicArray<T>::Get(int index)
{
    if (elements == nullptr)
        throw std::out_of_range("array is empty");
    if ((index < 0) || (index >= size))
        throw std::out_of_range("index is out of range");
    return elements[index];
};

template <class T>
void DynamicArray<T>::Set(int index, T value)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("index is out of range");
    }
    elements[index] = value;
};

template <class T>
void DynamicArray<T>::Resize(int newSize)
{
    T *tmpElements = new T[size];
    memcpy(tmpElements, elements, size * sizeof(T));
    delete[] elements;
    elements = new T[newSize];
    for (int i = 0; i < std::min(size, newSize); i++)
    {
        elements[i] = tmpElements[i];
    }
    size = newSize;
};

template <class T>
DynamicArray<T> *DynamicArray<T>::GetSubArray(int startIndex, int endIndex)
{
    if (startIndex < 0 || endIndex >= size)
    {
        throw std::out_of_range("index is out of range");
    }
    int j = 0;
    DynamicArray<T> *SubArray = new DynamicArray<T>(endIndex - startIndex + 1);
    for (int i = startIndex; i <= endIndex; i++)
    {
        SubArray->Set(j, this->Get(i));
        j++;
    }
    return SubArray;
};

template <class T>
DynamicArray<T> *DynamicArray<T>::Concat(DynamicArray<T> *array)
{
    DynamicArray<T> *ConcatArray = new DynamicArray<T>(this->size + array->size);
    for (int i = 0; i < (this->size + array->size); i++)
    {
        if (i < this->size)
        {
            ConcatArray->Set(i, this->Get(i));
        }
        else
        {
            ConcatArray->Set(i, array->Get(i - this->size));
        }
    }
    return ConcatArray;
}
