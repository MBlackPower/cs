int main(int argc,char **argv) 
{ 
	char recvbuff[100]; //����Ҫ���յ����ݻ�����

	int sockfd;//����һ��socket�׽��֣�����ͨѶ

	struct sockaddr_in serveraddr; //���������׽��ֵ�ַ�ṹ

	if(argc != 2)
	{
		printf("Usage: echo ip��ַ");
		exit(0);
	}

	//����һ������ͨѶ���׽ӿ�
	sockfd = socket(AF_INET,SOCK_STREAM,0); //����һ���׽���
	//END

	//ͨ�������׽ӿڵ�ַ�ṹ������˵�����ͻ���Ҫ��֮ͨѶ�ķ�������IP��ַ�Ͷ˿�.
	bzero(&serveraddr,sizeof(serveraddr));

	serveraddr.sin_family = AF_INET; //ָ��ʹ�õ�ͨѶЭ����

	serveraddr.sin_port = htons(5000);//ָ��Ҫ���ӵķ������Ķ˿�

	inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);
	//END

	//����connect���������ӷ�����
	connect(sockfd,(sockaddr *)&serveraddr,sizeof(serveraddr)); //���ӷ�����
	//END

	//���ͻ��߽������ݣ�һ��ʹ��send��recv����������ʵ��
	recv(sockfd,recvbuff,sizeof(recvbuff),0); //���շ�����������

	printf("%s\n",recvbuff); //��ӡ���յ�������
	//END

	//��ֹ����
	close(sockfd); //�ر��׽���
	//END
}
