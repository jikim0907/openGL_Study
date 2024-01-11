#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename){
    std::ifstream fin(filename);
    if(!fin.is_open()){
        SPDLOG_ERROR("Failed to open file:{}",filename);
        return 0;
    }
    std::stringstream text;
    text << fin.rdbuf();  // fin(filename) store to text(stringstream)
    return text.str(); //text exchange to string
}