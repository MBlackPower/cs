#include 
#include 
#include 
#include 

int main(int argc,char *argv[])
{
	int listensock,//��������socket�׽��֣�һ���׽������ڼ�����
		connsock; //һ���׽�������ͨѶ

	struct sockaddr_in serveraddr; //���������׽��ֵ�ַ�ṹ

	const char buff[] = "Hello! Welcome here!\r\n"; //����Ҫ���͵����ݻ�����

	//����һ������ͨѶ���׽ӿ�
	listensock = socket(AF_INET,SOCK_STREAM,0); //����һ���׽��֣����ڼ��� 
	//END

	//������׽ӿ��趨�˿�
	bzero(&serveraddr,sizeof(servaddr)); //��ַ�ṹ���� 

	serveraddr.sin_family = AF_INET; //ָ��ʹ�õ�ͨѶЭ����

	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //ָ�������κ����ӣ���Ϊ��������֪��˭��Ҫ������ 

	serveraddr.sin_port = htons(5000); //ָ�������Ķ˿�

	bind(listensock,(sockaddr *)&serveraddr,sizeof(serveraddr)); //���׽ӿڰ��ַ 
	//END

	//ʹ����׽ӿڳ�Ϊһ�������׽���
	listen(listensock,1024); //��ʼ���� 
	//END

	//��������׽��֣���ʱ��ĳ���Ϳ��Եȴ��ͻ��˵�������
	connsock = accept(listensock,(sockaddr *)NULL, NULL); //����ͨѶ���׽��֣�accept�������ȴ��ͻ��˳���ʹ��connect����������
	//END

	//����ͻ��˵���������
	send(connsock,buff,sizeof(buff), 0); //��ͻ��˷������� 
	//END

	//��ֹ����
	close(connsock); //�ر�ͨѶ�׽��� 

	close(listensock); //�رռ����׽���
	//END
}
