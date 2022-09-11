#include <thread>
#include<iostream>

int a = 0;

int main(int argc, char **argv)
{
    std::thread t1([]()
    {   
        int i = 1000;
        for( int j = 0; j < i; ++j)
        {
            a = 10;
        }
        std::cout << "t1 over" << std::endl;
    });

    std::thread t2([]()
    {
        int i = 1000;
        for( int j = 0; j < i; ++i)
        {
            a = 100;
        }
    std::cout << "t2 over" << std::endl;
    });
    
    getchar();
    std::cout << a << std::endl;

    t1.join();
    t2.join();

    return 0;
}
