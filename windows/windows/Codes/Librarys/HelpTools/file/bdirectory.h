#ifndef _BDIRECTORY_H_
#define _BDIRECTORY_H_


#include "../share/share.h"


class __EXPORT_DLL CBDirectory
{
public:
	CBDirectory();
	virtual ~CBDirectory();

public:
	static int CreateDirectory(char * strPath);
	static int DeleteDirectory(char * strPath);
	

	/* ��õ�ǰ����Ŀ¼ */
	static int GetCurrentDir(char * strPath, int nPathLen);
	

	/* ��û�������ֵ */
	static int GetEnvionmentVar(
								const char * strEnvName,
								char * strRetEnvVar
								);


	/* ��õ�ǰ����Ŀ¼�������ļ�·�� */
	static int GetCurrentDirObjPath(
									int			nPathLen,
									char		* szPath,
									const char	* szFileName
									);


	/* ����������·������������ */
	static int GetUtterlyPathDriveLetter(
											const char	* szPath,
											char		* szDriveLetter
											);
};




#endif//_BDIRECTORY_H_