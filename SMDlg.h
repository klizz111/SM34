// SMDlg.h: 头文件
//

#pragma once


// CSMDlg 对话框
class CSMDlg : public CDialogEx
{
	// 构造
public:
	CSMDlg(CWnd* pParent = nullptr); // 标准构造函数
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CEdit EDIT1;
	afx_msg void OnEnChangeEdit1();
	virtual void OnOK();
	CEdit EDIT2;
	afx_msg void OnBnClickedBut1();
	CComboBox CUM;
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox CUM2;
	afx_msg void OnCbnSelchangeCombo1();
	CEdit EDIT3;
	afx_msg void OnBnClickedBut3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	CButton CK1;
	CButton CK2;
	CButton CK3;
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnEnChangeEdit4();
	CEdit VECTOR;
	afx_msg void OnEnChangeVector();
};
