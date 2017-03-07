#pragma once


#include "protocol_interface.h"


enum
{
	_err_allot_memory = _err_memory_start + 1,//�����ڴ�ʧ��
	_err_allot_size,
	_err_array_over,//����Խ�����
};


typedef struct __tag_MEMORY_HANDLE
{
	_STATUS			status_;
	_DATA_TYPE		data_type_;
	_BOOLEAN		delete_data_;
	u_long			allot_size_;
	u_char			* memory_;
}
MEMORY_HANDLE;


extern RESULT __cdecl memory_init		(
											_in_ _out_ MEMORY_HANDLE * h
										);

/*
���obj״̬Ϊ_STATUS��
���allot_size���ȵ���obj���ȣ����obj->mm_data_
��������obj�������´���obj
���򣬴���obj
*/
extern RESULT __cdecl memory_create		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long allot_size
										);

extern RESULT __cdecl memory_recreate	(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long allot_size,
											_in_ const u_long bak_begin_pos,
											_in_ const u_long bak_end_pos
										);
/*
����obj
*/
extern RESULT __cdecl memory_destroy	(
											_in_ _out_ MEMORY_HANDLE * h
										);


extern RESULT __cdecl memory_set		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_char ch
										);

/*
����obj����
*/
extern RESULT __cdecl memory_size		(
											_in_ const MEMORY_HANDLE * h,
											_out_ u_long * allot_size
										);

/*
��byte_array���ݴ�obj��mm_begin_posλ��д��write_length���ֽ�
*/
extern RESULT __cdecl memory_write		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const u_char * byte_array,
											_in_ const u_long write_length
										);

/*
����obj��mm_begin_posλ�õ�ָ��ָ��byte_array��������read_length�ֽ���
*/
extern RESULT __cdecl memory_read		(
											_in_ const MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_out_ u_char ** byte_array,
											_in_ _out_ u_long * read_length
										);

/*
��in_mm�ĵ�in_mm_begin_pos�ֽڿ�ʼ���write_length���ֽ������ڴ�Σ�д��obj����mm_begin_pos�ֽ�Ϊ�����ڴ���
*/
extern RESULT __cdecl memory_write_o	(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const MEMORY_HANDLE * in_mm,
											_in_ const u_long in_mm_begin_pos,
											_in_ const u_long write_length
										);

extern RESULT __cdecl memory_read_o		(
											_in_ const MEMORY_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ _out_ MEMORY_HANDLE * out_mm,
											_in_ const u_long out_mm_begin_pos,
											_in_ _out_ u_long * read_length
										);

extern RESULT __cdecl memory_copy		(
											_in_ _out_ MEMORY_HANDLE * h,
											_in_ const MEMORY_HANDLE * src
										);

extern RESULT __cdecl memory_compare	(
											_in_ const MEMORY_HANDLE * h,
											_in_ const MEMORY_HANDLE * src,
											_out_ _BOOLEAN * is_same
										);