#ifndef CARRAYRC_SUNYONGJIE_20101204
#define CARRAYRC_SUNYONGJIE_20101204
#include "CArray.h"
template <class elemType>
class CArrayRC: public CArray<elemType> {
public:
	CArrayRC(int sz = CArray<elemType>::DefaultArraySize): CArray<elemType>(sz)
	{

	}
	CArrayRC(elemType* ia, int sz): CArray<elemType>(ia, sz)
	{

	}
	CArrayRC(const CArray& rhs): CArray<elemType>(rhs)
	{

	}
	virtual elemType& operator[](int index) // ��������ﶨ�Ͼ�û�����˰ɣ����Ǻͻ����һ��ô
	{
		assert((index >= 0) && (index < CArray<elemType>::size()));
		return ia[index];
	}
};
#endif