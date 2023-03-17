//============================================================================
//
// Object.h
// Author : �����@�t��
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include"main.h"
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;						//�e�N�X�`�����W
	D3DXVECTOR3 rot;
};
//���_���(3D)�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;						//���_���W
	D3DXVECTOR3 nor;						//���_���W
	D3DCOLOR col;							//���_�J���[
	D3DXVECTOR2 tex;						//�e�N�X�`�����W
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
	CObject *m_pPrev;							//�O�̃I�u�W�F�N�g�̃|�C���^
	CObject *m_pNext;							//���̃I�u�W�F�N�g�̃|�C���^
	int m_nID;		
	int m_nPriority;
	ObjeType m_nType;
	bool m_bDeth;								//���S�t���O
	bool m_canPoseUpdate;						
};
#endif
