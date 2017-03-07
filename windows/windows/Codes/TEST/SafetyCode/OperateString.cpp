// OperateString.cpp: implementation of the COperateString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SafetyCode.h"
#include "OperateString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COperateString::COperateString()
{

}

COperateString::~COperateString()
{

}

char g_szvariableaddress[MAX_PATH];		// ���ڴ�ŵ�����Ϣ



/**************************************************************************************************
 * ������: set_file_full_path ( char * lpszfilepath , const char * lpszfilename )
 *
 * ��  ��: ���ݸ�����(lpszfilepath)�ļ�·�����õ��ڸ�·��Ŀ¼�µ�ָ���ļ�(lpszfilename)��ȫ·��
 *
 * ����ֵ: �ɹ�����SUCCESS_FLAG��ʧ�ܷ���FAILED_FLAG
 **************************************************************************************************/
int COperateString::set_file_full_path (	char	   * lpszfilepath ,
											const char * lpszfilename		)
{
	//
	// ���ַ���β������'\\'����ȷ��β��'\\'���ֵ�λ��
	//
	char * pszlastfind = strrchr ( lpszfilepath , '\\' );
	//
	// �жϵ�ǰ�ַ����ǲ��ǺϷ��ļ�·��
	//
	if ( NULL == pszlastfind )
	{
		//
		//û���ҵ�'\\'��������ǰ�ַ������ǺϷ��ļ�·��
		//
		//logerror
		return FAILED_FLAG;
	}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
#endif
//-------------------------------------------------------------------------------------------

	int nstrsize = 0;
	//
	// �����Ҫ��ȡ���ַ������ȣ����û��巶Χ
	//
	nstrsize = (++pszlastfind) - lpszfilepath;
	//
	// �ж��Ƿ�����������
	//
	if ( ( 1 > nstrsize ) || ( nstrsize > MAX_PATH ) )
	{
		//
		// ���ڻ�������Χ
		//

		//logerror
		return FAILED_FLAG;
	}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "nstrsize" ,
						&nstrsize , nstrsize											)
#endif
//-------------------------------------------------------------------------------------------

	//
	// ���建����
	//
	char sztempmemory[MAX_PATH];

	memset ( sztempmemory , 0 , MAX_PATH );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "++pszlastfind" ,
						&(++pszlastfind) , ++pszlastfind								)
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "sztempmemory" ,
						&sztempmemory , sztempmemory									)
#endif
//-------------------------------------------------------------------------------------------

	pszlastfind = strncpy ( sztempmemory , lpszfilepath , nstrsize );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "lpszfilepath" ,
						&lpszfilepath , lpszfilepath									)
#endif
//-------------------------------------------------------------------------------------------

	//
	// ���Ҫ�ϲ����ַ�������
	//
	nstrsize = strlen (sztempmemory) + strlen (lpszfilename);
	//
	// �ж��Ƿ�����������
	//
	if ( (MAX_PATH-1) < nstrsize )
	{
		//
		// ���ڻ�������Χ
		//

		//logerror
		return FAILED_FLAG;
	}

	pszlastfind = strcat ( sztempmemory , lpszfilename );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
#endif
//-------------------------------------------------------------------------------------------

	memset ( lpszfilepath , 0 , MAX_PATH );
	//
	// ��øú���Ҫ�������ַ���
	//
	pszlastfind = strcpy ( lpszfilepath , sztempmemory );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
	SHOW_TEST_INFO (	"COperateString::set_file_full_path( )" , "pszlastfind" ,
						&pszlastfind , pszlastfind										)
#endif
//-------------------------------------------------------------------------------------------

	return SUCCESS_FLAG;
}