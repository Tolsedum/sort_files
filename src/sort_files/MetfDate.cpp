#include "sort_files/MetfDate.hpp"

sort_files::MetaFileDate::MetaFileDate(std::string file_name){
    et_ = new ExifTool();
    info_ = et_->ImageInfo(file_name.c_str());
}

sort_files::MetaFileDate::~MetaFileDate(){
    if(info_){
        delete info_;
    }
    delete et_;
}

std::string sort_files::MetaFileDate::getDate(){
    if(date_.empty()){
        if (info_) {
            for (TagInfo *i = info_; i; i = i->next) {
                if(std::string(i->name).find("Date") != std::string::npos){
                    date_list_[i->name] = i->value;
                }
            }
            for (auto &&var : {"CreateDate", "DateTimeOriginal", "FileModifyDate"}){
                std::map<std::string, std::string>::iterator iter = date_list_.find(var);
                if(iter != date_list_.end()){
                    date_ = iter->second;
                    break;
                }
            }
        } else if (et_->LastComplete() <= 0) {
            std::cerr << "Error executing exiftool!" << std::endl;
        }
        char *err = et_->GetError();
        if (err) 
            std::cout << err;
    }
    return date_;
}

std::string sort_files::MetaDate::getFileDate(std::filesystem::directory_entry path){
    std::string ret_value;
    if(path.is_regular_file()){
        MetaFileDate metaFileDate(path.path().string());
        if(metaFileDate.getDate().empty()){
            return ret_value;
        }
        
        std::string year;
        std::string month;
        std::string date;
        std::vector<std::string> date_line = ufn::exploed(metaFileDate.getDate(), ":");
        for (std::size_t i = 0; i < 3; i++){
            if(i == 0){
                year = date_line[i];
            }else if(i == 1){
                month = date_line[i];
            }else if(i == 2){
                date = date_line[i];
            }
        }
        date = date.substr(0, 2);
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