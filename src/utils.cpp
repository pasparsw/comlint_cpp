#include <numeric>

#include "utils.hpp"

namespace comlint {
namespace utils {

std::string VectorToString(const std::vector<std::string> &vector, const std::string &delimiter, const std::string &opening_string, const std::string &closing_string)
{
    const std::string text = std::accumulate(vector.begin(), vector.end(), std::string(), [delimiter](const std::string &a, const std::string &b){
        return a + (a.size() > 0U ? delimiter : "") + b;
    });

    return opening_string + text + closing_string;
}

} // utils
} // comlint