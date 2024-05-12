#pragma once
#include "SFML/Audio.hpp"

class AudioPlayer
{
public:
	enum ESound
	{
		Eat,
		Theme,
		Hit,
		Menu,
		None
	};
public:
	static AudioPlayer& GetInstance();
	
	AudioPlayer(const AudioPlayer& other) = delete;
	AudioPlayer(AudioPlayer&& other) noexcept = delete;
	AudioPlayer& operator=(const AudioPlayer& other) = delete;
	AudioPlayer& operator=(AudioPlayer&& other) noexcept = delete;
	void ToggleSoundMute();
	void ToggleMusicMute();
	void PlaySound(ESound soundType);
private:
	AudioPlayer();
	const std::string _themePath = R"(Resources/Audio/Clinthammer__Background_Music.wav)";
	const std::string _eatPath = R"(Resources/Audio/Owlstorm__Snake_hit.wav)";
	const std::string _hitPath = R"(Resources/Audio/Maodin204__Lose.wav)";
	const std::string _menuPath = R"(Resources/Audio/Theevilsocks__menu-hover.wav)";
	sf::SoundBuffer _themeBuffer;
	sf::SoundBuffer _eatBuffer;
	sf::SoundBuffer _hitBuffer;
	sf::SoundBuffer _menuBuffer;
	sf::Sound _currentSound;
	sf::Sound _currentMusic;
	float _musicVolume;
	bool _bMusicMuted;
	float _soundVolume;
	bool _bSoundMuted;
};

