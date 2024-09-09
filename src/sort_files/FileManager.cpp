#include "sort_files/FileManager.hpp"

sort_files::FileManager::FileManager(std::string path)
    : path_for_sort_(path)
{
    defaulInit();
}

sort_files::FileManager::FileManager(std::string path, std::vector<SortType> types)
    : path_for_sort_(path)
{
    list_type_ = types;
    defaulInit();
}

sort_files::FileManager::FileManager(
    std::string path, std::vector<SortType> types, std::map<std::string, std::string> params
)
    : path_for_sort_(path)
    , params_(params)
{
    list_type_ = types;
    defaulInit();
}

void sort_files::FileManager::defaulInit(){
    if(params_.empty()){
        for (auto &&key : {"params_dir", "rename_file"}){
            params_[key] = "";
        }
    }
    direction_ = "sort";
    month_ = {
        "Январь", "Февраль", "Март", "Апрель", 
        "Май", "Июнь", "Июль", "Август", "Сентябрь", 
        "Октябрь", "Ноябрь", "Декабрь"
    };
    if(std::filesystem::exists(path_for_sort_)){
        valid_ = true;
    }else{
        valid_ = false;
    }
    if(list_type_.empty()){
        for (int i = 0; i <= (int)SortType::params; i++){
            list_type_.push_back((SortType)i);
        }
    }
}


void sort_files::FileManager::sort(){
    if(valid_){
        for (const std::filesystem::directory_entry &file_name_in_path
            : std::filesystem::recursive_directory_iterator(path_for_sort_)
        ){
            std::string new_path;
            for (auto &&type : list_type_){
                switch (type){
                    case SortType::date_in_path:
                        new_path = dateInPath(file_name_in_path);
                        break;
                    case SortType::date_in_file_name:
                        new_path = dateInFileName(file_name_in_path);
                        break;
                    case SortType::timestamp:
                        new_path = timestampFileName(file_name_in_path);
                        break;
                    case SortType::params:
                        new_path = fileParams(file_name_in_path);
                        break;
                    default:
                        break;
                }
                if(!new_path.empty()){
                    break;
                }
            }
            if(!new_path.empty()){
                createFile(new_path, file_name_in_path.path().string());
            }
        }
    }
}


void sort_files::FileManager::createFile(std::string new_file, std::string source_file){
    if(!std::filesystem::exists(new_file)){
        std::string parent_dir = ufn::getParentDir(new_file);
        if(!std::filesystem::exists(parent_dir)){
            std::filesystem::create_directories(parent_dir);
        }

        if(params_["rename_file"] == "true"){ // Если есть запрос на перенос файла
            rename(source_file.c_str(), new_file.c_str());
        }else{
            std::filesystem::file_time_type new_time = std::filesystem::last_write_time(source_file);
            std::filesystem::copy_file(source_file, new_file);
            std::filesystem::last_write_time(new_file, new_time);
        }
        std::cout<< "File is ready: " << new_file <<std::endl;
    }else{
        std::cout<< "File exists: " << new_file <<std::endl;
    }
}

std::string sort_files::FileManager::dateInPath(std::filesystem::directory_entry path){
    DateInPath dateInPath(direction_, month_);
    return dateInPath.parsName(path);
}

std::string sort_files::FileManager::dateInFileName(std::filesystem::directory_entry path){
    DateInFileName dateInFileName(direction_, month_);
    return dateInFileName.parsName(path);
}

std::string sort_files::FileManager::timestampFileName(std::filesystem::directory_entry path){
    Timestamp timestamp(direction_, month_);
    return timestamp.parsName(path);
}

std::string sort_files::FileManager::fileParams(std::filesystem::directory_entry path){
    ParamsFile paramsFile(direction_, month_, params_["params_dir"]);
    return paramsFile.parsName(path);
}