#pragma once

#include "protocol_enum.h"
#include "protocol_macro.h"
#include "protocol_type_define.h"


/******************************************************************************************/
//���庯��
//�������� --> ����Сд����_���ָ�
//�������� --> ʹ��_in_ / _out_��ʾ��������
//�������� --> ʹ��RESULT���ͱ�ʾ����״̬
/******************************************************************************************/

// ���Ժ���
extern RESULT __cdecl test_func_name( _in_ const u_char t, _in_ _out_ u_char * buff );

extern int __cdecl get_error( void );
extern void __cdecl set_debug_depict(_in_ _out_ RESULT * ret);
