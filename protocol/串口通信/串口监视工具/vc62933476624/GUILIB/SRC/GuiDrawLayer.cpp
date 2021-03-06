//-----------------------------------------------------------------------//
// This is a part of the GuiLib MFC Extention.							 //	
// Autor  :  Francisco Campos											 //
// (C) 2002 Francisco Campos <www.beyondata.com> All rights reserved     //
// This code is provided "as is", with absolutely no warranty expressed  //
// or implied. Any use is at your own risk.								 //		
// You must obtain the author's consent before you can include this code //
// in a software library.												 //
// If the source code in  this file is used in any application			 //
// then acknowledgement must be made to the author of this program		 //	
// fco_campos@tutopia.com													 //
// version : 1.1														 //
// Modified by : Francisco Campos										 //
//-----------------------------------------------------------------------//

#include "stdafx.h"
#include "..\header\GuiDrawLayer.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COLORREF GuiDrawLayer::DarkenColor( long lScale, COLORREF lColor)
{ 
  long R = MulDiv(GetRValue(lColor),(255-lScale),255);
  long G = MulDiv(GetGValue(lColor),(255-lScale),255);
  long B = MulDiv(GetBValue(lColor),(255-lScale),255);

  return RGB(R, G, B); 
}

GuiDrawLayer::GuiDrawLayer()
{
	if (!m_img.Create(IDB_DOCKBAR,9,10,RGB(255,0,255)))
	{
		TRACE0("error");
	}
	m_iWidthDrowDown=GetSystemMetrics(SM_CXHTHUMB);
	CBitmap cbmp;
	BITMAP bmp;
	cbmp.LoadBitmap(IDB_DOCKBAR);
	cbmp.GetBitmap(&bmp);
	mHeight=CPoint(bmp.bmWidth,bmp.bmHeight);	
	

}

COLORREF GuiDrawLayer::GetRGBColorWhite()
{
	return RGB(255,255,255);
}

COLORREF GuiDrawLayer::GetRGBColorTabs()
{
	BYTE byRvalue =GetRValue(GetRGBColorXP());
	BYTE byGvalue =GetGValue(GetRGBColorXP());
	BYTE byBvalue =GetBValue(GetRGBColorXP());
//	byRvalue =byRvalue>>2;
//	byGvalue =byGvalue>>2;
//	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.08);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBColorBTNHigh()
{
	return ::GetSysColor(COLOR_BTNHIGHLIGHT);
}

COLORREF GuiDrawLayer::GetRGBColorFace()
{
	return ::GetSysColor(COLOR_BTNFACE);
}

COLORREF GuiDrawLayer::GetRGBColorShadow()
{
	return ::GetSysColor(COLOR_BTNSHADOW);
}

COLORREF GuiDrawLayer::GetRGBPressBXP()
{
	COLORREF clrPress = ::GetSysColor (COLOR_HIGHLIGHT);

	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.21);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBMenu()
{
	COLORREF clrPress = ::GetSysColor (COLOR_BTNSHADOW);

	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	byRvalue =byRvalue>>3;
	byGvalue =byGvalue>>3;
	byBvalue =byBvalue>>3;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.47);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBTitleMenu()
{
	COLORREF clrPress = ::GetSysColor (COLOR_BTNSHADOW);

	BYTE byRvalue =GetRValue(::GetSysColor(clrPress));
	BYTE byGvalue =GetGValue(::GetSysColor(clrPress));
	BYTE byBvalue =GetBValue(::GetSysColor(clrPress));
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.8);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
	
}

COLORREF GuiDrawLayer::GetRGBCaptionXP()
{

	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	return RGB(byRvalue+10,byGvalue+10,byBvalue+10);	
}

COLORREF GuiDrawLayer::GetRGBFondoXP()
{
	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_HIGHLIGHT));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_HIGHLIGHT));
	byRvalue =byRvalue>>2;
	byGvalue =byGvalue>>2;
	byBvalue =byBvalue>>2;
	int iMaximo=max(byRvalue,byGvalue);
	iMaximo=max(iMaximo,byBvalue);
	iMaximo= 255-iMaximo;
	iMaximo=iMaximo-(int)(iMaximo*0.14);
	return RGB(byRvalue+iMaximo,byGvalue+iMaximo,byBvalue+iMaximo);	
}

BOOL GuiDrawLayer::IsGrayed()
{
	BYTE byRvalue =GetRValue(::GetSysColor(COLOR_3DFACE));
	BYTE byGvalue =GetGValue(::GetSysColor(COLOR_3DFACE));
	BYTE byBvalue =GetBValue(::GetSysColor(COLOR_3DFACE));
	if ((byRvalue ==byGvalue) && (byGvalue == byBvalue) &&
		 (byBvalue > 190 && byBvalue < 193) || (byBvalue == 216))
		return TRUE;
	else
		return FALSE;
}

COLORREF GuiDrawLayer::GetRGBColorXP()
{

	
	COLORREF clr3DFace = ::GetSysColor (COLOR_3DFACE);
	return RGB (((3*GetRValue (clr3DFace)+240)/4)+1,
				((3*GetGValue (clr3DFace)+240)/4)+1,
				((3*GetBValue (clr3DFace)+240)/4)+1);

}

GuiDrawLayer::~GuiDrawLayer()
{

}

HICON GuiDrawLayer::LoadIconLib(UINT uIcon)
{
	HINSTANCE hIrs = AfxFindResourceHandle(MAKEINTRESOURCE(uIcon),
											RT_GROUP_ICON);
	return (HICON)::LoadImage(hIrs, MAKEINTRESOURCE(uIcon), IMAGE_ICON,16, 16, 0);
}

void GuiDrawLayer::DrawArrow(CDC* pDC,CRect m_rc,BOOL m_bDown)
{
	int difh =m_rc.Height()-mHeight.y;
	difh/=2;
	m_rc.left=m_rc.right-m_iWidthDrowDown;
	m_img.Draw(pDC,m_bDown?0:2,CPoint(m_rc.left+2,m_rc.top+difh),ILD_TRANSPARENT);		

}

void GuiDrawLayer::DrawCheck(CDC* pDC,CRect m_rcTemp)
{
	int iMediaAltura=(m_rcTemp.Height()/2)-2;
	int iMedioBox= m_rcTemp.Width()/2;
	CPen cp(PS_SOLID,1,GuiDrawLayer::GetRGBCaptionXP());
	CPen *pOld=pDC->SelectObject(&cp);
	pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+3);
	pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-2);
	pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-2);
	pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top+2);
				
	pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+2);
	pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-3);
	pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-3);
	pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top+1);

	pDC->MoveTo(m_rcTemp.left+1,m_rcTemp.top+iMediaAltura+1);
	pDC->LineTo(m_rcTemp.left+3,m_rcTemp.bottom-4);
	pDC->MoveTo(m_rcTemp.left+3,m_rcTemp.bottom-4);
	pDC->LineTo(m_rcTemp.right-1,m_rcTemp.top);
	pDC->SelectObject(pOld);
}

HICON GuiDrawLayer::GetIcon(int nIcon)
{
	return m_img.ExtractIcon(nIcon);
}

//function of Bruno Podetti

void GuiDrawLayer::DrawShade( CRect Rect,CPoint screen,CDC* pDC)
{ 
//  if(!SystemParametersInfo(SPI_GETDROPSHADOW,0,&bEnabled,0))
  //  return;

  // Get the size of the menu... 
  
  long winW = Rect.Width(); 
  long winH = Rect.Height(); 
  long xOrg = screen.x;  
  long yOrg = screen.y;

  // Get the desktop hDC... 
  HDC hDcDsk = GetWindowDC(0) ;
  
  int X,Y;
  // Simulate a shadow on right edge... 
  for (X=1; X<=2 ;X++)
  { 
    for (Y=0; Y<2 ;Y++)
    {
      SetPixel(pDC->m_hDC,winW-X,Y, GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y) );
    }
    for (Y=4; Y<8 ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel(pDC->m_hDC,winW-X,Y,DarkenColor(3 * X * (Y - 3), c)) ;
    }
    for (Y=8; Y<=(winH-5) ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel(pDC->m_hDC, winW - X, Y, DarkenColor(15 * X, c) );
    }
    for (Y=(winH-4); Y<=(winH-1) ;Y++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
      SetPixel( pDC->m_hDC, winW - X, Y, DarkenColor(3 * X * -(Y - winH), c)) ;
    }
  } 

  // Simulate a shadow on the bottom edge... 
  for(Y=1; Y<=2 ;Y++)
  {
    for(X=0; X<=2 ;X++)
    {
      SetPixel(pDC->m_hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y)) ;
    }
    for(X=4; X<=7 ;X++)
    {
      COLORREF c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y) ;
      SetPixel(pDC->m_hDC, X, winH - Y, DarkenColor(3 * (X - 3) * Y, c)) ;
    }
    for(X=8; X<=(winW-5) ;X++)
    {
      COLORREF  c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y); 
      SetPixel(pDC->m_hDC, X, winH - Y, DarkenColor(15 * Y, c)) ;
    }
  }   
  // Release the desktop hDC... 
  ReleaseDC(0,hDcDsk);
}



CGuiControlBarButton::CGuiControlBarButton()
{
	bTypeButton=GUINORMAL;
	m_bEnabled=TRUE;
}


CGuiControlBarButton::~CGuiControlBarButton()
{

}

void CGuiControlBarButton::SetTypeButton(GuiType bTypeb)
{
	bTypeButton=bTypeb;
}


void CGuiControlBarButton::SetEnabled(BOOL bEnabled)
{
	m_bEnabled=bEnabled;
}

void CGuiControlBarButton::Paint(CDC* pDC,int st,CRect rc,COLORREF clrFondo)
{
	CBrush cb;
	if(bTypeButton==GUINORMAL) 
		cb.CreateSolidBrush(clrFondo);
	else
	{
		if (m_bEnabled)
			if (st == OVERBTN)
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBFondoXP());
			else if(st == PRESSBTN)
				cb.CreateSolidBrush(GuiDrawLayer::GetRGBPressBXP());
			else
				cb.CreateSolidBrush(clrFondo);
	}

	if (m_bEnabled)
	{
		pDC->FillRect(rc,&cb);
		if (st == OVERBTN)
			pDC->Draw3dRect(rc,bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNHIGHLIGHT):GuiDrawLayer::GetRGBCaptionXP(),
							   bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNSHADOW):GuiDrawLayer::GetRGBCaptionXP());
		if (st == PRESSBTN)
			pDC->Draw3dRect(rc,bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNSHADOW):GuiDrawLayer::GetRGBCaptionXP(),
			bTypeButton==GUINORMAL?::GetSysColor(COLOR_BTNHIGHLIGHT):GuiDrawLayer::GetRGBCaptionXP());
	}
	if(bTypeButton==GUINORMAL) 
		m_imgList.Draw(pDC,clrFondo == ::GetSysColor(COLOR_ACTIVECAPTION)? m_nIcon+1:m_nIcon, 
						CPoint(rc.left+3,rc.top+2), ILD_TRANSPARENT);				
	else
	{
		HICON m_Icon=m_imgList.ExtractIcon(m_nIcon);
		ICONINFO bm;
		ZeroMemory(&bm, sizeof(ICONINFO));
		::GetIconInfo(m_Icon,&bm);
		CSize m_SizeImage =CSize((BYTE)(bm.xHotspot*2),(BYTE)(bm.yHotspot*2));
		int yngap=rc.Height()-m_SizeImage.cy;
		int xngap=rc.Width()-m_SizeImage.cx;
		yngap/=2;
		xngap/=2;
		if (m_bEnabled)
			m_imgList.Draw(pDC,m_nIcon, CPoint(rc.left+xngap+1,bTypeButton==GUINORMAL?rc.top+1:rc.top+yngap), ILD_TRANSPARENT);				
		else
		{
			
			CSize m_SizeImage =CSize((BYTE)(bm.xHotspot*2),(BYTE)(bm.yHotspot*2));
			pDC->DrawState(CPoint(rc.left+xngap+3,rc.top+yngap),m_SizeImage,m_Icon,DSS_MONO,CBrush (GuiDrawLayer::GetRGBColorShadow()));
		}
	}
}

void CGuiControlBarButton::SetData(int nIcon,LPCTSTR lpMsg)
{
	m_nIcon=nIcon;
	m_lpMsg=lpMsg;
}

void  CGuiControlBarButton::SetImageList(UINT nBitmapID, int cx, int nGrow, COLORREF crMask)
{
	CBitmap cbmp;
	BITMAP bmp;
	m_imgList.Create(nBitmapID,cx,nGrow,crMask);
	cbmp.LoadBitmap(nBitmapID);
	cbmp.GetBitmap(&bmp);
	m_imgList.Add(&cbmp,crMask);

}
