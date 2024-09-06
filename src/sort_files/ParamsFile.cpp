#include "sort_files/ParamsFile.hpp"
#include "ParamsFile.hpp"

sort_files::ParamsFile::ParamsFile(
    std::string &direction, 
    std::vector<std::string> &month, 
    std::string &params_dir
)
    : direction_(&direction)
    , month_(&month)
    , params_dir_(params_dir)
{}

std::string sort_files::ParamsFile::getFileDate(std::string file_name){
    struct stat fileStat;
    if (stat(file_name.c_str(), &fileStat) == 0) { 
        unsigned long tim = (unsigned long)fileStat.st_ctim.tv_sec;
        return ufn::convertTimestampDateToString(tim);
    } else { 
        return "Failed to retrieve file information\n"; 
    } 
    return "";
}

std::string sort_files::ParamsFile::parsName(std::filesystem::directory_entry path){
    std::string ret_value;
    if(path.is_regular_file()){
        std::string year;
        std::string month;
        std::string date;
        std::vector<std::string> date_line = ufn::exploed(
            ufn::exploed(getFileDate(path.path().string()), " ")[0], "-"
        );
        for (std::size_t i = 0; i < date_line.size(); i++){
            if(i == 0){
                year = date_line[i];
            }else if(i == 1){
                month = date_line[i];
            }else if(i == 2){
                date = date_line[i];
            }
        }
        if(!year.empty() && !month.empty() && !date.empty()){
            ret_value.append(*direction_).append("/");
            if(!params_dir_.empty()){
                ret_value.append(params_dir_).append("/");
            }
            ret_value.append(year).append("/")
                .append(month).append(" ")
                .append((*month_)[ufn::strToInt(month)-1]).append("/")
                .append(date).append(".")
                .append(month).append(".")
                .append(year).append("/")
                .append(path.path().filename());
        }
    }
    return ret_value;
}