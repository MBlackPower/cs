
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MYDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MYDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MYDLL_EXPORTS

	#define EXPORT extern "C" __declspec(dllexport)	///// ʹ��MFC�ṩ�����η���__declspec(dllexport)
													   // ��Ҫ����ĺ������ࡢ���ݵ�����ǰ����_declspec(dllexport)��
													   // ���η�����ʾ�����__declspec(dllexport)��C����Լ����C����
													   // ����¿���ȥ��������������»���ǰ׺��
													   // �ڡ�C++���¶��塰C����������Ҫ��extern ��C���ؼ��ʡ�
													   // ��extern "C"��ָ���ú���ʹ��C���뷽ʽ������ġ�C���������Դӡ�C�����������

#else

	#define EXPORT __declspec(dllexport)

#endif

EXPORT BOOL CALLBACK MyMsgBox();
EXPORT BOOL CALLBACK aMsgBoxA( HWND   hwnd,
							   LPCSTR lpText,
							   LPCSTR lpCaption );

