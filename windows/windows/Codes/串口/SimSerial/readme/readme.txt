
	���⴮���豸����
	Virtual Serial Device Driver
		ver 04.1.15

Windows2K�����⴮���豸�����������Ӧ�ó���

�����б�
===========

��Ҫ����
ʹ��˵��
��ģ��˵��
��������
ؽ���Ľ�֮��
������ϵ

��Ҫ����
===========

�����ϸ���ҵ���Virtual Serial Ports Driver XP3���ơ�

1.�ڲ���ϵͳ�У���������ɴ��ڡ�����ʹ�ô��ڹ��ߣ��������ϵͳ�Դ��ĳ����ն�������Դ��ڽ��д򿪡����͡����ա��رյȲ�����
2.  ���������⴮�ڣ����Կ����������Ⲩ���ʡ�����λ����żУ�顢ֹͣλ�ȶ˿ڲ�����
3.  ͨ��Э�鴫�͡��������ݡ�

ʹ��˵��
===========

1. ��װtoaster( win2k ddk sample)������������BusEnum.sys����װ�������DDK��toaster\bus����
2. ����̨������enum -p 1�����µ�Ӳ���豸ָ�� SimSerial\infĿ¼����װ���ǵ����⴮����������
��װ����Ժ��ڡ��豸����������Ӧ�ö��һ���豸��VirtualSerial����enum������DDK��toaster\exe\enum���ӱ��롣ֻ�ǸĶ���toaster\inc\public.h�е�#define BUS_HARDWARE_IDS L"Toaster\\MsToaster\0"
3. ����̨������enum -p 2����ӵڶ������⴮���豸
4. ����̨������test.exe��ö�ٲ��һ����ո����ɵ��������ڡ�
5. �򿪡������նˡ����ڡ����ӵ����Ի����ϡ�����ʱʹ�á���ѡ��COM20��
6. �򿪡������նˡ����ڡ����ӵ����Ի����ϡ�����ʱʹ�á���ѡ��COM21��
7. ж���豸�����ڿ���̨������ enum -u 1, enum -u 2
8. ������������ʱ��ֻ��Ҫ�����е����⴮��ж�أ�Ȼ���ٱ�����������build -ceZ������cc.bat���ɡ�

��ģ��˵��
===========

DebugLog	Debug��־
exe		�ο���Ŀ¼��˵��.txt
filter		���˳��򡣼��Ӹ��ִ��ڵĲ������ڿ��������а����ܴ�
inc		app �� sys��Ҫ�õ������ɺ궨�������
inf		���հ�װ����Ҫ��.inf and .sys
OptSerial		���ô�ͳ�ķ�ʽ���ʴ��ڵ�win32 app
readme		���ļ�����Ŀ¼
sys		WDM���͵������������⴮���������������


��������
===========

ԭ��
----------------

����ҵ���Virtual Serial Ports Driver XP3���ơ�
��������DDK��toaster bus���Ӱ�װtoaser bus���ߣ�Ȼ�����ø�����������������һ�����򼸸�������PDO������Щ�����PDO������������⴮����������
ע�⣺toaster bus driver��װ�Ժ󲻻��Զ����������豸PDO����Ҫ������Ӧ��enum����
��enum -p 1��������һ���µ������豸�����豸��Hardware ID����NTDDK\src\general\toaster\inc\public.h���#define BUS_HARDWARE_IDS L"Toaster\\MsToaster\0"�Ķ��塣���Hardware ID�����ǵ����⴮����������inf�ļ�(MySerial.inf)���ָ����Hardware ID����һ�¡�����װ�����������ʱ�򣬻���ʾ��δ������ص�Ӳ����Ϣ����


����ʵ��
----------------

DriverEntry:
����ͨ��WDM����һ��������˶�gDeviceArray, gPacketPool, gIdleQueue��ȫ�ֱ����ĳ�ʼ��

AddDevice:
����Kernel mode�µ�DeviceName
��ʼ��ReadIrp CancelSpinlock and ReadQueue Spinlock
��������Queue: ReadIrpQueue, WriteIrpQueue, ReadDataQueue
deviceExtension�е����������ĳ�ʼ��

IRP_MN_START_DEVICE

����AddInterface����win32 App�ṩ���ʽӿ�

IOCTL_CREATE_DOS_NAME
����SerialDoExternalNaming�����ɷ������Ӻ�DosName

ReadFile & WriteFile
ʹ��Packet���С���Ҫʵ��ȫ����ReadWrite.c�е�����������ʱ����ȣ����ñȽϴֲڡ�


ؽ���Ľ�֮��
=============

1��ReadFile��WriteFile������Ҫ�Ľ���Ŀǰʹ�õ���Packet���е���ʽ�������ݵĴ��ݣ�Ч�ʷ��治�ߡ���IOCTL_SERIAL_SET_QUEUE_SIZE�����õĻ������Ĵ�СĿǰû����ϵ������
2����ʱ����Ŀǰû�н��д���
3��������Line control��û�д���
4��Win32 app���治�Ѻã���Ҫ�Ľ��ɴ��ڽ���

������ϵ
=============

Email:	czzhou@sohu.com
acidfish@driverdevelop.com
