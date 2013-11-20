#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <algorithm>
#include <unistd.h>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find)
        != some_list.end();
}

void adder(const int maxval)
{
    for (int i = 0; i < maxval; ++i) {
        add_to_list(i);
    }
}

void finder(const int value_to_find)
{
    while (!list_contains(value_to_find)) {
        sleep(1);
    }
    std::cout << "value found!" << std::endl;
}

int main()
{
    std::thread t1(adder, 1000000);
    std::thread t2(finder, 999999);
    t1.join();
    t2.join();
}
