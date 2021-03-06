#ifndef _strategy__console__WindowWorld_h_
#define _strategy__console__WindowWorld_h_

#include "Window.h"

NS_CONSOLE;
NS_USING_STRATEGY;

class WindowWorld : public Window
{
protected:
	static const int 	HEX_HEIGHT = 2;
	static const int 	HEX_WIDTH = 2;
	static const int 	HEX_SPACE = 2;
	static const char	HEX_TERRAIN_PIT = ' ';

	REU__TYPEDEF_SPTR(WindowWorld);

	// cursol position
	REU__PROPERTY(ulong, cursol, Cursol);
	REU__PROPERTY(int, worldHeight, WorldHeight);
	REU__PROPERTY(int, worldWidth, WorldWidth);
	REU__PROPERTY(bool, isWorldCylinder, IsWorldCylinder);

public:
	WindowWorld(
			const console::Vec2& sizeVisibleHex, 
			const console::Vec2& pos, 
			int worldHeight, int worldWidth, bool isCylinder);

	virtual ~WindowWorld() {}

	static Ptr create(
			const console::Vec2& sizeVisibleHex, 
			const console::Vec2& pos, 
			int worldHeight, int worldWidth, bool isCylinder);

	/*** Accessors ***/

	uint getCursolX() { return hex::toV2(getCursol(), getWorldHeight(), getWorldWidth()).getX(); }
	uint getCursolY() { return hex::toV2(getCursol(), getWorldHeight(), getWorldWidth()).getY(); }
	bool getIsConnectH() { return getIsWorldCylinder(); } // TODO
	bool getIsConnectV() { return false; } //TODO
	strategy::PosHex getCursolPos();
	/***/


	bool cursolMoveLeft() 		{ return _cursolMove(hex::Direction::Left); }
	bool cursolMoveRight() 		{ return _cursolMove(hex::Direction::Right); }
	bool cursolMoveUpLeft() 	{ return _cursolMove(hex::Direction::UpLeft); }
	bool cursolMoveUpRight() 	{ return _cursolMove(hex::Direction::UpRight); }
	bool cursolMoveDownLeft() 	{ return _cursolMove(hex::Direction::DownLeft); }
	bool cursolMoveDownRight() 	{ return _cursolMove(hex::Direction::DownRight); }

	void display(const strategy::WorldInfo& worldInfo);

protected: 
	int getHexGridHeight();
	int getHexGridWidth();

private:
	bool _cursolMove(hex::Direction dir)
	{
		auto result = hex::move(getCursol(), dir, 
				getWorldHeight(), getWorldWidth(), 
				getIsConnectH(), getIsConnectV());

		if (result == hex::FnMoveFail) {
			return false;
		}
		else {
			setCursol(result);

			return true;
		}
	}
};

char makeChUnit(strategy::Unit::Ptr unit);
char makeColorUnit(strategy::Unit::Ptr unit);
char makeChTerrain(const Terrain& terrain);


WindowWorld::WindowWorld(
		const console::Vec2& sizeVisibleHex, 
		const console::Vec2& pos, 
		int worldHeight, int worldWidth, bool isCylinder) :
	Window(
			console::Vec2(

			sizeVisibleHex.getX() > worldWidth ?
			worldWidth * (HEX_WIDTH + HEX_SPACE) + HEX_SPACE :
			sizeVisibleHex.getX() * (HEX_WIDTH + HEX_SPACE) + HEX_SPACE,

			sizeVisibleHex.getY() > worldHeight ?
			worldHeight * HEX_HEIGHT :
			sizeVisibleHex.getY() * HEX_HEIGHT),

			pos, true),
	cursol(hex::fromV2(hex::HexVec2(worldWidth / 2, worldHeight / 2),
			worldHeight, worldWidth)),
	worldHeight(worldHeight),
	worldWidth(worldWidth),
	isWorldCylinder(isCylinder)
{
	assert (sizeVisibleHex.getX() % 2 == 0);
	assert (sizeVisibleHex.getY() % 2 == 0);
}

WindowWorld::Ptr WindowWorld::create(
		const console::Vec2& sizeVisibleHex, 
		const console::Vec2& pos, 
		int worldHeight, int worldWidth, bool isCylinder)
{
	return std::make_shared<WindowWorld>(sizeVisibleHex, pos, worldHeight, worldWidth, isCylinder);
}


strategy::PosHex WindowWorld::getCursolPos()
{
	return this->getWorldWidth() * this->getCursolY() + this->getCursolX();
}

int WindowWorld::getHexGridHeight()
{
	return this->getSize().getY() / HEX_HEIGHT;
}

int WindowWorld::getHexGridWidth()
{
	return (this->getSize().getX() - HEX_SPACE) / (HEX_WIDTH + HEX_SPACE);
}

void WindowWorld::display(const strategy::WorldInfo& worldInfo)
{
	/* oo  oo
	 * oo  oo
	 *   oo  oo
	 *   oo  oo
	 * oo  oo
	 * oo  oo
	 *   oo  oo
	 *   oo  oo
	 */
	int player = 0;
	// Cursol position of Hex croodinate
	auto cursolHexPos = console::Vec2(
			getHexGridWidth() / 2 - 1,
			getHexGridHeight() / 2 - 1);
	bool isCursolEvenRow = getCursolY() % 2 == 0;

	// for row of window
	for (int row = 0; row < this->getSize().getY(); row++) {

		int relativeY = row / HEX_HEIGHT - cursolHexPos.getY() + 1;
//		int worldY = util::math::addCircle(getCursolY(), relativeY, worldInfo.getWorld()->getHeight() - 1);
		int worldY = getCursolY() + relativeY;
		if (worldY < 0 || worldInfo.getWorld()->getHeight() - 1 < worldY)
			continue;

		bool isEvenWorldY = worldY % 2 == 0;
		bool isThisEven = isCursolEvenRow ? isEvenWorldY : ! isEvenWorldY;

		switch (row % 4) {
		case 0:
		case 1:
			this->move(Vec2(0, row));
			break;
		case 2:
		case 3:
			this->move(Vec2(HEX_SPACE, row));
			break;
		}

		// xx = 
		//
		// 00  11  22  33
		// 00  11  22  33
		//   00  11  22  33
		//   00  11  22  33
		// 00  11  22  33
		// 00  11  22  33
		//   00  11  22  33
		//   00  11  22  33
		for (int xx = 0; xx < this->getHexGridWidth(); xx++) {

			int xxx = isCursolEvenRow ? xx : isThisEven ? xx : xx + 1;
			int relativeX = xxx - cursolHexPos.getX();
			int worldX;

			if (getIsWorldCylinder()) {
				worldX = util::math::addCircle<int>(getCursolX(), relativeX, worldInfo.getWorld()->getWidth() - 1);
			}
			else {
				worldX = getCursolX() + relativeX;

				if (worldX < 0 || worldInfo.getWorld()->getWidth() - 1 < worldX) {
					this->addCh(WindowWorld::HEX_TERRAIN_PIT);
					this->addCh(WindowWorld::HEX_TERRAIN_PIT);
					this->addCh(Window::CH_BLANK);
					this->addCh(Window::CH_BLANK);

					continue;
				}
			}

			ulong index = worldY * worldInfo.getWorld()->getWidth() + worldX;
			auto terrain = worldInfo.getWorld()->terrains[worldY * worldInfo.getWorld()->getWidth() + worldX];

			auto visibleTerrains = worldInfo.getPlayerInfos().at(player)->getVisibleTerrains();
			auto iteVT = std::find(visibleTerrains.begin(), visibleTerrains.end(), index);
			auto isVisibleTerrain = iteVT == visibleTerrains.end() ? false : true;

			// 0 1
			// 2 3

			switch (row % HEX_HEIGHT) {
			case 0: // 0 1
				{
					/* 0 */

					auto units = worldInfo.getUnits();
					auto iteTargetUnit = units->begin();

					for (; iteTargetUnit != units->end(); iteTargetUnit++) {
						if ((*iteTargetUnit)->getPos() == index)
							break;
					}


					if (iteTargetUnit == units->end()) {
						this->addCh(Window::CH_BLANK);
					}
					else {
						this->addCh(makeChUnit(*iteTargetUnit) | makeColorPlayer((*iteTargetUnit)->getOwner()));
					}

					/* 1 */

					this->addCh(Window::CH_BLANK);

					break;
				}
			case 1: // 2 3
				{
					/* 2 */

					if (isVisibleTerrain) 
						this->addCh(makeChTerrain(terrain) | makeColorTerrain(terrain) | A_BOLD);
					else
						this->addCh(makeChTerrain(terrain) | makeColorTerrainOutOfSight());

					/* 3 */ 

					auto cities = worldInfo.getCities();
					auto iteTargetCity = std::find_if(cities.begin(), cities.end(), 
							[index] (strategy::City& c) { return c.getPos() == index; });

					if (iteTargetCity == cities.end()) {
						this->addCh(Window::CH_BLANK);
					}
					else {
						this->addCh('*' | makeColorPlayer((*iteTargetCity).getOwner()));
					} 

					break;
				}
			default:
				assert(false);
			}

			this->addCh(Window::CH_BLANK);
			this->addCh(Window::CH_BLANK);
		}
	}

	// move cursol
	this->move(console::Vec2(
				cursolHexPos.getX() * (HEX_WIDTH + HEX_SPACE),
				cursolHexPos.getY() * HEX_HEIGHT - 1));
}


/*** Helper functions ***/

char makeChUnit(strategy::Unit::Ptr unit)
{
	switch(unit->getType()) {
	case Unit::Type::Settler:
		return 's';
		break;
	case Unit::Type::Warrior:
		return 'w';
		break;
	default:
		assert(false);
	}
}

char makeChTerrain(const Terrain& terrain)
{
	switch (terrain.getBase()) {
	case Terrain::BaseType::None:
		return '+';
	case Terrain::BaseType::Glassland:
		if (terrain.getVertical() == Terrain::VerticalType::Flatland)
			return 'v';
		else
			return '-';

	case Terrain::BaseType::Plains:
		if (terrain.getVertical() == Terrain::VerticalType::Flatland)
			return '.';
		else
			return '^';

	case Terrain::BaseType::Tundra:
		if (terrain.getVertical() == Terrain::VerticalType::Flatland)
			return 't';
		else
			return 'T';

	case Terrain::BaseType::Desert:
		if (terrain.getVertical() == Terrain::VerticalType::Flatland)
			return 'd';
		else
			return 'D';

	case Terrain::BaseType::Ice:
		return '*';

		//// Oceans ////

	case Terrain::BaseType::Coast:
	case Terrain::BaseType::Ocean:
		return '~';
	default:
		return '?';
	}
}

NS_CONSOLE_END

#endif

