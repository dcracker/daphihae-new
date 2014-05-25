#ifndef IPlatform_H_
#define IPlatform_H_

#include "IInput.h"
#include "IFileIO.h"
#include "IGraphics.h"
#include "IAudio.h"
#include "TSingleton.hpp"

class IPlatform : public TSingleton<IPlatform> {
public:
	virtual ~IPlatform() {}

	virtual 	  IInput*		GetInput()		const = 0;
	virtual const IFileIO*		GetFileIO()		const = 0;
	virtual const IGraphics*	GetGraphics()	const = 0;
	virtual const IAudio*		GetAudio()		const = 0;
};

#endif	// IPlatform_H_
