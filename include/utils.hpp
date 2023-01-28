#pragma once

#include <string>
#include <vector>

namespace comlint {
namespace utils {

std::string VectorToString(const std::vector<std::string> &vector, const std::string &delimiter = "", const std::string &opening_string = "", const std::string &closing_string = "");
template <typename MapType>
bool AreMapsEqual(const MapType &lhs, const MapType &rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }

    for (const auto &[lhs_key, lhs_value] : lhs) {
        if (rhs.find(lhs_key) == rhs.end() || lhs_value != rhs.at(lhs_key)) {
            return false;
        }
    }

    return true;
}

template <typename MapType>
bool MapContainsKey(const MapType &map, const typename MapType::key_type &key)
{
    return map.find(key) != map.end();
}

template <typename VectorType>
bool VectorContainsElement(const VectorType &vector, const typename VectorType::value_type &element)
{
    return std::find(vector.begin(), vector.end(), element) != vector.end();
}

} // utils
} // comlint