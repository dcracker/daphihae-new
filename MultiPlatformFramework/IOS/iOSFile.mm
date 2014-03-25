//
//  iOSFile.cpp
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#include "iOSFile.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


CIOSFile::CIOSFile( const char* fileName )
    : m_nFD( -1 )
{
    strncpy( m_strFileName, fileName, 1024 );
    m_nFD = open( m_strFileName, O_RDONLY );
}

CIOSFile::~CIOSFile()
{
    close( m_nFD );
    m_nFD = -1;
}

const char* CIOSFile::GetFileName()
{
    return m_strFileName;
}

bool CIOSFile::ReadByte( void *out_byteBuffer, int numByteToRead )
{
    int numByteHasRead = (int)read( m_nFD, out_byteBuffer, numByteToRead );
    return (numByteHasRead == numByteToRead);
}