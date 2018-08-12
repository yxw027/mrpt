/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          http://www.mrpt.org/                          |
   |                                                                        |
   | Copyright (c) 2005-2018, Individual contributors, see AUTHORS file     |
   | See: http://www.mrpt.org/Authors - All rights reserved.                |
   | Released under BSD License. See details in http://www.mrpt.org/License |
   +------------------------------------------------------------------------+ */
#pragma once

#include <chrono>

namespace mrpt::system
{
/** Clock that is compatible with TTimeStamp representation
 * \ingroup mrpt_system_grp
 */
class Clock
{
   public:
	using rep = int64_t;
	// 100-nanoseconds
	using period = std::ratio<1, 10000000>;
	using duration = std::chrono::duration<rep, period>;
	using time_point = std::chrono::time_point<Clock>;

	static constexpr bool is_steady = std::chrono::system_clock::is_steady;

	static time_point now() noexcept
	{
		duration d = std::chrono::duration_cast<duration>(
			std::chrono::system_clock::now().time_since_epoch());
		d += std::chrono::seconds(11644473600);  // TTimeStamp offset constant
		return time_point(d);
	}
};

/** Returns the time difference from t1 to t2 (positive if t2 is posterior to
 * t1), in seconds \sa secondsToTimestamp
 * \ingroup mrpt_system_grp
 */
double timeDifference(
	const mrpt::system::Clock::time_point& t_first,
	const mrpt::system::Clock::time_point& t_later);

inline Clock::time_point toTimePoint(int64_t time)
{
	return Clock::time_point(Clock::duration(time));
}

}  // namespace mrpt::system