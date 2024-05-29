#pragma once
#include "SFML/Audio.hpp"

// Class responsible for managing audio playback in the game.
class AudioPlayer
{
public:
	// Enum defining various sound types.
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

	// Toggles the mute state of all sounds.
	void ToggleSoundMute();

	// Toggles the mute state of the background music.
	void ToggleMusicMute();

	// Plays the specified sound.
	void PlaySound(const ESound soundType);

	// Stops the currently playing background music.
	void StopMusic();
private:
	// Private constructor to prevent instantiation.
	AudioPlayer();

	// Resources path
	const std::string _themePath = R"(Resources/Audio/PlayingMusic.wav)";
	const std::string _eatPath = R"(Resources/Audio/EatSound.wav)";
	const std::string _hitPath = R"(Resources/Audio/Hit.wav)";
	const std::string _menuPath = R"(Resources/Audio/MenuSelection.wav)";

	// Sound buffers for sounds
	sf::SoundBuffer _themeBuffer;
	sf::SoundBuffer _eatBuffer;
	sf::SoundBuffer _hitBuffer;
	sf::SoundBuffer _menuBuffer;

	// Sound objects
	sf::Sound _currentSound;
	sf::Sound _currentMusic;

	// Volume levels and flags
	float _musicVolume;
	bool _bMusicMuted;
	float _soundVolume;
	bool _bSoundMuted;
};

