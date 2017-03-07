#include <iostream>
#include "isll.h"
isll::isll(int n)
{
    head = new islln;
    islln* p1 = head;
    cout << "������� 1���ڵ��ֵ" << endl;
    cin >> head->info;
    for (int i = 0; i < n - 1; i++)
    {
        islln* p2 = new islln;
        cout << "������� "<< i + 2 << "���ڵ��ֵ" << endl;
        cin >> p2->info;
        p1->next = p2;
        p1 = p2;
    }
    tail = p1;
    tail->next = NULL;
}
isll::~isll()
{
    for (islln* p; !isEmpty(); )
    {
        p = head->next;
        delete head;
        head = p;
    }
}
// {
//     islln* p = head;
//     while (0 != p)
//     {
//         delete p;
//     }
// }
void isll::addToHead(int el)
{
    head = new islln(el, head);
    if (tail == 0)
    {
        tail = head;
    }
}
void isll::addToTail(int el)
{
    if (tail != 0)
    {
        tail->next = new islln(el);
        tail = tail->next;
    }
    else
    {
        head = tail = new islln(el);
    }
}
bool isll::deleteFromHead()
{
    bool bFlag; // use one flay to get rid of the multi-return statement
    if (isEmpty())
    {
        bFlag = 0;
    }
    else
    {
        int el = head->info;
        islln* tmp = head;
        if (head == tail) // only one node
        {
            head = tail = 0;
        }
        else
        {
            head = head->next;
        }
        delete tmp; // if tmp = 0, no dangerous to delete a NULL pointer
                    // if tmp != 0, it is a normal ok
        bFlag = 1;
    }
    return bFlag;
}
bool isll::deleteFromTail()
{
    bool bFlag;
    if (isEmpty())
    {
        bFlag = 0;
    }
    else
    {
        int el = tail->info;
        if (head == tail) // only one node
        {
            delete head;
            head = tail = 0;
        }
        else
        {
            islln* tmp;
            for (tmp = head; tmp->next != tail; tmp = tmp->next);
            delete tail;
            tail = tmp;
            tail->next = 0;
        }
        bFlag = 1;
    }
    return bFlag;
}
bool isll::deleteNode(int el)
{
    bool bFlag = 0;
    if (!isEmpty())
    {
        if (head == tail && el == head->info)
        {
            delete head;
            head = tail = 0;
        }
        else if (el == head->info)
        {
            islln* tmp = head;
            head = head->next;
            delete tmp;
        }
        else
        {
            islln* pred;
            islln* tmp;
            for (pred = head, tmp = head->next; tmp != 0 && !(tmp->info == el);pred = pred->next, tmp = tmp->next);
            if (tmp != 0)
            {
                pred->next = tmp->next;
                if (tmp == tail)
                {
                    tail = pred;
                }
                delete tmp;
            }
        }
        bFlag = 1;
    }
    return bFlag;
}
bool isll::isInList(int el) const
{
    islln* tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}
/*
   ostream& operator<<(ostream& os, isll& object) // �����ˣ������Ұ�head��tailŪ��public��
   {                                                   // �Ҽ�һ����Ա������������ͷָ�벻�ͺ���
   for (islln* p = object.head; p != NULL; p = p->next) // ���Կ����Ǻ�
   {
   os << p->info << " ";
   }
   return os;
   }
 */
ostream& operator<<(ostream& os, const isll& object)
{
	    for (islln* p = object.getHead(); p != NULL; p = p->next)
    {
        os << p->info << " ";
    }
    return os;
}
// ������������ǿ������ˣ�������ɾ��һЩ����������   // ������head,tail��public������µ�
/*istream& operator>>(istream& is, isll& object) // �ҵ���������кܶ�ĵط�Ҫ�ģ���ֱ
  {                                                     // �����ĵط��١�
  object.head = new islln;
  cin >> object.head->info;
  islln* p1 = object.head;
  int x;
  while (std::cin >> x) // ���λ����ǰ����ĸ��������ʱ��������
  {                     // ����û���ˣ���������Ϊ�ڵ�Ĺ��캯��ÿ����һ����ʱ����ָ����ֵ0�ġ�
  islln* p2 = new islln;
  p2->info = x;
  p1->next = p2;
  p1 = p2;
  }
// object.tail = p1; // Ϊʲôע�������Ҳ���ԣ���Ҫ�����ҵ������
return is;        // �ҵ���������غ�������û���õ�tail
}*/
/*
// ���������head,tail,private��ʱ��
istream& operator>>(istream& is, isll& object)
{
islln* h = object.getHead();
//	islln* t = object.getTail(); ����ô��Ҫ������ô��
islln* p1 = h;
p1 = new islln; // �����ķǳ����أ���ϸ����һ�¡�
std::cin >> h->info;
int x;
while (std::cin >> x)
{
islln* p2 = new islln;
p2->info = x;
p1->next = p2;
p1 = p2;
}
p1->next = 0;
return is;
}*/
istream& operator>>(istream& is, isll& object)
{
    islln* h = new islln;
    object.setHead(h);
    std::cin >> h->info;
    int x;
    while (std::cin >> x)
    {
        islln* p2 = new islln;
        p2->info = x;
        h->next = p2;
        h = p2;
    }
    object.setTail(h);
    return is;
}
