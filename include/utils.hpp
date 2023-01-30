#pragma once

#include <string>
#include <vector>
#include <map>

namespace comlint {
namespace utils {

std::string VectorToString(const std::vector<std::string> &vector, const std::string &delimiter = "", const std::string &opening_string = "", const std::string &closing_string = "");
std::string GetSimilarValues(const std::vector<std::string> &vector, const std::string &value, const std::string &delimiter = "");

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

template <typename ValueType>
std::string MapKeysToString(const std::map<std::string, ValueType> &map, const std::string &delimiter = "")
{
    std::string keys {};

    for (const auto &[key, value] : map) {
        keys += key + delimiter;
    }

    return keys.substr(0U, keys.size() - delimiter.size());
}

template <typename ValueType>
std::string GetSimilarKeys(const std::map<std::string, ValueType> &map, const std::string &value, const std::string &delimiter = "")
{
    std::string similar_values {};

    for (const auto &[key, map_value] : map) {
        if (key.find(value) != std::string::npos || value.find(key) != std::string::npos) {
            similar_values += key + delimiter;
        }
    }

    return similar_values.empty() ? similar_values : similar_values.substr(0U, similar_values.size() - delimiter.size());
}

template <typename VectorType>
bool VectorContainsElement(const VectorType &vector, const typename VectorType::value_type &element)
{
    return std::find(vector.begin(), vector.end(), element) != vector.end();
}

} // utils
} // comlint