#include "stdafx.h"
#include "stdlib.h"

#include "HTMLParser.h"

CHtmlParser::CHtmlParser()
{
}

CHtmlParser::~CHtmlParser()
{
}

// ��buffer���ҳ�Ԥ����ı�ţ����ñ��λ�õ�����
BOOL CHtmlParser::FindToken(const char *pTokens, const char *pBuffer, int& nIndex, int nMaxLen)
{
	int nTokenCount = strlen(pTokens);
	BOOL bQuote = FALSE;

	while(nIndex < nMaxLen)
	{
		for(int i = 0; i < nTokenCount; i++)
		{
			if(pBuffer[nIndex] == pTokens[i])
				return(TRUE);
		}
		nIndex++;
	}
	return(FALSE);
}

// ����һ���ض����ַ���β���ַ���������������λ�����ַ�����β��
CString CHtmlParser::GetString(const char *pTerminals, const char *pBuffer,int &nIndex, int nMaxLen)
{
	int nOldIndex = nIndex;
	CString strText;

	while(nIndex < nMaxLen && pBuffer[nIndex] == ' ')
		nIndex++;

	if(FindToken(pTerminals,pBuffer,nIndex,nMaxLen))
	{
		nIndex++;
		strText = pBuffer+nOldIndex;
		strText = strText.Left(nIndex-nOldIndex-1);
	}
	return(strText);
}

//�õ���������
CString CHtmlParser::SaveParm(const CString& strParm, BOOL bLowercase)
{
	int nLen = strParm.GetLength();
	CString strNewParm = strParm;

	// �����������ŵĵط��ÿո����
	for(int i = 0; i < nLen; i++)
	{
		if(strNewParm[i] == '"')
			strNewParm.SetAt(i,' ');
	}

	// ɾ��ǰ���ͺ����Ŀո�
	strNewParm.TrimLeft();
	strNewParm.TrimRight();

	if(bLowercase)
		strNewParm.MakeLower();

	return(strNewParm);
}

// �õ�һ��������������Ϣ
void CHtmlParser::GetOptions(const char *pBuffer, int &nIndex, int nMaxLen)
{
	CString strParm;
	int nStart;

	while(nIndex < nMaxLen)
	{
		nStart = nIndex;

		// �ҳ��Ⱥ���ߵ��ַ�������indexΪ�綨��
		strParm = GetString("=",pBuffer,nIndex,nMaxLen);

		if(!strParm.IsEmpty())
		{
			COptions opt;
			int nStart = nIndex;

			opt.SetParm(SaveParm(strParm,TRUE));

			while(nIndex < nMaxLen && pBuffer[nIndex] == ' ')
				nIndex++;

			//Ѱ��html��tag�Ľ���λ��
			if(FindToken("\" >",pBuffer,nIndex,nMaxLen))
			{
				// �������Ų���
				if(pBuffer[nIndex] == '"')
					FindToken("\"",pBuffer,++nIndex,nMaxLen);

				// ����options��λ��
				strParm = pBuffer+nStart;
				strParm = strParm.Left(nIndex-nStart);
				opt.SetValue(SaveParm(strParm,FALSE));
				opt.SetIndex(nStart);
			}

			// ��option���������option
			m_arrOptions.Add(opt);

		}
		else 
			break;
	}
}

// ����html��tag
BOOL CHtmlParser::GetTag(const char *pBuffer, int& nIndex, int nMaxLen)
{
	m_strTag.Empty();
	m_arrOptions.RemoveAll();

	// �ҳ�tag����ʼλ�ü�"<"��λ��
	if(FindToken("<",pBuffer,nIndex,nMaxLen))
	{
		int nStart = nIndex+1;
		BOOL bFound = FALSE;

		nIndex++;

		// ������Ч��tag��������ע��Ҳ������html�ļ�����
		if(pBuffer[nIndex] == ' ' || pBuffer[nIndex] == '>' || pBuffer[nIndex] == '!')
			return FALSE;

		// �ҳ�tag����ֹλ�ã���">"��λ��
		if(FindToken(">",pBuffer,nIndex,nMaxLen))
		{
			m_strTag = GetString(" >\r\n",pBuffer,nStart,nMaxLen);
			m_strTag.MakeLower();

			// �ж�tag�Ƿ���Ԥ�����tag
			if(WantTag(m_strTag))
			{
				nStart--;
				GetOptions(pBuffer,nStart,nIndex+1);
			}
			return TRUE;
		}
	}

	return FALSE;
}

// ȱʡ����true
BOOL CHtmlParser::WantTag(const CString& strTag)
{
   return(TRUE);
}

// ȱʡ����true
BOOL CHtmlParser::ProcessTag(const CString& strTag, int nIndex, 
											const HTML_ARGS& arrOptions)
{
   return(TRUE);
}

// �ۺ�����ĺ�������html�ļ���tag
void CHtmlParser::ParseText(char *pBuffer, int nMaxLen)
{
	int nIndex = 0;

	m_strTag.Empty();
	m_arrOptions.RemoveAll();
	m_pRawBuffer = pBuffer;

	while(nIndex < nMaxLen)
	{
		if(GetTag(pBuffer,nIndex,nMaxLen))
		{
			if(!ProcessTag(m_strTag,nIndex,m_arrOptions))
				break;
		}
	}
}
