#include "Menu.h"
#include "GameSettings.h"
#include "AudioPlayer.h"

Menu::Menu
(
	ItemsList items,
	const sf::Font& font,
	sf::RenderWindow& window,
	std::string title,
	const float verticalSpacing,
	Menu* root,
	const sf::Color selectedColor,
	const sf::Color unselectedColor
) :	_items(items),
	_font(font),
	_window(window),
	_root(root),
	_selectedItemIndex(0),
	_selectedItemColor(selectedColor),
	_unselectedItemColor(unselectedColor)
{
	SetupText(verticalSpacing);
	SetupTitle(title);
}

void Menu::Draw(sf::RenderWindow& window)
{
	_title.Draw(window);
	_itemsBlock.Draw(window);
}

void Menu::HandleInput(const sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::W:
		MoveUp();
		break;
	case sf::Keyboard::S:
		MoveDown();
		break;
	case sf::Keyboard::Return:
		ExecuteSelectedItem();
		break;
	default:
		break;
	}
}

void Menu::SetRootItem(Menu* root)
{
	_root = root;
}

void Menu::SetMenuItemsAlignment(const TextBlock::Alignment horizontal, const TextBlock::Alignment vertical, const Text::Alignment textHorizontal)
{
	_itemsBlock.SetAlignmentProperties(horizontal, vertical, textHorizontal);
	_itemsBlock.AlignTexts();
}

Menu* Menu::GetRootItem() const
{
	return _root;
}

void Menu::MoveUp()
{
	if (_selectedItemIndex > 0)
	{
		AudioPlayer::GetInstance().PlaySound(AudioPlayer::ESound::Menu);
		_itemsBlock.SetColor(_selectedItemIndex, _unselectedItemColor);
		_selectedItemIndex--;
		_itemsBlock.SetColor(_selectedItemIndex, _selectedItemColor);
	}
}

void Menu::MoveDown()
{
	const int MAX_INDEX = _items.size() - 1;

	if (_selectedItemIndex < MAX_INDEX)
	{
		AudioPlayer::GetInstance().PlaySound(AudioPlayer::ESound::Menu);
		_itemsBlock.SetColor(_selectedItemIndex, _unselectedItemColor);
		_selectedItemIndex++;
		_itemsBlock.SetColor(_selectedItemIndex, _selectedItemColor);
	}
}

void Menu::ExecuteSelectedItem()
{
	if (_selectedItemIndex >= 0 && _selectedItemIndex < _items.size())
	{
		if (_items[_selectedItemIndex].second)
		{
			AudioPlayer::GetInstance().PlaySound(AudioPlayer::ESound::Menu);
			_items[_selectedItemIndex].second();
		}
	}
}

void Menu::SetupText(const float verticalSpacing)
{
	
	_itemsBlock.Clear(); // Очищаем все предыдущие тексты, если они были
	_itemsBlock.SetStartPosition(sf::Vector2f(_window.getSize().x / 2, _window.getSize().y / 2)); // Устанавливаем начальную позицию блока текста
	_itemsBlock.SetVerticalSpacing(verticalSpacing); // Устанавливаем вертикальный интервал между текстами

	for (const auto& item : _items)	
		_itemsBlock.AddText(item.first, _font, sf::Color::White, 25); // Добавляем текст в блок	

	if (!_items.empty())
		_itemsBlock.SetColor(0, _selectedItemColor);

	_itemsBlock.AlignTexts();
}

void Menu::SetupTitle(std::string& text)
{
	_title.setFont(_font);
	_title.setString(text);
	_title.setCharacterSize(30);
	float titleOffsetY = 25.0f;
	sf::Vector2f position { _window.getSize().x / 2.0f, titleOffsetY };
	_title.setPosition(position);
	_title.Align(position);
}

