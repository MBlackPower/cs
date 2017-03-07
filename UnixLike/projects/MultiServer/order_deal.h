///ί�е�, �ɽ����������ݽṹ����
/**
  *Դ��������:  order_deal.h
  *ϵͳ����:  NEEQ1.0 ���״�������������������������
  *ģ������:  ί�е�,�ɽ��������ṹ
  *����˵��:  ����ί�е�, �ɽ����������ݽṹ
  *��    ��:  yuxw 
  *��������: 20130815
  *�޸ļ�¼��
*/

#ifndef _ORDER_DEAL_H_
#define _ORDER_DEAL_H_
#include <stdint.h>

#pragma pack(1)

typedef struct{   
    uint32_t   BrokerNo;            // ���׵�Ԫ 
    uint32_t   OrderDate;           // ί������ 
    char       OrderNo[8];          // ί����ˮ�� 
    uint32_t   CompanyNo;           // ֤ȯ���� 
    char       AccountNo[10];       // ֤ȯ�ʺ� 
    uint32_t   OrderHands;          // ί������ 
    uint32_t   Price;               // ί�м۸� 
    char       FunctionCode;        // ������ 
    char       OrderKind;           // ҵ����� 
    uint32_t   OrderTime;           // ί��ʱ�� 
    uint16_t   UserNo;              // used for breakpoint resume 
    uint32_t   MatchBrokerNo;       // �Է����׵�Ԫ 
    char       MatchAccountNo[10];  // �Է�֤ȯ�ʺ� 
    uint32_t   OrderHands2;         // ί������2
    uint32_t   Price2;              // ί�м۸�2 
    char       CreditFlag;          // ������ȯ��ʶ
    char       PositioinFlag;       // ƽ�ֱ�ʶ 
    uint32_t   DealAgreedNo;        // �ɽ�Լ���� 
    //uint32_t   IntentDeclareNo;     // �����걨�� 20131115 xuzj �������½ӿ��ĵ�ɾ��
    char       Contact[12];         // ��ϵ�� 20131015 ���������ʼ����� ��C20��ΪC12
    char       ContactInfo[30];     // ��ϵ��ʽ  20131015 ���������ʼ����� ��C50��ΪC30
    char       GatewayNo[11];       // ����Сվ�� 
}ORDER_T;

typedef struct 
{
    uint32_t  DealNo;               // �ɽ����
    uint32_t  BuyBrokerNo;          // �򷽽��׵�Ԫ
    uint32_t  BuyOrderYmd;          // ��ί������
    char      BuyOrderNo[8];        // ��ί����ˮ��
    uint32_t  SellBrokerNo;         // �������׵�Ԫ
    uint32_t  SellOrderYmd;         // ����ί������
    char      SellOrderNo[8];       // ����ί����ˮ��
    uint32_t  CompanyNo;            // ֤ȯ����
    int32_t   MatchHands;           // �ɽ�����
    int32_t   MatchHands2;          // �ɽ�����2
    uint32_t  Price;                // �ɽ��۸� 
    uint32_t  Time;                 // �ɽ�ʱ�� 
    uint32_t  Ymd;                  // �ɽ�����
    char      FunctionCode;         // ������
    char      OrderKind;            // ҵ�����
    char      BuyAccountNo[10];     // ��֤ȯ�ʺ�
    char      SellAccountNo[10];    // ����֤ȯ�ʺ�
    char      BuyCreditFlag;        // ��������ȯ��ʶ
    char      BuyPositioinFlag;     // ��ƽ�ֱ�ʶ
    char      SellCreditFlag;       // ����������ȯ��ʶ
	char      SellPositioinFlag;	// ����ƽ�ֱ�ʶ
}ORDER_DEAL_T;

#pragma pack()

#endif
