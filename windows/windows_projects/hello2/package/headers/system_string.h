#pragma once

#include "system_memory.h"
#include "protocol_interface.h"


typedef struct __tag_STRING_HANDLE
{
	_STATUS	status_;
	//struct MEMORY_HANDLE;
}
STRING_HANDLE;


extern RESULT __cdecl string_init	(
											_in_ _out_ STRING_HANDLE * h
										);

/*
���obj״̬Ϊ_STATUS��
���allot_size���ȵ���obj���ȣ����obj->mm_data_
��������obj�������´���obj
���򣬴���obj
*/
extern RESULT __cdecl string_create		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long allot_size
										);

extern RESULT __cdecl string_recreate	(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long allot_size,
											_in_ const u_long bak_begin_pos,
											_in_ const u_long bak_end_pos
										);
/*
����obj
*/
extern RESULT __cdecl string_destroy	(
											_in_ _out_ STRING_HANDLE * h
										);


extern RESULT __cdecl string_set		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_char ch
										);

/*
����obj����
*/
extern RESULT __cdecl string_length	(
											_in_ const STRING_HANDLE * h,
											_out_ u_long * length
										);

/*
��byte_array���ݴ�obj��mm_begin_posλ��д��write_length���ֽ�
*/
extern RESULT __cdecl string_write		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const u_char * byte_array,
											_in_ const u_long write_length
										);

/*
����obj��mm_begin_posλ�õ�ָ��ָ��byte_array��������read_length�ֽ���
*/
extern RESULT __cdecl string_read		(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_out_ u_char ** byte_array,
											_in_ _out_ u_long * read_length
										);

/*
��in_mm�ĵ�in_mm_begin_pos�ֽڿ�ʼ���write_length���ֽ������ڴ�Σ�д��obj����mm_begin_pos�ֽ�Ϊ�����ڴ���
*/
extern RESULT __cdecl string_write_o	(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ const STRING_HANDLE * in_mm,
											_in_ const u_long in_mm_begin_pos,
											_in_ const u_long write_length
										);

extern RESULT __cdecl string_read_o		(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long mm_begin_pos,
											_in_ _out_ STRING_HANDLE * out_mm,
											_in_ const u_long out_mm_begin_pos,
											_in_ _out_ u_long * read_length
										);

extern RESULT __cdecl string_compare	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const u_char * src,
											_in_ const u_long src_begin_pos,
											_in_ const u_long cmp_length,
											_out_ _BOOLEAN * is_same
										);

extern RESULT __cdecl string_compare_o	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const STRING_HANDLE * src,
											_in_ const u_long src_begin_pos,
											_in_ const u_long cmp_length,
											_out_ _BOOLEAN * is_same
										);

extern RESULT __cdecl string_upper		(
											_in_ _out_ STRING_HANDLE * h
										);

extern RESULT __cdecl string_lower		(
											_in_ _out_ STRING_HANDLE * h
										);

extern RESULT __cdecl string_first_find	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const u_char * find_str,
											_out_ u_long * find_pos
										);

extern RESULT __cdecl string_last_find	(
											_in_ const STRING_HANDLE * h,
											_in_ const u_long h_begin_pos,
											_in_ const u_char * find_str,
											_out_ u_long * find_pos
										);

extern RESULT __cdecl string_copy		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const STRING_HANDLE * src
										);

extern RESULT __cdecl string_append		(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const u_char * append_str,
											_in_ const u_long append_length
										);

extern RESULT __cdecl string_append_o	(
											_in_ _out_ STRING_HANDLE * h,
											_in_ const STRING_HANDLE * append_obj
										);

