#ifndef RECVINFO_H
#define RECVINFO_H
#include <string>
class Recvinfo
{
public:
    Recvinfo();
    ~Recvinfo();
    char* Get_member_name();
    char* Get_member_time();
    int Get_member_flag();

private:
    char m_name[32];
    char m_time[32];
    int m_flag;
};

#endif // RECVINFO_H
