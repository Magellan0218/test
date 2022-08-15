#include <iostream>
#include <memory>
#include <unordered_map>
#include <future>
#include <thread>
#include <functional>

template<typename T, typename Key = std::string, typename... Args>
class Factory
{
    public:
        static Factory *getInstance(void)
        {
            static Factory factory;
            return &factory;
        }

        template<typename U>
        void registerProduct(const Key& key)
        {
            factory_map_.emplace(key, [](Args&&... args)
                {
                    return std::make_shared<U>(std::forward<Args>(args)...);
                });
        }

        std::shared_ptr<T> makeProduct(const Key& key, Args&&... args)
        {
            auto it = factory_map_.find(key);
            if(it != factory_map_.end())
            {
                return it->second(std::forward<Args>(args)...);
            }
            return std::shared_ptr<T>();
        }

    private:
        using CreateProduct = std::function<std::shared_ptr<T>(Args...)>;
        std::unordered_map<Key, CreateProduct> factory_map_;
};

class A
{
    public:
        A()
        {
            std::cout << "A" << std::endl;
        }

        virtual ~A()
        {
            std::cout << "~A" << std::endl;
        }

        virtual void show(void) = 0;
};

class B : public A
{
    public:
        B(int a) : A()
        {
            std::cout << "B" << std::endl;
        }

        ~B()
        {
            std::cout << "~B" << std::endl;
        }

        void show(void) override
        {
            std::cout << "product B from A" << std::endl;
        }
};

#define REGISTER_FACTORY GET_FACTORY->registerProduct<B>("B")
#define GET_FACTORY Factory<A, std::string, int>::getInstance()
#if 0
template<typename F, typename... Args>
auto submit(F &&f, Args&&... args) ->std::future<decltype<f(args...)>>
{
    std::function<decltypef(args...)()> func = std::bind(std::forward<F>(f), 
        std::forward<Args>(args)...);
 
    auto taskPtr = std::make_shared<std::packaged_task<
        decltype(std::forward<F>(f)(std::forward<Args>(args...)))()>>(func);
    
    std::function<void()> warpperFunc = [taskPtr]()
        {
            (*taskPtr)();
        };

    sync_queue_.enqueue(warpperFunc);
    conditional_lock_.notify_one();
    return taskPtr->get_future();
}
#endif
int main(int argc, char **argv)
{
    REGISTER_FACTORY;
    auto pa = GET_FACTORY->makeProduct("B", 2);
    pa->show();

    return 0;
}