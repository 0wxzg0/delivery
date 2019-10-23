/*
Created by
姜楠 符云霏 李昊东
2019/10/22
给出消息的定义
*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstring>

//引入货物/交互对象的定义
#include ""
#include ""

class Message
{
private:
    unsigned int Type;
    char* Msg;

public:
    Message(const unsigned int _Type, char* _Msg);
    ~Message();
    unsigned int getType() const;
    char* getMsg() const;
};

Message::Message(const unsigned int _Type, char* _Msg)
{
    Type = _Type;
    Msg = new char[strlen(_Msg)+1];
    strcpy(Msg, _Msg);
}

Message::~Message()
{
    delete[] Msg;
}

unsigned int Message::getType()
{
    return Type;
}

char* Message::getMsg()
{
    return Msg;
}


class ItemMessage: public Message
{
private:    //包含任务类型+货物信息
    char* Task;
public:
    ItemMessage(char* _Task):Message();
    ~ItemMessage();
};

ItemMessage::ItemMessage(char* _Task):Message()
{
    Task = new char[strlen(_Task)+1];
    strcpy(Task, _Task);
}

ItemMessage::~ItemMessage()
{
    delete[] Task;
}


class UserMessage: public Message
{
private:    //包含对象身份+任务类型+对象信息
    char* Identity;
    char* Task;
private:
    UserMessage(char* _Identity, char* _Task):Message();
    ~UserMessage();
}

UserMessage::UserMessage(char* _Identity, char* _Task):Message()
{
    Identity = new char[strlen(_Identity)+1];
    strcpy(Identity, _Identity);
    Task = new char[strlen(_Task)+1];
    strcpy(Task, _Task);
}

UserMessage::~UserMessage()
{
    delete[] Identity;
    delete[] Task;
}

#endif