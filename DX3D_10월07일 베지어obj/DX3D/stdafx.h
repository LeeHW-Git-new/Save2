// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <assert.h>//예외처리 할 때 경고문 사용하기 위해 사용
#include <iostream>

#include<d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

using namespace std;

extern HWND g_hWnd;
#define SafeRelease(p)	{if(p) p->Release(); p = NULL;}
#define SafeDelete(p) {if(p) delete p; p = NULL;}

#define Singletone(class_name)\
	private:\
	class_name(void);\
	~class_name(void);\
	public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
	return &instance;\
	}

struct ST_PC_VERTEX 
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DCOLOR c;
	
	enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR3 t;
	enum {FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1};
};

struct ST_PT_VERTEX 
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum {FVF = D3DFVF_XYZ | D3DFVF_TEX1};
};

struct face
{
	int v;
	int t;
	int n;
};


#define Synthesize(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const {return varName;}\
public: inline void Set##funName(varType var) {varName = var;}

#define Synthesize_pass_by_Ref(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) {return varName;}\
public: inline void Set##funName(varType& var) {varName = var;}



#include "cDeviceManage.h"

/*
	1. 그리드 PN 형태로 수정하고 Light 적용
	2. Directional Light : 해 뜨고 지는 것
	3. Spot Light : 키 입력에 따라 방향 조정
	4. Point Light : 키 입력에 따라 범위 조정
	5. 각 라이트의 위치를 박스로 표시할 것
*/