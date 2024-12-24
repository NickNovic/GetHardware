#include <cstdio>
#include <iomanip>
#include <ios>
#include <ostream>
#include <vector>
#include <iostream>

#include "Models/stat_dto.cpp"
#include "Collectors/disk_stats_collector.cpp"
#include "Collectors/cpu_stats_collector.cpp"
#include "Collectors/ram_stats_collector.cpp"

/*
===================================
         System Information
===================================
CPU:
- Usage:          25%
- Cores:          8
- Frequency:      3.20 GHz

Memory:
- Total:          16 GB
- Used:           8 GB
- Available:      8 GB

Disk:
- Total Space:    500 GB
- Used Space:     300 GB
- Free Space:     200 GB
-----------------------------------

*/










int main(){
    std::cout<<"====================================\n         System Information\n====================================\n";

    //CPU
    stats_collector* collector2 = new cpu_stats_collector;
    std::vector<stat_dto>* stats2 = collector2->collect();
    std::string label2 = collector2->get_label();

    std::cout<<label2+":"<<std::endl;
    for(auto it = stats2->begin(); it != stats2->end(); ++it){
        std::cout<<std::setw(20)<<std::left<<" - " + it->get_field();
        std::cout<<std::setw(20)<<std::left<<it->get_view();
        std::cout<<std::endl;
    }
    std::cout<<std::endl;


    // Memory
    stats_collector* mem_collector = new ram_stats_collector;
    std::vector<stat_dto>* mem_stats = mem_collector->collect();

    std::string mem_label = mem_collector->get_label();
    std::cout<<mem_label+":"<<std::endl;
    for(auto it= mem_stats->begin(); it != mem_stats->end(); ++it){
        std::cout<<std::setw(20)<<std::left<<" - " + it->get_field();
        std::cout<<std::setw(10)<<std::left<<it->get_view();
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    //Disk

    stats_collector* collector = new disk_stats_collector;
    std::vector<stat_dto>* stats = collector->collect();
    std::string label = collector->get_label();

    std::cout<<label+":"<<std::endl;
    for(auto it = stats->begin(); it != stats->end(); ++it){
        std::cout<<std::setw(20)<<std::left<<" - " + it->get_field();
        std::cout<<std::setw(10)<<std::left<<it->get_view();
        std::cout<<std::endl;
    }

    std::cout<<"------------------------------------\n";

    delete collector2;
    delete collector;
    delete  mem_collector;
}