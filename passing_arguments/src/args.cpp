#include <iostream>
#include <thread>

void f(int i, std::string const& s)
{
    std::cout << "[thread" << i << "] string: " << s << std::endl;
}

int main()
{
    const int nthreads = 5;
    const int bsize = 1024;
    int i;

    for (i = 0; i < nthreads; ++i) {
        char buf[bsize];
        sprintf(buf, "thread0 greets thread%i!", i);
        // buf can be destroyed before it has been converted to a std::string
        //std::thread t(f, i, buf);
        // solution: cast before passing buf to the std::thread constructor
        std::thread t(f, i, std::string(buf));
        t.detach();
    }
}
