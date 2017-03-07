// lassNetSetting.h: interface for the ClassNetSetting class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LASSNETSETTING_H__16D8BE23_3C61_4511_B8BB_75E9264B515B__INCLUDED_)
#define AFX_LASSNETSETTING_H__16D8BE23_3C61_4511_B8BB_75E9264B515B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Nb30.h"

//����ϵͳ����
enum Win32Type{
	Unknow,
	Win32s,
	Windows9X,
	WinNT3,
	WinNT4orHigher
};

typedef struct tagASTAT 
{ 
    ADAPTER_STATUS adapt; 
    NAME_BUFFER    NameBuff [30]; 
}ASTAT,*LPASTAT; 

//�洢������MAC��ַ�Ľṹ
typedef struct tagMAC_ADDRESS
{
	BYTE b1,b2,b3,b4,b5,b6;
}MAC_ADDRESS,*LPMAC_ADDRESS;

//������Ϣ�����ݽṹ��������¼�����ĳ��̼��ͺţ���֮�󶨵�IP��ַ������
//DNS���У���������������ַ
typedef struct tagNET_CARD
{
	TCHAR szDescription[256];
	BYTE  szMacAddr[6];
	TCHAR szGateWay[128];
	TCHAR szIpAddress[128];
	TCHAR szIpMask[128];
	TCHAR szDNSNameServer[128];
}NET_CARD,*LPNET_CARD;


#define MAX_CARD  10

class ClassNetSetting  
{
public:
	void ProcessMultiString(LPTSTR lpszString,DWORD dwSize);
	UCHAR GetAddressByIndex(int lana_num,ASTAT & Adapter);
	BOOL GetSettingOfWinNT();
	int GetMacAddress(LPMAC_ADDRESS pMacAddr);
	BOOL GetSetting();
	ClassNetSetting();
	virtual ~ClassNetSetting();
public:
	BOOL GetSettingOfWin9X();
	Win32Type GetSystemType();
	int			m_TotalNetCards;//ϵͳ��������
	TCHAR		m_szDomain[16];//����
	TCHAR		m_szHostName[16];//������
	int			m_IPEnableRouter;//�Ƿ�����IP·��0-������,1-����,2-δ֪
	int			m_EnableDNS;//�Ƿ�����DNS����0-������,1-����,2-δ֪
	NET_CARD    m_Cards[MAX_CARD];//Ĭ�ϵ������������10
	Win32Type   m_SystemType;//����ϵͳ����
	MAC_ADDRESS m_MacAddr[MAX_CARD];//����10������

};

#endif // !defined(AFX_LASSNETSETTING_H__16D8BE23_3C61_4511_B8BB_75E9264B515B__INCLUDED_)
