#include <iostream>
#include <thread>
#include <algorithm>

template<typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);

    if (!length)
        return init;
    
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads =
        (length + min_per_thread - 1) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads =
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(
                accumulate_block<Iterator, T>(),
                block_start,block_end,
                std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>() (block_start, last,
            results[num_threads - 1]);
    for (auto &t : threads)
        t.join();

    return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
    std::vector<int> v0;
    int sum = parallel_accumulate(v0.begin(), v0.end(), 0);
    std::cout << "Sum of vector elements: " << sum << std::endl;

    std::vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7};
    sum = parallel_accumulate(v1.begin(), v1.end(), 0);
    std::cout << "Sum of vector elements: " << sum << std::endl;

    
    std::vector<int> v2{1};
    sum = parallel_accumulate(v2.begin(), v2.end(), 0);
    std::cout << "Sum of vector elements: " << sum << std::endl;

    std::vector<int> v3;
    for (int i = 0; i < 102; i++)
        v3.push_back(i);
    sum = parallel_accumulate(v3.begin(), v3.end(), 0);
    std::cout << "Sum of vector elements: " << sum << std::endl;
}
