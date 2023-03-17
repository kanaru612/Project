#ifndef _PLIFE_H_
#define _PLIFE_H_

//インクルード
#include "main.h"
#include "object2D.h"

//マクロ定義
#define PLIFE_WIDTH (50.0f)

//スポーンクラス
class CPlife : public CObject
{
public:
	CPlife();
	~CPlife()override;

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	void setpos(const D3DXVECTOR3 pos)override { pos; };
	void setlife(int life)override { life; };
	D3DXVECTOR3 Getpos(void)override { return m_pos; };
	D3DXVECTOR3 Getsize(void)override { return m_size; };
	int Gettype(void)override { return m_type; };
	int Getlife(void)override { return m_nLife; };
	D3DXVECTOR3 Getrot(void)override { return m_rot; };
	static CPlife *Create();		
	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }				
	void SetColor(float r, float g, float b, float α);
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3	m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	int m_type;
	int m_nLife;
};

#endif

