
#ifndef ARRAYSEQ

#define ARRAYSEQ
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T> *elements;

public:
    ArraySequence()
    {
        this->elements = new DynamicArray<T>();
    }

    ~ArraySequence()
    {
        delete[] elements;
    }

    ArraySequence(int size)
    {
        this->elements = new DynamicArray<T>(size);
    }

    ArraySequence(T *elements, int size)
    {
        this->elements = new DynamicArray<T>(elements, size);
    }

    ArraySequence(const ArraySequence<T> &array)
    {
        this->elements = new DynamicArray<T>(*array.elements);
    }

    T Get(int index)
    {
        return this->elements->Get(index);
    }

    T GetFirst()
    {
        return this->elements->Get(0);
    }

    T GetLast()
    {
        return this->elements->Get(this->elements->GetSize() - 1);
    }

    Sequence<T> *GetSubSequence(int startIndex, int endIndex)
    {
        DynamicArray<T> *SubArray = this->elements->GetSubArray(startIndex, endIndex);
        ArraySequence<T> *SubSequence = new ArraySequence<T>;
        SubSequence->elements = SubArray;
        return SubSequence;
    }

    int GetLength()
    {
        return this->elements->GetSize();
    }

    Sequence<T> *Append(T element)
    {
        this->elements->Resize(this->elements->GetSize() + 1);
        this->elements->Set(this->elements->GetSize(), element);
        return this;
    }

    Sequence<T> *Prepend(T element)
    {
        this->elements->Resize(this->elements->GetSize() + 1);
        for (int i = this->elements->GetSize(); i > 0; i--)
        {
            this->elements->Set(i, this->Get(i - 1));
        }
        this->elements->Set(0, element);
        return this;
    }

    Sequence<T> *InsertAt(T element, int index)
    {
        this->elements->Set(index, element);
        return this;
    }

    Sequence<T> *Concat(Sequence<T> *array)
    {
        ArraySequence<T> *concatArray = new ArraySequence<T>;
        ArraySequence<T> *tmp = static_cast<ArraySequence<T> *>(array);
        concatArray->elements = this->elements->Concat(tmp->elements);
        return concatArray;
    }
};

#endif