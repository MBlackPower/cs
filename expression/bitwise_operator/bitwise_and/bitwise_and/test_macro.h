/////////////////////////////////////////////////////////////////////////////
#define WM_USER_NOTIFY           (WM_APP+1)
#define WM_USER_PUSH             (WM_APP+2)
#define WM_USER_COMMAND          (WM_APP+3)
#define WM_USER_GETMODALDATA     (WM_APP+4)
#define WM_USER_BROADCAST        (WM_APP+5)
#define WM_USER_MODULE           (WM_APP+16)    //ģ���Ӧ��
/////////////////////////////////////////////////////////////////////////////
//WM_USER_MODULE
#define MODULE_WP_GETGLOBALS     1              //ȡ���ñ���
#define MODULE_WP_SETLOGINNOTIFY 2              //���ʺŵ�¼��ʾ
#define MODULE_WP_ENABLEACCEL    3              //��ݼ�״̬
#define MODULE_WP_SETACCEL       4              //���ÿ�ݼ�
#define MODULE_WP_ALLOCATESESS   5              //AllocateSess
#define MODULE_WP_RELEASESESS    6              //ReleaseSess
/////////////////////////////////////////////////////////////////////////////
//MODULE_WP_GETGLOBALS
#define G_PCOMM                  0              //g_pComm
#define G_NWTFS                  1              //g_nWtfs
#define G_LREVISETIME_HI         2              //g_lReviseTime high
#define G_LREVISETIME_LO         3              //g_lReviseTime low
#define G_NSYSFUNSOPTION         4              //g_nSysFunsOption
#define G_STRSVRNAME             5              //g_strSvrName
#define G_NACTIVERECNO           6              //g_nActiveRecno
#define G_NMASTERRECNO           7              //g_nMasterRecno
#define G_STRNODE                8              //g_strNode
#define G_STRNODEEX              9              //g_strNodeEx

#define G_RECJYS                 10             //g_recJys
#define G_RECZQLB                11             //g_recZqlb
#define G_RECMONEY               12             //g_recMoney
#define G_RECXTDM                13             //g_recXtdm
#define G_RECHYHQ                14             //g_recHyhq
#define G_RECJGDM                15             //g_recJgdm
#define G_RECYHCS                16             //g_recYhcs
#define G_RECJYSTLDM             17             //g_recJysTldm
#define G_RECJYSTLHY             18             //g_recJysTlhy
#define G_RECSUBSCIBEHYDM        19             //g_recSubscibeHydm

#define G_RECKHH                 30             //g_recKhh
#define G_RECJYBM                31             //g_recJybm
#define G_RECZJZH                32             //g_recZjzh
#define G_RECHYCC                33             //g_recHycc
#define G_RECHYMX                34             //g_recHymx
#define G_RECYHZH                35             //g_recYhzh
#define G_RECNOTIFY              36             //g_recNotify
#define G_RECPUSHMSG             37             //g_recPushMsg
#define G_RECXZKH                38             //g_recXzkh
#define G_RECFZXX                39             //g_recFzxx
#define G_RECFZKH                40             //g_recFzkh
#define G_RECYYWT                41             //g_recYywt
#define G_NSYSTEMFLAGS           50             //g_nSystemFlags
/////////////////////////////////////////////////////////////////////////////
//�ʺű�־
#define ACCFLAG_CHKJYMM          0x00000001     //����֤
#define ACCFLAG_JYMMJY           0x00000002     //��֤��������ͨ��
#define ACCFLAG_XGJYMM           0x00000004     //�ⲿ�޸Ľ�������
#define ACCFLAG_XGJYMM_FIRST     0x00000008     //�״ε�¼Ҫ�����޸Ľ�������

#define ACCFLAG_CHKZJMM          0x00000010     //����֤
#define ACCFLAG_ZJMMJY           0x00000020     //�ʽ�������֤��־
#define ACCFLAG_XGZJMM           0x00000040     //�ⲿ�޸��ʽ�����
#define ACCFLAG_XGZJMM_FIRST     0x00000080     //�״ε�¼Ҫ�����޸��ʽ�����

#define ACCFLAG_JSDQR            0x00000100     //��Ҫȷ�Ͻ��㵥
#define ACCFLAG_PUSHMSG          0x00000400     //��¼����
#define ACCFLAG_XGKHZL           0x00000800     //�޸Ŀͻ�����

#define ACCFLAG_CHECKSTAMP       0x00001000     //��֤����������
#define ACCFLAG_BINDSTAMP        0x00002000     //���԰󶨻���������
#define ACCFLAG_AUTHMSG          0x00004000     //��Ԥ������֤��Ϣ

#define ACCFLAG_CXJYBM           0x00010000     //��ѯ���ױ���
#define ACCFLAG_CXZJZH           0x00020000     //��ѯ�ʽ��ʺ�
#define ACCFLAG_CXJSZD           0x00040000     //��ѯ���㵥
#define ACCFLAG_CXYHZH           0x00080000     //��ѯ�����ʺ�
#define ACCFLAG_CXXZKH           0x00100000     //ȡ����С��
#define ACCFLAG_CXFZKH           0x00200000     //ȡ��������
#define ACCFLAG_NOTIFYMSG        0x00400000     //��ȡ��ʾ��Ϣ
#define ACCFLAG_UNREADMSG        0x00800000     //δ�Ķ���Ϣ
#define ACCFLAG_HYCCDM           0x01000000     //�ֲֺ�Լ�����б䶯
//�ͻ����
#define KHLB_MASTER              1              //�����ͻ�
#define KHLB_XZKH                2              //����С��ͻ�,ͨ��FID_XZBH����
#define KHLB_GLKH                3              //����ӿͻ�,ͨ��FID_KHJL����
//�ڲ����
#define MODIFY_HYDM              0x00000001     //��Լ�����޸�
#define MODIFY_JYLB              0x00000002     //��ƽ��־�޸�
#define MODIFY_MMLB              0x00000004     //������־�޸�
#define MODIFY_WTJG              0x00000008     //ί�м۸��޸�
#define MODIFY_WTSL              0x00000010     //ί�������޸�
#define MODIFY_JYBM              0x00000020     //�����ʺ��޸�
#define MODIFY_HYDM2             0x00000040     //��Լ�����޸�
#define MODIFY_JYLB2             0x00000080     //��ƽ��־�޸�
#define MODIFY_MMLB2             0x00000100     //������־�޸�
#define MODIFY_WTJG2             0x00000200     //ί�м۸��޸�
#define MODIFY_WTSL2             0x00000400     //ί�������޸�
#define MODIFY_JYBM2             0x00000800     //�����ʺ��޸�
#define USER_UPDATED_THREAD      0x10000000     //�߳�����״̬
#define USER_UPDATED_CANCEL      0x20000000     //��ֹ���
#define USER_UPDATED_RESET       0x40000000     //���ñ��

#define USER_FLAG_EXIT           USER_UPDATED_CANCEL
#define USER_FLAG_CANCEL         USER_UPDATED_CANCEL
#define USER_FLAG_THREAD         USER_UPDATED_THREAD
#define USER_FLAG_SHOWWINDOW     0x80000000
//�ڲ�֪ͨ
#define USER_NOTIFY_UPDATED      0x00000001     //���ݸ��±�־
#define USER_NOTIFY_DATAREADY    0x00000002     //��������Ready��־
#define USER_NOTIFY_GLXZKHDL     0x00000004     //����С��ͻ���¼
#define USER_NOTIFY_ACTIVEKHH    0x00000008     //�ͻ����л�
#define USER_NOTIFY_ZJXX         0x00000010     //�ʽ�䶯
#define USER_NOTIFY_FEXX         0x00000020     //�ݶ�
#define USER_NOTIFY_HYDMGX       0x00000040     //�������
#define USER_NOTIFY_TLDMGX       0x00000080     //���½�������������
#define USER_NOTIFY_PARAM        0x00000100     //�����޸�
#define USER_NOTIFY_XGKHZL       0x00000200     //�ͻ������޸�
#define USER_NOTIFY_GLXZGX       0x00000400     //�����ʺŲ�ѯ
//����ҵ��
#define USER_NOTIFY_WTCX         0x00001000     //ί�м�¼
#define USER_NOTIFY_CJHB         0x00002000     //�ɽ�����
#define USER_NOTIFY_QYZZ         0x00004000     //����ҵ��
#define USER_NOTIFY_YYWT         0x00008000     //ԤԼί��
#define USER_NOTIFY_HQCF         0x00010000     //�Զ���ί��
#define USER_NOTIFY_HYHQ         0x00020000     //����䶯
#define USER_NOTIFY_GLWT         0x00040000     //����ί��
#define USER_NOTIFY_PLWT         0x00080000     //����ί��
#define USER_NOTIFY_ZSZY         0x00100000     //ֹ��ֹӯί��
#define USER_NOTIFY_CJCF         0x00200000     //�ɽ�������
#define USER_NOTIFY_TLWT         0x00400000     //����������
#define USER_NOTIFY_SWAP         0x00800000     //�������״�����

#define USER_NOTIFY_WTJY         (USER_NOTIFY_WTCX|USER_NOTIFY_ZJXX|USER_NOTIFY_FEXX)
#define USER_NOTIFY_EXWTCX       (USER_NOTIFY_GLWT|USER_NOTIFY_PLWT|USER_NOTIFY_ZSZY|USER_NOTIFY_CJCF|USER_NOTIFY_TLWT|USER_NOTIFY_SWAP)
#define USER_NOTIFY_ZZDWT        USER_NOTIFY_HQCF

//������Ϣ LOWORD(WPARAM)
#define USER_PUSH_MESSAGE        1              //��Ϣ����
#define USER_PUSH_WTQR           2              //ί��ȷ��
#define USER_PUSH_CJHB           3              //�ɽ��ر�
#define USER_PUSH_NOTIFY         4              //ͨ����Ϣ
#define USER_PUSH_HYHQ           5              //�ڻ���������
//ί��ȷ����� !!��Ӧ�����������,���ɵ����޸�
#define WTQR_WTQR                1              //�걨�ɹ�
#define WTQR_SBSB                2              //�걨ʧ��
#define WTQR_CDQR                3              //����ȷ��
#define WTQR_CDSB                4              //����ʧ��
//������֪ͨ
#define COMMAND_NOTIFY           1              //����֪ͨ
#define COMMAND_UPGRADE          2              //������������
#define COMMAND_QUOTESUBSCIBE    3              //���붩��
#define COMMAND_SETACCELERATOR   4              //���¿�ݼ�
#define COMMAND_BZJJGZX          5              //��¼��֤����������ҳ
#define COMMAND_SETLAYERED       6              //���ô���͸����
#define COMMAND_XGMM             7              //�����޸�
#define COMMAND_CXHYDM           8              //��ѯ��Լ����
#define COMMAND_CXJYSTLDM        9              //��ѯ��������������
#define COMMAND_CXKHZL           10             //��ѯ�ͻ����� ������Ŀ��
#define COMMAND_TZHDLTS          11             //ͬ�ʺŵ�¼��ʾ
#define COMMAND_PUSH_DLTS        12             //ͬ�ʺŵ�¼��ʾ
#define COMMAND_SYSLOCK          13             //ϵͳ����

#define COMMAND_NOTIFY_USER      30             //֮��Ϊ֪ͨ��,������ת��

#define COMMAND_NOTIFY_ZJMMDL    30             //�ʽ������¼
#define COMMAND_NOTIFY_CXHYDM    31             //��ѯ��Լ����
#define COMMAND_NOTIFY_CXJYSTLDM 32             //��ѯ��������������
#define COMMAND_NOTIFY_CXKHZL    33             //��ѯ�ͻ����� ������Ŀ��
#define COMMAND_NOTIFY_CXGLXZ    34             //��ѯ����С��
#define COMMAND_NOTIFY_CXJYBM    35             //��ѯ���ױ���
#define COMMAND_NOTIFY_CXYHZH    36             //��ѯ�����ʺ�

#define COMMAND_USER             60             //֮��Ϊ�Զ����ģ��ʹ��

//��������
#define WEBCUSTOMMESSAGE_PT      11             //��ͨ��ʾ
#define WEBCUSTOMMESSAGE_ZJBZJ   12             //׷��������
#define WEBCUSTOMMESSAGE_QZPC    13             //ǿƽ��������ʾ
#define WEBCUSTOMMESSAGE_KHDL    14             //���û���¼��ʾ
#define WEBCUSTOMMESSAGE_XGMM    15             //����Ч������Ҫ��
#define WEBCUSTOMMESSAGE_FWXM    21             //�޸ķ�����Ŀ
//֪ͨ��Ϣ��־
#define MSGFLAG_READ             1              //���Ķ�
#define MSGFLAG_SAVE             2              //�ѱ���
#define MSGFLAG_RESPONSES        4              //��Ӧ
//��¼��֤���(�������)
#define CLIENT_TYPE_JYMM         1L             //��������
#define CLIENT_TYPE_ZJMM         2L             //�ʽ�����
//��������
#define DDLX_XJWT                1
#define DDLX_SJWT                2
#define DDLX_TLWT                4              //����������ָ��
#define DDLX_SWAP                8              //����������ָ��
#define DDLX_ZSZL                16             //������ֹ��ָ��
#define DDLX_ZYZL                32             //������ֹӯָ��
//�м�ί�б�־
#define SJWTBZ_XJWT              0              //�޼�ί��
#define SJWTBZ_ZDTSJ             1              //�ǵ�ͣ�м�
#define SJWTBZ_SJZL              2              //�м�ָ��
//ί�в�ѯ��������
#define WTCX_FLAG_QBCJ           1              //������ȫ���ɽ�
#define WTCX_FLAG_CXBZ           2              //�����ѳ���
#define WTCX_FLAG_WTFD           4              //���˷ϵ�
#define WTCX_FLAG_KZWT           8              //������չί�е�
//��Լ�����־����
#define QF_QUERY                 0x00000001     //�Ѳ�ѯ������
#define QF_ALTER                 0x00000002     //�䶯����δ����(��ֲֺͳɽ�������)
#define QF_ZXJ                   0x00000004     //���¼ۻ������䶯
#define QF_JYSTLDM               0x00000010     //��������������
#define QF_ZXHYDM                0x00000020     //��ѡ��Լ����

#define QF_MASK_SUBSCIBE         0x0000FF00
#define QF_FOCUS                 0x00000100     //��ע����
#define QF_CCDM                  0x00000200     //�ֲִ���
#define QF_ZHDM                  0x00000400     //��ϴ���
#define QF_JYK                   0x00000800     //���׿�
#define QF_YMWT                  0x00001000     //Ԥ��ί��
#define QF_SUBSCIBE              0x00002000     //���ı�־(��ʱ)

#define ZHHQ_JCXX_FLAG           0x00000001     //�۲�С�����ޱ�־
#define ZHHQ_JCSX_FLAG           0x00000002
#define ZHHQ_FLAG_MASK           0x0000000F
#define ZHHQ_JCXX_ALERT          0x00010000     //�۲�С�����������ѱ�־
#define ZHHQ_JCSX_ALERT          0x00020000
#define ZHHQ_ALERT_MASK          0x000F0000

#define QF_ZSZY                  0x00100000     //Ĭ������ֹ��ֹӯ
#define QF_ZSZY_SJWT             0x00200000     //ֹ��ֹӯƽ�ְ��ǵ�ͣί��

//������Ŀ
#define FWXM_HQCF                0x00000001     //���鴥������
#define FWXM_ZSZY                0x00000002     //ֹ��ֹӯ����
#define FWXM_CJCF                0x00000004     //�ɽ���������
#define FWXM_GLWT                0x00000008     //����ί�з���
#define FWXM_PLWT                0x00000010     //����ί�з���
#define FWXM_HQGL                0x00000020     //�������ί��
#define FWXM_YQZZ                0x00000040     //ǰ������ת��
#define FWXM_TLWT                0x00000080     //����ί�з���
#define FWXM_JYSTLWT             0x00000200     //����������ί��
#define FWXM_SWAP                0x00000400     //��������
#define FWXM_JYSSWAP             0x00000800     //����������ָ��
#define FWXM_CCZSZY              0x00001000     //�ֲ�ֹ��ֹӯ
#define FWXM_ZLSX                0x00002000     //ָ������
#define FWXM_JYSZSZY             0x00004000     //������ֹ��ֹӯ
#define FWXM_ZDDCS               0x00100000     //�Զ���
#define FWXM_YJFJY               0x00200000     //һ���ɽ���
#define FWXM_LSCX                0x00400000     //��ʷ��ѯ
//����ҵ�����
#define YQYWLB_YHTOQH            2
#define YQYWLB_QHTOYH            4
#define YQYWLB_YECX              128
//ί�е����
#define WTDLB_PTWT               0              //��ͨί�е�
#define WTDLB_ZDQP               1              //�Զ�ǿƽ��
#define WTDLB_HQCF               2              //���鴥����
#define WTDLB_ZSZY               3              //ֹ��ֹӯ��
#define WTDLB_CJCF               4              //�ɽ�������
#define WTDLB_GLWT               5              //����ί�е�
#define WTDLB_PLWT               6              //����ί�е�
#define WTDLB_TLWT               7              //����ί�е�
#define WTDLB_QZPC               8              //ǿ��ƽ��
#define WTDLB_SWAP               11             //�������״�����
#define WTDLB_CCZSZY             13             //�ֲ�ֹ��ֹӯ
//��������С���µ���ʽ
#define XDFS_JSXD                1              //�������µ�
#define XDFS_ZLXD                2              //�������µ�
//��չί��
#define KZWT_ITEM_HQCF        1     //���鴥����
#define KZWT_ITEM_ZSZY        2     //ֹ��ֹӯ��
#define KZWT_ITEM_CJCF        3     //�ɽ�������
#define KZWT_ITEM_TLWT        4     //����ί�е�
#define KZWT_ITEM_PLWT        5     //����ί��
#define KZWT_ITEM_GLWT        6     //����ί��
#define KZWT_ITEM_SWAP        7     //��������
#define KZWT_ITEM_ZHTL        8     //����ί�е�
//��������չҵ��
#define JYSYW_ITEM_TLWT       1     //����������ί��
#define JYSYW_ITEM_SWAP       2     //��������
#define JYSYW_ITEM_ZSZY       3     //ֹ��ֹӯ
//��չ����
#define KZFW_ITEM_YYQK        1     //ԤԼȡ��

//�ؼ�����
#define SORT_ITEM_VERT     1
#define SORT_ITEM_HORZ     2
#define SORT_TAB_ORDER     4
//����
#define ALIGN_TOP          1
#define ALIGN_BOTTOM       2
#define ALIGN_LEFT         3
#define ALIGN_RIGHT        4
//�ɶ�����
#define GDSX_TJ            16          //Ͷ��
#define GDSX_TB            32          //�ױ�
#define GDSX_TL            64          //����
//Ͷ�����
#define TZLB_TJ            0           //Ͷ��
#define TZLB_TB            1           //�ױ�
#define TZLB_TL            2           //����
//wav����
#define WAV_WTSB_SUCCESS   0           //ί�гɹ�
#define WAV_WTSB_FAIL      1           //ί��ʧ��
#define WAV_WTCD_SUCCESS   2           //�����ɹ�
#define WAV_WTCD_FAIL      3           //����ʧ��
#define WAV_CJHB           4           //�ɽ��ر�
#define WAV_FAIL           5           //����ʧ��
#define WAV_TLHQ_JCXX      6           //�۲����
#define WAV_TLHQ_JCSX      7           //�۲�����
//����FOCUS
#define ICDS_HYDM             1
#define ICDS_WTJG             2
#define ICDS_WTSL             3
#define ICDS_CFJG             4
//ȫ��ϵͳ��־
#define GSF_SYSTEMSTATUS_MASK       0x0000000F  //ϵͳ״̬����
#define GSF_SYSTEMSTATUS_NORMAL     0           //����
#define GSF_SYSTEMSTATUS_LIQUIDATE  1           //����
#define GSF_SYSTEMSTATUS_TEST       2           //����
#define GSF_RESTARTPROGRAM          0x00000020  //���������־
#define GSF_DISABLEACCEL            0x00000040  //ͣ��ȫ�ֿ�ݼ�
#define GSF_SYSTEMLOCK              0x00000080  //��������
#define GSF_CHECKSTAMP              0x00000100  //��֤����������
#define GSF_SIGNINJGZX              0x00000400  //��¼�������
#define GSF_CHECKZJMMFIRST          0x00000800  //����ҵ������֤�ʽ�����

//ͳһ�ָ�������
#define SEPARATOR_HYDM              ','         //����ָ�
#define SEPARATOR_SUBSCIBE          ';'         //���Ĵ��еķָ���
//һЩ����
#define DEFAULT_ROWCOUNT            20          //Ĭ��ÿ�β�ѯ��¼��
#define DEFAULT_JMLX                2L          //��������
/////////////////////////////////////////////////////////////////////////////


#define USER_FLAG_DLTS           0x00000001     //ͬ�ʺŵ�¼��ʾ
#define USER_FLAG_UDPQUOTE       0x00000002     //UDP����
#define USER_FLAG_INITSUBSCIBE   0x00000004     //���ĳ�ʼ������
#define USER_FLAG_EXTERNSUBSCIBE 0x00000008     //���¶���
#define USER_FLAG_QHHQCX         0x00000010     //���Ĵ���䶯,���²�ѯ�ض��ĺ�Լ����
#define USER_FLAG_CHECKUPDATE    0x00000020     //������
#define USER_FLAG_QUERYALLHYDM   0x00000040     //�����а��������ں�Լ����ѯȫ���Լ��־
#define USER_FLAG_CCDMZXJGX      0x00000080     //�ֲִ������¼۸���
#define USER_FLAG_WTQR           0x00000100     //ί��ȷ��
#define USER_FLAG_BROADCAST      0x00000200     //���ع㲥����
#define USER_FLAG_LOCALTLDM      0x00000400     //�����������뻺��
#define USER_FLAG_DLTS_DONE      0x00010000     //ͬ�ʺŵ�¼��ʾ�Ѵ���