#include <iostream>
#include <future>

// Time-consuming function.
// Determines the answer to Life, the Universe, and Everything
int find_the_answer_to_ltuae()
{
    // long long calculation
    // ...

    return 42;
}

// Make something else
void do_other_stuff()
{
    ;
}


int main()
{
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout << "The answer is " << the_answer.get() << std::endl;
}
