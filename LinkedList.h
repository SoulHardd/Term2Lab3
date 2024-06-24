

template <class T>
class LinkedList
{
private:
    class Node
    {
    public:
        T data;
        Node *next;

        Node(T data, Node *next = nullptr)
        {
            this->data = data;
            this->next = next;
        };
    };

    int size;
    Node *head;

public:
    LinkedList();
    LinkedList(T *elements, int size);
    LinkedList(const LinkedList<T> &list)
    {
        size = list.size;
        head = list.head;
    }

    T Get(int index);
    T GetFirst();
    T GetLast();
    LinkedList<T> *GetSubList(int startIndex, int endIndex);
    int GetLength() { return size; }

    void Append(T data);
    void Prepend(T data);
    void InsertAt(T data, int index);

    LinkedList<T> *Concat(LinkedList<T> *list);
};

template <class T>
LinkedList<T>::LinkedList()
{
    size = 0;
    head = nullptr;
}

template <class T>
void LinkedList<T>::Append(T data)
{
    if (head == nullptr)
    {
        head = new Node(data);
    }
    else
    {
        Node *current = this->head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new Node(data);
    }
    size++;
}

template <class T>
void LinkedList<T>::Prepend(T data)
{
    Node *new_head = new Node(data);
    new_head->next = head;
    head = new_head;
    size++;
}

template <class T>
void LinkedList<T>::InsertAt(T data, int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("index is out of range");
    }
    Node *new_element = new Node(data);
    Node *current = this->head;
    int counter = 0;
    while (current != nullptr)
    {
        if (counter == index - 1)
        {
            Node *tmp = current->next;
            current->next = new_element;
            new_element->next = tmp->next;
            break;
        }
        current = current->next;
        counter++;
    }
}

template <class T>
LinkedList<T>::LinkedList(T *elements, int size)
{
    head = new Node(elements[0]);

    Node *current = this->head;
    for (int i = 1; i < size; i++)
    {
        current->next = new Node(elements[i]);
        current = current->next;
    }
    this->size = size;
}

template <class T>
T LinkedList<T>::Get(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("index is out of range");
    }
    int counter = 0;
    Node *current = this->head;
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->next;
        counter++;
    }
    return 0;
}

template <class T>
T LinkedList<T>::GetFirst()
{
    if (head == nullptr)
    {
        throw std::out_of_range("array is empty");
    }
    return head->data;
}

template <class T>
T LinkedList<T>::GetLast()
{
    if (head == nullptr)
    {
        throw std::out_of_range("array is empty");
    }
    return this->Get(size - 1);
}

template <class T>
LinkedList<T> *LinkedList<T>::GetSubList(int startIndex, int endIndex)
{
    if (startIndex < 0 || endIndex >= size)
    {
        throw std::out_of_range("index is out of range");
    }
    LinkedList<T> *SubList = new LinkedList<T>;
    for (int i = startIndex; i <= endIndex; i++)
    {
        SubList->Append(this->Get(i));
    }

    return SubList;
}

template <class T>
LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> *list)
{
    LinkedList<T> *ConcatList = new LinkedList<T>;
    for (int i = 0; i < (this->size + list->size); i++)
    {
        if (i < this->size)
        {
            ConcatList->Append(this->Get(i));
        }
        else
        {
            ConcatList->Append(list->Get(i - this->size));
        }
    }
    return ConcatList;
}