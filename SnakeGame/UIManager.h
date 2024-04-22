#pragma once

class UIManager
{
public:
	static UIManager& GetInstance();

	UIManager(const UIManager& other) = delete;
	UIManager(UIManager&& other) noexcept = delete;
	UIManager& operator=(const UIManager& other) = delete;
	UIManager& operator=(UIManager&& other) noexcept = delete;

	void ShowMainMenu();
	void ShowCurrentScore();
	void ShowDifficultyMenu();
	void ShowHighScoresMenu();
	void ShowSettingsMenu();
	void Update();
	void HandleInput();

private:
	UIManager() = default;
	~UIManager() = default;
};