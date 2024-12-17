#include <cstdio>
#include <iomanip>
#include <ios>
#include <ostream>
#include <vector>
#include <iostream>

#include "Models/stat_dto.cpp"
#include "Collectors/disk_stats_collector.cpp"

int main(){
    stats_collector* collector = new disk_stats_collector;
    std::vector<stat_dto>* stats = collector->collect();
    std::string label = collector->get_label();
    std::cout<<"====================================\n         System Information\n====================================\n";
    
    std::cout<<label+":"<<std::endl;
    for(auto it = stats->begin(); it != stats->end(); ++it){

        // std::string format_string = " - " + it->get_field() + " " + it->get_view();
        // std::cout<<format_string<<std::endl;
        std::cout<<std::setw(15)<<std::left<<" - " + it->get_field();
        std::cout<<std::setw(10)<<std::right<<it->get_view();
        std::cout<<std::endl;


    }

    delete collector;
}