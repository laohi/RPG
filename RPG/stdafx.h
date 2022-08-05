#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

// ������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define VK_B 0x42

// �ֶΣ���д��
#define CC_SYNTHESIZE(typeName, valueName, funcName)\
public:\
	void set##funcName(typeName value)\
	{\
		valueName = value;\
	}\
	typeName get##funcName()\
	{\
		return valueName;\
	}\
protected:\
	typeName valueName;\

// �ֶΣ�ֻ����
#define CC_SYNTHESIZE_READONLY(typeName, valueName, funcName)\
public:\
	typeName get##funcName()\
	{\
		return valueName;\
	}\
protected:\
	typeName valueName;\

// �ͷ���Դ
#define CC_SAFE_DELETE(p) if (p) { delete p; p = nullptr; }

// ���ݹ����߹�����
#include "DataMgr.h"
// ��Ϸ������
#include "GameMgr.h"
