/**
 *	Singleton Pattern을 위한 템플릿 클래스
 *	Ref : Game Programming Gems 1 - 1.3 자동적인 단일체 유틸리티
 */

#pragma once
#include <cassert>

template <typename T> class TSingleton
{
public:
	TSingleton() {
		assert( ms_pSingleton == 0 );
		// 다중 상속을 위한 처리
		int offset = (int)(T*)1 - (int)(TSingleton<T>*)(T*)1;
		ms_pSingleton = (T*)( (int)this + offset );
	}

	~TSingleton() {
		assert( ms_pSingleton );
		ms_pSingleton = 0;
	}

	static T& getInstance() {
		assert( ms_pSingleton && "has no Singleton instance" );
		return *ms_pSingleton;
	}

	static T* getInstancePtr() {
		assert( ms_pSingleton && "has no Singleton instance" );
		return ms_pSingleton;
	}

private:
	static T* ms_pSingleton;
};

template <typename T> T* TSingleton<T>::ms_pSingleton = 0;