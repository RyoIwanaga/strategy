#include "Unit.h"

NS_STRATEGY;

Unit::Unit(Unit::Type t, Owner owner, ulong pos, int hp, int damage, ushort move, ushort sight) :
	type(t),
	owner(owner),
	pos(pos),
	hp(hp),
	hpMax(hp),
	damage(damage),
	move(move),
	moveMax(move),
	sight(sight)
{
}

Unit::~Unit()
{
}

Unit::Ptr Unit::create(Type t, Owner owner, ulong p)
{
	switch (t) {
	case Unit::Type::Settler:
		return std::make_shared<Unit>(Unit::Type::Settler, owner, p, 100, 20, 4, 2);
	case Unit::Type::Warrior:
		return std::make_shared<Unit>(Unit::Type::Warrior, owner, p, 100, 20, 2, 2);

	default:
		assert(false);
	}
}

bool Unit::isMovable()
{
	return this->move != 0;
}

NS_STRATEGY_END;

