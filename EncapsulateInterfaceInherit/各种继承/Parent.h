#include <iostream>
class Parent {
public:
	Parent(int var = -1)
	{
		pub = var;
		ptd = var;
		prt = var;
	}
public:
	int pub;
protected:
	int ptd;
private:
	int prt;
};

class Child1: public Parent {
public:
	int Getpub() { return pub; }
    int Getptd() { return ptd; }
	// ��������������ú���
	int Getptd2() { ptd++; std::cout << ptd; return ptd; }
//	int Getprt() { return prt; } // ����prtΪ����˽�г�Ա�����಻�ɷ���
};
class Child2: protected Parent {
public:
	int Getpub() { return pub; }
	int Getptd() { return ptd; }
//	int Getprt() { return prt; } // ����prtΪ����˽�г�Ա�����಻�ɷ���
};

class Child3: private Parent {
public:
	int Getpub() { return pub; }
	int Getptd() { return ptd; }
//	int Getprt() { return prt; } // ����prtΪ����˽�г�Ա�����಻�ɷ���
};
