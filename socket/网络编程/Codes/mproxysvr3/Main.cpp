// Main.cpp : Defines the entry point for the console application.
//
//*******************************************************************
//              
//  FILE:       Main.cpp
//              
//  AUTHOR:     sam sha
//              
//  PROJECT:    mproxysvr2
//              
//  COMPONENT:  -
//              
//  DATE:       23.06.2003
//              
//  COMMENTS:   - ��Service.cpp��ʼ���޸ļ����˿ڣ���ָ�����������ַ���˿�
//                -I װ�ط���  �� -U ж�ط���
//              
//*******************************************************************

// Includes

#include "stdafx.h"
#include "Service.h"
#include "mproxy3.h"


int main(int argc, char* argv[])
{
//	CMProxy3 _proxy2(11600,"main-svr",8080);
//���Գ���ʹ��1
/*	_proxy2.Start();
	Sleep(1000);
	_proxy2.Stop();
	Sleep(5000);
	return 0;
*/
/*
//���Գ���ʹ��2
	_proxy2.Start();
	
	while(1)
	{//Ҫ����״̬ǿ����ֹ
		Sleep(1000);
	}
	return 0;
*/

	_Module.Init("mproxysvr3","mproxysvr3");
	if (argc > 1)
	{
		char seps[] = "-/";
		char *pToken;
		
		pToken = strtok(argv[1],seps);
		while (pToken)
		{
			if (!stricmp(pToken,"I"))
			{
				_Module.Install();
			}
			else if (!stricmp(pToken,"U"))
			{
				_Module.Uninstall();
			}
			pToken = strtok( NULL, seps );
			return 0;
		}
	}
	_Module.m_bService = TRUE;
	_Module.Start();

	return 0;
}
