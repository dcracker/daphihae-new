//
//  iOSFileIO.mm
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#include "iOSFileIO.h"
#include "iOSFile.h"


CIOSFileIO::CIOSFileIO()
{
    m_arrFileInstances = new std::vector<IFile*>;
}

CIOSFileIO::~CIOSFileIO()
{
    while ( !m_arrFileInstances->empty() )
    {
        delete m_arrFileInstances->back();
        m_arrFileInstances->pop_back();
    }
    delete m_arrFileInstances;
}


IFile* CIOSFileIO::ReadStorage( const char* fileName ) const
{
    return NULL;
}

IFile* CIOSFileIO::WriteStorage( const char* fileName ) const
{
    return NULL;
}

IFile* CIOSFileIO::ReadAsset( const char *fileName ) const
{
    m_arrFileInstances->push_back( new CIOSFile( fileName ) );
    return m_arrFileInstances->back();
}