// View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(__VIEW_H__)
#define __VIEW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyTreeCtrl.h"


#define UM_END_WAIT (WM_USER+1000)
#define UM_SHOW_PROMPT (WM_USER+1001)

class CMyView : public CView
{
protected:
	CMyTreeCtrl m_Tree;
	CImageList m_ImageList;
	HTREEITEM m_htreeRoot;
	HTREEITEM m_htreeContents;
	HTREEITEM m_htreeMedia;
	HTREEITEM m_htreePages;
	BOOL m_bSnagging;

protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();

// Operations
public:
	void InitTree(CString& strSite);

	HTREEITEM AddTreeMedia(CString strMedia, int nMediaType);
	HTREEITEM AddTreePage(CString& strPage, BOOL bOffsite);
	HTREEITEM AddTreeContent(CString& strPage);
	void ClearTree();
	BOOL TreeIsEmpty() { return(m_Tree.GetCount() <= 0); }
	void ClearProject(LPCTSTR lpszDir);
	void GetTreeSite(CString& strSite) { strSite = m_Tree.GetItemText(m_htreeRoot); }
	void SetSnagging(BOOL bSnagging) { m_bSnagging = bSnagging; }
	BOOL GetSnagging() { return m_bSnagging; }
	int ShowPrompt(int nID, int nOptions);

	void GetChildren(HTREEITEM htreeParent, CStringArray& arrstrEntries);
	void AddChildren(HTREEITEM htreeParent, CStringArray& arrstrEntries, int nPageType);
	void SerializeTree(CArchive& ar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileOptions();
	afx_msg void OnSnag();
	afx_msg void OnUpdateSnag(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOptions(CCmdUI* pCmdUI);
	afx_msg void OnFileRemoveall();
	afx_msg void OnUpdateFileRemoveall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileRename();
	afx_msg void OnUpdateFileRename(CCmdUI* pCmdUI);
	afx_msg void OnFileClose();
	afx_msg void OnUpdateFileClose(CCmdUI* pCmdUI);
	afx_msg LRESULT OnShowPrompt(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateFileMRU(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(__VIEW_H__)
