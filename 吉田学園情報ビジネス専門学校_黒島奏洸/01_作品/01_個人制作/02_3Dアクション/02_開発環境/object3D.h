//============================================================================
//
// Object3D.h
// Author : 黒島　奏洸
//
//=============================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_
#include"main.h"
#include"object.h"
class CInput;
class CObject3D : public CObject
{
public:
	explicit CObject3D(int nPriority = 3);
	~CObject3D()override;

	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void setpos(const D3DXVECTOR3 pos)override;
	static CObject3D *Create();
	D3DXVECTOR3 Getpos(void) override { return m_pos; };
	D3DXVECTOR3 Getsize(void) override { return m_Size; };
	int Gettype(void) override { return m_nType; };
	int Getlife(void) override { return m_nLife; };
	void setlife(int life)override;
	D3DXVECTOR3 Getrot(void)override { return m_rot; };
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void setsize(const D3DXVECTOR3 size);
	void settype(int type);
	void setTexture(float Upos1, float Upos2, float B1pos1, float Bpos2);
	void setrevCenter(D3DXVECTOR3 revCenter);
	void setrevPara(D3DXVECTOR3 Center, float fSpeed, float fRadius);
	void setrotate(D3DXVECTOR3 rot);
	void setcolor(float r, float g, float b, float α);
	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }
	void Setpos3D(const D3DXVECTOR3 pos);
	void Setsize3D(const D3DXVECTOR3 size);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Size;
	LPDIRECT3DTEXTURE9 m_pTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	float m_fWidth;							//haba 
	float m_fHeight;						//たかさ
	float m_fLength;
	float m_fAngle;
	D3DXVECTOR3 m_revCentor;		//公転ノチュウシンテン
	float m_frevSpeed;				//回転速度
	float m_frevAngle;				//
	float m_frevRadius;
	int m_nType;
	D3DXVECTOR3 m_rot;
	int m_nLife;
	D3DXMATRIX   m_mtxWorld;				//ワールドマトリックス
};
#endif

