#pragma once


/******************************************************************************************/
//��������
//�������� -> "_" + ���ʴ�д,��_���ָ����ԡ�_����Ϊ������
/******************************************************************************************/

// �ж�ָ���Ƿ�Ϊ��
#define _IS_NULLITY_POINTER_( pointer )			NULL == (pointer)

// �ж�ָ���Ƿ�ǿ�
#define _IS_OK_POINTER_( pointer )			    NULL != (pointer)

// ����set_debug_depict()�����ĺ�
#define _DEBUG_DEPICT_

// ���ý�������״̬�ʹ����
#define _SET_RESULT_( ret, err, results )	    {										\
                                                    (ret).error_ = (err);		    	\
                                                    (ret).result_ = (results);		    \
													set_debug_depict( &(ret) );			\
                                                }

#define _RETURN_RESULT_( ret, err, results )	    {										\
													(ret).error_ = (err);		    	\
													(ret).result_ = (results);		    \
													set_debug_depict( &(ret) );			\
													return (ret);						\
												}

#if 0
// ���ƽ������
#define _COPY_RESULT_( dest_ret, src_ret )		_SET_RESULT_( dest_ret,				    \
                                                              (src_ret).error_,			\
                                                              (src_ret).result_ )
#endif//0

// ��ʼ���������
#define _INIT_RESULT_( ret )    				_SET_RESULT_( ret, -1, _false )

// �Ƿ�ɹ�
#define _IS_OK_( results )						_true == (results)

// �Ƿ�ʧ��
#define _IS_ERR_( results )					    _false == (results)

// �Ƿ��Ѿ�ʵ����
#define _IS_INSTANCE_( status )					_instance == (status)

// �Ƿ��Ѿ�ʵ����
#define _IS_CREATE_( status )					_create == (status)

// �Ƿ��Ѿ�ʵ����
#define _IS_NO_STATUS_( status )				_instance != (status)

// �жϽ����״̬�Ƿ�Ϊ�ɹ�
#define _IS_OK_RESULT_( ret )				    _IS_OK_( (ret).result_ )

#define _IS_ERR_RESULT_( ret )				    _IS_ERR_( (ret).result_ )





/******************************************************************************************/
//�յĺ��������� -> "_" + ����Сд,��_���ָ����ԡ�_����Ϊ������
/******************************************************************************************/

//��������������
#define _in_
#define _out_

#define _windows_sys_




/******************************************************************************************/
// ��ĺ궨���new��delete���������������������
/******************************************************************************************/

#define _CLASS_(class_name)								\
typedef struct class_name class_name;					\
class_name * NEW_##class_name();						\
void DELETE_##class_name(class_name * obj);				\
void CTOR_##class_name(class_name * obj);				\
void DTOR_##class_name(class_name * obj);				\
struct class_name



#define EXTENDS(type)		struct type type

