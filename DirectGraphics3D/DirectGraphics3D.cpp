/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics3D.cpp
* @brief	This File is DirectGraphics3D DLL Project.
* @author	Alopex/Helium
* @version	v1.11a
* @date		2017-11-29	v1.00a	alopex	Create Project
* @date		2017-12-3	v1.01a	alopex	Modify Bug
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library
*/
#include "DirectCommon.h"
#include "DirectGraphics3D.h"

//------------------------------------------------------------------
// @Function:	 DirectGraphics3D()
// @Purpose: DirectGraphics3D���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D::DirectGraphics3D()
{
	m_pD3D9Device = NULL;					//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9VertexBuffer = NULL;				//IDirect3DVertexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9IndexBuffer = NULL;				//IDirect3DIndexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Texture = NULL;					//IDirect3DTexture9�ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics3D()
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D::~DirectGraphics3D()
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);		//IDirect3DVertexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9IndexBuffer);		//IDirect3DIndexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9Texture);			//IDirect3DTexture9�ӿ�ָ���ͷ�
}

//------------------------------------------------------------------
// @Function:	 DirectGraphics3D(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectGraphics3D���캯��
// @Since: v1.00a
// @Para: LPDIRECT3DDEVICE9 pD3D9Device		//IDirect3DDevice9�ӿ�ָ��
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D::DirectGraphics3D(IDirect3DDevice9* pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;			//IDirect3DDevice9�ӿ�ָ���ʼ��
	m_pD3D9VertexBuffer = NULL;				//IDirect3DVertexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9IndexBuffer = NULL;				//IDirect3DIndexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Texture = NULL;					//IDirect3DTexture9�ӿ�ָ���ʼ��(NULL)
}

//-------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DInit(int nPlane)
// @Purpose: DirectGraphics3D��ʼ��
// @Since: v1.00a
// @Para: int nPlane	//����ƽ����(������6��ƽ��)(�Դ�����...)(Vertex����:Base)
// @Return: None
//-------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics3D::DirectGraphics3DInit(int nPlane)
{
	//VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DTexture), 0, D3DFVF_VERTEX3D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	//IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DInit(int nPlane, LPCSTR lpszStrTexture)
// @Purpose: DirectGraphics3D��ʼ��
// @Since: v1.00a
// @Para: int nPlane					//����ƽ����(������6��ƽ��)(�Դ�����...)(Vertex����:Normal)
// @Para: LPCWSTR lpszStrTexture		//ƽ������·��(eg:L"Res\\title.png")
// @Return: None
//------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics3D::DirectGraphics3DInit(int nPlane, LPCWSTR lpszStrTexture)
{
	//VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DTexture), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	//IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	//Texture����ƽ������
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));

	return S_OK;
}

//------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane)
// @Purpose: DirectGraphics3D��ʼ��
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//��������(ö��)
// @Para: int nPlane					//����ƽ����(������6��ƽ��)(�Դ�����...)(Vertex����:Normal)
// @Return: None
//------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics3D::DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane)
{
	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DBase), 0, D3DFVF_VERTEX3D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DTexture), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DNormal), 0, D3DFVF_VERTEX3D_NORMAL, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DNormalTexture), 0, D3DFVF_VERTEX3D_NORMAL_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DNormalSpecularTexture), 0, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics3D��ʼ��
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//��������(ö��)
// @Para: int nPlane					//����ƽ����(������6��ƽ��)(�Դ�����...)(Vertex����:Normal)
// @Para: LPCWSTR lpszStrTexture		//ƽ������·��(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics3D::DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane, LPCWSTR lpszStrTexture)
{
	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DBase), 0, D3DFVF_VERTEX3D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DTexture), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		//Texture����ƽ������
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex3D_Type_Normal:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DNormal), 0, D3DFVF_VERTEX3D_NORMAL, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DNormalTexture), 0, D3DFVF_VERTEX3D_NORMAL_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		//Texture����ƽ������
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex3DNormalSpecularTexture), 0, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		//Texture����ƽ��ee����
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_RotatePara sRotatePara			//�����任����
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixScale;									//���ű任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	//�������ž���
	MatrixWorld = MatrixWorld * MatrixScale;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_RotatePara sRotatePara			//��ת�任����
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;	//��ת�任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);	//������ת����X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);	//������ת����Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);	//������ת����Z
	MatrixWorld = MatrixWorld * MatrixRotateX * MatrixRotateY * MatrixRotateZ;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_TranslatePara sTranslatePara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//ƽ�Ʊ任����
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_TranslatePara sTranslatePara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixTranslate;								//ƽ�Ʊ任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	//����ƽ�ƾ���
	MatrixWorld = MatrixWorld * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//ƽ�Ʊ任����
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixScale;									//���ű任����
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;	//��ת�任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	//�������ž���
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);	//������ת����X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);	//������ת����Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);	//������ת����Z
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_TranslatePara sTranslatePara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//ƽ�Ʊ任����
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_TranslatePara sTranslatePara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixScale;									//���ű任����
	D3DXMATRIX MatrixTranslate;								//ƽ�Ʊ任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	//�������ž���
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	//����ƽ�ƾ���
	MatrixWorld = MatrixWorld * MatrixScale * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//ƽ�Ʊ任����
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;	//��ת�任����
	D3DXMATRIX MatrixTranslate;								//ƽ�Ʊ任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);	//������ת����X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);	//������ת����Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);	//������ת����Z
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	//����ƽ�ƾ���
	MatrixWorld = MatrixWorld * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_ScalePara sScalePara			//�����任����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixScale;									//���ű任����
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;	//��ת�任����
	D3DXMATRIX MatrixTranslate;								//ƽ�Ʊ任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	//�������ž���
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);	//������ת����X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);	//������ת����Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);	//������ת����Z
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	//����ƽ�ƾ���
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DWorldSpaceTransform(DG3D_WorldTransformPara sWorldTransformPara)
// @Purpose: DirectGraphics3D��������任
// @Since: v1.00a
// @Para: DG3D_ScalePara sScalePara			//�����任����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DWorldSpaceTransform(DG3D_WorldTransformPara sWorldTransformPara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixScale;									//���ű任����
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;	//��ת�任����
	D3DXMATRIX MatrixTranslate;								//ƽ�Ʊ任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixScaling(&MatrixScale, sWorldTransformPara.sScalePara.fScaleX, sWorldTransformPara.sScalePara.fScaleY, sWorldTransformPara.sScalePara.fScaleZ);	//�������ž���
	D3DXMatrixRotationX(&MatrixRotateX, sWorldTransformPara.sRotatePara.fRotateX);	//������ת����X
	D3DXMatrixRotationY(&MatrixRotateY, sWorldTransformPara.sRotatePara.fRotateY);	//������ת����Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sWorldTransformPara.sRotatePara.fRotateZ);	//������ת����Z
	D3DXMatrixTranslation(&MatrixTranslate, sWorldTransformPara.sTranslatePara.fTranslateX, sWorldTransformPara.sTranslatePara.fTranslateY, sWorldTransformPara.sTranslatePara.fTranslateZ);	//����ƽ�ƾ���
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//�����λ��(�۲���λ��)
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye)
{
	D3DXMATRIX MatrixView;
	D3DXVECTOR3 Vector_At(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vector_Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&MatrixView, pvEye, &Vector_At, &Vector_Up);
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//�����λ��(�۲���λ��)
// @Para: D3DXVECTOR3* pvAt			//����λ��
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt)
{
	D3DXMATRIX MatrixView;
	D3DXVECTOR3 Vector_Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&MatrixView, pvEye, pvEye, &Vector_Up);
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt, D3DXVECTOR3* pvUp)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//�����λ��(�۲���λ��)
// @Para: D3DXVECTOR3* pvAt			//����λ��
// @Para: D3DXVECTOR3* pvUp			//��������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt, D3DXVECTOR3* pvUp)
{
	D3DXMATRIX MatrixView;
	D3DXMatrixLookAtLH(&MatrixView, pvEye, pvAt, pvUp);
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DViewSpaceTransform(DG3D_ViewTransformPara sViewTransformPara)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//�����λ��(�۲���λ��)
// @Para: D3DXVECTOR3* pvAt			//����λ��
// @Para: D3DXVECTOR3* pvUp			//��������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DViewSpaceTransform(DG3D_ViewTransformPara sViewTransformPara)
{
	D3DXMATRIX MatrixView;
	D3DXMatrixLookAtLH(&MatrixView, &(sViewTransformPara.vEye), &(sViewTransformPara.vAt), &(sViewTransformPara.vUp));
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPerspectiveTransform(DG3D_PrespectiveTransformPara sPrespectiveTransformPara)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: DG3D_PrespectiveTransformPara sPrespectiveTransformPara		//ͶӰ�任�ṹ�����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPerspectiveTransform(DG3D_PrespectiveTransformPara sPrespectiveTransformPara)
{
	D3DXMATRIX MatrixProject;
	D3DXMatrixPerspectiveFovLH(&MatrixProject, sPrespectiveTransformPara.fovy, sPrespectiveTransformPara.fAspect, sPrespectiveTransformPara.fZn, sPrespectiveTransformPara.fZf);
	m_pD3D9Device->SetTransform(D3DTS_PROJECTION, &MatrixProject);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPerspectiveTransform(float fovy, float fAspect, float fZn, float fZf)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: DG3D_PrespectiveTransformPara sPrespectiveTransformPara		//ͶӰ�任�ṹ�����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPerspectiveTransform(float fovy, float fAspect, float fZn, float fZf)
{
	D3DXMATRIX MatrixProject;
	D3DXMatrixPerspectiveFovLH(&MatrixProject, fovy, fAspect, fZn, fZf);
	m_pD3D9Device->SetTransform(D3DTS_PROJECTION, &MatrixProject);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DViewPortTransform(DG3D_ViewPortTransformPara sViewPortTransformPara)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: DG3D_ViewPortTransformPara sViewPortTransformPara				//�ӿڱ任�ṹ�����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DViewPortTransform(DG3D_ViewPortTransformPara sViewPortTransformPara)
{
	D3DVIEWPORT9 ViewPort;
	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = sViewPortTransformPara.nUserWidth;
	ViewPort.Height = sViewPortTransformPara.nUserHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	m_pD3D9Device->SetViewport(&ViewPort);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DViewPortTransform(int nUserWidth, int nUserHeight)
// @Purpose: DirectGraphics3D�ӿڱ任
// @Since: v1.00a
// @Para: DG3D_ViewPortTransformPara sViewPortTransformPara				//�ӿڱ任�ṹ�����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DViewPortTransform(int nUserWidth, int nUserHeight)
{
	D3DVIEWPORT9 ViewPort;
	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = nUserWidth;
	ViewPort.Height = nUserHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	m_pD3D9Device->SetViewport(&ViewPort);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DMatrixTransform(DG3D_WorldTransformPara sWorldTransformPara, DG3D_ViewTransformPara sViewTransformPara, DG3D_PrespectiveTransformPara sPrespectiveTransformPara, DG3D_ViewPortTransformPara sViewPortTransformPara)
// @Purpose: DirectGraphics3D����任
// @Since: v1.00a
// @Para: DG3D_ViewPortTransformPara sViewPortTransformPara				
// @Return: None
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DMatrixTransform(DG3D_WorldTransformPara sWorldTransformPara, DG3D_ViewTransformPara sViewTransformPara, DG3D_PrespectiveTransformPara sPrespectiveTransformPara, DG3D_ViewPortTransformPara sViewPortTransformPara)
{
	D3DXMATRIX MatrixWorld;									//����任����
	D3DXMATRIX MatrixScale;									//���ű任����
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;	//��ת�任����
	D3DXMATRIX MatrixTranslate;								//ƽ�Ʊ任����

	D3DXMatrixIdentity(&MatrixWorld);	//��λ������
	D3DXMatrixScaling(&MatrixScale, sWorldTransformPara.sScalePara.fScaleX, sWorldTransformPara.sScalePara.fScaleY, sWorldTransformPara.sScalePara.fScaleZ);	//�������ž���
	D3DXMatrixRotationX(&MatrixRotateX, sWorldTransformPara.sRotatePara.fRotateX);	//������ת����X
	D3DXMatrixRotationY(&MatrixRotateY, sWorldTransformPara.sRotatePara.fRotateY);	//������ת����Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sWorldTransformPara.sRotatePara.fRotateZ);	//������ת����Z
	D3DXMatrixTranslation(&MatrixTranslate, sWorldTransformPara.sTranslatePara.fTranslateX, sWorldTransformPara.sTranslatePara.fTranslateY, sWorldTransformPara.sTranslatePara.fTranslateZ);	//����ƽ�ƾ���
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);		//��������任

	D3DXMATRIX MatrixView;
	D3DXMatrixLookAtLH(&MatrixView, &(sViewTransformPara.vEye), &(sViewTransformPara.vAt), &(sViewTransformPara.vUp));
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);

	D3DXMATRIX MatrixProject;
	D3DXMatrixPerspectiveFovLH(&MatrixProject, sPrespectiveTransformPara.fovy, sPrespectiveTransformPara.fAspect, sPrespectiveTransformPara.fZn, sPrespectiveTransformPara.fZf);
	m_pD3D9Device->SetTransform(D3DTS_PROJECTION, &MatrixProject);

	D3DVIEWPORT9 ViewPort;
	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = sViewPortTransformPara.nUserWidth;
	ViewPort.Height = sViewPortTransformPara.nUserHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	m_pD3D9Device->SetViewport(&ViewPort);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DLightSetting(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9����
// @Para: D3DCOLOR dwAmbientLight					//������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DLightSettingPoint(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, float fRange, D3DCOLOR dwAmbientLight)
{
	D3DLIGHT9 D3D9Light;

	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));		//����ڴ�

	D3D9Light.Type = D3DLIGHT_POINT;				//��Դ����(���Դ)
	D3D9Light.Ambient = cAmbient;					//������
	D3D9Light.Diffuse = cDiffuse;					//�������
	D3D9Light.Specular = cSpecular;					//���淴���
	D3D9Light.Position = vPosition;					//���Դλ��
	D3D9Light.Attenuation0 = 1.0f;					//��Դ˥��ϵ��0
	D3D9Light.Attenuation1 = 0.0f;					//��Դ˥��ϵ��1
	D3D9Light.Attenuation2 = 0.0f;					//��Դ˥��ϵ��2
	D3D9Light.Range = fRange;						//��Դ��Χ

	m_pD3D9Device->SetLight(0, &D3D9Light);										//���ù�Դ  
	m_pD3D9Device->LightEnable(0, true);										//���ù���  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				//����һ�»�����
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DLightSettingDirectional(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9����
// @Para: D3DCOLOR dwAmbientLight					//������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DLightSettingDirectional(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vDirectional, D3DCOLOR dwAmbientLight)
{
	D3DLIGHT9 D3D9Light;

	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));		//����ڴ�

	D3D9Light.Type = D3DLIGHT_DIRECTIONAL;			//��Դ����(ƽ�й�Դ)
	D3D9Light.Ambient = cAmbient;					//������
	D3D9Light.Diffuse = cDiffuse;					//�������
	D3D9Light.Specular = cSpecular;					//���淴���
	D3D9Light.Direction = vDirectional;				//ƽ�йⷽ��

	m_pD3D9Device->SetLight(0, &D3D9Light);										//���ù�Դ  
	m_pD3D9Device->LightEnable(0, true);										//���ù���  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				//����һ�»�����
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DLightSettingSpot(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9����
// @Para: D3DCOLOR dwAmbientLight					//������
// @Return: None
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DLightSettingSpot(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight)
{
	D3DLIGHT9 D3D9Light;

	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));		//����ڴ�

	D3D9Light.Type = D3DLIGHT_SPOT;					//��Դ����(�۹�ƹ�Դ)
	D3D9Light.Ambient = cAmbient;					//������
	D3D9Light.Diffuse = cDiffuse;					//�������
	D3D9Light.Specular = cSpecular;					//���淴���
	D3D9Light.Position = vPosition;					//�۹�ƹ�Դλ��
	D3D9Light.Direction = vDirectional;				//ƽ�йⷽ��
	D3D9Light.Attenuation0 = 1.0f;					//��Դ˥��ϵ��0
	D3D9Light.Attenuation1 = 0.0f;					//��Դ˥��ϵ��1
	D3D9Light.Attenuation2 = 0.0f;					//��Դ˥��ϵ��2
	D3D9Light.Range = fRange;						//��Դ��Χ
	D3D9Light.Falloff = fFallOff;					//�۹��˥��
	D3D9Light.Phi = fPhi;
	D3D9Light.Theta = fTheta;

	m_pD3D9Device->SetLight(0, &D3D9Light);										//���ù�Դ  
	m_pD3D9Device->LightEnable(0, true);										//���ù���  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				//����һ�»�����
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DLightSetting(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9����
// @Para: D3DCOLOR dwAmbientLight					//������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DLightSetting(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight)
{
	m_pD3D9Device->SetLight(0, pD3D9Light);										//���ù�Դ  
	m_pD3D9Device->LightEnable(0, true);										//���ù���  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				//����һ�»�����
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DLightSetting(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9����
// @Para: D3DCOLOR dwAmbientLight					//������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DLightSetting(LightType eLightType, D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight)
{
	D3DLIGHT9 D3D9Light;

	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));		//����ڴ�

	switch (eLightType)
	{
	case LightType_Point://(���Դ)
		D3D9Light.Type = D3DLIGHT_POINT;				//��Դ����(���Դ)
		D3D9Light.Ambient = cAmbient;					//������
		D3D9Light.Diffuse = cDiffuse;					//�������
		D3D9Light.Specular = cSpecular;					//���淴���
		D3D9Light.Position = vPosition;					//���Դλ��
		D3D9Light.Attenuation0 = 1.0f;					//��Դ˥��ϵ��0
		D3D9Light.Attenuation1 = 0.0f;					//��Դ˥��ϵ��1
		D3D9Light.Attenuation2 = 0.0f;					//��Դ˥��ϵ��2
		D3D9Light.Range = fRange;						//��Դ��Χ
		break;
	case LightType_Direction://(ƽ�й�Դ)
		D3D9Light.Type = D3DLIGHT_DIRECTIONAL;			//��Դ����(ƽ�й�Դ)
		D3D9Light.Ambient = cAmbient;					//������
		D3D9Light.Diffuse = cDiffuse;					//�������
		D3D9Light.Specular = cSpecular;					//���淴���
		D3D9Light.Direction = vDirectional;				//ƽ�йⷽ��
		break;
	case LightType_Spot://(�۹�ƹ�Դ)
		D3D9Light.Type = D3DLIGHT_SPOT;					//��Դ����(�۹�ƹ�Դ)
		D3D9Light.Ambient = cAmbient;					//������
		D3D9Light.Diffuse = cDiffuse;					//�������
		D3D9Light.Specular = cSpecular;					//���淴���
		D3D9Light.Position = vPosition;					//�۹�ƹ�Դλ��
		D3D9Light.Direction = vDirectional;				//ƽ�йⷽ��
		D3D9Light.Attenuation0 = 1.0f;					//��Դ˥��ϵ��0
		D3D9Light.Attenuation1 = 0.0f;					//��Դ˥��ϵ��1
		D3D9Light.Attenuation2 = 0.0f;					//��Դ˥��ϵ��2
		D3D9Light.Range = fRange;						//��Դ��Χ
		D3D9Light.Falloff = fFallOff;					//�۹��˥��
		D3D9Light.Phi = fPhi;
		D3D9Light.Theta = fTheta;
		break;
	default:
		return;
		break;
	}

	m_pD3D9Device->SetLight(0, &D3D9Light);										//���ù�Դ  
	m_pD3D9Device->LightEnable(0, true);										//���ù���  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				//����һ�»�����
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DMaterialSetting(D3DMATERIAL9* pD3D9Material)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DMATERIAL9* pD3D9Material				//D3D9����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DMaterialSetting(D3DMATERIAL9* pD3D9Material)
{
	m_pD3D9Device->SetMaterial(pD3D9Material);				//����һ�²���
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DMATERIAL9* pD3D9Material				//D3D9����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive)
{
	D3DMATERIAL9 D3D9Material;

	ZeroMemory(&D3D9Material, sizeof(D3DMATERIAL9));		//����ڴ�

	D3D9Material.Ambient = cAmbient;						//������
	D3D9Material.Diffuse = cDiffuse;						//�������
	D3D9Material.Specular = cSpecular;						//���淴���
	D3D9Material.Emissive = cEmissive;						//�����Է���

	m_pD3D9Device->SetMaterial(&D3D9Material);				//����һ�²���
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive)
// @Purpose: DirectGraphics3D��������
// @Since: v1.00a
// @Para: D3DMATERIAL9* pD3D9Material				//D3D9����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive, float fPower)
{
	D3DMATERIAL9 D3D9Material;

	ZeroMemory(&D3D9Material, sizeof(D3DMATERIAL9));		//����ڴ�

	D3D9Material.Ambient = cAmbient;						//������
	D3D9Material.Diffuse = cDiffuse;						//�������
	D3D9Material.Specular = cSpecular;						//���淴���
	D3D9Material.Emissive = cEmissive;						//�����Է���
	D3D9Material.Power = fPower;							//���淴��ǿ��

	m_pD3D9Device->SetMaterial(&D3D9Material);				//����һ�²���
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertex(Vertex3DBase* VertexArray, int nSize)
// @Purpose: DirectGraphics3D��䶥��
// @Since: v1.00a
// @Para: Vertex3DBase* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertex(Vertex3DBase* VertexArray, int nSize)
{
	Vertex3DBase* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertex(Vertex3DTexture* VertexArray, int nSize)
// @Purpose: DirectGraphics3D��䶥��
// @Since: v1.00a
// @Para: Vertex3DTexture* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertex(Vertex3DTexture* VertexArray, int nSize)
{
	Vertex3DTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertex(Vertex3DNormal* VertexArray, int nSize)
// @Purpose: DirectGraphics3D��䶥��
// @Since: v1.00a
// @Para: Vertex3DNormal* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertex(Vertex3DNormal* VertexArray, int nSize)
{
	Vertex3DNormal* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertex(Vertex3DNormalTexture* VertexArray, int nSize)
// @Purpose: DirectGraphics3D��䶥��
// @Since: v1.00a
// @Para: Vertex3DNormalTexture* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertex(Vertex3DNormalTexture* VertexArray, int nSize)
{
	Vertex3DNormalTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertex(Vertex3DNormalSpecularTexture* VertexArray, int nSize)
// @Purpose: DirectGraphics3D��䶥��
// @Since: v1.00a
// @Para: Vertex3DNormalSpecularTexture* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertex(Vertex3DNormalSpecularTexture* VertexArray, int nSize)
{
	Vertex3DNormalSpecularTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertex(Vertex3DType eVertex3DType, LPVOID VertexArray, int nSize)
// @Purpose: DirectGraphics3D��䶥��
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType
// @Para: LPVOID VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertex(Vertex3DType eVertex3DType, LPVOID VertexArray, int nSize)
{
	Vertex3DBase* pVertices3DBase = NULL;
	Vertex3DTexture* pVertices3DTexture = NULL;
	Vertex3DNormal* pVertices3DNormal = NULL;
	Vertex3DNormalTexture* pVertices3DNormalTexture = NULL;
	Vertex3DNormalSpecularTexture* pVertices3DNormalSpecularTexture = NULL;

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DBase, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DBase + i) = *((Vertex3DBase*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DTexture, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DTexture + i) = *((Vertex3DTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormal, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DNormal + i) = *((Vertex3DNormal*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalTexture, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DNormalTexture + i) = *((Vertex3DNormalTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalSpecularTexture, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DNormalSpecularTexture + i) = *((Vertex3DNormalSpecularTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	default:
		return;
		break;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingIndex(int nPlane)
// @Purpose: DirectGraphics3D�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingIndex(int nPlane)
{
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane)
// @Purpose: DirectGraphics3D��䶥�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane)
{
	//��䶥�㻺��
	Vertex3DBase* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane)
// @Purpose: DirectGraphics3D��䶥�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertexAndIndex(Vertex3DTexture* VertexArray, int nPlane)
{
	//��䶥�㻺��
	Vertex3DTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane)
// @Purpose: DirectGraphics3D��䶥�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormal* VertexArray, int nPlane)
{
	//��䶥�㻺��
	Vertex3DNormal* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane)
// @Purpose: DirectGraphics3D��䶥�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormalTexture* VertexArray, int nPlane)
{
	//��䶥�㻺��
	Vertex3DNormalTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane)
// @Purpose: DirectGraphics3D��䶥�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormalSpecularTexture* VertexArray, int nPlane)
{
	//��䶥�㻺��
	Vertex3DNormalSpecularTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane)
// @Purpose: DirectGraphics3D��䶥�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DPaddingVertexAndIndex(Vertex3DType eVertex3DType, LPVOID VertexArray, int nPlane)
{
	//��䶥�㻺��
	Vertex3DBase* pVertices3DBase = NULL;
	Vertex3DTexture* pVertices3DTexture = NULL;
	Vertex3DNormal* pVertices3DNormal = NULL;
	Vertex3DNormalTexture* pVertices3DNormalTexture = NULL;
	Vertex3DNormalSpecularTexture* pVertices3DNormalSpecularTexture = NULL;

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DBase, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DBase + i) = *((Vertex3DBase*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DTexture + i) = *((Vertex3DTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormal, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DNormal + i) = *((Vertex3DNormal*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DNormalTexture + i) = *((Vertex3DNormalTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalSpecularTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DNormalSpecularTexture + i) = *((Vertex3DNormalSpecularTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	default:
		return;
		break;
	}

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRenderStateAlphaEnable()
// @Purpose: DirectGraphics3D����Alpha���
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRenderStateAlphaEnable()
{
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//Alpha��Ͽ���
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRenderStateAlphaDisable()
// @Purpose: DirectGraphics3D�ر�Alpha���
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRenderStateAlphaDisable()
{
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					//Alpha��Ϲر�
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRenderStateLightEnable()
// @Purpose: DirectGraphics3D����Light����
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRenderStateLightEnable()
{
	m_pD3D9Device->SetRenderState(D3DRS_LIGHTING, TRUE);							//Light��������
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRenderStateLightDisable()
// @Purpose: DirectGraphics3D�ر�Light����
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRenderStateLightDisable()
{
	m_pD3D9Device->SetRenderState(D3DRS_LIGHTING, FALSE);							//Light�رչ���
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRenderStateSetting()
// @Purpose: DirectGraphics3D������Ⱦģʽ
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRenderStateSetting()
{
	//��Ⱦģʽ:Alpha�������
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//Alpha��Ͽ���
	m_pD3D9Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					//Alpha���ģʽ:ADD
	m_pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//��Ⱦģʽ:����������
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);//D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRender(Vertex3DType eVertex3DType, int nPlane, bool bIsTexture)
// @Purpose: DirectGraphics3D��Ⱦ
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//��������
// @Para: int nPlane					//����ƽ������
// @Para: bool bIsTexture				//�Ƿ���������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRender(Vertex3DType eVertex3DType, int nPlane, bool bIsTexture)
{
	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DBase));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormal));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormalTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormalSpecularTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture)
// @Purpose: DirectGraphics3D��Ⱦ
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//��������
// @Para: int nStartIndex				//��ʼ�����������
// @Para: int nPlane					//����ƽ������
// @Para: bool bIsTexture				//�Ƿ���������
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture)
{
	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DBase));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormal));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormalTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormalSpecularTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
// @Purpose: DirectGraphics3D��Ⱦ
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType			//��������
// @Para: int nStartIndex						//��ʼ�����������
// @Para: int nPlane							//����ƽ������
// @Para: LPDIRECT3DTEXTURE9 pRenderTexture		//������Ⱦ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics3D::DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
{
	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DBase));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormal));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormalTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex3DNormalSpecularTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}
}