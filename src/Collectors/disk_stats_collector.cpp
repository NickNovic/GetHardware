#include <cmath>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
#include <vector>
#include <sys/statvfs.h>

#include <iostream>

#include "stats_collector.cpp"

#ifndef DISK_STATS_COLLECTOR
#define DISK_STATS_COLLECTOR

class disk_stats_collector : public stats_collector{
private:
    std::vector<stat_dto>* stats_list;
    std::string _label;
    struct statvfs64 disk_data;

    unsigned long divider = pow(2, 30); // 1GB = 2^30B 

    // All fuctions return free space in GB
    float get_size()
    {
        unsigned long size = disk_data.f_blocks * disk_data.f_bsize;
        return (float)size / (float)divider;
    }

    float get_free_space()
    {
        unsigned long free_space = disk_data.f_bsize * disk_data.f_bfree;
        return (float)free_space/(float)divider;
    }

    stat_dto* form_to_dto(std::string field, float data){
        stat_dto* dto = new stat_dto;

        std::ostringstream sstream;
        sstream<<std::fixed<<std::setprecision(2)<<data<<" GB";
        
        dto->set_field(field+":");
        dto->set_view(sstream.str());
        
        return dto;
    }

public:
    disk_stats_collector()
    {
        _label = "Disk";
        stats_list = new std::vector<stat_dto>();
        statvfs64("/", &disk_data);
    }

    ~disk_stats_collector()
    {
        delete stats_list;
    }
    std::string get_label() override{
        return _label;
    }

    std::vector<stat_dto>* collect() override{
        float total_space = get_size();
        float free_space = get_free_space();
        float used_space = total_space - free_space;

        stat_dto* dto = form_to_dto("Total Space", total_space);
        stats_list->insert(stats_list->end(), *dto);

        dto = form_to_dto("Used Space", used_space);
        stats_list->insert(stats_list->end(), *dto);

        dto = form_to_dto("Free Space", free_space);
        stats_list->insert(stats_list->end(), *dto);

        delete dto;
        return stats_list;
    }
};

#endif