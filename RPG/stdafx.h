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

// 按键宏
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define VK_B 0x42

// 字段（读写）
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

// 字段（只读）
#define CC_SYNTHESIZE_READONLY(typeName, valueName, funcName)\
public:\
	typeName get##funcName()\
	{\
		return valueName;\
	}\
protected:\
	typeName valueName;\

// 释放资源
#define CC_SAFE_DELETE(p) if (p) { delete p; p = nullptr; }

// 数据管理者管理类
#include "DataMgr.h"
// 游戏管理者
#include "GameMgr.h"
