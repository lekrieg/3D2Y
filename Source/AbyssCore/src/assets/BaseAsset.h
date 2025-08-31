//
// Created by lekrieg on 22/08/25.
//

#ifndef BASE_ASSET_H
#define BASE_ASSET_H

#include <string>

namespace abyss
{
    namespace assets
    {
        class BaseAsset
        {
        public:

            std::string name {};
            std::string path;

            BaseAsset()
            {
                internalId++;
                assetId = internalId;
            }

            const unsigned int GetId() const
            {
                return assetId;
            }

        private:

            static unsigned int internalId;
            unsigned int assetId {};
        };
    }
}

#endif //BASE_ASSET_H
