#include <iostream>
#include <thread>
#include <unistd.h>

void some_function(int i)
{
    const int sleep_time = 6;
    std::cout << "thread " << i << " started." << std::endl;
    sleep(sleep_time);
    std::cout << "thread " << i << " ended." << std::endl;
}

void some_other_function()
{
    const int sleep_time = 3;
    std::cout << "[some] thread started." << std::endl;
    sleep(sleep_time);
    std::cout << "[some] thread ended." << std::endl;
}

std::thread f()
{
    return std::thread(some_function, 2);
}

std::thread g()
{
    return std::thread(some_other_function);
}

int main()
{
    std::thread t1(some_function, 1);
    std::thread t2=std::move(t1);
    t1 = std::thread(some_other_function);
    std::thread t3;
    t3 = std::move(t2);
    // next assignment terminate program because t1 already had an
    // associated thread
    //t1 = std::move(t3);
    t2 = f();

    t1.join();
    t2.join();
    t3.join();
}
