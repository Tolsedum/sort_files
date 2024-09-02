#ifndef PARAMS_FIEL_HPP
#define PARAMS_FIEL_HPP

#include <string>
#include "functions.hpp"

namespace sort_files{
class ParamsFile{
private:
    std::string *direction_;
    std::vector<std::string> *month_;
    std::string params_dir_;

    std::string getFileDate(std::string file_name);
public:
    ParamsFile(std::string &direction, std::vector<std::string> &month, std::string &params_dir);
    ~ParamsFile(){};
    std::string parsName(std::filesystem::directory_entry path);

};
}


#endif // PARAMS_FIEL_HPP