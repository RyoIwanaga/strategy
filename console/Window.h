#ifndef _Console__Window_h_
#define _Console__Window_h_

#include "../strategy.h"
#include "../Unit.h"
#include "console.h"

NS_CONSOLE;

typedef reu::diagram::Vec2<int> Vec2;

class Window
{
	/* ......
	 * .+--+.
	 * .|  |.
	 * .|  |.
	 * .+--+.
	 * ......
	 *
	 * position = 	(1, 1)
	 * size = 	  	(2, 2)
	 * windowSize = (4, 4)
	 */
	REU__PROPERTY_PRIVATE(WINDOW*, window, Window);
	REU__PROPERTY_READONLY(console::Vec2, size, Size);
	REU__PROPERTY_READONLY(console::Vec2, pos, Pos);
	REU__PROPERTY_READONLY(bool, isBox, IsBox);

protected:
	static const char BOX_DEFAULT_CH_V = '|';
	static const char BOX_DEFAULT_CH_H = '-';
	static const char CH_BLANK = ' ';

public:
	typedef std::shared_ptr<Window> Ptr;

	Window(console::Vec2 size, console::Vec2 pos, bool isBox = false);
	virtual ~Window();
	static Ptr create(console::Vec2 size, console::Vec2 pos, bool isBox = false);

	console::Vec2 getWindowSize();

	// TODO no box ver
	int refresh();
	int clear();
	int move(const console::Vec2& pos);
	int addCh(console::chtype ch);
	int addStr(char* str);
	template <typename ... Args>
	int format(char* str, const Args& ... args);
	int moveAddCh(const console::Vec2& pos, console::chtype ch);
	int moveAddStr(const console::Vec2& pos, char* str);
	template <typename ... Args>
	int moveFormat(const console::Vec2& pos, char* str, const Args& ... args);

	/*** Useful shorcuts ***/

	int moveAddStr(int row, char* str) 
	{ 
		return this->moveAddStr(console::Vec2(0, row), str); 
	}

	template <typename ... Args>
	int moveFormat(int row, char* str, const Args& ... args)
	{
		return this->moveFormat(console::Vec2(0, row), str, args ...); 
	}
	
private:
	int box();
	Vec2 posToWindowPos(const Vec2& pos);
};

Window::Window(console::Vec2 size, console::Vec2 pos, bool isBox) : // = false
	size(size),
	pos(pos),
	isBox(isBox)
{
	if (isBox) {
		this->window = newwin(
				this->getSize().getY() + 2,
				this->getSize().getX() + 2,
				this->getPos().getY(),
				this->getPos().getX());
	}
	else {
		this->window = newwin(
				this->getSize().getY(),
				this->getSize().getX(),
				this->getPos().getY(),
				this->getPos().getX());
	}
}

Window::~Window()
{
	delwin(this->window);
}

Window::Ptr Window::create(console::Vec2 size, console::Vec2 pos, bool isBox) // = false
{
	return std::make_shared<Window>(size, pos, isBox);
}

console::Vec2 Window::getWindowSize()
{
	if (this->getIsBox()) {
		return console::Vec2(
				this->getSize().getX() + 2,
				this->getSize().getY() + 2);
	}
	else {
		return this->getSize();
	}
}

int Window::box()
{
	return console::box(this->getWindow(), Window::BOX_DEFAULT_CH_V, Window::BOX_DEFAULT_CH_H);
}

int Window::refresh()
{
	if (this->getIsBox()) 
		Window::box();

	return console::wrefresh(this->getWindow());
}

int Window::clear()
{
	return console::wclear(this->getWindow());
}

int Window::move(const Vec2& pos)
{
	auto posWindow = Window::posToWindowPos(pos);

	return console::wmove(this->getWindow(), posWindow.getY(), posWindow.getX());	
}

int Window::addCh(console::chtype ch)
{
	return console::waddch(this->getWindow(), ch);
}

int Window::addStr(char* str)
{
//	console::wattron(this->getWindow(), COLOR_PAIR(2));
	return console::waddstr(this->getWindow(), str);
}

template <typename ... Args>
int Window::format(char* str, const Args& ... args)
{
	return console::wprintw(this->getWindow(), str, args ...);
}

int Window::moveAddCh(const console::Vec2& pos, console::chtype ch)
{
	this->move(pos);

	return console::waddch(this->getWindow(), ch);
}

int Window::moveAddStr(const console::Vec2& pos, char* str)
{
	this->move(pos);

	return console::waddstr(this->getWindow(), str);
}

template <typename ... Args>
int Window::moveFormat(const console::Vec2& pos,char* str, const Args& ... args)
{
	this->move(pos);

	return console::wprintw(this->getWindow(), str, args ...);
}

Vec2 Window::posToWindowPos(const Vec2& pos)
{
	if (this->getIsBox()) {
		return Vec2(pos.getX() + 1, pos.getY() + 1);
	}
	else {
		return pos;
	}
}


NS_CONSOLE_END;

#endif // _Console__Window_h_

