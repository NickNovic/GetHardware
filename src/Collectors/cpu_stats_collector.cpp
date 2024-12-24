#include "stats_collector.cpp"
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#ifndef CPU_STATS_COLLECTOR
#define CPU_STATS_COLLECTOR

// I found no library for getting infro about CPU for linux,
// maybe they exists, sincerly, I wasn't searching too much.
// For this part of fuctionality I will use linux files from /proc and /sys


class cpu_stats_collector : public stats_collector{
private:
    std::string _label;
    std::vector<stat_dto>* stats_list;
    unsigned long max_frequency;
    // Returns max frequency of CPU in Hz
    unsigned long get_max_frequency(){
        unsigned long frequency;

        std::ifstream file;
        // In this file linux stores cpu max frequency in Hz
        file.open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
        
        file>>frequency;
        
        file.close();
        return frequency;
    }
    // Returns average frequency in MHz
    float get_current_average_frequency(){
        float summ = 0, count = 0;
        std::ifstream file;
        // In this file linux stores more infromation about every core of CPU
        file.open("/proc/cpuinfo");

        std::string line;
        while (getline(file, line)) {
            std::string label = line.substr(0,7);
            if(label == "cpu MHz")
            {
                std::string value = line.substr(10,11);
                float fr = std::stoi(value);
                summ += fr;
                count++;
            }

        }
        
        file.close();

        return summ / count;
    }
    int get_cores_count(){
        std::ifstream file;
        int count = 0;
        // In this file linux stores more infromation about every core of CPU
        file.open("/proc/cpuinfo");

        std::string line;
        while (getline(file, line)) {
            std::string label = line.substr(0,9);
            if(label == "cpu cores")
            {
                std::string value = line.substr(11,13);

                count = std::stoi(value);
                file.close();
            }
        }
        
        return count;
    }
public:
    cpu_stats_collector(){
        max_frequency = get_max_frequency();
        stats_list = new std::vector<stat_dto>;
        _label = "CPU";
    }
    ~cpu_stats_collector(){
        delete stats_list;
    }
    std::string get_label() override{
        return _label;
    }
    std::vector<stat_dto>* collect() override{
        stat_dto* dto = new stat_dto;


        // Getting processor usage now
        dto->set_field("Usage");
        // Getting average frequency and converting it to Hz
        float current_frequency = get_current_average_frequency() * 1000;
        float usage = (current_frequency / (float)max_frequency);
        int usage_percent = round(usage * 100);
        dto->set_view(std::to_string(usage_percent)+ "%");
        
        stats_list->insert(stats_list->end(), *dto);
        
        // Getting cores count
        dto->set_field("Cores");
        int cores_count = get_cores_count();
        dto->set_view(std::to_string(cores_count));
        
        stats_list->insert(stats_list->end(), *dto);
        
        // Getting processor frequency
        dto->set_field("Frequency");
        
        float max_frequency_GHz = (float) max_frequency / 1000000; // Converting from Hz to GHz
        std::ostringstream sstream;
        sstream<<std::fixed<<std::setprecision(2)<<max_frequency_GHz<<" GHz";
        dto->set_view(sstream.str());
        
        stats_list->insert(stats_list->end(), *dto);
        
        return stats_list;
    }
};

#endif
