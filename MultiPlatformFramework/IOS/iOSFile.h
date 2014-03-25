//
//  iOSFile.h
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef __Project_iOS__iOSFile__
#define __Project_iOS__iOSFile__

#include "Interfaces/IFile.h"


class CIOSFile : public IFile
{
protected:
    int m_nFD;
    char m_strFileName[1024];
    
public:
    CIOSFile( const char* fileName );
    virtual ~CIOSFile();
    
    const char* GetFileName();
    bool ReadByte( void* out_byteBuffer, int numByteToRead );
};

#endif /* defined(__Project_iOS__iOSFile__) */
