#ifndef _strategy__console__WindowMessage_h_
#define _strategy__console__WindowMessage_h_

#include "Window.h"

NS_CONSOLE;

class WindowMessage : public Window
{
public:
	typedef std::shared_ptr<WindowMessage> Ptr;

	WindowMessage(console::Vec2 size, console::Vec2 pos);
	virtual ~WindowMessage();
	static Ptr create(console::Vec2 size, console::Vec2 pos);

	void display();
};

WindowMessage::WindowMessage(console::Vec2 size, console::Vec2 pos) :
		Window(size, pos)
{}

WindowMessage::~WindowMessage() {}

WindowMessage::Ptr WindowMessage::create(console::Vec2 size, console::Vec2 pos)
{
	return std::make_shared<WindowMessage>(size, pos);
}

void WindowMessage::display()
{
	this->refresh();
}

NS_CONSOLE_END

#endif

