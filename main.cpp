#include "strategy.h"
#include "hex.h"
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
// help popup
// unit idou
// unit / town info
// boosts
// window layer
// automake ソース整理
// format string
// no cylinder world

int main () 
{
	NS_USING_STRATEGY;

	const int CONSOLE_MARGIN_LEFT = 0;
	const int CONSOLE_MARGIN_TOP = 0;

	/*** create world ***/

	auto world = World::createMassive(
			28, 20, true, 0.5f);

	/*** create units ***/

	auto units = std::make_shared<std::list<Unit::Ptr>>();
	units->push_back(Unit::create(Unit::Type::Settler, 0, 50));
	units->push_back(Unit::create(Unit::Type::Warrior, 1, 0));
	units->push_back(Unit::create(Unit::Type::Settler, 0, 210));
	units->push_back(Unit::create(Unit::Type::Warrior, 1, 21));

	/*** create town ***/ // for test XXX

	std::list<City> cities;
	cities.push_back(City("t1", 0, 2));
	cities.push_back(City("t2", 1, 3));

	/*** create player infos ***/

	std::vector<PlayerInfo::Ptr> playerInfos;
	playerInfos.push_back(std::make_shared<PlayerInfo>());
	playerInfos.push_back(std::make_shared<PlayerInfo>());

	auto visible = hex::createRange(50, 2,
		world->height, world->width, world->isCylinder);
/*
	std::set<PosHex> visibleHexes;
	visibleHexes.insert(10);
	visibleHexes.insert(11);
	visibleHexes.insert(12); */

//	playerInfos[0].setVisibleTerrains(*(visible));

//	playerInfos[0].set

	/*** set infomation ***/

	auto worldInfo = std::make_shared<WorldInfo>();
	worldInfo->setWorld(world);
	worldInfo->setUnits(units);
	worldInfo->setCities(cities);
	worldInfo->setPlayerInfos(playerInfos);
	// TODO
	worldInfo->updateVisibleTerrains(0);


	/***** create console windows *****/

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
		auto itee = std::find_if(units->begin(), units->end(), 
				[cursolPos](Unit::Ptr& u){ return u->getPos() == cursolPos; });

		/*** clear windows ***/

		windowInfo->clear();
		windowMessage->clear();
		windowWorld->clear();

		/*** writing windows ***/

		if (itee != units->end()) {
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
			windowWorld->cursolMoveUpLeft();
			break;
		case 'u':
			windowWorld->cursolMoveUpRight();
			break;
		case 'b':
			windowWorld->cursolMoveDownLeft();
			break;
		case 'n':
			windowWorld->cursolMoveDownRight();
			break;
		case 'k':
			windowWorld->cursolMoveUpLeft();
			break;
		case 'j':
			windowWorld->cursolMoveDownRight();
			break;
		case 'h':
			windowWorld->cursolMoveLeft();
			break;
		case 'l':
			windowWorld->cursolMoveRight();
			break;
		case 'g': 
			{
				auto iteUnit = std::find_if(units->begin(), units->end(), 
						[cursolPos](Unit::Ptr& u) { return u->getPos() == cursolPos; });

				if (iteUnit != units->end()) {
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

