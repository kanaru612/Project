//=============================================================================
//
// object.h
// Author : 
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include"main.h"
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;						//テクスチャ座標
	D3DXVECTOR3 rot;
};
class CObject
{
public:
	explicit CObject(int nPriority = 3);
	virtual ~CObject(void);

	enum ObjeType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLSION,
		OBJTYPE_BLOCK,
		OBJTYPE_TAIL, 
		OBJTYPE_BG,
		OBJTYPE_MODE,
		OBJTYPE_MAX,
	};

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;	

	

	static void ReleaseAll(void);
	static void UpdataAll(void);
	static void DrawAll(void);
	static void ModeRelease(void);

	virtual void setpos(const D3DXVECTOR3 pos) = 0;
	virtual void setlife(int life) = 0;
	void SetType(ObjeType nType);

	static CObject *Getobject(int nCnt,int nPriority) { return m_pObject[nPriority][nCnt]; };
	ObjeType GetObjType(void) { return m_nType; };
	virtual D3DXVECTOR3 Getpos(void) = 0;
	virtual D3DXVECTOR3 Getsize(void) = 0;
	virtual int Gettype(void) = 0;
	virtual int Getlife(void) = 0;	
	virtual D3DXVECTOR3 Getrot(void) = 0;

protected:
	void Release(void);
private:
	static CObject *m_pObject[5][MAX_OBJECT];
	static int m_nNumAll;
	int m_nID;
	int m_nPriority;
	ObjeType m_nType;
};
#endif
