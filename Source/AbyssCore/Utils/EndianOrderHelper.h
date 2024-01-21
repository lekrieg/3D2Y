#ifndef ENDIAN_ORDER_HELPER_H
#define ENDIAN_ORDER_HELPER_H

namespace abyss
{
	namespace utils
	{
		enum class ABYSS_ENDIAN_TYPE
		{
			ABYSS_ENDIAN_UNKNOWN = 0,
			ABYSS_ENDIAN_LITTLE,
			ABYSS_ENDIAN_BIG,
			ABYSS_ENDIAN_MIDDLE
		};

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