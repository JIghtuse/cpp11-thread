#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

struct data_chunk {
    int val;
    bool is_last;
};

struct stat {
    int total_values;
    int sum;
};

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;
struct stat st{0, 0};

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
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
// TODO: avoid duplication of loop exit condition
        if (data.is_last)
            break;
    }
}

void data_processing_thread()
{
    while (true) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(
                lk, []{return !data_queue.empty();});
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
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
}
