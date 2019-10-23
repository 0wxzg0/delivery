/*
Created by 
姜楠 符云霏 李昊东
2019/10/22
*/

//引入标准库
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
using std::cout;
using std::cin;
using std::cerr;
using std::strcpy;
using std::queue;
using std::fstream;
using std::ifstream;
using std::ofstream;

//引入对货物/仓库/交互对象/消息的定义
#include ""
#include ""
#include "Message.h"

class InteractSystem
{
private:
    //预定义命令参数
    static const char* CLR = "--clear";         //--clear表示清空用户记录
    static const char* LIM = "--limit";         //--limit表示限制消息队列长度
    static const char* TEST = "--test";         //--test表示在测试状态工作

    //系统设置
    static bool IfTest = false;     //false 表示不工作在测试状态，此时将会把客户数据的所有修改保存到文件
    static size_t SizeLimit = 0;    //0表示消息队列的大小不加限制

    //运行数据
    queue<ItemMessage> ItemMsgQue;
    queue<UserMessage> UserMsgQue;
    unsigned int Status;            //系统运行状态，0表示正常运行，1表示中断

public:
    InteractSystem(int argc, char* argv[]);
    ~InteractSystem();
    void runMainLoop();         //主循环
    bool readUserInfo();        //读取之前保存的用户记录
    bool saveLog();             //保存运行记录
    void saveModification();    //保存更新的资料到文件
};

InteractSystem::InteractSystem(int argc, char* argv[])
{
    if(!readUserInfo())
    {
        cerr << "Warning: No users' data can be found.\n";
        cerr << "Would you like to run the system with no users' data?\n";
        cerr << "Please input Y for yes or N for not: ";
        char Cmd;
        cin >> Cmd;
        if(Cmd == 'N')
        {
            Status = 1;
            return;
        }
    }

    Status = 0;

    for(int i = 1; i <= argc; ++i)
    {
        if(strcmp(argv[i], CLR))
        {
            ofstream FileClr;
            FileClr.open("userdata.log", ofstream::out | ofstream::trunc);
            FileClr.close();
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
            sscanf(Input, "%d%s%s", &CurType, CurMsg, CurTask);
            ItemMsgQue.push(ItemMessage(CurTask):Message(CurMsg));
        }
        else if(CurType == 1)           //用户消息
        {
            sscanf(Input, "%d%s%s%s", &CurType, CurMsg, CurTask, CurIdentity);
            UserMsgQue.push(UserMessage(CurIdentity, CurTask):Message(CurMsg));
        }
        else
        {
            for(int i = 0; Input[i] != '\0'; ++i)
                Input[i] = toupper(Input[i]);
        }
    }while(strcmp(Input, "END"));
};

InteractSystem::~InteractSystem()
{
    while(!ItemMsgQue.empty())
    {
        ItemMsgQue.pop();
    }
    while(!UserMsgQue.empty())
    {
        UserMsgQue.pop();
    }
}

bool InteractSystem::readUserInfo()
{
    ifstream UserInfo;
    UserInfo.open("userdata.log", ifstream::in);

    if(!UserInfo)
    {
        cerr << "Error: Fail to open users' data.\n";
        return false;
    }

    //从文件读取所有用户的数据并装入内存


    UserInfo.close();
    return true;
}

void InteractSystem::runMainLoop()
{

}

void InteractSystem::saveModification()
{
    ofstream UserInfo;
    UserInfo.open("userdata.log", ofstream::out | ofstream::trunc);

    //写入所有当前的用户信息到文件

}

int main(int argc, char* argv[])
{
    InteractSystem sys(argc, argv[]);
    sys.runMainLoop();
    return 0;
}