#include "client.h"
#include <iostream>
#include <thread>

int main()
{
    Client task;
    while (true)
    {
        try
        {
            std::thread thread_one(&Client::thread_1, std::ref(task));
            std::thread thread_two(&Client::thread_2, std::ref(task));

            thread_one.join();
            thread_two.join();
        }
        catch (std::exception &ex)
        {
            std::cout << ex.what() << '\n';
        }
    }

    return 0;
}