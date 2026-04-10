#include "Label.h"

Label::Label(string text, string font) {
	this->font.loadFromFile(font);

	this->text.setString(text);
	this->text.setFont(this->font);
	this->text.setCharacterSize(64);

	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
}

void Label::draw(RenderTarget& target, RenderStates states) const {
	states.transform.combine(getTransform());
	target.draw(text, states);
}

void Label::setString(string text) {
	this->text.setString(text);
}

void Label::centerString(Vector2u window) {
	setPosition(window.x / 2, window.y / 2);
}

Vector2f Label::getSize() {
	return Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height);
}