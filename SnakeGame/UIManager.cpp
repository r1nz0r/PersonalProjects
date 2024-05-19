#include <iomanip>
#include <sstream>
#include "UIManager.h"
#include "Exception.h"
#include "GameSettings.h"
#include "Time.h"
#include "Game.h"
#include "TextBlock.h"
#include "Menu.h"
#include "TextInputBox.h"
#include "Application.h"
#include "AudioPlayer.h"

UIManager& UIManager::GetInstance()
{
	static UIManager sUiManager;
	return sUiManager;
}

UIManager::UIManager()
{
	try
	{
		_mainFont.loadFromFile(_fontPath);
	}
	catch (const LoadResourceException& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	_background.setSize(sf::Vector2f(GameSettings::WINDOW_SIZE.x, GameSettings::WINDOW_SIZE.y));
	_background.setFillColor(sf::Color(10, 20, 40, 230)); // Little transparent dark blue color.

	CreateMenuItems();
	CreateSettingsCheckBoxes();
	CreateHudLabels();
}

UIManager::~UIManager()
{
	Clear();
}

void UIManager::ShowMainMenu()
{
	_selectedMenu = _mainMenu;
	_bIsMenuOpen = true;
}

void UIManager::UpdateScoreText(const int score)
{
	if (!_scoreText)
		return;

	_scoreText->setString("Score: " + std::to_string(score));
}

void UIManager::UpdatePlayTimeText(const float time)
{
	if (!_timeText)
		return;

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << time;
	_timeText->setString("Playing time: " + oss.str() + " s");

	float timeLabelOffsetX = 35.0f;
	sf::Vector2f timeLabelPosition
	{
		timeLabelOffsetX,
		GameSettings::UI_HUD_OFFSET_Y / 4.0f
	};
	_timeText->setPosition(timeLabelPosition);
}

void UIManager::UpdatePrepareText(const float time)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << time;
	_timeText->setString("Get ready! " + oss.str());
	
	sf::Vector2f timeLabelPosition
	{
		(GameSettings::WINDOW_SIZE.x - _timeText->getLocalBounds().width) / 2.0f,
		GameSettings::WINDOW_SIZE.y / 3.0f
	};
	_timeText->setPosition(timeLabelPosition);
}

void UIManager::UpdateGameOverLabel(const int score, const int highScore)
{
	if (!_gameOverBlock)
		return;

	_gameOverBlock->Clear();
	_gameOverBlock->AddText(std::string("Game Over!"), _mainFont);
	_gameOverBlock->AddText(std::string("Your score is - " + std::to_string(score)), _mainFont);
	_gameOverBlock->AddText(std::string("High score is - " + std::to_string(highScore)), _mainFont);
	_gameOverBlock->AlignTexts();
}

void UIManager::Update()
{
	sf::Event menuEvent;

	while (_menuWindow->pollEvent(menuEvent))
	{
		HandleInput(menuEvent);
	}

	_menuWindow->clear();

	if (_selectedMenu == _settingsMenu)
		ShowSettingsCheckBoxes(*_menuWindow);

	if (_bIsInputActive)
		_nameInputBox->Draw(*_menuWindow);
	else
		_selectedMenu->Draw(*_menuWindow);

	_menuWindow->display();
}

void UIManager::HandleInput(const sf::Event& menuEvent)
{
	switch (menuEvent.type)
	{
	case sf::Event::Closed:
		_menuWindow->close();
		break;
	case sf::Event::KeyPressed:
		if (menuEvent.key.scancode == sf::Keyboard::Scancode::Escape)
		{
			AudioPlayer::GetInstance().PlaySound(AudioPlayer::ESound::Menu);

			if (_bIsMenuOpen && _selectedMenu == _enterNameDialog)
			{
				_bIsInputActive = false;
				_nameInputBox->UpdateText("", sf::Color::White); // Очищаем текст
			}

			if (_selectedMenu->GetRootItem())
				_selectedMenu = _selectedMenu->GetRootItem();
		}
		else if (_bIsInputActive == false)
		{
			_selectedMenu->HandleInput(menuEvent);
		}
		break;
	case sf::Event::TextEntered:
		if (_bIsInputActive)
		{
			std::string enteredText = _nameInputBox->HandleTextEntered(menuEvent);

			if (!enteredText.empty())
			{
				std::cout << enteredText << std::endl;
				_bIsInputActive = false; 
				_selectedMenu = _mainMenu;
			}
		}			
		break;
	default:
		break;
	}
}

void UIManager::DrawPlayingHud(sf::RenderWindow& window)
{
	if (_scoreText != nullptr)
		_scoreText->Draw(window);

	if (_timeText != nullptr)
		_timeText->Draw(window);
}

void UIManager::DrawPrepareHud(sf::RenderWindow& window)
{
	DrawBackground(window, GameSettings::sPrepareBackgroundColor);

	if (_timeText != nullptr)
		_timeText->Draw(window);
}

void UIManager::DrawPauseHud(sf::RenderWindow& window, Menu* pauseMenu)
{
	DrawBackground(window, GameSettings::sPauseBackgroundColor);

	if (!pauseMenu)
		return;

	pauseMenu->Draw(window);
}

void UIManager::DrawGameOverHud(sf::RenderWindow& window)
{
	DrawBackground(window, GameSettings::sGameOverBackgroundColor);

	if (_gameOverBlock != nullptr)
		_gameOverBlock->Draw(window);
}

void UIManager::DrawBackground(sf::RenderWindow& window, const sf::Color& color)
{
	_background.setFillColor(sf::Color(color));
	window.draw(_background);
}

void UIManager::CreateHudLabels()
{
	_timeText = new Text {"", _mainFont, sf::Color::White};
	_gameOverBlock = new TextBlock
	{
		sf::Vector2f(GameSettings::WINDOW_SIZE.x / 2, GameSettings::WINDOW_SIZE.x / 2),
		10 
	};

	float scoreLabelOffsetX = 145.0f;
	sf::Vector2f scoreTextPosition
	{
		GameSettings::WINDOW_SIZE.x - scoreLabelOffsetX,
		GameSettings::UI_HUD_OFFSET_Y / 4.0
	};

	_scoreText = new Text { "", _mainFont, sf::Color::Cyan };
	_scoreText->setPosition(scoreTextPosition);
	
}

void UIManager::ShowSettingsCheckBoxes(sf::RenderWindow& window)
{
	_soundCheck->Draw(window);
	_musicCheck->Draw(window);
}

void UIManager::CreateSettingsCheckBoxes()
{
	_soundCheck = new TextInputBox(GetFont(), 1u);
	_soundCheck->SetPosition({ _menuWindow->getSize().x / 1.2f, _menuWindow->getSize().y / 2.3f });
	_soundCheck->UpdateText("V", sf::Color::Green);
	_musicCheck = new TextInputBox(GetFont(), 1u);
	_musicCheck->SetPosition({ _menuWindow->getSize().x / 1.2f, _menuWindow->getSize().y / 1.9f });
	_musicCheck->UpdateText("V", sf::Color::Green);
}

void UIManager::CreateMenuItems()
{
	_menuWindow = new sf::RenderWindow { sf::VideoMode(300,400), "Menu" };

	Menu::ItemsList settingsMenuItems
	{
		{"Sound", [this]() { std::cout << "Sound selected!" << std::endl; ToggleCheckbox(_soundCheck); AudioPlayer::GetInstance().ToggleSoundMute(); }},
		{"Music", [this]() { std::cout << "Music selected!" << std::endl; ToggleCheckbox(_musicCheck); AudioPlayer::GetInstance().ToggleMusicMute(); }},
	};
	_settingsMenu = new Menu { settingsMenuItems, GetFont() , *_menuWindow, "Settings", 20.0f };
	_settingsMenu->SetMenuItemsAlignment(TextBlock::Alignment::End, TextBlock::Alignment::Center, Text::Alignment::Start);

	Menu::ItemsList difficultyItems
	{
		{"Beginner", [this]() { std::cout << "Beginner selected!" << std::endl; Application::GetInstance().GetGame()->SetDifficulty(EGameDifficulty::Beginner); _selectedMenu = _mainMenu; }},
		{"Easy", [this]() { std::cout << "Easy selected!" << std::endl; Application::GetInstance().GetGame()->SetDifficulty(EGameDifficulty::Easy); _selectedMenu = _mainMenu; }},
		{"Normal", [this]() { std::cout << "Normal selected!" << std::endl; Application::GetInstance().GetGame()->SetDifficulty(EGameDifficulty::Normal); _selectedMenu = _mainMenu; }},
		{"Hard", [this]() { std::cout << "Hard selected!" << std::endl; Application::GetInstance().GetGame()->SetDifficulty(EGameDifficulty::Hard); _selectedMenu = _mainMenu; }},
		{"Insane", [this]() { std::cout << "Insane selected!" << std::endl; Application::GetInstance().GetGame()->SetDifficulty(EGameDifficulty::Insane); _selectedMenu = _mainMenu; }},
	};
	_difficultyMenu = new Menu { difficultyItems, GetFont(), *_menuWindow, "Difficulty" };

	Menu::ItemsList enterNameItems
	{
		{"Yes", [this]() { std::cout << "Yes selected!" << std::endl; _bIsInputActive = true; }},
		{"No", [this]() { std::cout << "No selected!" << std::endl; _selectedMenu = _mainMenu; }},
	};
	_enterNameDialog = new Menu { enterNameItems, GetFont() , *_menuWindow, "Wish to enter name?", 20.0f };
	_enterNameDialog->SetMenuItemsAlignment(TextBlock::Alignment::Center, TextBlock::Alignment::Center, Text::Alignment::Start);

	_nameInputBox = new TextInputBox { GetFont(), 18u, sf::Color::Green};
	_nameInputBox->SetPosition({ _menuWindow->getSize().x / 2.0f, _menuWindow->getSize().y / 2.0f});
	_nameInputBox->SetRelativeOrigin(0.5f, 0.5f);

	Menu::ItemsList mainMenuItems
	{
		{"Start", [this]() { std::cout << "Start game selected!" << std::endl; SetMenuOpen(false); Application::GetInstance().GetGame()->Start(); }},
		{"Difficulty", [this]() { std::cout << "Difficulty selected!" << std::endl; _selectedMenu = _difficultyMenu; }},
		{"Records table", [this]() { std::cout << "Records table!" << std::endl; _selectedMenu = _enterNameDialog;}},
		{"Settings", [this]() { std::cout << "Settings selected!" << std::endl; _selectedMenu = _settingsMenu; }},
		{"Exit", [this]() { _menuWindow->close(); }}
	};
	_mainMenu = new Menu { mainMenuItems, GetFont(), *_menuWindow, "Snake Game" };

	_settingsMenu->SetRootItem(_mainMenu);
	_difficultyMenu->SetRootItem(_mainMenu);
	_enterNameDialog->SetRootItem(_mainMenu);
}

void UIManager::ToggleCheckbox(TextInputBox* checkBox)
{
	if (!checkBox)
		return;

	if (checkBox->GetText() == "")
		checkBox->UpdateText("V", sf::Color::Green);
	else
		checkBox->UpdateText("", sf::Color::Black);
}

void UIManager::SetMenuOpen(bool flag)
{
	_bIsMenuOpen = flag;
	_menuWindow->setVisible(flag);
	_menuWindow->setActive(flag);
}

void UIManager::Clear()
{
	delete _scoreText;
	delete _timeText;
	delete _gameOverBlock;
	delete _selectedMenu;
	delete _difficultyMenu;
	delete _settingsMenu;
	delete _soundCheck;
	delete _musicCheck;
	delete _menuWindow;
	delete _nameInputBox;
}