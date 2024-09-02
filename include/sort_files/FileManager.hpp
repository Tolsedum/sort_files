#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

/** Version 0 */

/**
 *  __________________________________________
 * |                                          |
 * |   ╭━━━━┳━━━┳╮╱╱╭━━━┳━━━┳━━━┳╮╱╭┳━╮╭━╮    |
 * |   ┃╭╮╭╮┃╭━╮┃┃╱╱┃╭━╮┃╭━━┻╮╭╮┃┃╱┃┃┃╰╯┃┃    |
 * |   ╰╯┃┃╰┫┃╱┃┃┃╱╱┃╰━━┫╰━━╮┃┃┃┃┃╱┃┃╭╮╭╮┃    |
 * |   ╱╱┃┃╱┃┃╱┃┃┃╱╭╋━━╮┃╭━━╯┃┃┃┃┃╱┃┃┃┃┃┃┃    |
 * |   ╱╱┃┃╱┃╰━╯┃╰━╯┃╰━╯┃╰━━┳╯╰╯┃╰━╯┃┃┃┃┃┃    |
 * |   ╱╱╰╯╱╰━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻╯╰╯╰╯    |
 * |__________________________________________|
 * |                                          |
 * | Permission is hereby granted, free of    |
 * | charge, to any person obtaining a copy of|
 * | of this software and accompanying files, |
 * | to use them without restriction,         |
 * | including, without limitation, the       |
 * | rights to use, copy, modify, merge,      |
 * | publish, distribute, sublicense and/or   |
 * | sell copies of the software. The authors |
 * | or copyright holders shall not be liable |
 * | for any claims, damages or other         |
 * | liability, whether in contract, tort or  |
 * | otherwise, arising out of or in          |
 * | connection with the software or your use |
 * | or other dealings with the software.     |
 * |__________________________________________|
 * |   website: tolsedum.ru                   |
 * |   email: tolsedum@gmail.com              |
 * |   email: tolsedum@yandex.ru              |
 * |__________________________________________|
 */

#include <string>
#include <map>
#include "functions.hpp"
#include "sort_files/DateInFileName.hpp"
#include "sort_files/Timestamp.hpp"
#include "sort_files/DateInPath.hpp"
#include "sort_files/ParamsFile.hpp"

namespace sort_files{


enum SortType{date_in_path, date_in_file_name, timestamp, params};// params alwaнs last
inline std::vector<std::string> strSortType{"date_in_path", "date_in_file_name", "timestamp", "params"};

class FileManager{
protected:
    bool valid_;
    
    std::string direction_;
    /** Path wheare sorting file */
    std::string path_for_sort_;
    /** Sort type */
    std::vector<SortType> list_type_;

    std::vector<std::string> month_;

    std::map<std::string, std::string> params_;

    void defaulInit();

    void createFile(std::string new_file, std::string source_file);

    std::string dateInPath(std::filesystem::directory_entry path);
    std::string dateInFileName(std::filesystem::directory_entry path);
    std::string timestampFileName(std::filesystem::directory_entry path);
    std::string fileParams(std::filesystem::directory_entry path);
public:
    FileManager(std::string path);
    FileManager(std::string path, std::vector<SortType> types);
    FileManager(std::string path, std::vector<SortType> types, std::map<std::string, std::string> params);
    
    ~FileManager(){};
    void sort();

};
}
#endif // FILE_MANAGER_HPP