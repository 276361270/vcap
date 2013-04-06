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
	AudioCapture();
	~AudioCapture();

public:
	virtual void	setFileName(const wchar_t* filename);
	virtual void	setServer(char* ip, int port, char* app, char* stream);
	virtual int		startCapture();
	virtual int		stopCapture();

private:
	Engine*			m_pEngine;
	std::wstring	m_wstrFileName;

	Mic*			m_pMic;	
	FileFilter*		m_pFileFilter;
	FfmEncoder*		m_pFfmEncoder;
	std::vector<Mic*>	m_arrMics;

	std::string		m_strIp;
	int				m_nPort;
	std::string		m_strApp;
	std::string		m_strStream;
};


#endif