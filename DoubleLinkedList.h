#pragma once

template<typename T>
class DoubleLinkedList
{
private:
    struct Node;
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    void push_front(const T&);
    void push_back(const T&);
    void insert(const T&, int);
    void pop_front();
    void pop_back();
    void erase(int);
    void view();

    T& operator[](int);
private:
    Node* getNode(int);
private:
    struct Node
    {
        T data{ };
        Node* prev = nullptr;
        Node* next = nullptr;

        Node() {}
        Node(const T& t) : data{ t } {}
    };
};

template<typename T>
void DoubleLinkedList<T>::push_front(const T& t)
{
    Node* node = new Node(t);
    node->next = head;
    if (head)
        head->prev = node;
    if (tail == nullptr)
        tail = node;
    head = node;
}

template<typename T>
void DoubleLinkedList<T>::push_back(const T& t)
{
    Node* node = new Node(t);

    node->prev = tail;
    if (tail)
        tail->next = node;
    if (head == nullptr)
        head = node;
    tail = node;
}

template<typename T>
void DoubleLinkedList<T>::insert(const T& t, int index)
{
    Node* rnode = getNode(index);
    if (rnode == nullptr)
    {
        push_back(t);
        return;
    }

    Node* lnode = rnode->prev;
    if (lnode == nullptr)
    {
        push_front(t);
        return;
    }

    Node* node = new Node(t);

    node->prev = lnode;
    node->next = rnode;
    lnode->next = node;
    rnode->prev = node;
}

template<typename T>
void DoubleLinkedList<T>::pop_front()
{
    if (head == nullptr) return;

    Node* node = head->next;
    if (node)
        node->prev = nullptr;
    else
        tail = nullptr;

    delete head;
    head = node;
}

template<typename T>
void DoubleLinkedList<T>::pop_back()
{
    if (tail == nullptr) return;

    Node* node = tail->prev;
    if (node)
        node->next = nullptr;
    else
        head = nullptr;

    delete tail;
    tail = node;
}

template<typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::getNode(int index)
{
    int n(0);
    Node* node = head;

    while (n != index)
    {
        if (node == nullptr)
            return node;

        node = node->next;
        n++;
    }

    return node;
}

template<typename T>
T& DoubleLinkedList<T>::operator[](int index)
{
    return getNode(index)->data;
}

template<typename T>
void DoubleLinkedList<T>::erase(int index)
{
    Node* node = getNode(index);

    if (node == nullptr) return;

    if (node->prev == nullptr)
    {
        pop_front();
        return;
    }

    if (node->next == nullptr)
    {
        pop_back();
        return;
    }

    node->prev->next = node->next->prev;
    delete node;
}

template<typename T>
void DoubleLinkedList<T>::view()
{
    Node* node = head;
    int count = 0;
    while (node)
    {
        std::cout << count++ << ". "
            << node->data << std::endl;

        node = node->next;
    }
}
