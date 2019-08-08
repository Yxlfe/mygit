#include "sendinfo.h"

SendInfo::SendInfo():m_flag(0)
{
    strcpy(m_name,"0");
}

SendInfo::~SendInfo()
{

}

void SendInfo::Set_flag(int flag)
{
    m_flag = flag;
}
void SendInfo::Set_name(const char* name)
{
    strcpy(m_name,name);
}

SendInfo:: SendInfo(const SendInfo& obj)
{
    strcpy(m_name,obj.m_name);
    m_flag = obj.m_flag;
}
