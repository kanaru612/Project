//============================================================================
//
// Object.h
// Author : 黒島　奏洸
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
//頂点情報(3D)の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;						//頂点座標
	D3DXVECTOR3 nor;						//頂点座標
	D3DCOLOR col;							//頂点カラー
	D3DXVECTOR2 tex;						//テクスチャ座標
}VERTEX_3D;

class CObject
{
public:
	explicit CObject(int nPriority = PRIORITY_0);
	virtual ~CObject(void);

	enum ObjeType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_POLYGON,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLSION,
		OBJTYPE_BLOCK,
		OBJTYPE_TAIL, 
		OBJTYPE_BG,
		OBJTYPE_MODE,
		OBJTYPE_MESHFIELD,
		OBJTYPE_PAUSE,		
		OBJTYPE_MAX,
	};
	enum EPRIORITY
	{
		PRIORITY_0 = 0,
		PRIORITY_1,
		PRIORITY_2,
		PRIORITY_3,
		PRIORITY_4,
		PRIORITY_5,
		PRIORITY_FADE,
		PRIORITY_MAX
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
	bool IfDie() { return m_bDeth; }
	ObjeType GetObjType(void) { return m_nType; };
	void Death();
	virtual D3DXVECTOR3 Getpos(void) = 0;
	virtual D3DXVECTOR3 Getsize(void) = 0;
	virtual int Gettype(void) = 0;
	virtual int Getlife(void) = 0;	
	virtual D3DXVECTOR3 Getrot(void) = 0;

protected:
	void Release(void);
private:
	static int m_nNumAll;
	static CObject *m_pTop[PRIORITY_MAX];
	static CObject *m_pCurrent[PRIORITY_MAX];
	CObject *m_pPrev;							//前のオブジェクトのポインタ
	CObject *m_pNext;							//次のオブジェクトのポインタ
	int m_nID;		
	int m_nPriority;
	ObjeType m_nType;
	bool m_bDeth;								//死亡フラグ
	bool m_canPoseUpdate;						
};
#endif
