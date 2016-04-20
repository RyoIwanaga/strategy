#ifndef _strategy__WorldInfo_h_
#define _strategy__WorldInfo_h_

#include "strategy.h"
#include "World.h"
#include "Unit.h"
#include "City.h"
#include "PlayerInfo.h"

NS_STRATEGY;

class WorldInfo
{
	REU__PROPERTY(World::Ptr, world, World);
	REU__PROPERTY(std::shared_ptr<std::list<Unit::Ptr>>, units, Units);
	REU__PROPERTY(std::list<City>, cities, Cities);
	REU__PROPERTY(std::vector<PlayerInfo::Ptr>, playerInfos, PlayerInfos);

public:
	bool updateVisibleTerrains(ushort player);
protected:
	std::shared_ptr<std::set<PosHex>> createVisibleTerrains(ushort player);
};

bool WorldInfo::updateVisibleTerrains(ushort player)
{
	auto visible = hex::createRange(50, 2,
		world->height, world->width, world->isCylinder);

//	getPlayerInfos()[0]->setVisibleTerrains(*visible); */
	auto result = createVisibleTerrains(player);

	if (result == nullptr) {
		return false;
	}
	else {
		// XXX Destructive operation
		getPlayerInfos().at(player)->setVisibleTerrains(*result);

		return true;
	}
}

std::shared_ptr<std::set<PosHex>> WorldInfo::createVisibleTerrains(ushort player)
{
	auto acc = std::make_shared<std::set<PosHex>>();

	/*** Unit sight ***/

	for (Unit::Ptr u : *getUnits()) {
		if (u->getOwner() == player) {
			// XXX Destructive operation
			bool result = hex::collectRange(acc.get(), u->getPos(), u->getSight(),
					getWorld()->getHeight(),
					getWorld()->getWidth(),
					getWorld()->isCylinder);
			/*
			bool result = hex::collectRange(acc.get(), u->getPos(), u->getSight(),
					getWorld()->getHeight(),
					getWorld()->getWidth(),
					getWorld()->isCylinder);
					*/

//			if (result) return nullptr;
		}
	}

//	acc->insert(5);

	/*** Town sight ***/

	/*** Other ***/

	return acc;
}

NS_STRATEGY_END;

#endif 

