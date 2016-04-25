#ifndef _strategy__World_h_
#define _strategy__World_h_

#include "strategy.h"
#include "hex.h" // TODO remove later
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

World::Ptr World::createMassive(int height, int width, bool isCylinder, float landPersentage)
{
	assert (height % 2 == 0);
	
	int worldSize = height * width;
	int land = worldSize * landPersentage;

	std::random_device rnd;

	auto world = std::make_shared<World>(height, width, isCylinder);
	auto terrains = &(world->terrains);
	auto target = height / 2 * width + width / 2;
	std::set<int> coasts;

	terrains->resize(worldSize);
	terrains->at(target) = Terrain(
			Terrain::BaseType::Glassland,
			Terrain::VerticalType::Flatland,
			Terrain::FeatureType::None);


	// already placed 1
	for (int n = 1; n < land; n++) {
		auto neighbors = hex::neighbors(target, height, width, false);
		for (auto n : neighbors) {
			auto y = n / width;
			auto x = n % width;

			if (y <= 0 
					|| height - 1 <= y 
					|| x <= 1
					|| width - 2 <= x)
				continue;

			// add coast
			if (terrains->at(n).getBase() == Terrain::BaseType::None) {
				coasts.insert(n);
			}	
		}
		auto targetIndex = rnd() % coasts.size();
		auto itr = coasts.begin();
		std::advance(itr, targetIndex);
		target = *itr;

		// XXX Destructive operation
		terrains->at(target).setBase(Terrain::BaseType::Glassland);

	}

	for (int i = 0; i < worldSize; i++) {
		if (terrains->at(i).getBase() == Terrain::BaseType::None)
			// XXX Destructive operation
			terrains->at(i).setBase(Terrain::BaseType::Ocean);
	}

	//			terrain = Terrain(
	//					rnd() % 2 == 0 ? Terrain::BaseType::Glassland : Terrain::BaseType::Ocean,
	//					Terrain::VerticalType::Flatland,
	//					Terrain::FeatureType::None);

	return world;
}

NS_STRATEGY_END;

#endif // _World_h_

