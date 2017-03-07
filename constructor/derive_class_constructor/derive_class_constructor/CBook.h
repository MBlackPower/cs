#include <string>
#include <iostream>
class CBook {
public:
	CBook(): isbn("sunyongjie"), count(0)
	{
		std::cout << "CBook default constructor" << std::endl;	
	}
	CBook(std::string s): isbn(s), count(0)
	{
		std::cout << "CBook constructor 2" << std::endl;	
	}
	CBook(std::string& s): isbn(s), count(0)
	{
		std::cout << "CBook constructor 3" << std::endl;	
	}
	CBook(std::string& s, int c): isbn(s), count(c)
	{
		std::cout << "CBook constructor 4" << std::endl;	
	}
	friend std::ostream& operator<<(std::ostream& os, const CBook& book)
	{
		os << "isbn: " <<  book.isbn << "\t\tcount: " << book.count/*<< std::endl*/; // ����������ʱ���ֻ�ṩ������������ﲻҪ���������Ķ�����
		return os;
	}
	virtual void print(std::ostream& os)
	{   // ����������ʱ���ֻ�ṩ������������ﲻҪ���������Ķ�����
		os << "isbn: " <<  isbn << "\t\tcount: " << count<< std::endl; 
	}
	void print2(std::ostream& os) // print2����Ϊ���麯�������õ���������Ӧ���ǳ�ֿ��ǵ���
	{	// û���������д����������ٸ����ӣ�Ҳ����˵CBookOnSale��ò�Ҫȥ��д���������						  
		os << "isbn: " <<  isbn << "\t\tcount: " << count<< std::endl; 
	}
//private: // ��Ȼ�����಻�ܷ�����
protected:
	std::string isbn;
	int count;
};

class CBookOnSale: public CBook {
public:
	//CBookOnSale()
	//{
	//	std::cout << "CBookOnSale default constructor" << std::endl;
	//}

    // ���캯�������ñȽϺã��û����ʼ�������Ա���Լ���ʼ���Լ��ĳ�Ա��												  
	CBookOnSale(std::string& s, int c, double d = 23.23): CBook(s, c), price(d)
	{
		std::cout << "CBookOnSale constructor" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& os, const CBookOnSale& book)
	{
		os << "isbn: " <<  book.isbn << "\t\tcount: " << book.count << "\t\tprice: " << book.price/*<< std::endl*/; 
		return os;
	}
	CBookOnSale(char* p)
	{
		isbn = p;
	}
	CBookOnSale(int c, double d)
	{
		count = c;
		price = d;
	}
	void print(std::ostream& os)
	{
		os << "isbn: " << isbn << "\t\tcount: " << count << "\t\tprice: " << price << std::endl; 
	}
	void print2(std::ostream& os)
	{
		os << "isbn: " << isbn << "\t\tcount: " << count << "\t\tprice: " << price << std::endl; 
	}
private:
	double price;
};