#include <iostream>
#include "test_macro.h"
int main()
{   // ��λ�룬��λ��
    
    // ��λ����ǹ�����ӵ���˼
    int m_nUserFlags = 1;
    m_nUserFlags |= USER_FLAG_EXTERNSUBSCIBE;

    m_nUserFlags = 1;
    m_nUserFlags |= (USER_FLAG_WTQR|USER_FLAG_LOCALTLDM);

    // �궼�����ֻ��һλΪ1������flag�����ǰ�λ����ھ���˵������ĳ����ʶ
    // flag�����ǰ�λ�룬����Ҫ�ж�Ŀǰ��flag����û��������ܣ��Ƿ������������ʶ�����flag��������������ʶ����λ��Ľ����Ϊ0
    if ((m_nUserFlags&USER_FLAG_EXIT) == 0)
    {

    }
    m_nUserFlags = USER_FLAG_INITSUBSCIBE;
    if ((m_nUserFlags&USER_FLAG_INITSUBSCIBE) == 0)
    { // 1289 ..> 1293
        m_nUserFlags |= (USER_FLAG_INITSUBSCIBE|USER_FLAG_EXTERNSUBSCIBE);
    }

    m_nUserFlags &= ~USER_FLAG_UDPQUOTE;
    
    // 1293��269
    m_nUserFlags &= ~USER_FLAG_LOCALTLDM;
    
    // 269��285
    m_nUserFlags |= USER_FLAG_QHHQCX;
    getchar();
    return 0;
}