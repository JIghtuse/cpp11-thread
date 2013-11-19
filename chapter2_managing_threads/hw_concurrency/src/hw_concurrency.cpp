#include <iostream>
#include <thread>

int main()
{
    unsigned nthreads = std::thread::hardware_concurrency();
    if (nthreads != 0)
        std::cout << nthreads << " concurrent threads are supported by hw.\n";
    else
        std::cout << "Can't determine number of concurrent threads supported\n";
}
