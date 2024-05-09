#include <iostream>
#include <string>

class Log{
public:
    Log() = default;
    ~Log() = default;
    Log(const Log& log) = delete;
    Log& operator=(const Log& log)=delete;
    static Log& getInstance()
    {
        static Log log;
        return log;
    }
    void print(std::string str)
    {
        std::cout<<"打印错误:"<<str<<std::endl;
    }
};

int main()
{
    Log::getInstance().print("你好");
    return 0;
}