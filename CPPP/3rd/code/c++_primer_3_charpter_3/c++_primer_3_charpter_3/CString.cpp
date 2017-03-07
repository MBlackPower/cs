#include "CString.h"
CString::CString()
{
	m_string = 0;
	m_size = 0;
}

CString::CString(const char* p) // ��������Լ�д�ģ������������д��һ����Ч����
{
	m_size = strlen(p);
	m_string = new char[m_size + 1];
	memcpy(m_string, p, m_size + 1);
	//m_string[m_size + 1] = '\0'; // ����ͨ�����г���
	//memcpy(m_string + m_size, '\0', 1); // ����
}

//CString::CString(const char* p) 
//{
//	m_size = strlen(p);
//	while(p)
//	{
//		*m_string = *p; // ����Ӧ���ǲ��еģ���Ϊ*m_stringӦ������ͨ�����룬�������л����
//	}
//}

//CString::CString(const char* str)
//{
//	if (!str)
//	{
//		m_size = 0;
//		m_string = 0;
//	}
//	else
//	{
//		m_size = strlen(str);
//		m_string = new char[m_size + 1];
//		strcpy(m_string, str);
//	}
//}

CString::CString(const CString& rhs)
{
	m_size = rhs.m_size;
	if (!rhs.m_string)
	{
		m_string = 0;
	}
	else
	{
		m_string = new char[rhs.m_size + 1];
		strcpy(m_string, rhs.m_string);
	}
}

CString::~CString()
{
	delete[] m_string;
}

CString& CString::operator=(const char* s)
{
	
	if (!s)
	{
		m_size = 0;
		delete[] m_string;
		m_string = 0;
	}
	else
	{
		m_size = strlen(s);
		delete[] m_string;
		m_string = new char[m_size + 1];
		strcpy(m_string, s);
	}
	return *this;
}

CString& CString::operator=(const CString& rhs)
{
	if (this != &rhs)
	{
		delete[] m_string;
		m_size = rhs.m_size;
		if (!rhs.m_string)
		{
			m_string = 0;
		}
		else
		{
			m_string = new char[m_size + 1];
			strcpy(m_string, rhs.m_string);
		}
	}
	return *this;
}

char& CString::operator [](int elem) const
{
	assert((elem >= 0) && (elem < m_size));
	return m_string[elem];
}

std::istream& operator>>(std::istream& io, CString& s)
{
	const int limit_string_size = 4096;
	char inBuf[limit_string_size];
	//io >> std::setw(limit_string_size) >> inBuf;
	io >> inBuf;
	s = inBuf;
	return io;
}

std::ostream& operator<<(std::ostream& os, const CString& s)
{
	return os << s.c_str();
	//return os << s.m_string; // ����û�ðѺ���operator<<����Ϊ��Ԫ����
}