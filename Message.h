/*
Created by
姜楠 符云霏 李昊东
2019/10/22
给出消息的定义
*/
#ifndef MESSAGE_H
#define MESSAGE_H

//引入货物/交互对象的定义
#include ""
#include ""

class Message
{
private:
    unsigned int Type;
    char* Msg;

public:
    Message(unsigned int _Type, const char* _Msg);
    ~Message();
    unsigned int getType();
    char* getMsg();
};



class ItemMessage: public Message
{
private:    //包含任务类型+货物信息
    char* Task;
public:
    ItemMessage(char _Task):Message();
    ~ItemMessage();
};



class UserMessage: public Message
{
private:    //包含对象身份+任务类型+对象信息
    char* Identity;
    char* Task;
private:
    UserMessage(const char* _Identity, const char* _Task):Message();
    ~UserMessage();
}

#endif