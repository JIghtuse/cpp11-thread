#include <iostream>
#include <thread>

class background_task
{
public:
    void operator()() const
    {
        std::cout << "Hello Concurrent World!\n";
    }
};

int main()
{
    // function object copied into the storage belonging to the new thread
    background_task f;
    std::thread tc(f);
    tc.join();

    // prevent interpretation as function declaration
    std::thread tp((background_task()));
    tp.join();

    // uniform initialization syntax
    std::thread tu{background_task()};
    tu.join();

    // lambda expression
    std::thread tl([]{
        std::cout << "Hello Concurrent World!\n";
    });
    tl.join();
}
