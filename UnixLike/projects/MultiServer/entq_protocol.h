//����ί���Ŷӻ��ͽ��״������֮���ҵ��Э��ӿ�
/**
 *Դ��������:entq_protocol.h
 *ϵͳ����:NEEQ1.0 ί���Ŷӻ������״������
 *ģ������:��Ҫ����ж���
 *����˵��:����ί���Ŷӻ��ͽ��״������֮���ҵ��Э��ӿ�
 *��    ��: ��־��
 *��������: 20130702
 *�޸ļ�¼��
 *20140201  *****
 */
 
#ifndef _ENTQ_PROTOCOL_H_
#define _ENTQ_PROTOCOL_H_

#include "config_env.h"

#include "order_deal.h"

#pragma pack(1)

///ί�нṹ
typedef struct {
    ///ί������ �˴�Ϊ0
    uint32_t   OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC */
    uint32_t   TimeStamp;

	///��Ӧ����ͨί�нṹ
	ORDER_T entcommEntrust;
} ENTQ_OUT_ENTRUST;

///���׽׶�ʱ�����ָ��
typedef struct {
    ///ί������
    /**  ��0����ʾΪָ�
	 *   1: ����
	 *   3�����羺������
     *   4�����羺�ۿ�ʼ
     *   8���̺�ָ�ʼ
	 *   9��ȫ�����
     *   40��ʱ��Ƭָ��
     */
    uint32_t   OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC*/
    uint32_t   TimeStamp;
    ///���ģʽ ��'0'
    char	   MatchType;
} TIMER_ORDER;

///֤ȯͣ����ָ��
typedef struct {
    ///ί������
    /**  ��0����ʾΪָ��
     *   600060��֤ȯ��ʱͣ��
     *   600061��֤ȯ����
     */
    uint32_t   OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///ָ����ˮ��
    uint32_t   OrderNo; 
    ///֤ȯ����
    uint32_t   StockCode; 
	///ͣ��״̬ F:������ת�á�T:��ͣ�ƣ�������ת���걨��H:��ͣ�ƣ�����ת���걨��
	char     StopType;
	///ͣ������ 1:��ͣ��һСʱ��2:��ͣ�ư��족3:��ͣ��һ�족4:������ͣ�ơ�
	char     StopTimeType;
} STOP_ORDER;

///֤ȯ�˻�����ά��ָ��
typedef struct {
    ///ί������
    /**  ��0����ʾΪָ��
     *  600050��֤ȯ�˻�����ά��
     */
    uint32_t   OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///ָ����ˮ��
    uint32_t   OrderNo; 
    ///֤ȯ�ʺ�
    char       StockAccount[11];
	/// �˻���� 1-��A�ɡ���2-��B�ɡ�
	char    HolderType;
    /// �˻�����
    char    HolderAttr;
	///�˻����� 
	char    AccountProp[3];
	///֤ȯ�˻�״̬ 1-����������2-�����ϸ񡱡�9-��ͣ�á�
	char    HolderStatus;
} HOLDER_EMERGENCY_ORDER;

///֤ȯ�˻��������ƽ���ά��ָ��
typedef struct {
    ///ί������
    /**  ��0����ʾΪָ��
     *   600051��֤ȯ�˻��������ƽ���ά��
     */
    uint32_t   OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///ָ����ˮ��
    uint32_t   OrderNo; 
	///���׵�Ԫ
	uint32_t   UnitNo;
	///֤ȯ����
	uint32_t   StockCode;
	///����ҵ�����
	char       EnTradeType[128];
	///֤ȯ�˻�
	char       StockAccount[11];
	///�������� 0���ӣ�1�޸ģ�2ɾ��
	char       ActionIn;
	///֤ȯ���
	char       StockType[3];
	///���׵�Ԫ���� 1-������ҵ�񡱡�2-������ҵ�񡱡�3-����Ӫҵ�񡱡�4-��������
	char       UnitType;
	///������� 0��ͨ 1���
	char       SystemType;
	///�����־ 0��ֹ��1����
	char	   AllowFlag;
	///������Դ
	char       LimitSource;
} HOLDER_LIMIT_ORDER;

///֤ȯ���ײ�������ά��ָ��
typedef struct {
    ///ί������
    /**  ��0����ʾΪָ��
     *  600052��֤ȯ���ײ�������ά��
     */
    uint32_t   	OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t   	TimeStamp;
    ///ָ����ˮ��
    uint32_t    OrderNo; 
    ///֤ȯ����
    uint32_t   	StockCode; 
    ///ǰ���̼ۣ��壩
    uint32_t   	ClosePrice;
	///��ͣ�۸��壩
	uint32_t   	UpPrice;
	///��ͣ�۸��壩
	uint32_t	DownPrice;
	///�����ͣ�۸��壩
	uint32_t    BigUpPrice;
	///����ͣ�۸��壩
	uint32_t	BigDownPrice;
} STOCK_EMERGENCY_ORDER;

///֤ȯҵ��������ά��ָ��
typedef struct {
    ///ί������  ��0����ʾΪָ��
    /**
     *  600053��֤ȯҵ��������ά��
     */
    uint32_t   OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///ָ����ˮ��
    uint32_t   OrderNo; 
	///֤ȯ����
	uint32_t   StockCode;
	///�������� 0���ӣ�1�޸ģ�2ɾ��
	char       ActionIn;
	///������� 0��ͨ 1���
	char       SystemType;
	///����ҵ�����
	char       EnTradeType[128];
} STOCK_LIMIT_ORDER;

///��Ѻʽ�ع�ծȯ����ά��ָ��
typedef struct {
    ///ί������  ��0����ʾΪָ��
    /**
     *   600054����Ѻʽ�ع�ծȯ����ά��
     */
    uint32_t   OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///ָ����ˮ��
    uint32_t   OrderNo; 
    ///֤ȯ����
    uint32_t   StockCode;
    ///��׼ȯ���� 
    uint32_t   Standard;
    ///������
    uint32_t   BondRate;
} BONDRATE_ORDER;

///���׵�Ԫ�������ƽ���ά��ָ��
typedef struct {
    ///ί������  ��0����ʾΪָ��
    /**
     *   600055�����׵�Ԫ�������ƽ���ά��
     */
    uint32_t    OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t    TimeStamp;
    ///ָ����ˮ��
    uint32_t   OrderNo; 
	///���׵�Ԫ
	uint32_t    UnitNo;
	///֤ȯ����
	uint32_t    StockCode;
	///����ҵ�����
	char       EnTradeType[128];
	///֤ȯ���
	char       StockType[3];
	///�������� 0���ӣ�1�޸ģ�2ɾ��
	char       ActionIn;
	///������� 0��ͨ 1���
	char       SystemType;
	///�����־ 0��ֹ��1����
	char	   AllowFlag;
	///������Դ
	char        LimitSource;
} BROKERNO_LIMIT_ORDER;

///�ֹ�����,��ʱͣ��ָ��
typedef struct {
    ///ί������  ��0����ʾΪָ��
    /**
     *   600098: �ֹ�����ָ��
     *   600099����ʱͣ��ָ��
     */
    uint32_t    OrderType;
    ///���Ŷӻ����ʱ��� /* TIME-8, HHMMSSCC
    uint32_t    TimeStamp;
    ///ָ����ˮ��
    uint32_t   OrderNo; 
} TEMP_CLOSE_ORDER;


struct ACD_ORDER  // ί�е������ڴ��е�ί�е�
{
	///ί��ָ�����Ͻṹ�����ڽ����鲥��ȡ����
	union
	{
		///ί��
		ENTQ_OUT_ENTRUST		Entrust;
		///���׽׶�ʱ�����ָ��
		TIMER_ORDER			TimerOrder;
		///֤ȯͣ����ָ��
		STOP_ORDER			StopOrder;
		///֤ȯ�˻�����ά��ָ��
		HOLDER_EMERGENCY_ORDER	HolderEmergencyOrder;
		///֤ȯ�˻��������ƽ���ά��ָ��
		HOLDER_LIMIT_ORDER		HolderLimitOrder;
		///֤ȯ���ײ�������ά��ָ��
		STOCK_EMERGENCY_ORDER	StockEmergencyOrder;
		///֤ȯҵ��������ά��ָ��
		STOCK_LIMIT_ORDER		StockLimitOrder;
		///��Ѻʽ�ع�ծȯ����ά��ָ��
		BONDRATE_ORDER			BondRateOrder;
		///���׵�Ԫ�������ƽ���ά��ָ��
		BROKERNO_LIMIT_ORDER	BrokerNoLimitOrder;
		///�ֹ�����,��ʱͣ��ָ��
		TEMP_CLOSE_ORDER       TempCloseOrder;
	};
	unsigned char   LinkId;         // ����ID
	bool            LastOrder;      // ί�а��е�����ί�е���FALSE:��TRUE:��
	bool            ConfirmStatus;  // ����ȷ�ϱ�־��FALSE:δȷ�ϣ�TRUE:ȷ��
};

#pragma pack()
#endif /* _ENTQ_PROTOCOL_H_ */
