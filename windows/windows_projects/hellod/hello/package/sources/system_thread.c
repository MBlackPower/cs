#include "../headers/system_thread.h"
#include <stdio.h>


#pragma warning(disable:4096 4996 4013)


#ifdef _windows_sys_
_ERROR __cdecl thread_os_init( _in_ _out_ THREAD_HANDLE * h )
{
	h->status_		= _initialize;
	h->handle_		= NULL;
	h->initialcode_ = NULL;
	h->argument_	= NULL;
	h->u_id_		= 0;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_init( _in_ _out_ THREAD_HANDLE * h )
{
	h->status_		= _initialize;
	h->handle_		= 0;
	h->initialcode_ = NULL;
	h->argument_	= NULL;
	h->u_id_		= 0;
	memset( (h->name_), 0, sizeof(h->name_) );
	return _ok;
}
#endif//_linux_sys_


#ifdef _windows_sys_

unsigned __stdcall start_address( void * argument )
{
	__try
	{
		THREAD_HANDLE * h = (THREAD_HANDLE *)argument;

		if ( NULL != h )
		{
			if ( NULL != h->initialcode_ )
			{
				h->initialcode_( h->argument_, h->name_, h->u_id_ );
			}
		}
	}
	__finally
	{
		thread_os_exit( 0 );
	}
	return 0;
}

_ERROR __cdecl thread_os_create(
								_in_ _out_ THREAD_HANDLE * h,
								_in_ INITIAL_CODE initialcode,
								_in_ void * argument,
								_in_ const u_char * thread_name
								)
{
	_ERROR ret = _failed;	

	thread_os_init( h );

	h->argument_ = argument;
	h->initialcode_ = initialcode;
	strcpy(h->name_, thread_name);

	/*
	uintptr_t _beginthreadex( 
								void *security,
								unsigned stack_size,
								unsigned ( *start_address )( void * ),
								void *arglist,
								unsigned initflag,
								unsigned *thrdaddr 
							);
	*/
	h->handle_ = (HANDLE)_beginthreadex( 0, 0, &start_address, (void *)h, 0, &(h->u_id_ ) );

	if ( NULL != h->handle_ )
	{
		h->status_ = _create;
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}
#endif//_windows_sys_

#ifdef _linux_sys_

void * start_routine(void * __arg)
{
	__try
	{
		THREAD_HANDLE * h = (THREAD_HANDLE *)__arg;

		if ( NULL != h )
		{
			if ( NULL != h->initialcode_ )
			{
				h->initialcode_( h->argument_, h->name_, h->u_id_ );
			}
		}
	}
	__finally
	{
		thread_os_exit( 0 );
	}
	return NULL;
}

_ERROR __cdecl thread_os_create(
								_in_ _out_ THREAD_HANDLE * h,
								_in_ INITIAL_CODE initialcode,
								_in_ void * argument,
								_in_ const u_char * thread_name
								)
{
	_ERROR ret = _failed;	

	thread_os_init( h );

	h->argument_ = argument;
	h->initialcode_ = initialcode;
	strcpy(h->name_, thread_name);

	/*
	//�������̳߳ɹ�ʱ����������0������Ϊ0��˵�������߳�ʧ�ܣ�
	//�����Ĵ��󷵻ش���ΪEAGAIN(��ʾϵͳ���ƴ����µ��̣߳������߳���Ŀ������)��EINVAL(��ʾ�ڶ�������������߳�����ֵ�Ƿ�)
	extern int pthread_create __P	(
										(
											pthread_t *__thread,				//ָ���̱߳�ʶ����ָ��
											__const pthread_attr_t *__attr,		//�����߳�����
	����									void *(*__start_routine) (void *),	//�߳����к�������ʼ��ַ
											void *__arg							//���к����Ĳ���
										)
									); 
	*/

	if ( 0 == pthread_create( &(h->handle_), NULL, &start_routine, __arg ) )
	{
		h->u_id_ = h->handle_;
		h->status_ = _create;
		ret = _ok;
	}
	else
	{
		ret = _failed;
	}
	return ret;
}
#endif//_linux_sys_




#ifdef _windows_sys_
_ERROR __cdecl thread_os_wait( _in_ const THREAD_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;

	/*
	DWORD WINAPI WaitForSingleObject(
										__in          HANDLE hHandle,
										__in          DWORD dwMilliseconds
									);
	*/

	switch( WaitForSingleObject( h->handle_, (-1 == ms) ? INFINITE : ms ) )
	{
	case WAIT_OBJECT_0:
		{
			ret = _ok;
			break;
		}
	case WAIT_TIMEOUT:
		{
			ret = _err_time_out;
			break;
		}
	default:
		{
			ret = get_error();
			break;
		}
	}
	return ret;
}
#endif _windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_wait( _in_ const THREAD_HANDLE * h, _in_ const long ms )
{
	_ERROR ret = _failed;
	//_ERROR __thread_return = _failed;

	/*
	//���������һ���߳������ĺ������������ĺ�����һֱ�ȴ������ȴ����߳̽���Ϊֹ������������ʱ�����ȴ��̵߳���Դ���ջء�
	//���ִ�гɹ���������0�����ʧ���򷵻�һ�������
	extern int pthread_join __P	(
									(
										pthread_t __th,			//���ȴ����̱߳�ʶ��
										void **__thread_return	//һ���û������ָ�룬�����������洢���ȴ��̵߳ķ���ֵ
									)
								); 
	*/
	switch( pthread_join( h->handle_, NULL )
	{
	case 0:
		{
			ret = _ok;
			break;
		}
	default:
		{
			ret = get_error();
			break;
		}
	}
	return ret;
}
#endif//_linux_sys_


#ifdef _windows_sys_
_ERROR __cdecl thread_os_exit( _in_ const unsigned retval )
{
	/*
	void _endthreadex( unsigned retval );
	*/
	_endthreadex( retval );

	return _ok;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_exit( _in_ const unsigned retval )
{
	/*
	//��ֹ���������̲߳�����һ��ָ��ĳ�������ָ��
	void pthread_exit(void* retval); 
	*/
	pthread_exit( NULL );

	return _ok;
}
#endif//_linux_sys_

#ifdef _windows_sys_
_ERROR __cdecl thread_os_destroy( _in_ THREAD_HANDLE * h )
{
	_ERROR ret = _failed;

	if ( CloseHandle( h->handle_ ) )
	{
		thread_os_init(h);
		ret = _ok;
	}
	else
	{
		ret = get_error();
	}
	return ret;
}
#endif//_windows_sys_

#ifdef _linux_sys_
_ERROR __cdecl thread_os_destroy( _in_ THREAD_HANDLE * h )
{
	_ERROR ret = _ok;

	return ret;
}
#endif//_linux_sys_

_ERROR __cdecl thread_create		(
										_in_ _out_ THREAD_HANDLE * h,
										_in_ INITIAL_CODE initialcode,
										_in_ void * argument,
										_in_ const u_char * thread_name 
									)
{
	_ERROR ret = _failed;

	if ( (NULL == h) || (NULL == initialcode) || (NULL == thread_name) )
	{
		return _err_parameter;
	}
	if ( _create != h->status_ )
	{
		return thread_os_create( h, initialcode, argument, thread_name );
	}
	return _err_exist;
}


_ERROR __cdecl thread_destroy	(
									_in_ THREAD_HANDLE * h,
									_in_ const long ms
								)
{
	_ERROR ret = _failed;

	if ( NULL == h )
	{
		return _err_parameter;
	}
	if ( _create != h->status_ )
	{
		return _err_create;
	}
	if ( _ok == (ret = thread_os_wait(h, ms)) )
		return thread_os_destroy(h);
	else
		return ret;
}

