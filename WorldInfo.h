#ifndef _strategy__WorldInfo_h_
#define _strategy__WorldInfo_h_

#include "strategy.h"
#include "World.h"
#include "Unit.h"
#include "City.h"

NS_STRATEGY;

class WorldInfo
{
	REU__PROPERTY(World::Ptr, world, World);
	REU__PROPERTY(std::list<Unit::Ptr>, units, Units);
	REU__PROPERTY(std::list<City>, cities, Cities);
};

NS_STRATEGY_END;

#endif 

