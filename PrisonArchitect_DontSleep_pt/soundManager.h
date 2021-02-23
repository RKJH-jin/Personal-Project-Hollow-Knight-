#pragma once
#include "singletonBase.h"

#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER


class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>			arrSounds;
	typedef map<string, Sound**>::iterator	arrSoundsIter;

	typedef map<string, Channel**>			 arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;

private:
	System*			_system;
	Sound**			_sound;
	Channel**		_channel;

	arrSounds		_mTotalSounds;

	vector<string> _vBGM;	//�����
	vector<string> _vSFX;	//ȿ����

	float _masterVolume;	//������ ����
	float _bgmVolume;		//����� ����
	float _sfxVolume;		//ȿ���� ����

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);

	void play(string keyName, float volume = 1.0f);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	//���� ����
	void SetMasterVolume(float volume);
	void SetBGMVolume(float volume);
	void SetSFXVolume(float volume);

	float GetMasterVolume() { return _masterVolume; }
	float GetBGMVolume() { return _bgmVolume; }
	float GETSFXVolume() { return _sfxVolume; }

};

