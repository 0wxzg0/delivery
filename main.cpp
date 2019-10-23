/*
Created by 
姜楠 符云霏 李昊东
2019/10/22
*/

//引入标准库
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
using std::cout;
using std::cin;
using std::cerr;
using std::strcpy;
using std::queue;

//引入对货物/仓库/交互对象/消息的定义
#include ""
#include ""
#include "Message.h"

class InteractSystem
{
private:
    //预定义命令参数
    static const char* CLR = "--clear";
    static const char* LIM = "--limit";
    static const char* TEST = "--test";

    //系统设置
    static bool IfTest = false;     //false 表示不工作在测试状态，此时将会把客户数据的所有修改保存到文件
    static size_t SizeLimit = 0;    //0表示消息队列的大小不加限制

    //运行数据
    queue<Message> MsgQue;
    unsigned int Status;

public:
    InteractSystem(int argc, char* argv[]);
    ~InteractSystem();
    void runMainLoop();         //主循环
    bool saveLog();             //保存运行记录
    void saveModification();    //保存更新的资料到文件
};

InteractSystem::InteractSystem(int argc, char* argv[])
{
    for(int i = 1; i <= argc; ++i)
    {
        if(strcmp(argv[i], CLR))
        {

        }
        else if(strcmp(argv[i], LIM))
        {
            ++i;
            sscanf(argv[i], "%d", &SizeLimit);
            while(SizeLimit < 0)
            {
                cerr << "The size limitation is illegal, please reset it.\n"
                cin >> SizeLimit;
            }
        }
        else if(strcmp(argv[i], TEST))
        {
            IfTest = true;
        }
    }

    cout << "Please input the tasks\n";
    char Input[200] = "";
    unsigned int CurType;
    char CurMsg[100], CurTask[100], CurIdentity[100];
    
    do
    {
        cin.getline(Input, 199);
        sscanf(Input, "%d", &CurType);
        if(CurType == 0)                //货物消息
        {

        }
        else if(CurType == 1)           //用户消息
        {

        }
        else
        {
            for(int i = 0; Input[i] != '\0'; ++i)
                Input[i] = toupper(Input[i]);
        }
    }while(strcmp(Input, "END"))
};

InteractSystem::~InteractSystem()
{

};


void InteractSystem::runMainLoop()
{

};

void InteractSystem::saveModification()
{

};

int main(int argc, char* argv[])
{
    InteractSystem sys(argc, argv[]);
    sys.runMainLoop();
    return 0;
}