#include "strategy.h"
#include "WorldInfo.h"
#include "console/console.h"

// 洗濯する楽しみはある
// 	手段の豊富さ
// 	でも、操作量が増えないように
//
// 戦闘はHomm
// Unitがスタック
// 拠点がユニットを毎ターン生み出す？
// 戦闘はsquare
// 	主力スタックだけになってしまう
// 	移動力が同じになってしまう
//	地形効果が出しづらい
//	戦果が予測しづらい
// マルチプレイできない
// umi vs riku???
// 3 sukumi
//
//// TODO
// tikei iro
// sikai
// help popup
// unit idou
// unit / town info
// boosts
// window layer
// worldinf units の渡し方
// 上下の移動時に循環しないように
// format string
// automake ソース整理

int main () 
{
	NS_USING_STRATEGY;

	const int CONSOLE_MARGIN_LEFT = 0;
	const int CONSOLE_MARGIN_TOP = 0;

	/*** create world ***/

	auto world = World::createMassive(
			28, 20, true, 0.5f);

	/*** create units ***/

	std::list<Unit::Ptr> units;
	units.push_back(Unit::create(Unit::Type::Settler, 0, 0));
	units.push_back(Unit::create(Unit::Type::Warrior, 1, 1));
	units.push_back(Unit::create(Unit::Type::Settler, 0, 20));
	units.push_back(Unit::create(Unit::Type::Warrior, 1, 21));

	/*** create town ***/ // for test XXX

	std::list<City> cities;
	cities.push_back(City("t1", 0, 2));
	cities.push_back(City("t2", 1, 3));

	/*** set infomation ***/

	auto worldInfo = std::make_shared<WorldInfo>();
	worldInfo->setWorld(world);
	worldInfo->setUnits(units);
	worldInfo->setCities(cities);


	/***/

	console::initialize();

	auto windowWorld = console::WindowWorld::create(
			console::Vec2(30, 20),
			console::Vec2(CONSOLE_MARGIN_LEFT, CONSOLE_MARGIN_TOP),
			// world info
			world->height, world->width, world->isCylinder);

	auto windowInfo = console::Window::create(
			console::Vec2(18, windowWorld->getSize().getY()),
			console::Vec2(windowWorld->getWindowSize().getX(), 0),
			true);
	
	auto windowMessage = console::Window::create(
			console::Vec2(windowWorld->getSize().getX(), 5),
			console::Vec2(0, windowWorld->getWindowSize().getY()),
			true);

	bool isEndGame = false;

	for (;;) {
		auto cursolPos = windowWorld->getCursolPos();
		auto itee = std::find_if(units.begin(), units.end(), 
				[cursolPos](Unit::Ptr& u){ return u->getPos() == cursolPos; });

		/*** clear windows ***/

		windowInfo->clear();
		windowMessage->clear();
		windowWorld->clear();

		/*** writing windows ***/

		if (itee != units.end()) {
			windowInfo->moveAddStr(console::Vec2(0, 0), "hoge");
			windowInfo->refresh();
		}

		windowMessage->moveFormat(0, "x:%d, y:%d, c:%d", 
				windowWorld->getCursolX(),
				windowWorld->getCursolY(),
				cursolPos);
		windowWorld->display(*worldInfo);

		/*** refresh windows ***/

		windowMessage->refresh();
		windowInfo->refresh();
		windowWorld->refresh();

		int ch = getchar();
	
		switch (ch) {
		case 'y':
			windowWorld->moveLeftUp();
			break;
		case 'u':
			windowWorld->moveRightUp();
			break;
		case 'b':
			windowWorld->moveLeftDown();
			break;
		case 'n':
			windowWorld->moveRightDown();
			break;
		case 'k':
			windowWorld->moveLeftUp();
			break;
		case 'j':
			windowWorld->moveRightDown();
			break;
		case 'h':
			windowWorld->moveLeft();
			break;
		case 'l':
			windowWorld->moveRight();
			break;
		case 'g': 
			{
				auto iteUnit = std::find_if(units.begin(), units.end(), 
						[cursolPos](Unit::Ptr& u) { return u->getPos() == cursolPos; });

				if (iteUnit != units.end()) {
					(*iteUnit)->setPos(5);
				}


				/*
				auto ite = units.begin();
				for (; ite != units.end(); ite++) {
					if ((*ite)->getPos() == windowWorld->getCursolPos())
						break;
				}

				if (ite == units.end()) {
					isEndGame = true;
				}
				else {
	
				} */
			}
			break;
		case 'q':
			isEndGame = true;
		}

		if (isEndGame)
			break;
	}

	console::finalize();

	return 0;	
}

