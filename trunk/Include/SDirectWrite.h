#pragma once
#include "SUtils.h"
#include "STemplate.h"

class SDirectWrite : public Singleton<SDirectWrite>
{
private:
	friend class Singleton<SDirectWrite>;
public:
	//===============================================================================================
	// ȭ�� DPI
	//===============================================================================================
	float				m_fDPIScaleX;
	float				m_fDPIScaleY;
	FLOAT				m_fdpiX;
	FLOAT				m_fdpiY;
	//===============================================================================================
	// Direct Interface Pointer
	//===============================================================================================
	ID2D1RenderTarget*			m_pD2DRenderTargetView;
	ID2D1Factory*				m_pD2DFactory;
	ID2D1SolidColorBrush*		m_pBlackBrush;
	IDWriteFactory*				m_pDWriteFactory;
	IDWriteTextFormat*			m_pTextFormat;
	IDWriteTextLayout*			m_pTextLayout;

	//===============================================================================================
	// ���̾ƿ� ���ڿ� ���� ��
	//===============================================================================================
	DWRITE_FONT_WEIGHT			m_FontWeight;			// ��Ʈ ����
	DWRITE_FONT_STYLE			m_FontStyle;			// ��Ʈ ��Ÿ��
	BOOL						m_fontUnderline;		// ����
	wstring						m_wszFontFamily;		// Font�� ���ڿ�
	float						m_FontSize;				// ��Ʈ ������
	wstring						m_wszText;				// Layout�� ���ڿ�
	UINT32						m_cTextLength;			// ���ڿ� ����
	//===============================================================================================
	// Other Value
	//===============================================================================================
	HWND				m_hWnd;
public:
	//===============================================================================================
	// Initialize and Create
	//===============================================================================================
	bool			Set(HWND hWnd, int iWidth, int iHeight, IDXGISurface1* m_pSurface);
	bool			Init();
	HRESULT			CreateDeviceIndependentResources();					// ����̽��� ���ӵ��� ���� ���ҽ� ����
	HRESULT			CreateDeviceResources(IDXGISurface1* m_pSurface);	// ����̽��� ���ӵǴ� ���ҽ� ����
	//===============================================================================================
	// Render
	//===============================================================================================
	bool			Render() {return true;}
	bool			Begin();
	bool			DrawText(RECT rc, TCHAR* pText, D2D1::ColorF Color = D2D1::ColorF(1, 0, 0, 1)); // Format ���
	bool			DrawText(D2D1_POINT_2F origin, D2D1::ColorF Color = D2D1::ColorF(1, 0, 0, 1));	// Layout ���
	bool			End();

	//===============================================================================================
	// Release
	//===============================================================================================
	bool			Release(); // Enter Release Function

	void			DiscardDeviceIndependentResources();		// ����̽��� ���ӵ��� ���� ���ҽ��� ����
	void			DiscardDeviceResources();				// ����̽��� ���ӵǴ� ���ҽ��� ����

	//===============================================================================================
	// Setter
	//===============================================================================================
	HRESULT			SetText(D2D1_POINT_2F pos, wchar_t *text, D2D1::ColorF Color);
	HRESULT			SetFont(wchar_t *FontFamily);
	HRESULT			SetFontSize(float size);
	HRESULT			SetWeight(DWRITE_FONT_WEIGHT FontWeight);
	HRESULT			SetItalic(DWRITE_FONT_STYLE FontStyle);
	HRESULT			SetUnderline(bool underline);

	// ��½� �ʿ��� �� ����
	bool			SetPragraghAlighment(DWRITE_PARAGRAPH_ALIGNMENT nPragraghAlighment);
	bool			SetTextAlighment(DWRITE_TEXT_ALIGNMENT nTextAlighment);

	//===============================================================================================
	// Other
	//===============================================================================================
	void			OnResize(UINT width, UINT height, IDXGISurface1* pSurface);
	bool			Frame() { return true;}
private:
	SDirectWrite();
public:
	virtual ~SDirectWrite();
};
#define I_DirectWrite SDirectWrite::GetInstance()
