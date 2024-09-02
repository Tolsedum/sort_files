#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <string>
#include "functions.hpp"

namespace sort_files{
struct FileDate{
    short day;
    short month;
    int year;

    FileDate(){
        day = 0;
        month = 0;
        year = 0;
    };

    bool notEmpty(){
        return day > 0 && month > 0 && year > 0;
    }
};
class Timestamp{
private:
    std::string *direction_;
    std::vector<std::string> *month_;

    FileDate getFileDate(std::string file_name);
public:
    Timestamp(std::string &direction, std::vector<std::string> &month);
    ~Timestamp(){};
    std::string parsName(std::filesystem::directory_entry path);

};
}


#endif // TIMESTAMP_HPP