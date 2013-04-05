#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include "vcapconfig.h"

class Engine;
class VCapAudioEncoder;
class FileFilter;
class Mic;
class VCapSpxEncFilter;
class FfmEncoder;
class AudioCapture : public IVCapAudioCapture
{
public:
	AudioCapture(Engine* engine);
	~AudioCapture();

public:
	virtual void	setFileName(const wchar_t* filename);
	virtual int		startCapture();
	virtual int		stopCapture();

private:
	Engine*			m_pEngine;
	std::wstring	m_wstrFileName;

	Mic*			m_pMic;	
	FileFilter*		m_pFileFilter;
	FfmEncoder*		m_pFfmEncoder;
	std::vector<Mic*>	m_arrMics;
};


#endif