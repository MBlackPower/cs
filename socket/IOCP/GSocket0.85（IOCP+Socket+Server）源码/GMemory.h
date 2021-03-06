/********************************************************************************
*																				*
*					GSocket：完成端口通讯模块（IOCP Socket）					*
*								——GMem										*
*																				*
*				Copyright © 2009  代码客（卢益贵）  版权所有					*
*						未经许可，不得用于任何项目开发							*
*  QQ:48092788  E-Mail:gcode@qq.com  源码博客：http://blog.csdn.net/guestcode	*
*																				*
*					GSN:34674B4D-1F63-11D3-B64C-11C04F79498E					*
********************************************************************************/

#pragma once

typedef	void(*PFN_ON_GMEM_TRAVERSAL)(DWORD dwParam, const void* pAddr, const DWORD dwSize, const BOOL bIsFree);

BOOL GMem_IsActive(void);
DWORD GMem_GetPageSize(void);
DWORD GMem_SetPageSize(DWORD dwSize);
DWORD GMem_GetPageNumber(void);
DWORD GMem_GetTotalBytes(void);
DWORD GMem_SetTotalBytes(DWORD dwBytes);
DWORD GMem_GetUsedBytes(void);
DWORD GMem_GetAvailPhyBytes(DWORD* pdwTotalPhyBytes);
DWORD GMem_GetPhyPageSize(void);
DWORD GMem_GetUsedPhyPageNumber(void);
DWORD GMem_GetUsedPhyBytes(void);
DWORD GMem_GetSysUsedBytes(void);

void GMem_Traversal(DWORD dwParam, PFN_ON_GMEM_TRAVERSAL pOnProc);

void* GMem_Alloc(DWORD dwSize);
void GMem_Free(void* pMem);

void GMem_Create(void);
void GMem_Destroy(void);


  