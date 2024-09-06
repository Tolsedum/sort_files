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
        if(file_name.find("-") != std::string::npos){
             std::vector<std::string> list_name = ufn::exploed(file_name, "_");
            if(!list_name.empty() && list_name.size() > 0){
                std::string tmp;
                std::string year;
                std::string month;
                std::string date;
                for (auto &&str_date : list_name){
                    if(ufn::isDate(str_date)){
                        list_name = ufn::exploed(str_date, "-");
                        int count = 1;
                        if(list_name.size() > 3){
                            count = 3 - (list_name.size() - 3);
                        }
                        for (int i = list_name.size()-count; i > -1; i--){
                            if(date.empty()){
                                date = list_name[i];
                            }else if(month.empty()){
                                month = list_name[i];
                            }else{
                                year = list_name[i];
                                if(year.size() == 2 && year[0] == '0'){
                                    year = "20" + year;
                                }
                                list_name[i] = year;
                            }
                            if(i == (int)list_name.size()-count){
                                tmp += list_name[i];
                            }else{
                                tmp += "." + list_name[i];
                            }
                        }
                        break;
                    }
                }
                if(!tmp.empty()){
                    result_name = *direction_;
                    result_name.append("/")
                        .append(year)
                        .append(1, '/')
                        .append(month)
                        .append(" ")
                        .append((*month_)[ufn::strToInt(month)-1])
                        .append(1, '/')
                        .append(tmp)
                        .append(1, '/')
                        .append(path.path().filename());
                }
            }
        }else{
            std::string_view date_name = getName(file_name);
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
    }
    
    return result_name;
}