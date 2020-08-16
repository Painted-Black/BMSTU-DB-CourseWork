#pragma once

#include "core/ISerializable.h"
#include "staff.h"
#include "user_data.h"
#include "passport.h"

class ProxyAuth
{
public:
    static std::tuple<AccessData, QByteArray> deserialize(const QByteArray&);
};

