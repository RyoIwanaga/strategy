#ifndef _Util_h_
#define _Util_h_

#include <cassert>

namespace util {

	namespace math {

		template<typename T>
			inline T addCircle(T base, T add, T max, T min = 0) 
			{
				assert(max >= min);

				auto range = max - min + 1;
				auto moveFromMin = (base - min + add) % range;

				if (moveFromMin >= 0)
					return min + moveFromMin;
				else
					return max + moveFromMin + 1;

			}

		template<typename T>
			inline T addRange(T base, T add, T max, T min = 0)
			{
				assert(max >= min);

				auto result = base + add;

				if (result < min)
					return min;
				else if (max < result)
					return max;
				else
					return result;
			}

		template<typename T>
			inline T addToMax(T base, T value, T max)
			{
				auto result = base + value;

				if (result > max )
					return max;
				else
					return result;
			}

		template<typename T>
			inline T subToMin(T base, T value, T min)
			{
				auto result = base - value;

				if (result < min)
					return min;
				else
					return result;
			}
	}

} // end of namespace Util


#endif // _Util_h_

