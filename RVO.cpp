#include <cstdio>
#include <iostream>

class A
{
    public:
        A()
        {
            printf("A Constructor: %p\n", this);
        }

        ~A()
        {
            printf("A Destructor: %p\n", this);
        }

        A(const A &that)
        {
            printf("A Copy Constructor: %p\n", this);
        }

        A &operator= (const A &that)
        {
            printf("A Copy Assign Operator: %p", this);
        }

        A(A &&that)
        {
            printf("A Move Constructor: %p\n", this);
        }

        A &operator= (A &&that)
        {
            printf("A Move Assign Operator: %p\n", this);
        }
};

A test(void)
{
    A a;
    return std::move(a);
}

int main(int argc, char **argv)
{
    {
        test();
    }
    printf("------------------------\n");
    std::forward
    A a;
    const A &a1 = std::move(a);
    return 0;
}