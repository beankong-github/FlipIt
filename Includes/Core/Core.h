#pragma once

// dll 외부로 템플릿 내보낼 때 발생하는 경고 비활성화.
#pragma warning(disable: 4251)
// 지역 변수의 주소를 반환할 때 발생하는 경고 비활성화.
#pragma warning(disable: 4172)

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if BuildEngineDLL
#define Engine_API __declspec(dllexport)
#else
#define Engine_API __declspec(dllimport)
#endif

#ifdef _DEBUG
	//#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new new
#else
#define new new
#endif

// 메모리 정리 함수.
template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& target)
{
	if (target)
	{
		delete[] target;
		target = nullptr;
	}
}

#include <vector>
template<typename T>
void SafeDeleteVector(std::vector<T>& vector)
{
	typename std::vector<T>::iterator iter = vector.begin();
	for (; iter != vector.end(); ++iter)
	{
		SafeDelete(*iter);
	}
	vector.clear();
}


#include <map>
template<typename T1, typename T2>
void SafeDeleteMap(std::map<T1, T2>& map)
{
	typename std::map<T1, T2>::iterator iter = map.begin();
	for (; iter != map.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	map.clear();
}

#include <unordered_map>
template<typename T1, typename T2>
void SafeDeleteHashTable(std::unordered_map<T1, T2>& hashTable)
{
	typename std::unordered_map<T1, T2>::iterator iter = hashTable.begin();
	for (; iter != hashTable.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	hashTable.clear();
}