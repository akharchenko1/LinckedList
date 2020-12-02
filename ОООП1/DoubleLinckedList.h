#pragma once


#include <cstdlib>
#include <iostream>
#include "Exeptions.h"

//В этой задаче для простоты не требуется делать контейнер шаблонным,
//но это вполне допускается по желанию студента
typedef int value_type;
struct Node {
    value_type data;
    Node* prev;
    Node* next;
};

class LinkedList {
private:
    size_t linkedListSize;
    Node* pointer;

public:
    class iterator {
    private:
        friend class LinkedList;
        Node* iteratorPointer;
    public:
        iterator(Node* pNode)
        {
            iteratorPointer = pNode;
        };
        iterator& operator=(const iterator& other)
        {
            if (this != &other) {
                iteratorPointer = other.iteratorPointer;
            }
            return *this;
        };
        bool operator!=(const iterator& other) const
        {
            return iteratorPointer != other.iteratorPointer;
        };
        bool operator==(const iterator& other) const
        {
            return iteratorPointer == other.iteratorPointer;
        };
        //Возвращает ссылку на текущий элемент коллекции.
        value_type& operator*()
        {
            return iteratorPointer->data;
        };
        //Возвращает указатель на текущий элемент коллекции.
        value_type* operator->()
        {
            return &(iteratorPointer->data);
        };

        iterator& operator++()
        {
            iteratorPointer = iteratorPointer->next;
            return *this;
        };
        iterator operator++(int)
        {
            iterator retval = *this;
            ++(*this);
            return retval;
        }
        iterator& operator--()
        {
            iteratorPointer = iteratorPointer->prev;
            return *this;
        }
        iterator operator--(int)
        {
            iterator retval = *this;
            --(*this);
            return retval;
        }
    };
    class const_iterator {
    private:
        friend class LinkedList;
        Node* constIteratorPointer;
    public:
        const_iterator(Node* pNod)
        {
            constIteratorPointer = pNod;
        };
        const_iterator& operator=(const const_iterator& other)
        {
            if (this != &other) {
                constIteratorPointer = other.constIteratorPointer;
            }
            return *this;
        }
        bool operator!=(const const_iterator& other) const
        {
            return constIteratorPointer != other.constIteratorPointer;
        }
        bool operator==(const const_iterator& other) const
        {
            return constIteratorPointer == other.constIteratorPointer;
        }
        //Возвращает ссылку на текущий элемент коллекции.
        const value_type& operator*() const
        {
            return constIteratorPointer->data;
        };
        //Возвращает указатель на текущий элемент коллекции.
        const value_type* operator->() const
        {
            return &(constIteratorPointer->data);
        };

        const_iterator& operator++()
        {
            constIteratorPointer = constIteratorPointer->next;
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator retval = *this;
            ++(*this);
            return retval;
        }

        const_iterator& operator--()
        {
            constIteratorPointer = constIteratorPointer->prev;
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator retval = *this;
            --(*this);
            return retval;
        }

    };
    /* Конструкторы */
    LinkedList()
    {
        pointer = new Node();
        pointer->prev = pointer;
        pointer->next = pointer;
        linkedListSize = 0;
    }
    LinkedList(const LinkedList& other)
    {
        pointer = new Node();
        pointer->prev = pointer;
        pointer->next = pointer;
        linkedListSize = 0;
        Node* current = other.pointer->next;
        while (current != other.pointer) {
            push_back(current->data);
            current = current->next;
        }
    }

    LinkedList (LinkedList&& other) noexcept
    {
        pointer = other.pointer;
        linkedListSize = other.linkedListSize;
        other.linkedListSize = 0;
        other.pointer = nullptr;
    }

    /* Деструктор */
    ~LinkedList()
    {
        if (!empty()) {
            clear();
        }
        delete pointer;
    }

    /* Оператор присваивания */
    LinkedList& operator=(const LinkedList& other)
    {
        if (this != &other) {
            if (!empty()) {
                clear();
            }
            Node* current = other.pointer->next;
            while (current != other.pointer) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    LinkedList& operator=(LinkedList&& other) noexcept
    {
        if (this != &other) {
            if (!empty()) {
                clear();
            }
            delete pointer;
            pointer = other.pointer;
            linkedListSize = other.linkedListSize;
            other.linkedListSize = 0;
            other.pointer = nullptr;
        }
        return *this;
    }

    /* Доступ к итераторам */
    //Возвращает итератор, указывающий на первый элемент списка.
    iterator begin()
    {
        return iterator(pointer->next);
    }
    const_iterator begin() const
    {
        return const_iterator(pointer->next);
    }
    const_iterator cbegin() const
    {
        return const_iterator(pointer->next);
    }
    //Возвращает итератор, указывающий на элемент списка, следующий за последним
    //т.е. отсутствующий в списке.
    iterator end()
    {
        return iterator(pointer);
    }
    const_iterator end() const
    {
        return const_iterator(pointer);
    }
    const_iterator cend() const
    {
        return const_iterator(pointer);
    }

    /* Размерность */
    //Возвращает размер списка.
    int size() const
    {
        return linkedListSize;
    }
    //Возвращает истину, если список пуст.
    bool empty() const
    {
        return linkedListSize == 0;
    }

    /* Доступ к элементам */
    //Возвращает ссылку на первый элемент списка.
    value_type& front()
    {
        if (!empty()) {
            return pointer->next->data;
        }
        else {
            throw LinkedLists::LinkedListsException("Can't return a reference to the first item in the list");
        }
    }

    const value_type& front() const
    {
        if (!empty()) {
            return pointer->next->data;
        }
        else {
            throw LinkedLists::LinkedListsException("Can't return a reference to the first item in the list");
        }
    }

    //Возвращает ссылку на последний элемент списка.
    value_type& back() 
    {
        if (!empty()) {
            return pointer->prev->data;
        }
        else {
            throw LinkedLists::LinkedListsException("Can't return a reference to the last item in the list");
        }
    }

    const value_type& back() const
    {
        if (!empty()) {
            return pointer->prev->data;
        }
        else {
            throw LinkedLists::LinkedListsException("Can't return a reference to the last item in the list");
        }
    }

    /* Модификаторы */
    //Удаляет элемент, на который указывает итератор pos.
    iterator erase(iterator position)
    {
        if (position != end()) {
            --linkedListSize;

            Node* saveNextNode = position.iteratorPointer->next;
            Node* savePrevNode = position.iteratorPointer->prev;
            savePrevNode->next = saveNextNode;
            saveNextNode->prev = savePrevNode;
            iterator current(saveNextNode);
            delete position.iteratorPointer;
            return current;
        }
        else {
            throw LinkedLists::LinkedListsException("Can't erase a nonexistent element in erase method");
        }
    }
    //Удаляет элементы в интервале [start, finish).
    iterator erase(iterator start, iterator finish)
    {
        iterator current = start;
        while (current != finish) {
            current = erase(current);
        }
        return finish;
    }
    //Удаляет все вхождения value в список.
    int remove(const value_type& value)
    {
        int counter = 0;
        iterator current = begin();
        while (current != end()) {
            if (current.iteratorPointer->data == value) {
                current = erase(current);
                ++counter;
            }
            else {
                ++current;
            }
        }
        return counter;
    }
    //Очищает список.
    void clear()
    {
        iterator current = begin();
        while (current != end()) {
            current = erase(current);

        }
    }

    //Удаляет последний элемент списка.
    void pop_back()
    {
        erase(--end());
    }
    //Удаляет первый элемент списка.
    void pop_front()
    {
        erase(begin());
    }

    //Добавляет значение value в конец списка.
    void push_back(const value_type& value)
    {
        insert(end(), value);
    }
    //Добавляет значение value в начало списка.
    void push_front(const value_type& value)
    {
        insert(begin(), value);
    }
    //Вставляет значение value перед элементом, на который указывает before
    iterator insert(iterator before, const value_type& value)
    {
        Node* newNode = new Node();
        newNode->data = value;

        Node* savePrevBefore = before.iteratorPointer->prev;
        savePrevBefore->next = newNode;
        newNode->next = before.iteratorPointer;
        before.iteratorPointer->prev = newNode;
        newNode->prev = savePrevBefore;
        linkedListSize++;

        return iterator(newNode);
    }

    /* Операторы внутренние */
    //Присоединяет other к списку.
    LinkedList& operator+=(const LinkedList& other) 
    {
        if (other.empty()) {
            return *this;
        }

        Node* currentOtherNode = other.pointer->next;
        while (currentOtherNode != other.pointer) {
            push_back(currentOtherNode->data);
            currentOtherNode = currentOtherNode->next;
        }

        return *this;
    }

    /* Операторы внешние */
    friend bool operator!=(const LinkedList& left, const LinkedList& right);
    friend bool operator==(const LinkedList& left, const LinkedList& right);

};

/* Операторы внешние */
//Сравнивает 2 листа
bool operator!=(const LinkedList& left, const LinkedList& right)
{
    if (&left == &right) {
        return false;
    }

    if (left.size() != right.size()) {
        return true;
    }

    auto curItLeft = left.begin();
    auto curItRight = right.begin();
    while (curItLeft != left.end() && curItRight != right.end()) {
        if (*curItLeft != *curItRight) {
            return true;
        }
        curItLeft++;
        curItRight++;
    }
    return false;
}

bool operator==(const LinkedList& left, const LinkedList& right)
{
    return !(left != right);
}

//Возвращает лист объединяющий 2 листа.
LinkedList operator +(const LinkedList& left, const LinkedList& right)
{
    LinkedList newlist(left);
    newlist += right;
    return newlist;
}

