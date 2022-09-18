#include <cstdio>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <functional>
#include <vector>

template<typename R, typename ...Args>
class Subscribe
{
    public:
        using Functor = std::function<R(Args...)>;

    public:
        void connect(Functor &&func)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            notifys_.emplace_back(std::forward<Functor>(func));
        }

        void notify(Args &&...args) const
        {
            std::lock_guard<std::mutex> lock(mutex_); 
            for(const auto &it : notifys_)
            {
                it(std::forward<Args>(args)...);
            }
        }

    private:
        mutable std::mutex mutex_;
        std::vector<Functor> notifys_;       
};

int print(int a)
{
    std::cout << "print" << std::endl;
    return 0;
}

int main(int argc, char **argv)
{
    Subscribe<int, int> sub;
    sub.connect([](int)
    {
        std::cout << "sssss" << std::endl;
        return 1;
    });

    sub.connect(print);

    sub.notify(1);
    return 0;
}