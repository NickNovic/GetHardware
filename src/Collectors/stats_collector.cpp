#include <vector>

#include "../Models/stat_dto.cpp"

#ifndef STATS_COLLECTOR
#define STATS_COLLECTOR

class stats_collector{
    public:
    virtual std::string get_label() = 0;
    virtual std::vector<stat_dto>* collect() = 0;
    virtual ~stats_collector() = 0;
};

stats_collector::~stats_collector(){}

#endif