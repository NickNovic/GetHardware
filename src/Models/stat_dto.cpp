#include <string>

#ifndef STAT_DTO
#define STAT_DTO

class stat_dto{
    private:
    // Properies
    std::string _field;
    std::string _view;
    
    // Fields
    static const int MAX_FIELD_LENGHT = 10;
    static const int VIEW_FIELD_LENGHT = 10;
    
    public:
    // Getters
    std::string get_field()
    {
        return  _field;
    }
    std::string get_view()
    {
        return  _view;
    }

    // Mutators
    void set_field(std::string field)
    {
        if(_field.length() > MAX_FIELD_LENGHT || field == ""){
            _field = "ERROR";
            return;
        }

        _field = field;
        return;
    }
    void set_view(std::string view)
    {
        if(_view.length() > MAX_FIELD_LENGHT || view == ""){
            _view = "ERROR";
            return;
        }

        _view = view;
        return;
    }
};

#endif