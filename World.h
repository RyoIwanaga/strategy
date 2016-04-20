#ifndef _strategy__World_h_
#define _strategy__World_h_

#include "strategy.h"
#include "Terrain.h"

NS_STRATEGY;

class World
{
public:
	typedef std::shared_ptr<World> Ptr;

	int height;
	int width;
	bool isCylinder;

	std::vector<Terrain> terrains;

	World (int height, int width, bool isCylinder) :
		height(height),
		width(width),
		isCylinder(isCylinder)
	{
		assert(height % 2 == 0);
		assert(width % 2 == 0);
	}

	static Ptr createMassive(int height, int width, bool isCylinder, float landPersentage);

	int getHeight() const { return height; }
	int getWidth() { return width; }
};

NS_STRATEGY_END;

#endif // _World_h_

