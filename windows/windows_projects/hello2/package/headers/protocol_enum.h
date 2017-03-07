#pragma once



/******************************************************************************************/
//���幫��ö��
//ö��ֵ���������� ->��_��Ϊ��ͷ�� + ����Сд + �ָ���_��
//ö�����Ͷ������ ->��_��Ϊ��ͷ�� + ���ʴ�д + �ָ���_��
/******************************************************************************************/

// ����ִ��ʱ״̬�Ƿ���ȷ
typedef enum
{
	_false	= 0x00000000,
	_true	= 0x00000001
}
_BOOLEAN;

// ����ִ��ʱ�Ĵ����
typedef enum
{
	_ok		= 0x00000000,
	_failed	= 0x00000001,
	_err_unknown,//δ֪����
	_err_input_para,//���뺯���Ĳ�������
	_err_object_instance,//û��ʵ����
	_err_object_create,//û��ʵ����
	_err_object_destroy,//���ٴ���
	_err_memory_start = 0x01000001,
	_err_socket_start = 0x01100001,
	_err_thread_start
}
_ERROR;

// ��������
typedef enum
{
	_data_type	= 0x00100000
}
_DATA_TYPE;


typedef enum
{
	_instance = 0x00001000,
	_create,
	_destroy,
	_callback,
	_thread_status_start
}
_STATUS;

// ���鳤�ȵ�ö��ֵ
enum _ARRAY_LEN
{
	_L_256 = 256,
};

