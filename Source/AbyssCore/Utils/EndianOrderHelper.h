#ifndef ENDIAN_ORDER_HELPER_H
#define ENDIAN_ORDER_HELPER_H

#include "Enums.h"

namespace abyss
{
	namespace utils
	{
		class EndianOrderHelper
		{
			ABYSS_ENDIAN_TYPE m_systemEndian;

		public:
			EndianOrderHelper();
			virtual ~EndianOrderHelper();

			void ResolveEndian(char* data, int size, ABYSS_ENDIAN_TYPE inputEndian);

			void SwapBytes(char* data, int size);
			void SwapBytes(char* data, int size, int number);

			ABYSS_ENDIAN_TYPE GetEndianType() const
			{
				return m_systemEndian;
			}
		};
	}
}

#endif