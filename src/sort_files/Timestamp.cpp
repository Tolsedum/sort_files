#include "sort_files/Timestamp.hpp"
#include "Timestamp.hpp"

sort_files::Timestamp::Timestamp(std::string &direction, std::vector<std::string> &month)
    : direction_(&direction), month_(&month)
{}

sort_files::FileDate sort_files::Timestamp::getFileDate(std::string file_name){
    FileDate result{};
    if(ufn::isNumeric(file_name)){
        unsigned long times = ufn::strToUnsignedLong(file_name);
        if(times > 9999999999){
            times = times/1000;
        }
        std::time_t temp = times;
        std::tm* t = std::localtime(&temp);
        result.day = t->tm_mday;
        result.month = t->tm_mon;
        result.year = t->tm_year + 1900;
    }
    return result;
}

std::string sort_files::Timestamp::parsName(std::filesystem::directory_entry path){
    std::string result{};
    FileDate date = getFileDate(path.path().stem());
    if(date.notEmpty()){
        std::string str_date = std::to_string(date.day);
        std::string month = std::to_string(date.month);
        std::string year = std::to_string(date.year);
        if(month.size() == 1){
            month = "0" + month;
        }
        if(str_date.size() == 1){
            str_date = "0" + str_date;
        }
        result = *direction_;
        result.append("/")
            .append(year)
            .append(1, '/')
            .append(month)
            .append(" ")
            .append((*month_)[date.month-1])
            .append(1, '/')
            .append(str_date)
            .append(".")
            .append(month)
            .append(".")
            .append(year)
            .append(1, '/')
            .append(path.path().filename());
    }
    
    return result;
}
