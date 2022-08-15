#include <iostream>
#include <functional>
#include <memory>
#include <thread>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

template<typename T>
class SyncQueue
{
    public:
        using size_type = typename std::queue<T>::size_type;
        
        SyncQueue() = default;
 
        ~SyncQueue() = default;

        bool empty(void)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }

        size_type size(void)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.size();
        }

        template<typename U>
        void enqueue(U &&element)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.emplace(std::forward<U>(element));
        }

        bool dequeue(T &element)
        {
             std::lock_guard<std::mutex> lock(mutex_);
             if(queue_.empty())
             {
                return false;
             }

             element = queue_.front();
             queue_.pop();
        }

    private:
        SyncQueue(const T &that) = delete;

        SyncQueue& operator=(const SyncQueue& that) = delete;

        SyncQueue(T &&that) = delete;

        SyncQueue& operator=(SyncQueue&& that) = delete;

    private:
        std::mutex mutex_;
        std::queue<T> queue_;   

};

class ThreadPool final
{
    public:
        ThreadPool(std::size_t size)
            : size_(size),
            thread_pool_(std::vector<std::thread>(size_)),
            stoped_(false)
        {}

        ~ThreadPool() = default;

        ThreadPool(const ThreadPool& that) = delete;

        ThreadPool &operator=(const ThreadPool &that) = delete;

        ThreadPool(ThreadPool&& that) = delete;

        ThreadPool &operator=(ThreadPool &&that) = delete;
    
    public:
        void init(void)
        {
            for(std::size_t i = 0; i < size_; ++i)
            {
                thread_pool_.emplace_back(std::thread([this, i]()
                {
                    doTask(i);
                }));
            }
        }

        void deInit(void)
        {
            stoped_ = true;
            cond_.notify_all();

            for(auto &it : thread_pool_)
            {
                if(it.joinable())
                {
                    it.join();
                }
            }
        }
        
        template<typename F, typename... Args>
        bool addTask(F &&f, Args&&... args)
        {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.emplace(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
            cond_.notify_one();
        }
 
    private:
        void doTask(int i)
        {
            while(!stoped_)
            {
                std::function<void()> func;
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    cond_.wait(lock, [this]()
                        {
                            return !queue_.empty() || stoped_;
                        });

                    if(!queue_.empty())
                    {
                        func = queue_.front();
                        queue_.pop();
                    }
                }
                
                if(func)
                {
                    std::cout << "task: " << i << " process work!" << std::endl;
                    func();
                    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }

    private:
        bool stoped_;
        std::size_t size_;
        std::queue<std::function<void()>> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
        std::vector<std::thread> thread_pool_;
};

int main(int argc, char **argv)
{
    ThreadPool pool(4);
    pool.init();


    for( int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        pool.addTask([i]()
            {
                std::cout << "hello " << i << " come here" << std::endl;
            });
    }

    getchar();
    pool.deInit();
    getchar();
    return 0;
}