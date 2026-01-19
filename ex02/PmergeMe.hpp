#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <climits>
#include <iostream>
#include <algorithm>
#include <iomanip>

template <template <typename, typename> class Container>
class fordJohnsonSort
{
private:
    typedef Container<std::pair<int, int>, std::allocator<std::pair<int, int> > > T_pair;
    typedef typename T_pair::iterator T_it;

    Container<int, std::allocator<int> > main;
    T_pair numbers;
    int odd;

    void prepare_pairs(char **av)
    {
        for (int i = 1; av[i]; i++)
        {
            if (av[i + 1])
            {
                std::pair<int, int> new_pair(std::atoi(av[i]), std::atoi(av[i + 1]));
                this->numbers.push_back(new_pair);
                i++;
            }
            else
                odd = std::atoi(av[i]);
        }
        sort_pairs(odd);
    }
    
    void sort_pairs(int odd)
    {
        T_it it = this->numbers.begin();
        while (it != this->numbers.end())
        {
            if (it->first > it->second)
                std::swap(it->first, it->second);
            it++;
        }
        mergeSort(this->numbers.begin(), this->numbers.end());
        startMain();
        fillMain(odd);
    }
    
    static bool cmp(std::pair<int, int> a, std::pair<int, int> b)
    {
        return (a.second < b.second);
    }
    
    void mergeSort(T_it start, T_it end)
    {
        if (std::distance(start, end) <= 1)
            return;
    
        T_it middle = start;
        std::advance(middle, std::distance(start, end) / 2);
    
        mergeSort(start, middle);
        mergeSort(middle, end);
        std::inplace_merge(start, middle, end, &cmp);
    }
    
    void startMain()
    {
        for (T_it it = this->numbers.begin(); it != this->numbers.end(); ++it)
            this->main.push_back(it->second);
    }
    
    void binaryInsert(typename Container<int, std::allocator<int> >::iterator end, int numToInsert)
    {
        typename Container<int, std::allocator<int> >::iterator ins = std::lower_bound(this->main.begin(), end, numToInsert);
        this->main.insert(ins, numToInsert);
    }
    
    size_t jacobsthalNumber(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        size_t prev = 0, curr = 1;
        for (int i = 2; i <= n; ++i)
        {
            size_t next = curr + 2 * prev;
            prev = curr;
            curr = next;
        }
        return curr;
    }
    
    void fillMain(int odd)
    {
        typename Container<int, std::allocator<int> >::iterator delimiter;
        size_t jacob = 1;
        T_it pairs_it;
        T_it last_jacob = this->numbers.begin();
        
        while(jacobsthalNumber(jacob) <= this->numbers.size())
        {
            pairs_it = this->numbers.begin();
            std::advance(pairs_it, jacobsthalNumber(jacob) - 1);
            last_jacob = pairs_it;
    
            int insert = 0;
            while(jacobsthalNumber(jacob) - insert > jacobsthalNumber(jacob - 1))
            {
                delimiter = std::lower_bound(this->main.begin(), this->main.end(), pairs_it->second);
                binaryInsert(delimiter, pairs_it->first);
                pairs_it--;
                insert++;
            }
            jacob++;
        }
    
        if(jacobsthalNumber(jacob) != this->numbers.size())
        {
            pairs_it = this->numbers.end();
            if(pairs_it != this->numbers.begin())
                pairs_it--;
            while (pairs_it != last_jacob)
            {
                delimiter = std::lower_bound(this->main.begin(), this->main.end(), pairs_it->second);
                binaryInsert(delimiter, pairs_it->first);
                pairs_it--;
            }
        }
    
        if (odd != -1)
            binaryInsert(this->main.end(), odd);
    }

public:

    fordJohnsonSort() : main(), numbers(), odd(-1) {}
    ~fordJohnsonSort() {}
    fordJohnsonSort(const fordJohnsonSort &copy) : main(copy.main), numbers(copy.numbers), odd(copy.odd) {}
    fordJohnsonSort &operator=(const fordJohnsonSort &other)
    {
        if (this != &other)
        {
            this->main = other.main;
            this->numbers = other.numbers;
            this->odd = other.odd;
        }
        return *this;
    }

    void display()
    {
        typename Container<int, std::allocator<int> >::iterator it = this->main.begin();
        while(it != this->main.end())
            std::cout << *it++ << " ";
        std::cout << std::endl;
    }

    void sort(char **av)
    {
        this->prepare_pairs(av);
    }

    void check()
    {
        typename Container<int, std::allocator<int> >::iterator it = this->main.begin();
        typename Container<int, std::allocator<int> >::iterator prev;

        while(it != this->main.end())
        {
            if(it != this->main.begin())
            {
                if(*it < *prev)
                {
                    std::cerr << "KO" << std::endl;
                    return ;
                }
            }
            prev = it;
            it++;
        }
        std::cout << "OK" << std::endl;
    }

};

bool checkInput(char **av);

#endif