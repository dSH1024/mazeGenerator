#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack
{
public:
    Stack()
    {
        this->size = 0;
    }

    void push(T c);
    T pop();

private:
    T* data;
    int size;
};

#endif
