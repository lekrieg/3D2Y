#ifndef RENDER_DEFINES_H
#define RENDER_DEFINES_H

namespace abyss
{
	namespace render
	{
		// TEXTURRE
		#define ABYSS_MAX_TEXTURES 16
		
		// LEVEL OF DETAIL
		#define ABYSS_MAX_LOD 3
		
		// SHADER STUFF
		#define ABYSS_FILTER_LIST std::vector<ABYSS_FILTER_TYPE>
		#define ABYSS_FILTER_LIST_PTR ABYSS_FILTER_LIST*

		#define ABYSS_NULL_HANDLE -1;
	}
}

#endif
