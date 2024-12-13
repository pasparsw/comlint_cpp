#include <numeric>

#include "comlint/utils.hpp"

namespace comlint {
namespace utils {

std::string VectorToString(const std::vector<std::string> &vector, const std::string &delimiter, const std::string &opening_string, const std::string &closing_string)
{
    const std::string text = std::accumulate(vector.begin(), vector.end(), std::string(), [delimiter](const std::string &a, const std::string &b){
        return a + (a.size() > 0U ? delimiter : "") + b;
    });

    return opening_string + text + closing_string;
}

std::string GetSimilarValues(const std::vector<std::string> &vector, const std::string &value, const std::string &delimiter)
{
    std::string similar_values {};

    for (const auto &element : vector) {
        if (element.find(value) != std::string::npos || value.find(element) != std::string::npos) {
            similar_values += element + delimiter;
        }
    }

    return similar_values.empty() ? similar_values : similar_values.substr(0U, similar_values.size() - delimiter.size());
}

} // utils
} // comlint