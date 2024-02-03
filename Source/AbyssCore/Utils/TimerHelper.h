#ifndef TIMER_HELPER_H
#define TIMER_HELPER_H

#include <ctime>

namespace abyss
{
	namespace utils
	{
		namespace TimerLinux
		{
			float g_start = 0;

			float GetTimeMs()
			{
				clock_t time = clock();

				if (g_start == 0)
				{
					g_start = (float)clock();
				}

				return (float)time - g_start;
			}

			float GetTimeSeconds()
			{
				clock_t time = GetTimeMs() / CLOCKS_PER_SEC;
				return (float)time;
			}
		}
	}
}

#endif