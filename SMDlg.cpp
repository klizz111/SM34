
// SMDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SM.h"
#include "SMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <clocale>
#include <string>
#include <iostream>
#include "sm34.h"


// CSMDlg 对话框



CSMDlg::CSMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, EDIT1);
	DDX_Control(pDX, IDC_EDIT2, EDIT2);
	DDX_Control(pDX, IDC_COMBO2, CUM);
	DDX_Control(pDX, IDC_COMBO1, CUM2);
	DDX_Control(pDX, IDC_EDIT3, EDIT3);
	DDX_Control(pDX, IDC_CHECK1, CK1);
	DDX_Control(pDX, IDC_CHECK2, CK2);
	DDX_Control(pDX, IDC_CHECK3, CK3);
	DDX_Control(pDX, IDC_EDIT4, VECTOR);
}

BEGIN_MESSAGE_MAP(CSMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CSMDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUT1, &CSMDlg::OnBnClickedBut1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSMDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSMDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUT3, &CSMDlg::OnBnClickedBut3)
	ON_BN_CLICKED(IDC_CHECK1, &CSMDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CSMDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CSMDlg::OnBnClickedCheck3)
	ON_EN_CHANGE(IDC_EDIT4, &CSMDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_VECTOR, &CSMDlg::OnEnChangeVector)
END_MESSAGE_MAP()


// CSMDlg 消息处理程序

BOOL CSMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString temp;
	temp.Format(L"HEX字符串");
	CUM.AddString(temp);
	temp.Format(L"ASCII字符串");
	CUM.AddString(temp);
	CUM.SetCurSel(1);
	temp.Format(L"SM3");
    CUM2.AddString(temp);
    temp.Format(L"SM4");
    CUM2.AddString(temp);
	CUM2.SetCurSel(1);	
	CUM.SetCurSel(0);
	CK1.SetCheck(1);
	CK2.SetCheck(1);
	//设定CK2为无法更改
	CK1.EnableWindow(FALSE);
	setlocale(LC_CTYPE, "chs");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CSMDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}


void CSMDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CSMDlg::OnBnClickedBut1()
{
	CString str;
	EDIT1.GetWindowTextW(str);
	std::string str1 = CW2A(str.GetString());//CString转string(EDIT1明文)
	int code_mode = CUM.GetCurSel();
	int code_mode2 = CUM2.GetCurSel();
	if (code_mode2 == 0)//SM3
	{
		if (code_mode == 0)//字符串
		{
			std::string temp_string = sm3(str1, 0);
			EDIT2.SetWindowTextW(CA2W(temp_string.c_str()));
		}
		else //HEX
		{
			//将小写转换为大写与判断是否为HEX
			for (int i = 0; i < str1.size(); i++)
			{
				if (str1[i] >= 'a' && str1[i] <= 'f')
				{
					str1[i] = str1[i] - 32;
				}
				if (!((str1[i] >= '0' && str1[i] <= '9') || (str1[i] >= 'A' && str1[i] <= 'F')))
				{
					MessageBox(L"请输入正确的HEX字符串！");
					return;
				}
			}
			std::string temp_string = sm3(str1, 1);
			EDIT2.SetWindowTextW(CA2W(temp_string.c_str()));
		}
	}
	else if (code_mode2 == 1 && EDIT3.GetWindowTextLength()==0)
	{
		MessageBox(L"请输入密钥！");
		return;
	}
	//
	//SM4
	else if (code_mode2 == 1)
	{
		CString temp;
		EDIT3.GetWindowTextW(temp);
		string key = CW2A(temp.GetString());

		//判断明文类型
		
		//字符串默认使用PKCS7填充
		if (code_mode == 0)//字符串
		{

			//判断模式

			//ECB模式
			if (CK2.GetCheck() == 1)
			{
				string temp = sm4_encode_ECB(StringToHex(str1), String2Hex(key));
				EDIT2.SetWindowTextW(CA2W(temp.c_str()));	
			}
			//CBC模式
			else if (CK3.GetCheck() == 1)
			{
				string res = "";
				string vector;
				//如果没有输入向量
				if (VECTOR.GetWindowTextLength() == 0)
				{
					vector = Gen_IV();	
					VECTOR.SetWindowTextW(CA2W(vector.c_str()));
				}
				//如果输入了向量
				else
				{
					VECTOR.GetWindowTextW(temp);					
					vector = CW2A(temp.GetString());
					if (vector.size() != 32)
					{
						MessageBox(L"请输入正确的HEX向量！");
						return;
					}
				}
				res = sm4_encode_CBC(StringToHex(str1),StringToHex(key), vector);
				EDIT2.SetWindowTextW(CA2W(res.c_str()));
			}
		}

		else if (code_mode == 1)//HEX
		{
			//将小写转换为大写与判断是否为HEX
			for (int i = 0; i < str1.size(); i++)
			{
				if (str1[i] >= 'a' && str1[i] <= 'f')
				{
					str1[i] = str1[i] - 32;
				}
				if (!((str1[i] >= '0' && str1[i] <= '9') || (str1[i] >= 'A' && str1[i] <= 'F')))
				{
					MessageBox(L"请输入正确的HEX字符串！");
					return;
				}
			}
			//检查密钥
			for (int i = 0; i < key.size(); i++)
			{
				if (key[i] >= 'a' && key[i] <= 'f')
				{
					key[i] = key[i] - 32;
				}
				if (!((key[i] >= '0' && key[i] <= '9') || (key[i] >= 'A' && key[i] <= 'F')))
				{
					MessageBox(L"请输入正确的HEX密钥！");
					return;
				}
			}

			//是否使用PCKS7填充
			if (CK1.GetCheck() == 1)//是
			{
				//判断加密方式

				//ECB模式
				if (CK2.GetCheck() == 1)
				{
					std::string temp_string = sm4_encode_ECB(str1, key);
					EDIT2.SetWindowTextW(CA2W(temp_string.c_str()));
					return;
				}
				
				//CBC模式
				else if (CK3.GetCheck() == 1)
				{
					string res = "";
					string vector;
					//如果没有输入向量
					if (VECTOR.GetWindowTextLength() == 0)
					{
						vector  = Gen_IV();
						VECTOR.SetWindowTextW(CA2W(vector.c_str()));
					}
					//如果输入了向量
					else
					{
						VECTOR.GetWindowTextW(temp);
						vector = CW2A(temp.GetString());
						if (vector.size() != 32)
						{
							MessageBox(L"请输入正确的HEX向量！");
							return;
						}
					}
					res = sm4_encode_CBC(str1, key, vector);
					EDIT2.SetWindowTextW(CA2W(res.c_str()));
					return;
				}
			}

			else//否,，不使用PCKS7填充
			{
				if (str1.size()%32 != 0 || key.size() % 32 != 0)
				{
					MessageBox(L"请输入正确的HEX字符串和密钥！");
				}

				//ECB模式
				else if (CK2.GetCheck() == 1)
				{
					string res = "";
					if (key.size() > 32)
					{
						key = key.substr(0, 32);
					}
					for (int i = 0; i < str1.size(); i += 32)
					{
						res += sm4_encode(str1.substr(i, 32), key);
					}
					EDIT2.SetWindowTextW(CA2W(res.c_str()));
					return;
				}

				//CBC模式
				else if (CK3.GetCheck() == 1)
				{
					string res = "";
					string vector;
					//如果没有输入向量
					if (VECTOR.GetWindowTextLength() == 0)
					{
						vector = Gen_IV();
						VECTOR.SetWindowTextW(CA2W(vector.c_str()));
					}
					//如果输入了向量
					else
					{
						VECTOR.GetWindowTextW(temp);
						vector = CW2A(temp.GetString());
						if (vector.size() != 32)
						{
							MessageBox(L"请输入正确的HEX向量！");
							return;
						}
					}
					if (key.size() > 32)
					{
						key = key.substr(0, 32);
					}
					res  = sm4_encode_CBC_1(str1, key, vector);
					EDIT2.SetWindowTextW(CA2W(res.c_str()));
					return;
				}
				
			}
		
		}
		
	}
	
}



void CSMDlg::OnCbnSelchangeCombo2()
{
	//设置字符串为ASCII时，CK1为不可更改
if (CUM.GetCurSel() == 0 || CUM2.GetCurSel() == 0)
	{
		CK1.EnableWindow(FALSE);
		if (CUM2.GetCurSel() == 1)
		{
			CK1.SetCheck(1);
			CK2.SetCheck(1);
		}
		return;
	}
else if (CUM2.GetCurSel()==1 || CUM.GetCurSel() == 0)
{
	CK1.EnableWindow(TRUE);
	CK2.EnableWindow(TRUE);
	CK3.EnableWindow(TRUE);
	CK1.SetCheck(1);
	CK2.SetCheck(1);
	return;
}
else
{

}
}


void CSMDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(CUM2.GetCurSel()==0)//SM3
	{
		CK1.EnableWindow(FALSE);
		CK1.SetCheck(0);
		CK2.EnableWindow(FALSE);
		CK2.SetCheck(0);
		CK3.EnableWindow(FALSE);
		CK3.SetCheck(0);
		//关闭EDIT3
		EDIT3.EnableWindow(FALSE);
		VECTOR.EnableWindow(FALSE);
	}
	else
	{
		if (CUM.GetCurSel() == 0)
		{
			CK1.EnableWindow(FALSE);
			CK1.SetCheck(1);
			CK2.EnableWindow(TRUE);
			CK3.EnableWindow(TRUE);
			CK2.SetCheck(1);
		}
		else
		{
			CK1.EnableWindow(TRUE);
			CK1.SetCheck(TRUE);
			CK2.EnableWindow(TRUE);
			CK2.SetCheck(TRUE);
			CK3.EnableWindow(TRUE);
		}
		EDIT3.EnableWindow(TRUE);
		VECTOR.EnableWindow(TRUE);
	}
}



void CSMDlg::OnBnClickedBut3()
{
	CString str;
	EDIT2.GetWindowTextW(str);
	std::string str1 = CW2A(str.GetString());//CString转string
	int code_mode = CUM.GetCurSel();
	int code_mode2 = CUM2.GetCurSel();
	if (code_mode2 == 0)//SM3
	{
		MessageBox(L"SM3不支持解密！");
		return;
	}
	else if (code_mode2 == 1 && EDIT3.GetWindowTextLength() == 0)
	{
		MessageBox(L"请输入密钥！");
		return;
	}

	else if (code_mode2 == 1 && code_mode == 1 && CK3.GetCheck() == 1 && CK1.GetCheck() == 0)
	{
		string res = "";
		string vector;
		CString temp;
		//如果没有输入向量
		if (VECTOR.GetWindowTextLength() == 0)
		{
			MessageBox(L"请输入向量！");
			return;
		}
		//如果输入了向量
		else
		{
			VECTOR.GetWindowTextW(temp);
			vector = CW2A(temp.GetString());
			if (vector.size() != 32)
			{
				MessageBox(L"请输入正确的HEX向量！");
				return;
			}
		}
		EDIT3.GetWindowTextW(temp);
		string key = CW2A(temp.GetString());
		res = sm4_decode_CBC_1(str1, key, vector);
		EDIT1.SetWindowTextW(CA2W(res.c_str()));
		return;
	}


	//SM4
	else if (code_mode2 == 1)
	{
		CString temp;
		EDIT3.GetWindowTextW(temp);
		string key;
		key = CW2A(temp.GetString());

		//判断明文类型
		if (code_mode == 0)//字符串
		{
			//判断模式

			//ECB模式
			if (CK2.GetCheck() == 1)
			{
				std::string temp = sm4_decode_ECB(str1, String2Hex(key));
				temp = Hex2string(temp);
				EDIT1.SetWindowTextW(CA2W(temp.c_str()));
			}

			//CBC模式
			else if (CK3.GetCheck() == 1)
			{
				string res = "";
				string vector;
				//如果没有输入向量
				if (VECTOR.GetWindowTextLength() == 0)
				{
					MessageBox(L"请输入向量！");
					return;
				}
				//如果输入了向量
				else
				{
					VECTOR.GetWindowTextW(temp);
					vector = CW2A(temp.GetString());
					if (vector.size() != 32)
					{
						MessageBox(L"请输入正确的HEX向量！");
						return;
					}
				}
				res = sm4_decode_CBC(str1, StringToHex(key), vector);
				res = Hex2string(res);
				EDIT1.SetWindowTextW(CA2W(res.c_str()));
			}	
		}

		//HEX
		else if (code_mode == 1)//HEX
		{
			//将小写转换为大写与判断是否为HEX
			for (int i = 0; i < str1.size(); i++)
			{
				if (str1[i] >= 'a' && str1[i] <= 'f')
				{
					str1[i] = str1[i] - 32;
				}
				if (!((str1[i] >= '0' && str1[i] <= '9') || (str1[i] >= 'A' && str1[i] <= 'F')))
				{
					MessageBox(L"请输入正确的HEX字符串！");
					return;
				}
			}	
			//检查密钥
			for (int i = 0; i < key.size(); i++)
			{
				if (key[i] >= 'a' && key[i] <= 'f')
				{
					key[i] = key[i] - 32;
				}
				if (!((key[i] >= '0' && key[i] <= '9') || (key[i] >= 'A' && key[i] <= 'F')))
				{
					MessageBox(L"请输入正确的HEX密钥！");
					return;
				}
			}
			
			//是否使用PCKS7填充

			//是
			if (CK1.GetCheck() == 1)
			{
				string res = "";
				//判断加密方式

				//ECB模式
				if (CK2.GetCheck() == 1)
				{
					std::string temp_string = sm4_decode_ECB(str1, key);
					EDIT1.SetWindowTextW(CA2W(temp_string.c_str()));
					return;
				}

				//CBC模式
				else if (CK3.GetCheck() == 1)
				{
					string res = "";
					string vector;
					//如果没有输入向量
					if (VECTOR.GetWindowTextLength() == 0)
					{
						MessageBox(L"请输入向量！");
						return;
					}
					//如果输入了向量
					else
					{
						VECTOR.GetWindowTextW(temp);
						vector = CW2A(temp.GetString());
						if (vector.size() != 32)
						{
							MessageBox(L"请输入正确的HEX向量！");
							return;
						}
					}
					res = sm4_decode_CBC(str1, key, vector);
					EDIT1.SetWindowTextW(CA2W(res.c_str()));
					return;
				}


				//不使用PCKS7填充
				else
				{
					if (str1.size() % 32 != 0 || key.size() % 32 != 0)
					{
						MessageBox(L"请输入正确的HEX字符串和密钥！");
					}

					//ECB模式
					else if (CK2.GetCheck() == 1)
					{
						string res = "";
						if (key.size() > 32)
						{
							key = key.substr(0, 32);
						}
						for (int i = 0; i < str1.size(); i += 32)
						{
							res += sm4_decode(str1.substr(i, 32), key);
						}
						EDIT1.SetWindowTextW(CA2W(res.c_str()));
						return;
					}

					//CBC模式
					else
					{
						string res = "";
						string vector;
						//如果没有输入向量
						if (VECTOR.GetWindowTextLength() == 0)
						{
							MessageBox(L"请输入向量！");
							return;
						}
						//如果输入了向量
						else
						{
							VECTOR.GetWindowTextW(temp);
							vector = CW2A(temp.GetString());
							if (vector.size() != 32)
							{
								MessageBox(L"请输入正确的HEX向量！");
								return;
							}
						}
						res = sm4_decode_CBC_1(str1, key, vector);
						EDIT1.SetWindowTextW(CA2W(res.c_str()));
						MessageBox(CA2W(res.c_str()));
						return;
					}
				}
			}
		}
	}
	return;
}


void CSMDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSMDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	CK3.SetCheck(0);
	return;
}


void CSMDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	CK2.SetCheck(0);
	return;
}


void CSMDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSMDlg::OnEnChangeVector()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
