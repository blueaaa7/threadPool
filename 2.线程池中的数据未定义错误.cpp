#include <iostream>
#include <thread>

void threadFunction(int &i) {
    std::cout << "Hello from thread!" << std::endl;
}

int main()
{
    int i =5;
    std::thread t(threadFunction,std::ref(i));
    t.join();
    return 0;
}