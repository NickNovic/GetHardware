#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>

#include "stats_collector.cpp"

#ifndef RAM_STATS_COLLECTOR
#define RAM_STATS_COLLECTOR

class ram_stats_collector : public stats_collector{
private:
    std::string _label;
    std::vector<stat_dto>* stats_list;
    // In this file in linux systems are stored all information about RAM
    std::string file_path = "/proc/meminfo";
    float divider = 1000000;
    float get_total_ram(){
        std::ifstream file;
        file.open(file_path);
        std::string output;
        getline(file, output);
        std::string memory_str = output.substr(16, 8);
        float available_ram = std::stoi(memory_str) / divider;
        file.close();
        return available_ram;
    }

    float get_free_ram(){
        std::ifstream file;
        file.open(file_path);
        
        // Skipping one line:
        std::string output;
        getline(file, output);

        // Getting data
        getline(file, output);
        std::string memory_str = output.substr(16, 8);
        float available_ram = std::stoi(memory_str) / divider;
        file.close();
        return available_ram;
    }

    // TODO: Rewrite and reuse)
    stat_dto* form_to_dto(std::string field, float data){
        stat_dto* dto = new stat_dto;

        std::ostringstream sstream;
        sstream<<std::fixed<<std::setprecision(2)<<data<<" GB";
        
        dto->set_field(field+":");
        dto->set_view(sstream.str());
        
        return dto;
    }
public:
    ram_stats_collector(){
        _label = "Memory";
        stats_list = new std::vector<stat_dto>();
    }
    ~ram_stats_collector(){
        delete stats_list;
    }
    std::string get_label() override{
        return _label;
    }

    std::vector<stat_dto>* collect() override{
        stat_dto* dto = new stat_dto;
        float total_ram = get_total_ram();
        float free_ram = get_free_ram();
        
        dto = form_to_dto("Total", total_ram);
        stats_list->insert(stats_list->end(), *dto);

        dto = form_to_dto("Used", total_ram - free_ram);
        stats_list->insert(stats_list->end(), *dto);

        dto = form_to_dto("Available", free_ram);
        stats_list->insert(stats_list->end(), *dto);


        delete dto;
        return stats_list;
    }
};

#endif