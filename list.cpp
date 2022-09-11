#include <iostream>

namespace test
{

template<typename T>
class list_node
{
    public:
        list_node(const T &value = T()) : value_(value), next_(nullptr), prev_(nullptr) {}
        T value_;
        list_node<T> *next_;
        list_node<T> *prev_;
};

template<typename T>
class list
{
    public:
        using value_type = T;
        using node_type = list_node<T>;
        using link_type = node_type *;

    public:
        template<typename Type, typename Ref, typename Ptr>
        class list_iterator
        {
            public:
                using self = list_iterator;
                using pointer = Ptr;
                using reference = Ref;
                using value_type = Type;
                using link_type = list_node<Type> *;
            
            public:
                link_type head_;
            
            public:
                list_iterator(link_type head = nullptr) : head_(head){}

                list_iterator(const list_iterator &that)
                {
                    head_(that.head_);
                }

                self &operator= (const list_iterator &that)
                {
                    if(this == &that)
                    {
                        return *this;
                    }
                    return self(that);
                }

                self &operator++ (void)
                {
                    head_ = head_->next_;
                    return *this;
                }

                self operator++ (int)
                {
                    self tmp = *this;
                    ++this;
                    return tmp;
                }

                self &operator-- (void)
                {
                    head_ = head_->prev_;
                    return *this;
                }

                self operator-- (int)
                {
                    self tmp = *this;
                    --this;
                    return tmp;
                }

                reference operator *(void)
                {
                    head_->value_;
                }        

                pointer operator-> (void)
                {
                    return &(operator*());
                }       
        };

    public:
        using iterator = list_iterator<T, T&, T*>;

    public:
        list() : head_(new list_node<T>())
        {
            head_->next_ = head_;
            head_->prev_ = head_;
        }
 
    private:
        link_type head_;
};
};

void printCategory(std::random_access_iterator_tag)
{
    std::cout << "random" << std::endl;
}

void printCategory(std::bidirectional_iterator_tag)
{
    std::cout << "bidirect" << std::endl;
}

void printCategory(std::forward_iterator_tag)
{
    std::cout << "forward" << std::endl;
}

void printCategory(std::input_iterator_tag)
{
    std::cout << "input" << std::endl;
}

void printCategory(std::output_iterator_tag)
{
    std::cout << "output" << std::endl;
}

template<typename Iter>
void printCategory(Iter iter)
{
    typename std::iterator_traits<Iter>::iterator_category category;
    printCategory(category);
}

#include <algorithm>

int main(int argc, char **argv)
{
    std::copy
    return 0;
};