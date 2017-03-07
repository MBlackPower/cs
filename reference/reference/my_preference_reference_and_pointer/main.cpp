int main()
{
    // modify start for coding rule and style
    // the following way of comment is good
    /* ������*& const    ������  meaning
     * int*     const    p       // ok��p��const���������޸�p��ֵ�����ı�ָ�����p��ָ��
     * int&     const    r       // bad��r��һ�����ã�����ʱ��ʼ��������һ�ˣ�qualifier const is ignored
     *                           // ���const������
     *
     * const    ������*& ������   ˵��
     * const    int*     p        // ok��������ͨ��p��ȥ�޸�pָ��Ķ���
     * const    int&     r        // ok��������ͨ��r��ȥ�޸�r�󶨵Ķ���
     */
    int i = 10;
    int* const pp1 = &i;      // pp1Ϊconst���󣬲������޸�pp1��ֵ�����ı�pp1��ָ��
#ifndef SUNYJ_UNIXLIKE
    int& const rr1 = i;       // ignored��������(in windows visual 2012), error in linux

    rr1 = 10;
#endif

    const int* pp2 = &i;
    const int& rr2 = i;

    // *pp2 = 10;              // error
    // rr2  = 10;              // error

                               // �����������ķ�����������ǰ�����������ͣ�������������const����
    int a = 10;                // ���Ͷ���aΪnon-const
    int const b = 20;          // ���Ͷ���bΪconst
    int const c = 20;          // ���Ͷ���cΪconst
    int* p = &a;              // ָ��non-const���ζ����ָ�����pΪnon-const
                               // ����Ա����ͨ��p�޸�a������Ա�����޸�p
    const int* p2 = &a;       // ָ��non-const����const���Ͷ����ָ�����p2Ϊnon-const
                               // ����Ա������Ҳ������ͨ��p2�޸�a������Ա�����޸�p2
    const int* p3 = &b;       // ָ��non-const����const���Ͷ����ָ�����p3Ϊnon-const
                               // ����Ա������Ҳ������ͨ��p3�޸�b������Ա�����޸�p3
    int* const p4 = &a;       // ָ��non-const���ζ����ָ�����p4Ϊconst
                               // ����Ա����ͨ��p4�޸�a������Ա������Ҳ�������޸�p4
    const int* const p5 = &a; // ָ��non-const����const���Ͷ����ָ�����p5Ϊconst
                               // ����Ա������Ҳ������ͨ��p5�޸�a������Ա������Ҳ�������޸�p5 
    const int* const p6 = &b; // ָ��non-const����const���Ͷ����ָ�����p6Ϊconst
                               // ����Ա������Ҳ������ͨ��p6�޸�b������Ա������Ҳ�������޸�p6 
    int& r = a;               // �󶨵�non-const���Ͷ�������ö���rΪnon-const
                               // ����Ա����ͨ��r�޸�a
    const int& r2 = a;        // �󶨵�non-const����const���Ͷ�������ö���r2Ϊconst
                               // ����Ա������Ҳ������ͨ��r2�޸�a
    const int& r3 = b;        // �󶨵�non-const����const���Ͷ�������ö���r3Ϊconst
                               // ����Ա������Ҳ������ͨ��r3�޸�b
    // add start for testing the above definition
    *p = 10;                   // ok��ͨ��p�޸�a
    ++p;                       // ok���޸�p��ֵ���Ըı�ָ������ָ��

    // *p2 = 10;               // error��������ͨ��p2�޸�a��������ΪaΪconst��������Ϊp2�Ķ���
    ++p2;                      // ok���޸�p2��ֵ���Ըı�ָ������ָ��

    // *p3 = 10;               // error��������ͨ��p3�޸�a��������ΪbΪconst��������Ϊp3�Ķ���
    ++p3;                      // ok���޸�p3��ֵ���Ըı�ָ������ָ��

    *p4 = 10;                  // ok��ͨ��p4�޸�a
    // ++p4;                   // error���޸�p4��ֵ����Ϊ����p4Ϊconst

    // *p5 = 10;               // error��ͨ��p5�޸�a
    // ++p5;                   // error���޸�p5��ֵ���Ըı�ָ������ָ��

    // *p6 = 10;               // error��ͨ��p6�޸�a
    // ++p6;                   // error���޸�p6��ֵ���Ըı�ָ������ָ��
    // add end for testing the above definition
    // 2011_12_01_syj


    // int* p7 = &b;          // cannot convert from 'const int *' to 'int *'
                              // ����b����Ϊconst int������&b����Ϊconst int*������p7����Ϊint*
                              // ����Ա����ͨ��p7�޸Ķ���b��������b����Ϊconst int�����Գ���
    // int& r6 = b;           // cannot convert from 'const int' to 'int &'
                              // ����r6����Ϊint&, ����b����Ϊconst int
                              // ����Ա����ͨ��r6�޸�b��������b����Ϊconst int�����Գ���
    // int& const r7 = b;     // ����Ķ��巽ʽ
    // modify end for coding rule and style
    // 2011_12_01_syj
}
