#ifndef _strategy__City_h_
#define _strategy__City_h_

#include "strategy.h"

NS_STRATEGY;

class City
{
	REU__PROPERTY(std::string, name, Name);
	REU__PROPERTY(Owner, owner, Owner);
	REU__PROPERTY(PosHex, pos, Pos);

public:
	City(std::string name, Owner owner, PosHex pos) :
		name(name),
		owner(owner),
		pos(pos)
	{}
	virtual ~City() {}
};

NS_STRATEGY_END;

#endif

