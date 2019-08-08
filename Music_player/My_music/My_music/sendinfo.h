#ifndef SENDINFO_H
#define SENDINFO_H
#include <string>

enum Menue_Flag
{
    Music_list = 1,
    Start,
    Stop,
    Continue,
    Pause,
    Last_music,
    Next_music,
    Sequential_Play,
    Rand_Play,
    Signel_Play,
    Sound_add,
    Sound_reduce,
    Music_play_list,
    Music_choose
};

class SendInfo
{
public:
    SendInfo();
    ~SendInfo();
    SendInfo(const SendInfo& obj);
    void Set_flag(int flag);
    void Set_name(const char* name);

private:
    char m_name[32];
    int m_flag;
};

#endif // SENDINFO_H
