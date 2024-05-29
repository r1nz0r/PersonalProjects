#pragma once
#include <vector>
#include <functional>
#include "SFML/Graphics.hpp"
#include "IDrawable.h"
#include "TextBlock.h"

class Menu : public IDrawable
{
public:
	using ItemCallback = std::function<void(void)>;
	using Item = std::pair<std::string, ItemCallback>;
	using ItemsList = std::vector<Item>;

	Menu
	(
		ItemsList items,
		const sf::Font& font,
		sf::RenderWindow& window,
		std::string title = "",
		const float verticalSpacing = 10.0f,
		bool bInputEnabled = true,
		Menu* root = nullptr,
		const sf::Color selectedColor = sf::Color::Green,
		const sf::Color unselectedColor = sf::Color::White
	);
	virtual ~Menu() {}
	virtual void Draw(sf::RenderWindow& window) override;
	void HandleInput(const sf::Event& event);
	void SetPosition(const sf::Vector2f& position);
	void SetRootItem(Menu* root);
	void SetMenuItemsAlignment(const TextBlock::Alignment horizontal, const TextBlock::Alignment vertical, const Text::Alignment textHorizontal);
	void EnableInput();
	void DisableInput();
	Menu* GetRootItem() const;

private:
	ItemsList _items;
	TextBlock _itemsBlock; // Text block for displaying menu items.
	Text _title;
	sf::Color _selectedItemColor;
	sf::Color _unselectedItemColor;
	sf::Font _font;
	sf::RenderWindow& _window;
	int _selectedItemIndex;
	Menu* _root;
	bool _bInputEnabled;

	void MoveUp();
	void MoveDown();
	void ExecuteSelectedItem();
	void SetupText(const float verticalSpacing);
	void SetupTitle(std::string& text);
};

