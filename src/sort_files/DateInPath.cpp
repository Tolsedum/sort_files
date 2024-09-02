#include "sort_files/DateInPath.hpp"
#include "DateInPath.hpp"


sort_files::DateInPath::DateInPath(std::string & direction, std::vector<std::string> & month)
    : direction_(&direction)
    , month_(&month)
{}

std::string sort_files::DateInPath::parsName(std::filesystem::directory_entry path){
    std::string ret_value;
    if(path.is_regular_file()){
        std::string year;
        std::string month;
        std::string date;
        for (auto iter : ufn::exploed(path.path().string(), "/")){
            if(year.empty() && ufn::isNumeric(iter) && iter.size() == 4){
                year = iter;
            }else if(month.empty() && !year.empty() && ufn::inArray(*month_, iter.substr(3))){
                month = iter;
            }else if(!month.empty()){
                struct tm tm;
                std::string s(iter);
                if (strptime(s.c_str(), "%d.%m.%Y", &tm)){
                    date = iter;
                }
            }
        }
        if(!year.empty() && !month.empty() && !date.empty()){
            ret_value.append(*direction_).append("/")
                .append(year).append("/")
                .append(month).append("/")
                .append(date).append("/")
                .append(path.path().filename());

        }
    }
    return ret_value;
}