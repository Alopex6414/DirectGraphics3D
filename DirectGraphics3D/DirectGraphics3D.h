/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics3D.h
* @brief	This File is DirectGraphics3D DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-11-29
*/
#pragma once

#ifndef __DIRECTGRAPHICS3D_H_
#define __DIRECTGRAPHICS3D_H_

//Include Windows Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	DIRECTGRAPHICS3D_EXPORTS
#define DIRECTGRAPHICS3D_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS3D_API	__declspec(dllimport)
#endif

//Struct Definition
//Vertex 3D Base(3D���������ʽ)
struct Vertex3DBase
{
	float X, Y, Z;
	DWORD COLOR;
	Vertex3DBase(float x, float y, float z, DWORD Color) :X(x), Y(y), Z(z), COLOR(Color) {}
};

#define D3DFVF_VERTEX3D_BASE	(D3DFVF_XYZ | D3DFVF_DIFFUSE)				//���������ʽģʽ(3D����/���������)

//Vertex 3D Texture(3D�������ʽ)
struct Vertex3DTexture
{
	float X, Y, Z;
	DWORD COLOR;
	float U, V;
	Vertex3DTexture(float x, float y, float z, DWORD Color, float u, float v) :X(x), Y(y), Z(z), COLOR(Color), U(u), V(v) {}
};

#define D3DFVF_VERTEX3D_TEXTURE	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//�������ʽģʽ(3D����/���������/����ͼ��)

//Vertex 3D Normal(3D���߶����ʽ)
struct Vertex3DNormal
{
	float X, Y, Z;
	float nX, nY, nZ;
	DWORD COLOR;
	Vertex3DNormal(float x, float y, float z, float nx, float ny, float nz, DWORD Color) :X(x), Y(y), Z(z), nX(nx), nY(ny), nZ(nz), COLOR(Color) {}
};

#define D3DFVF_VERTEX3D_NORMAL	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)	//���߶����ʽģʽ(3D����/��������/���������)

//Vertex 3D Normal Texture(3D�����������ʽ)(����դ��)
struct Vertex3DNormalTexture
{
	float X, Y, Z;
	float nX, nY, nZ;
	DWORD COLOR;
	float U, V;
	Vertex3DNormalTexture(float x, float y, float z, float nx, float ny, float nz, DWORD Color, float u, float v) :X(x), Y(y), Z(z), nX(nx), nY(ny), nZ(nz), COLOR(Color), U(u), V(v) {}
};

#define D3DFVF_VERTEX3D_NORMAL_TEXTURE	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//�����������ʽģʽ(3D����/��������/���������/����ͼ��)

//Vertex 3D Normal Specular Texture(3D���߾��淴���������ʽ)(���淴��⡢����դ��)
struct Vertex3DNormalSpecularTexture
{
	float X, Y, Z;
	float nX, nY, nZ;
	DWORD DIFFUSE;
	DWORD SPECULAR;
	float U, V;
	Vertex3DNormalSpecularTexture(float x, float y, float z, float nx, float ny, float nz, DWORD Diffuse, DWORD Specular, float u, float v) :X(x), Y(y), Z(z), nX(nx), nY(ny), nZ(nz), DIFFUSE(Diffuse), SPECULAR(Specular), U(u), V(v) {}
};

#define D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)	//���߾��淴���������ʽģʽ(3D����/��������/���������/����ͼ��)

//World Space Scale Transform
typedef struct
{
	float fScaleX;
	float fScaleY;
	float fScaleZ;
} DG3D_ScalePara;

//World Space Rotate Transform
typedef struct
{
	float fRotateX;
	float fRotateY;
	float fRotateZ;
} DG3D_RotatePara;

//World Space Translate Transform
typedef struct
{
	float fTranslateX;
	float fTranslateY;
	float fTranslateZ;
} DG3D_TranslatePara;

//World Space Transform
typedef struct
{
	DG3D_ScalePara sScalePara;
	DG3D_RotatePara sRotatePara;
	DG3D_TranslatePara sTranslatePara;
} DG3D_WorldTransformPara;

//View Space Transform
typedef struct
{
	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vAt;
	D3DXVECTOR3 vUp;
} DG3D_ViewTransformPara;

//Perspective Transform
typedef struct
{
	float fovy;										//Y������Ƕ�(����) eg:D3DX_PI * 0.5f
	float fAspect;									//�ӿ���Ļ����(���/�߶�)
	float fZn;										//�ӽ�����ü������
	float fZf;										//�ӽ���Զ�ü������
} DG3D_PrespectiveTransformPara;

//ViewPort Transform
typedef struct
{
	int nUserWidth;									//�����ӿڿ��
	int nUserHeight;								//�����ӿڸ߶�
} DG3D_ViewPortTransformPara;

//Enum Definition(Vertex��������)
enum Vertex3DType
{
	Vertex3D_Type_Base = 0,							//Base����
	Vertex3D_Type_Texture = 1,						//Texture����
	Vertex3D_Type_Normal = 2,						//Normal����
	Vertex3D_Type_Normal_Texture = 3,				//NormalTexture����
	Vertex3D_Type_Normal_Specular_Texture = 4,		//NormalSpecularTexture����
};

//Enum Definition(Light��Դ����)
enum LightType
{
	LightType_Point = 0,							//Point���Դ
	LightType_Direction = 1,						//Directionƽ�й�Դ
	LightType_Spot = 2,								//Spot�۹�ƹ�Դ
};

//Class Definition
class DIRECTGRAPHICS3D_API DirectGraphics3D
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;						//The Direct3D 9 Render Device 
	LPDIRECT3DVERTEXBUFFER9 m_pD3D9VertexBuffer;			//The Direct3D 9 Vertex Buffer
	LPDIRECT3DINDEXBUFFER9 m_pD3D9IndexBuffer;				//The Direct3D 9 Index  Buffer

private:
	LPDIRECT3DTEXTURE9 m_pD3D9Texture;						//The Direct3D 9 Texture

public:
	DirectGraphics3D();				//DirectGraphics3D Constructor Function
	virtual ~DirectGraphics3D();	//DirectGraphics3D Destructor  Function

	//����
	DirectGraphics3D(IDirect3DDevice9* pD3D9Device);	//DirectGraphics3D Constructor Function

	//��ʼ��
	virtual HRESULT WINAPI DirectGraphics3DInit(int nPlane);								//DirectGraphics3D Initialization(��ʼ��)
	virtual HRESULT WINAPI DirectGraphics3DInit(int nPlane, LPCWSTR lpszStrTexture);		//DirectGraphics3D Initialization(��ʼ��)
	virtual HRESULT WINAPI DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane);	//DirectGraphics3D Initialization(��ʼ��)
	virtual HRESULT WINAPI DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane, LPCWSTR lpszStrTexture);	//DirectGraphics3D Initialization(��ʼ��)
	
	//����(T)(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara);			//DirectGraphics3D WorldSpaceTransform(Scale)(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara);		//DirectGraphics3D WorldSpaceTransform(Rotate)(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_TranslatePara sTranslatePara);	//DirectGraphics3D WorldSpaceTransform(Translate)(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara);									//DirectGraphics3D WorldSpaceTransform(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_TranslatePara sTranslatePara);								//DirectGraphics3D WorldSpaceTransform(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara);							//DirectGraphics3D WorldSpaceTransform(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara);	//DirectGraphics3D WorldSpaceTransform(����任)
	virtual void WINAPI DirectGraphics3DWorldSpaceTransform(DG3D_WorldTransformPara sWorldTransformPara);												//DirectGraphics3D WorldSpaceTransform(����任)
	virtual void WINAPI DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye);																			//DirectGraphics3D ViewSpaceTransform(ȡ���任)
	virtual void WINAPI DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt);														//DirectGraphics3D ViewSpaceTransform(ȡ���任)
	virtual void WINAPI DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt, D3DXVECTOR3* pvUp);									//DirectGraphics3D ViewSpaceTransform(ȡ���任)
	virtual void WINAPI DirectGraphics3DViewSpaceTransform(DG3D_ViewTransformPara sViewTransformPara);													//DirectGraphics3D ViewSpaceTransform(ȡ���任)
	virtual void WINAPI DirectGraphics3DPerspectiveTransform(DG3D_PrespectiveTransformPara sPrespectiveTransformPara);									//DirectGraphics3D PerspectiveTransform(͸��/ͶӰ�任)
	virtual void WINAPI DirectGraphics3DPerspectiveTransform(float fovy, float fAspect, float fZn, float fZf);											//DirectGraphics3D PerspectiveTransform(͸��/ͶӰ�任)
	virtual void WINAPI DirectGraphics3DViewPortTransform(DG3D_ViewPortTransformPara sViewPortTransformPara);											//DirectGraphics3D ViewPortTransform(�ӿڱ任)
	virtual void WINAPI DirectGraphics3DViewPortTransform(int nUserWidth, int nUserHeight);																//DirectGraphics3D ViewPortTransform(�ӿڱ任)
	virtual void WINAPI DirectGraphics3DMatrixTransform(DG3D_WorldTransformPara sWorldTransformPara, DG3D_ViewTransformPara sViewTransformPara, DG3D_PrespectiveTransformPara sPrespectiveTransformPara, DG3D_ViewPortTransformPara sViewPortTransformPara);					//DirectGraphics3D MatrixTransform

	//����(L)
	virtual void WINAPI DirectGraphics3DLightSettingPoint(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, float fRange, D3DCOLOR dwAmbientLight);																							//DirectGraphics3D Light Setting(��Դ����)(���Դ)
	virtual void WINAPI DirectGraphics3DLightSettingDirectional(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vDirectional, D3DCOLOR dwAmbientLight);																								//DirectGraphics3D Light Setting(��Դ����)(ƽ�й�Դ)
	virtual void WINAPI DirectGraphics3DLightSettingSpot(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight);						//DirectGraphics3D Light Setting(��Դ����)(�۹�ƹ�Դ)
	virtual void WINAPI DirectGraphics3DLightSetting(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight);																																											//DirectGraphics3D Light Setting(��Դ����)
	virtual void WINAPI DirectGraphics3DLightSetting(LightType eLightType, D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight);		//DirectGraphics3D Light Setting(��Դ����)

	//����(M)
	virtual void WINAPI DirectGraphics3DMaterialSetting(D3DMATERIAL9* pD3D9Material);																					//DirectGraphics3D Material Setting(��������)
	virtual void WINAPI DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive);								//DirectGraphics3D Material Setting(��������)
	virtual void WINAPI DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive, float fPower);				//DirectGraphics3D Material Setting(��������)

	//���
	//����
	virtual void WINAPI DirectGraphics3DPaddingVertex(Vertex3DBase* VertexArray, int nSize);						//DirectGraphics3D Padding Vertex(��䶥������)(3D���������ʽ)
	virtual void WINAPI DirectGraphics3DPaddingVertex(Vertex3DTexture* VertexArray, int nSize);						//DirectGraphics3D Padding Vertex(��䶥������)(3D�������ʽ)
	virtual void WINAPI DirectGraphics3DPaddingVertex(Vertex3DNormal* VertexArray, int nSize);						//DirectGraphics3D Padding Vertex(��䶥������)(3D���߶����ʽ)
	virtual void WINAPI DirectGraphics3DPaddingVertex(Vertex3DNormalTexture* VertexArray, int nSize);				//DirectGraphics3D Padding Vertex(��䶥������)(3D�����������ʽ)
	virtual void WINAPI DirectGraphics3DPaddingVertex(Vertex3DNormalSpecularTexture* VertexArray, int nSize);		//DirectGraphics3D Padding Vertex(��䶥������)(3D���߾��淴���������ʽ)
	virtual void WINAPI DirectGraphics3DPaddingVertex(Vertex3DType eVertex3DType, LPVOID VertexArray, int nSize);	//DirectGraphics3D Padding Vertex(��䶥������)

	//����
	virtual void WINAPI DirectGraphics3DPaddingIndex(int nPlane);													//DirectGraphics3D Padding Index(�����������)

	//All
	virtual void WINAPI DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane);							//DirectGraphics3D Padding Vertex and Index(��䶥�����������)
	virtual void WINAPI DirectGraphics3DPaddingVertexAndIndex(Vertex3DTexture* VertexArray, int nPlane);						//DirectGraphics3D Padding Vertex and Index(��䶥�����������)
	virtual void WINAPI DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormal* VertexArray, int nPlane);							//DirectGraphics3D Padding Vertex and Index(��䶥�����������)
	virtual void WINAPI DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormalTexture* VertexArray, int nPlane);					//DirectGraphics3D Padding Vertex and Index(��䶥�����������)
	virtual void WINAPI DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormalSpecularTexture* VertexArray, int nPlane);			//DirectGraphics3D Padding Vertex and Index(��䶥�����������)
	virtual void WINAPI DirectGraphics3DPaddingVertexAndIndex(Vertex3DType eVertex3DType, LPVOID VertexArray, int nPlane);		//DirectGraphics3D Padding Vertex and Index(��䶥�����������)

	//��Ⱦ
	//��Ⱦģʽ
	virtual void WINAPI DirectGraphics3DRenderStateAlphaEnable();																//DirectGraphics3D Render State Setting(����Alpha���)//��Ⱦ��Ϲر�Alpha���
	virtual void WINAPI DirectGraphics3DRenderStateAlphaDisable();																//DirectGraphics3D Render State Setting(�ر�Alpha���)
	virtual void WINAPI DirectGraphics3DRenderStateSetting();																	//DirectGraphics3D Render State Setting(������Ⱦģʽ)

	//��Ⱦ
	virtual void WINAPI DirectGraphics3DRender(Vertex3DType eVertex3DType, int nPlane, bool bIsTexture = false);											//DirectGraphics3D Render(��Ⱦ)
	virtual void WINAPI DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture = false);							//DirectGraphics3D Render(��Ⱦ)
	virtual void WINAPI DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture);					//DirectGraphics3D Render(��Ⱦ)
};


#endif