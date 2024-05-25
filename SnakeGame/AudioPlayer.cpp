#include "AudioPlayer.h"
#include "Exception.h"

AudioPlayer& AudioPlayer::GetInstance()
{
	static AudioPlayer instance;
	return instance;
}

void AudioPlayer::ToggleSoundMute()
{
	_bSoundMuted = !_bSoundMuted;

	if (_bSoundMuted)
		_currentSound.setVolume(0.0);
	else
		_currentSound.setVolume(_soundVolume);
}

void AudioPlayer::ToggleMusicMute()
{
	_bMusicMuted = !_bMusicMuted;

	if (_bMusicMuted)
		_currentMusic.setVolume(0.0);
	else
		_currentMusic.setVolume(_musicVolume);
}

void AudioPlayer::PlaySound(const ESound soundType)
{
	switch (soundType)
	{
		case ESound::Menu:
			_currentSound.setBuffer(_menuBuffer);
			_currentSound.play();
			break;
		case ESound::Hit:
			_currentSound.setBuffer(_hitBuffer);
			_currentSound.play();
			break;
		case ESound::Eat:
			_currentSound.setBuffer(_eatBuffer);	
			_currentSound.play();
			break;
		case ESound::Theme:
			_currentMusic.setBuffer(_themeBuffer);			
			_currentMusic.play();
			break;
		case ESound::None:
		default:
			_currentSound.resetBuffer();
			_currentMusic.resetBuffer();
			break;
	}
}

void AudioPlayer::StopMusic()
{
	_currentMusic.stop();
}

AudioPlayer::AudioPlayer()
{
	try
	{
		_themeBuffer.loadFromFile(_themePath);
		_hitBuffer.loadFromFile(_hitPath);
		_eatBuffer.loadFromFile(_eatPath);
		_menuBuffer.loadFromFile(_menuPath);
	}
	catch (const LoadResourceException& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	_musicVolume = 80.0f;
	_soundVolume = 30.0f;
	_currentSound.setVolume(_soundVolume);
	_bMusicMuted = false;
	_bSoundMuted = false;
	_currentMusic.setLoop(true);
}
