/*
  target: ��ȡĳĿ¼�µ������ļ���
*/
#include <windows.h>
#include <iostream.h>
//using namespace std;

int main(int argc,char *argv[])
{
	WIN32_FIND_DATA FileData;
	HANDLE          hSearch;
	BOOL  bFinished = false;
//	hSearch = FindFirstFile("C:\\test\\*.*", &FileData);
	hSearch = FindFirstFile("d:\\*.*", &FileData);

	if(hSearch == INVALID_HANDLE_VALUE)
	{ 
		cout << "Can't find any file!" << endl;
		return 0;
	}
    cout << FileData.cFileName << endl;

	while(!bFinished)
	{
		if(!FindNextFile(hSearch, &FileData))
		{
			cout << "No more file!" << endl;
			return 0;
		}
		cout << FileData.cFileName << endl;
	}

	return 0;
}

//��������CSDN���ͣ�ת�������������file:///N:/��ҳ/��ȡĳĿ¼���ļ����ĳ���%20-%20�����ǻ������ڰ���%20-%20CSDN����.htm