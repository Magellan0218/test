#include <iostream>
#include <vector>
#include <memory>

void print(void)
{}

template<typename T, typename... Args>
void print(const T &first, const Args&... args)
{
    std::cout << first << " " << sizeof...(args)<< std::endl;
    print(args...);
}

template<typename... Values> class Mytuple;
template<> class Mytuple<>{};

template<typename Head, typename... Tail>
class Mytuple<Head, Tail...> : private Mytuple<Tail...>
{
    public:
        using Inherited = Mytuple<Tail...>;

        Mytuple(Head v, Tail... tail) : head_(v), Inherited(tail...) {}

        Head head(void)
        {
            return head_;
        }

        Inherited &tail(void)
        {
            return *this;
        }
    
    private:
        Head head_;
};

int main(int argc, char **argv)
{
    print(1, 2, 2, 2);
    Mytuple<int, int ,int, int, int, int, int, int, int, int> t(
        1, 2, 3, 1, 2, 3, 4, 4, 4, 3);

    std::cout << sizeof(t) << std::endl;
    return 0;
}