#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include "vcapconfig.h"

class VCapEngine;
class VCapAudioEncoder;
class VCapFileFilter;
class VCapMic;
class VCapSpxEncFilter;
class FfmEncoder;
class AudioCapture : public IVCapAudioCapture
{
public:
	AudioCapture();
	~AudioCapture();

public:
	virtual void	setFileName(const wchar_t* filename);
	virtual void	setAudioFormat(int format);
	virtual int		startCapture();
	virtual int		stopCapture();

private:
	VCapEngine*			m_pEngine;
	std::wstring		m_wstrFileName;

	VCapMic*			m_pMic;	
	VCapFileFilter*		m_pFileFilter;
	FfmEncoder*			m_pFfmEncoder;
	std::vector<VCapMic*>	m_arrMics;
};


#endif