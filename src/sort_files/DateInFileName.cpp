#include "sort_files/DateInFileName.hpp"

sort_files::DateInFileName::DateInFileName(std::string &direction, std::vector<std::string> &month)
    : direction_(&direction)
    , month_(&month)
{}

std::string_view sort_files::DateInFileName::getName(std::string file_name){
    std::string_view result{};
    std::string d;
    
    for (auto &&iter : {"_", "-"}){
        if(file_name.find(iter) != std::string::npos){
            d = iter;
            break;
        }
    }
    
    if(!d.empty()){
        std::vector<std::string> list_name = ufn::exploed(file_name, d);

        if(
            list_name.size() == 2
            && ufn::isNumeric(list_name[0])
            && ufn::isNumeric(list_name[1])
        ){
            result = list_name[0];
        }else if(
            list_name.size() == 3
            && ufn::isNumeric(list_name[1])
            && ufn::isNumeric(list_name[2])
        ){
            result = list_name[1];
        }
    }
    
    return result;
}

std::string sort_files::DateInFileName::parsName(std::filesystem::directory_entry path){
    std::string result_name;
    if(path.is_regular_file()){
        std::string file_name = path.path().stem();
        std::string_view date_name = getName(file_name);
        // ToDo Если дата 2018-05-22-12_24_10_828
        if(!date_name.empty()){
            result_name = *direction_;
            result_name.append("/");
            std::vector<std::pair<int, int>> v{{0,4}, {4,2}, {6,2}};
            std::string year;
            std::string month;
            short count = 0;
            for (std::pair<int, int> &i : v){
                std::string element{date_name.substr(i.first, i.second)};
                if(count == 0){
                    year = element;
                }else if(count == 1){
                    month = element;
                    element.append(" ").append((*month_)[ufn::strToInt(element)-1]);
                }else if(count == 2){
                    element.append(".")
                        .append(month)
                        .append(".")
                        .append(year);
                }
                result_name.append(element).append(1, '/');
                count++;
            }
            result_name.append(path.path().filename());
        }
    }
    
    return result_name;
}