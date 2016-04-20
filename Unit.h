#ifndef _strategy__Unit_h_
#define _strategy__Unit_h_

#include "strategy.h"

NS_STRATEGY;

class Unit
{
public: 
	enum class Type {
		Settler = 0,
		Scout,
		Warrior,
		Archer,
	};

	REU__PROPERTY(Type, type, Type);
	REU__PROPERTY(Owner, owner, Owner);
	REU__PROPERTY(PosHex, pos, Pos);
	REU__PROPERTY(uint, hp, Hp);
	REU__PROPERTY(int, hpMax, HpMax);
	REU__PROPERTY(int, damage, Damaege);
	REU__PROPERTY(ushort, move, Move);
	REU__PROPERTY(ushort, moveMax, MoveMax);
	REU__PROPERTY(ushort, sight, Sight);

public:
	typedef std::shared_ptr<Unit> Ptr;
	static Ptr create(Type t, Owner owner, ulong pos);

	Unit(Type t, Owner owner, PosHex pos, int hp, int damage, ushort move, ushort sight);
	virtual ~Unit();

	bool isMovable();
};

NS_STRATEGY_END;

#endif // _Unit_h_

