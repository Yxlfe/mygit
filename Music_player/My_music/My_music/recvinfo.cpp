#include "recvinfo.h"

Recvinfo::Recvinfo():m_flag(0)
{
    strcpy(m_time,"0");
    strcpy(m_name,"0");
}

Recvinfo::~Recvinfo()
{
    char* Get_member_name();
    char* Get_member_time();
    int Get_member_flag();
}

char* Recvinfo::Get_member_name()
{
    return m_name;
}

char* Recvinfo::Get_member_time()
{
    return m_time;
}


int Recvinfo::Get_member_flag()
{
    return m_flag;
}

