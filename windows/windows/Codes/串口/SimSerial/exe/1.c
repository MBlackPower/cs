// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
//#include <ntddser.h>

#include <winioctl.h>

#include <setupapi.h>
#include "objbase.h"
#include <initguid.h>
#include "..\inc\wdmioctl.h"

DEFINE_GUID(GUID_CLASS_COMPORT,          0x86e0d1e0L, 0x8089, 0x11d0, 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73);

void HandleDevice( PSP_INTERFACE_DEVICE_DETAIL_DATA detail );

int main(int argc, char* argv[])
{
	HDEVINFO	info;
	DWORD		n;
	BOOL		bRet;
	DWORD		needed;
	SP_INTERFACE_DEVICE_DATA			ifdata;
	PSP_INTERFACE_DEVICE_DETAIL_DATA	detail = NULL;

	// ���ȵõ���ClassGUIDֵ�µ��豸��Ϣ��� info. ��������ClassGUID�������豸��
	// HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses\{86e0d1e0-8089-11d0-9ce4-08003e301f73}
	info = SetupDiGetClassDevs( (LPGUID) &GUID_CLASS_COMPORT,//(LPGUID)&GUID_WDMSAMPLE_DEVICE_INTERFACE_CLASS,
		NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if( info == INVALID_HANDLE_VALUE ){
		printf("Error %d trying to open enumeration handle for \n", GetLastError() );
		return 0;
	}

    ifdata.cbSize = sizeof(ifdata);
	n = 0;
	// ʹ�ø� info ����ö�ٵ�ǰ��ClassGUID�µ������豸�ӿڣ����ýӿ���Ϣ����ifdata
    while( SetupDiEnumDeviceInterfaces(info, NULL, (LPGUID)&GUID_CLASS_COMPORT,//(LPGUID) &GUID_WDMSAMPLE_DEVICE_INTERFACE_CLASS,
		n, &ifdata))
	{
		// ��һ�ε��� SetupDiGetDeviceInterfaceDetail���õ�ifdata����ռ��С
		SetupDiGetDeviceInterfaceDetail(info, &ifdata, NULL, 0, &needed, NULL);
		detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA) malloc(needed);
		if (!detail)
		{
			printf("Error %d trying to get memory for interface detail\n", GetLastError());
			goto FAILED;
		}
		// �ڶ��ε��� SetupDiGetDeviceInterfaceDetail���õ�ifdataָ�����豸����ϸ��Ϣ
		detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		if (!SetupDiGetDeviceInterfaceDetail(info, &ifdata, detail, needed, NULL, NULL))
		{
			printf("Error %d getting interface detail\n", GetLastError());
			goto FAILED;
		}

		// ��ifdata/detail��ָ�����豸���д򿪣�IoControl���رյȲ���
		HandleDevice( detail );

		free( detail );
		detail = NULL;
		n++;
	}
FAILED:
	if( detail != NULL ){
		free( detail );
	}
	bRet = SetupDiDestroyDeviceInfoList( info );
	return 0;
}
void HandleDevice( PSP_INTERFACE_DEVICE_DETAIL_DATA detail )
{
    char	name[ MAX_PATH ];
	HANDLE	hfile;
	DWORD	junk;
	INT		ComX;

	// ���豸���˴����豸����ΪKernel mode��IoRegisterDeviceInterface��OS�Զ��������ơ�������ʽ
	// ##?#Toaster#MsToaster#1&1aafb3d5&2&01#{86e0d1e0-8089-11d0-9ce4-08003e301f73}
	strncpy(name, detail->DevicePath, sizeof(name));
	hfile = CreateFile( name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hfile == INVALID_HANDLE_VALUE)
    {
        printf("Error %d trying to open %s\n", GetLastError(), name);
        return;
    }
	scanf( "%d", &ComX );
#if 1
	if(!DeviceIoControl(hfile,IOCTL_INIT_SETTING, &ComX, sizeof( INT ), NULL , 0, &junk, NULL))
    {
		printf("Direct IOCTL failed with code %d\n", GetLastError());
	}
#else
	if(!DeviceIoControl(hfile,IOCTL_FINISH_SETTING,NULL,0,NULL,0,&junk,NULL))
    {
		printf("Direct IOCTL failed with code %d\n", GetLastError());
	}
#endif

	CloseHandle( hfile );

	printf("Hello World!\n");
	return;
}