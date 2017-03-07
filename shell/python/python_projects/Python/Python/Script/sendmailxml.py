# -*- coding: gb2312 -*-

import os
import sys
import email
import smtplib
import xml.dom.minidom

# ���ڵ��������־
debuglog = 1
debuglogfile = 1
debuglogmail = 0

def Log(sLog):
    if debuglogfile:
        f = open('sendmaillog.txt','a')
        f.write(str(sLog))
        f.write('\r\n')
        f.close()
    if debuglog:
        print str(sLog)
        

# �����ʼ�
class MailCreator:
    def __init__(self):
        # �����ʼ���message����
        self.msg = email.Message.Message()
        self.mail = ""    
        
    def create(self, mailheader, maildata, mailattachlist=[]):
        # mailheader ��dict���ͣ�maildata��list, �������һ��Ϊ���ı����ͣ��ڶ���Ϊhtml.
        # mailattachlist ��list, ����Ϊ�����ļ���
        if not mailheader or not maildata:
            return
        
        for k in mailheader.keys():
            # ��subjectҪ�����⴦������Ҫת��һ�¡�
            # ���� "�ҵ�һ�������ʼ�" ��Ҫת��Ϊ =?gb2312?b?ztK1xNK7uPay4srU08q8/g==?=
            if k == 'subject':
                self.msg[k] = email.Header.Header(mailheader[k], 'gb2312')           
            else:
                self.msg[k] = mailheader[k]
        # �������ı�����
        body_plain = email.MIMEText.MIMEText(maildata[0], _subtype='plain', _charset='gb2312')
        body_html = None
        # ����html���֣�����ǿ�ѡ��
        if maildata[1]:
            body_html = email.MIMEText.MIMEText(maildata[1], _subtype='html', _charset='gb2312')
        
        
        # ����һ��multipart, Ȼ���ǰ����ı����ֺ�html���ֶ����ӵ����棬����Ϊʲô�����Կ���mime�������
        attach=email.MIMEMultipart.MIMEMultipart()
        attach.attach(body_plain)
        if body_html:
            attach.attach(body_html)
        # ����ÿһ������
        for fname in mailattachlist:
            attachment=email.MIMEText.MIMEText(email.Encoders._bencode(open(fname,'rb').read()))
            # ���������ļ����ͣ�ȫ��������ΪApplication.��ȻҲ������Image,Audioʲô�ģ����ﲻ����ô��
            attachment.replace_header('Content-type','Application/octet-stream;name="'+os.path.basename(fname)+'"')
            # һ��Ҫ�Ѵ����������Ϊbase64,��Ϊ����Ĭ�Ͼ����õ�base64
            attachment.replace_header('Content-Transfer-Encoding', 'base64')
            attachment.add_header('Content-Disposition','attachment;filename="'+os.path.basename(fname)+'"')
            attach.attach(attachment)
        # �������յ��ʼ�            
        self.mail = self.msg.as_string()[:-1] + attach.as_string()
        
        return self.mail
        
# ��ȡ��������Ϣ
def smtpsetting(xdom):
	xsrv = xdom.getElementsByTagName('smtp')[0]
	
	sServer = xsrv.getAttributeNode('server').nodeValue
	sPort = xsrv.getAttributeNode('port').nodeValue	
	sUser = xsrv.getAttributeNode('user').nodeValue	
	sPwd = xsrv.getAttributeNode('password').nodeValue	
	
	return sServer,sPort,sUser,sPwd
	
# ��ȡ�ʼ���Ϣ
def mailsetting(xdom):
	xsrv = xdom.getElementsByTagName('mail')[0]
	
	sSendTo = xsrv.getAttributeNode('sendto').nodeValue
	sFrom = xsrv.getAttributeNode('from').nodeValue	
	sTitle = xsrv.getAttributeNode('title').nodeValue
	
	sBodyFile = ''
	sAttachFile = []
	for iNode in xsrv.childNodes:
		if iNode.nodeName == 'body':
			sBodyFile = iNode.getAttributeNode('file').nodeValue
		if iNode.nodeName == 'attach':
#			print iNode.getAttributeNode('file').nodeValue	
			sAttachFile.append(iNode.getAttributeNode('file').nodeValue)
		
	return sSendTo,sFrom,sTitle,sBodyFile,sAttachFile

def readxmlgb2312(xmlpath):
	fp = open(xmlpath, 'r')
	content = fp.read()
	fp.close()
	content = content.replace("encoding=\"GB2312\"", " encoding='utf-8'")
	content = content.replace("encoding=\"gb2312\"", " encoding='utf-8'")
	content = content.decode('gb2312').encode('utf-8')
	print content
	xdom = xml.dom.minidom.parseString(content)
	return xdom

# ������	
def sendmailxml(xmlfile):

	Log('�ʼ���'+xmlfile)
	xdom = readxmlgb2312(xmlfile)
	sServer,sPort,sUser,sPwd = smtpsetting(xdom)
	sSendTo,sFrom,sTitle,sBodyFile,sAttachFile = mailsetting(xdom)
	Log('��������������:'+str(sServer)+str(sPort)+str(sUser)+str(sPwd))
	Log('�����ʼ�����:'+str(sSendTo)+str(sFrom)+str(sBodyFile)+str(sAttachFile))
	
	# �ʼ�����
	mc = MailCreator()

	sBodyTxt = 'txt'
	f = open(sBodyFile,'rb')
	sBodyTxt = f.read()
	f.close()
	
	
	header = {'from': sFrom, 'to':sSendTo, 'subject':sTitle}
	sBody=[sBodyTxt, 0]#'Not Support HTML View']
	mail = mc.create(header, sBody, sAttachFile)
	
	
	if mail:
		Log('�ʼ����ɳɹ�')

	# �����ʼ���������
	smtpsrv = smtplib.SMTP(str(sServer), int(sPort))
	smtpsrv.set_debuglevel(1)
	sret = smtpsrv.ehlo()
	if sret[0]== 250:
            Log('���ӷ������ɹ�:' + str(sServer) + ':' + str(sPort))
        else:
            Log('���ӷ�����ʧ��:' + str(sServer) + ':' + str(sPort) + 'err:' + str(sret))
        
	sret = smtpsrv.login(str(sUser), str(sPwd))
	if sret[0]== 235:
            Log('��½�������ɹ�:' + str(sUser))
        else:
            Log('��½������ʧ��:' + str(sUser) + 'err:' + str(sret))
        
	smtpsrv.ehlo()
	try:
            sret = smtpsrv.sendmail(str(sFrom), str(sSendTo), str(mail))
        except Exception, e:
            Log('����ʧ��' + str(sFrom)+ str(sSendTo)+ 'err:' + str(e))
        smtpsrv.quit()
	smtpsrv.close()
	Log('�ʼ��������')

    # ��������ʼ�
	if debuglogmail:
		f = open('sendmailtest.eml','wb')
		f.write(mail)
		f.close() 
	
		
if __name__ == '__main__':
    
	# ������
	if len(sys.argv) < 2 :
		print '���з�ʽ��python[w].exe sendmailxml.py mail.xml'
		print '     python[w].exe �ű�������'
		print '     sendmailxml.py �����ʼ��Ľű�'
		print '     mail.xml ��һ����ʽ�淶���ʼ����������ʼ����ݵ������ļ�'
		print ''
		Log('��������')
        else:
            try:
                xmlfile = sys.argv[1]
                sendmailxml(xmlfile)
            except Exception, e:
                Log('�������' + str(xmlfile) + ' err:' + str(e))
