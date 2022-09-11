#include <iostream>
#include <vector>

template<typename Arg, typename Result>
struct my_unary_function
{
    using argument_type = Arg;
    using result_type = Result;
};

template<typename Arg1, typename Arg2, typename Result>
struct my_binary_function
{
    using first_argument_type = Arg1;
    using second_argument_type = Arg2;
    using result_type = Result;
};

template<typename T>
struct my_less : public my_binary_function<T, T, bool>
{
    bool operator() (const T &x, const T &y) const
    {
        return x < y;
    }
};

template<typename Operation>
class my_binder2nd : public my_unary_function<typename Operation::first_argument_type, 
                                        typename Operation::result_type>
{
    protected:
        Operation op;
        typename Operation::second_argument_type value;
    
    public:
        my_binder2nd(const Operation &x, const typename Operation::second_argument_type &y) :
            op(x), value(y) {}

    typename Operation::result_type operator() (const typename Operation::first_argument_type &x) const
    {
        return op(x, value);
    }
};

template<typename Operation, typename T>
inline my_binder2nd<Operation> my_bind2nd(const Operation &op, const T &x)
{
    using arg2_type = typename Operation::second_argument_type;
    return my_binder2nd<Operation>(op, arg2_type(x));
}

template<typename InputIterator, typename Predicate>
typename std::iterator_traits<InputIterator>::difference_type my_count_if(
    InputIterator first, InputIterator last, Predicate pred
)
{
    typename std::iterator_traits<InputIterator>::difference_type n = 0;
    for( ; first != last; ++first)
    {
        if(pred(*first))
        {
            ++n;
        }
    }
    return n;
}

template<typename Predicate>
class my_unary_negate : public my_unary_function<typename Predicate::argument_type, 
                                        typename Predicate::result_type>
{
    protected:
        Predicate pred;

    public:
        explicit my_unary_negate(const Predicate& x) : pred(x) { }

        bool operator()(const typename Predicate::argument_type& x) const
        {
            return !pred(x); 
        }
};

template<typename Predicate>
inline my_unary_negate<Predicate> my_not1(const Predicate& pred)
{
    return my_unary_negate<Predicate>(pred); 
}

int main(int argc, char **argv)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "start ----------------------\n";
    std::cout << my_count_if(v.begin(), v.end(), my_not1(my_bind2nd(my_less<int>(), 4))) 
        << std::endl;
    std::cout << "end ------------------------\n";
    return 0;
}
