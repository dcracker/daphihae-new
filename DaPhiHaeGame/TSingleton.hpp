/**
 *	Singleton Pattern�� ���� ���ø� Ŭ����
 *	Ref : Game Programming Gems 1 - 1.3 �ڵ����� ����ü ��ƿ��Ƽ
 */

#pragma once
#include <cassert>

template <typename T> class TSingleton
{
public:
	TSingleton() {
		assert( ms_pSingleton == 0 );
		// ���� ����� ���� ó��
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