//
// Created by lekrieg on 02/08/25.
//

#ifndef BASE_ASSET_H
#define BASE_ASSET_H

#include <string>

class BaseAsset
{
public:

    std::string filePath {};
    std::string fileName {};
    bool isActive = true;

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

#endif //BASE_ASSET_H

