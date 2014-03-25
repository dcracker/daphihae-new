//
//  iOSFileIO.h
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef __Project_iOS__iOSFileIO__
#define __Project_iOS__iOSFileIO__

#include <vector>
#include "Interfaces/IFileIO.h"


class CIOSFileIO : public IFileIO
{
protected:
    std::vector<IFile*>* m_arrFileInstances;

public:
    CIOSFileIO();
    virtual ~CIOSFileIO();
    
    IFile* ReadStorage( const char* fileName ) const;
    IFile* WriteStorage( const char* fileName ) const;
    IFile* ReadAsset( const char* fileName ) const;
};

#endif /* defined(__Project_iOS__iOSFileIO__) */
