// (c) 12/18/16 Lucas Deecke (ldeecke@gmail.com)

#ifndef common_h
#define common_h

#include <fstream>
#include <string>
#include <vector>

namespace utilities {

const char default_delimiter = ',';

template<typename T>
void write_result(const std::vector<T>& a, const std::vector<T>& b, std::ofstream& stream)
{
    for (size_t i = 0; i < a.size(); ++i)
    {
        stream << std::to_string(a[i]);
        stream << default_delimiter;
        stream << std::to_string(b[i]);
        stream << std::endl;
    }
};

} // namespace utilities

#endif //common_h
