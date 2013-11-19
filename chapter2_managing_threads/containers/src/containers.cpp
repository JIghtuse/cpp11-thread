#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

void f(int i)
{
    std::cout << "[thread" << i << "] started" << std::endl;
}

int main()
{
    const int nthreads = 20;
    std::vector<std::thread> threads;

    for (unsigned i = 0; i < nthreads; ++i) {
        threads.push_back(std::thread(f, i));
    }
    for (auto &t : threads)
        t.join();

    // or like this
    //std::for_each(threads.begin(),threads.end(),
            //std::mem_fn(&std::thread::join));
}
