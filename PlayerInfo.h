#ifndef _strategy__PlayerInfo_h_
#define _strategy__PlayerInfo_h_

#include "strategy.h"

NS_STRATEGY;

class PlayerInfo
{
	REU__TYPEDEF_SPTR(PlayerInfo);

	REU__PROPERTY(std::set<PosHex>, visibleTerrains, VisibleTerrains);
	// TODO tech
	// TODO Score
};

NS_STRATEGY_END;

#endif 

