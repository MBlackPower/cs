def readfile1() :
    filename = raw_input('Enter file name:')
    file = open(filename, 'r')
    allline = file.readlines()
    file.close()
    for eachline in allline:
        print eachline

def readfile2() :
    """
    �ļ����� ���Է�����ͨ�Ĵ����ļ��������Է��ʷ��ϡ��ļ������������������͵��豸
    �����ļ�ʱʹ��open()�ڽ��������ļ���������һ���ļ���������ļ������ṩ�˲����ļ���д�ķ���
    open()������filename���ļ����ļ����ƣ���a+�����ļ�����ķ��ʷ�ʽ����ʾ�Զ���д��ʽ�򿪣�
    �ļ����� read()�������ֽ�ֱ�Ӷ���һ���ַ�������ݲ���������ȡ����
    �ļ���� write()����
    �ر��ļ���� close() ���һ���ļ������������������Ϊ�㣬Python�ķ�����������Ҳ���Զ��ر�����ļ�
    �ļ�����ķ��ʷ�ʽ
    r �Զ��ķ�ʽ��
    w ��д�ķ�ʽ��
    a ��д�ķ�ʽ�򿪣���EOF��ʼ���ļ�������ʱ���ȴ����ļ�
    r+ �Զ���д�ķ�ʽ��
    w+ �Զ���д�ķ�ʽ��
    a+ �Զ���д�ķ�ʽ��
    rb �Զ����ƶ���ʽ��
    wb �Զ�����д��ʽ��
    ab �Զ�����׷�ӷ�ʽ��
    rb+ �Զ����ƶ���д��ʽ��
    wb+ �Զ����ƶ���д��ʽ��
    ab+ �Զ����ƶ���д��ʽ��
    """
    filename = raw_input('enter file name:')
    readsize = 100
    done = 0
    file = open(filename, 'a+')
    while not done :
        readdata = file.read(readsize)
        if readdata != "":
            #print readdata
            print file.tell()
        else :
            done = 1
    file.close()

if __name__ == "__main__":
    readfile2()
