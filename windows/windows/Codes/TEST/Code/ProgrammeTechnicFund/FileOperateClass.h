// FileOperateClass.h: interface for the CFileOperateClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPERATECLASS_H__991837AB_C42B_4680_BA53_A41081FD18E0__INCLUDED_)
#define AFX_FILEOPERATECLASS_H__991837AB_C42B_4680_BA53_A41081FD18E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ACE_Frame.h"
#include "ProgrammeTechnicFund.h"
//����淶
//////////////////////////////������ƶ�Ҫ�Դ�д��ĸ��C����ͷ�����һ���������ʡ�
//////////////////////////////Ϊ���ڽ綨��ÿ�����ʵ�����ĸҪ��д��
class CFileOperateClass
{
public:
	static ACE_Process_Mutex m_FileOpeateProcessMutex;

public:
	CFileOperateClass();
	virtual ~CFileOperateClass();


//////////////////////////////������Ӧ��ʹ��"����"����"���ʣ�����"���������飩����ʽ��
//////////////////////////////ָ���ͱ����͵����ӣ�pointer�� ǰ׺����һ������������ -- p
public:

	static  VOID  GetFilePath(
							IN  OUT   PCHAR              lpFileName );

	static  VOID  GetFilePath(
							IN  OUT   string            &strFileName );

	static  BOOL  ReadFile( 
							IN        PCHAR              lpFileFullPath,
							IN  OUT   PDATA_STRUCTURE   &pDataStructure );

	static  int   ReadFile(
							IN  OUT   unsigned char     *pchBuffer,
							IN 	      const UINT         nDataLength,
							IN        string             strFileFullPath );		

	static  BOOL  WriteFile( 
							IN        PCHAR              lpFileFullPath,
							IN        PDATA_STRUCTURE    pDateStructure );

	static  BOOL  WriteFile(
							IN        unsigned char      *pchBuffer,
							IN 	      const UINT          nDataLength,
							IN        string              strFileFullPath );

	static  int   ParseConnectDbConfigurationFile(
							IN  OUT   string            &strConnection,
							IN        string             strIp,
							IN  OUT   string            &strUseID,
							IN  OUT   string	        &strPassWord,
							IN        string			 strFileFullPathName );

	static  HBITMAP CopyScreenToBitmap( LPRECT lpRect );

	static  int		SaveBitmapToFile( HBITMAP hBitmap,
									  LPSTR   lpFileName );
	
//////////////////////////////������Ա�����Ŀ�ͷӦ������һ���»��ߡ�_����ʾ����.
protected:


private:

};

#endif // !defined(AFX_FILEOPERATECLASS_H__991837AB_C42B_4680_BA53_A41081FD18E0__INCLUDED_)
