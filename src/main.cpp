#include "sort_files/FileManager.hpp"


std::string date(std::string new_file){
    struct stat fileStat;
    if (stat(new_file.c_str(), &fileStat) == 0) { 
        unsigned long tim = (unsigned long)fileStat.st_ctim.tv_sec;
        return ufn::convertTimestampDateToString(tim);
    } else { 
        return "Failed to retrieve file information\n"; 
    } 
    return "";
}

int main(int argc, char *argv[]){
    if(argc > 1){
        std::string path_name;
        std::vector<sort_files::SortType> types;
        std::map<std::string, std::string> params;
        for (int i = 0; i < argc; i++){
            std::string arg{argv[i]};
            if(arg == "--help"){
                std::cout 
                << " --path_name  - The folder from which to sort files" << std::endl
                << std::endl
                << " --types_sort - Types of file sorting" << std::endl
                << "        date_in_path      - takes file data from the directory structure (year/month/day.month.year)" << std::endl
                << "        date_in_file_name - takes the creation date of the file from its name (row_date_number in order)" << std::endl
                << "        timestamp         - the name of the file is the type of timestamp" << std::endl
                << "        params            - taking the date from the file parameters (doesn't always work)" << std::endl
                << std::endl
                << " --params_dir - sort by type 'params' in a separate folder" << std::endl
                << std::endl;
                return 0;
            }else if(arg == "--path_name"){
                i++;
                if(i < argc){
                    path_name = argv[i];
                }
            }else if(arg == "--types_sort"){
                i++;
                if(i < argc){
                    std::vector<std::string> list_param = ufn::exploed(argv[i], ",");
                    for (auto &&iter : list_param){
                        iter = ufn::trim(iter);
                        short count = 0;
                        for (auto &&sort_type : sort_files::strSortType){
                            if(sort_type == iter){
                                types.push_back((sort_files::SortType)count);
                            }
                            count++;
                        }
                    }
                }
            }else if(arg == "--params_dir"){
                i++;
                if(i < argc){
                    params["params_dir"] = argv[i];
                }
            }
        }
        if(!path_name.empty()){
            sort_files::FileManager manager(path_name, types, params);
            manager.sort();
        }else{
            std::cout<< "Enter dir name!!!" << std::endl;
        }
    }

    std::cout << "Exit" << std::endl;
}
