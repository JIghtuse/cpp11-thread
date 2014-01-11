#include <iostream>
#include <thread>
#include "threadsafe_queue"

struct data_chunk {
    int val;
    bool is_last;
};

struct stat {
    int total_values;
    int sum;
};

struct stat st{0, 0};

threadsafe_queue<data_chunk> data_queue;

data_chunk prepare_data() {
    data_chunk d{0, false};
    std::cin >> d.val;
    if (0 == d.val)
        d.is_last = true;

    return d;
}

bool more_data_to_prepare() {
    return !std::cin.eof();
}

void process(data_chunk d)
{
    st.total_values++;
    st.sum += d.val;
}

void data_preparation_thread()
{
    while (more_data_to_prepare()) {
        data_chunk const data = prepare_data();
        data_queue.push(data);
        if (data.is_last)
            break;
    }
}

void data_processing_thread()
{
    while (true) {
        data_chunk data;
        data_queue.wait_and_pop(data);
        if (data.is_last)
            break;
        process(data);
    }
}

int main()
{
    std::cout << "Enter integer values, 0 or Ctrl+D to stop\n";

    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);
    t1.join();
    t2.join();

    std::cout << "Total values entered: " << st.total_values << std::endl;
    std::cout << "Sum of values: " << st.sum << std::endl;
    if (st.total_values)
        std::cout << "Average value: "
                  << st.sum / (double)st.total_values
                  << std::endl;
    return 0;
}
