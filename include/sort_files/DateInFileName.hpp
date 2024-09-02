#ifndef DATE_IN_FILE_NAME_HPP
#define DATE_IN_FILE_NAME_HPP

#include "functions.hpp"

namespace sort_files{
class DateInFileName{
private:
    std::string *direction_;
    std::vector<std::string> *month_;

    std::string_view getName(std::string file_name);
public:
    DateInFileName(std::string &direction, std::vector<std::string> &month);
    ~DateInFileName(){};
    std::string parsName(std::filesystem::directory_entry path);

};
}


#endif // DATE_IN_FILE_NAME_HPP