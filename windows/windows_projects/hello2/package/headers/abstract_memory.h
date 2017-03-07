#pragma once


#include "system_memory.h"


_CLASS_( MEMORY )
{
	_INSTANCE	instance_;
	EXTENDS( MEMORY_HANDLE );
	
	/*
	����obj
	*/
	RESULT ( __cdecl * mm_set       ) ( _in_ _out_ MEMORY * obj, _in_ const u_char ch );

	/*
	����obj����
	*/
	RESULT ( __cdecl * mm_size      ) (
										_in_ const MEMORY * obj,
										_out_ u_long * allot_size
										);

	/*
	��byte_array���ݴ�obj��mm_begin_posλ��д��write_length���ֽ�
	*/
	RESULT ( __cdecl * mm_write     ) (
										_in_ _out_ MEMORY * obj,
										_in_ const u_long mm_begin_pos,
										_in_ const u_char * byte_array,
										_in_ const u_long write_length
										);

	/*
	����obj��mm_begin_posλ�õ�ָ��ָ��byte_array��������read_length�ֽ���
	*/
	RESULT ( __cdecl * mm_read      ) (
										_in_ const MEMORY * obj,
										_in_ const u_long mm_begin_pos,
										_out_ u_char ** byte_array,
										_in_ _out_ u_long * read_length
										);

	/*
	��in_mm�ĵ�in_mm_begin_pos�ֽڿ�ʼ���write_length���ֽ������ڴ�Σ�д��obj����mm_begin_pos�ֽ�Ϊ�����ڴ���
	*/
	RESULT ( __cdecl * mm_write_o   ) (
										_in_ _out_ MEMORY * obj,
										_in_ const u_long mm_begin_pos,
										_in_ const MEMORY * in_mm,
										_in_ const u_long in_mm_begin_pos,
										_in_ const u_long write_length
										);

	RESULT ( __cdecl * mm_read_o    ) (
										_in_ const MEMORY * obj,
										_in_ const u_long mm_begin_pos,
										_in_ _out_ MEMORY * out_mm,
										_in_ const u_long out_mm_begin_pos,
										_in_ _out_ u_long * read_length
										);

	RESULT ( __cdecl * mm_copy      ) (
										_in_ _out_ MEMORY * obj,
										_in_ const MEMORY * src_obj
										);

	RESULT ( __cdecl * mm_compare   ) (
										_in_ const MEMORY * obj,
										_in_ const MEMORY * src_obj,
										_out_ _BOOLEAN * is_same
										);
};

#if 0

_CLASS_(MEMORY_DATA)
{
    _INSTANCE		instance_;
	u_long			allot_size_;
	u_char			* memory_;
};


_CLASS_(MEMORY)
{
    _INSTANCE	instance_;
    MEMORY_DATA mm_data_;


    /*
      ����obj
    */
    RESULT ( __cdecl * mm_set       ) ( _in_ MEMORY * obj, _in_ const u_char ch );

    /*
      ����obj����
    */
    RESULT ( __cdecl * mm_size      ) (
                                        _in_ const MEMORY * obj,
                                        _out_ u_long * allot_size
                                        );

    /*
      ��byte_array���ݴ�obj��mm_begin_posλ��д��write_length���ֽ�
    */
    RESULT ( __cdecl * mm_write     ) (
                                        _in_ MEMORY * obj,
                                        _in_ const u_long mm_begin_pos,
                                        _in_ const u_char * byte_array,
                                        _in_ const u_long write_length
                                        );

    /*
      ����obj��mm_begin_posλ�õ�ָ��ָ��byte_array��������read_length�ֽ���
    */
    RESULT ( __cdecl * mm_read      ) (
                                        _in_ const MEMORY * obj,
                                        _in_ const u_long mm_begin_pos,
                                        _out_ u_char ** byte_array,
                                        _in_ _out_ u_long * read_length
                                        );

    /*
      ��in_mm�ĵ�in_mm_begin_pos�ֽڿ�ʼ���write_length���ֽ������ڴ�Σ�д��obj����mm_begin_pos�ֽ�Ϊ�����ڴ���
    */
    RESULT ( __cdecl * mm_write_o   ) (
                                        _in_ MEMORY * obj,
                                        _in_ const u_long mm_begin_pos,
                                        _in_ const MEMORY * in_mm,
                                        _in_ const u_long in_mm_begin_pos,
                                        _in_ const u_long write_length
                                        );

    RESULT ( __cdecl * mm_read_o    ) (
                                        _in_ const MEMORY * obj,
                                        _in_ const u_long mm_begin_pos,
                                        _in_ _out_ MEMORY * out_mm,
                                        _in_ const u_long out_mm_begin_pos,
                                        _in_ _out_ u_long * read_length
                                        );

    RESULT ( __cdecl * mm_copy      ) (
                                        _in_ MEMORY * obj,
                                        _in_ const MEMORY * src_obj
                                        );

    RESULT ( __cdecl * mm_compare   ) (
                                        _in_ const MEMORY * obj,
                                        _in_ const MEMORY * src_obj,
										_out_ _BOOLEAN * is_same
                                        );
};

#endif//0