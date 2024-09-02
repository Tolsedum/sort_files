#ifndef DATE_IN_PATH_HPP
#define DATE_IN_PATH_HPP

#include "functions.hpp"

namespace sort_files{
class DateInPath{
private:
    std::string *direction_;
    std::vector<std::string> *month_;

    std::string_view getName(std::string file_name);
public:
    DateInPath(std::string &direction, std::vector<std::string> &month);
    ~DateInPath(){};

    std::string parsName(std::filesystem::directory_entry path);
};
}
#endif // DATE_IN_PATH_HPP