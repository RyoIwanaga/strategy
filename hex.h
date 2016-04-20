#ifndef _strategy__hex_h_
#define _strategy__hex_h_

#include "strategy.h"

NS_STRATEGY;

namespace hex {

	bool collectRange(std::set<PosHex>* acc, PosHex index, ushort range, int height, int width, bool isCyinder);
	std::shared_ptr<std::set<PosHex>> 
	createRange(PosHex index, ushort n, int height, int width, bool isCyinder);
	std::list<PosHex> neighbors(PosHex index, int height, int width, bool isCyinder);



	bool collectRange(std::set<PosHex>* acc, PosHex index, ushort range, int height, int width, bool isCyinder)
	{
		if (range == 0) {
			return true;
		}
		else {
			auto neighbors = hex::neighbors(index, height, width, isCyinder);

			for (auto neighbor : neighbors) {
				// XXX Destructive operation
				auto isInserted = acc->insert(neighbor);

				// TODO
				//if (isInserted) continue;

				auto resultCollect = hex::collectRange(acc, neighbor, (ushort)(range - 1), height, width, isCyinder);

				if (! resultCollect) {
					return false;
				}
			}

			return true;
		}
	}

	std::shared_ptr<std::set<PosHex>> 
	createRange(PosHex index, ushort n, int height, int width, bool isCyinder)
	{
		auto acc = std::make_shared<std::set<PosHex>>();
		auto result = collectRange(acc.get(), index, n, height, width, isCyinder);

		if (result) {
			return acc;
		}
		else {
			return nullptr;
		}
	}

	std::list<PosHex> neighbors(PosHex index, int height, int width, bool isCyinder)
	{
		/*  width = 3
		 *
		 *     0 1 2
		 *	 +-------
		 * 0 | 0 1 2
		 * 1 |  3 4 5
		 * 2 | 6 7 8
		 * 3 |  9 a b 
		 */
		int y = index / width;
		int x = index % width; 
		std::list<PosHex> lst;

		//// left ////

		// 3 -> 5 
		if (x == 0 && isCyinder) {
			lst.push_back(index + width - 1);	
		}
		// 3 
		else if (x == 0 && ! isCyinder) {
			// pass
		}
		// 4 -> 3
		else {
			lst.push_back(index - 1);	
		}


		//// right ////

		// 5 -> 3
		if (x == width - 1 && isCyinder) {
			lst.push_back(index - width + 1);	
		}
		// 5
		else if (x == width - 1 && ! isCyinder) {
			// pass
		}
		// 4 -> 5
		else {
			lst.push_back(index + 1);	
		}


		if (y > 0) {

			// odd y
			if (y % 2 == 0) {

				//// upper left ////

				// 6 -> 5
				if (x == 0 && isCyinder) {
					lst.push_back(index - 1);	
				}
				// 6
				else if (x == 0 && ! isCyinder) {
					// pass
				}
				// 7 -> 3
				else {
					lst.push_back(index - width - 1);	
				}

				//// upper right ////

				// 8 -> 5
				lst.push_back(index - width);	
			}
			// y is even
			else {
				//// upper left ////

				// 3 -> 0
				lst.push_back(index - width);


				//// upper right ////

				// 5 -> 0
				if (x == width - 1 && isCyinder) {
					lst.push_back(index - width * 2 + 1);	
				}
				// 5
				else if (x == width - 1 && ! isCyinder) {
					// pass
				}
				// 4 -> 3
				else {
					lst.push_back(index - width + 1);	
				}
			}
		}

		if (y < height - 1) {

			// y == 0 or 2
			if (y % 2 == 0) {

				//// left lower ////

				// 6 -> 11 
				if (x == 0 && isCyinder) {
					lst.push_back(index + width * 2 - 1);	
				}
				// 6
				else if (x == 0 && ! isCyinder) {
					// pass
				}
				// 7 -> 9
				else {
					lst.push_back(index + width - 1);	
				}

				//// right lower ////

				// 8 -> 11
				lst.push_back(index + width);	
			}
			else {
				//// left lower ////

				// 3 -> 6
				lst.push_back(index + width);


				//// right lower ////

				// 5 -> 6
				if (x == width - 1 && isCyinder) {
					lst.push_back(index + 1);	
				}
				// 5
				else if (x == width - 1 && ! isCyinder) {
					// pass
				}
				// 4 -> 8
				else {
					lst.push_back(index + width + 1);	
				}
			}
		}

		return lst;
	}

}

NS_STRATEGY_END;

#endif

