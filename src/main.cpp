#include "sort_files/FileManager.hpp"

#include <chrono>

int main(int argc, char *argv[]){

    // ToDo Добавить настройку, если проверка по параметрам то складывать в отдельное место
    
    if(argc > 1){
        std::string file_name;
        std::vector<sort_files::SortType> types;
        std::map<std::string, std::string> params;
        for (int i = 0; i < argc; i++){
            std::string arg{argv[i]};
            if(arg == "--file_name"){
                i++;
                if(i < argc){
                    file_name = argv[i];
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
        if(!file_name.empty()){
            sort_files::FileManager manager(file_name, types, params);
            manager.sort();
        }else{
            std::cout<< "Enter dir name!!!" << std::endl;
        }
    }
    std::cout << "Exit" << std::endl;
}
