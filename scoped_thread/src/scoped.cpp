#include <iostream>
#include <thread>

class scoped_thread
{
    std::thread t;
public:
    explicit scoped_thread(std::thread t_):
        t(std::move(t_))
    {
        if (!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread()
    {
        t.join();
    }
    scoped_thread(scoped_thread const&)=delete;
    scoped_thread& operator=(scoped_thread const&)=delete;
};

struct func
{
    int& i;
    func(int& i_): i(i_) {}

    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
        {
            int k = i * i * i + i;
            k++;
        }
    }
};

void f(int i, std::string const& s)
{
    std::cout << "[thread" << i << "] string: " << s << std::endl;
}

int main()
{
    int some_local_state;
    scoped_thread t{std::thread(func(some_local_state))};
}
