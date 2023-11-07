#pragma once
#include <string> 
#include <string_view>
#include <deque> 
#include <unordered_map>
#include <vector> 
#include <sstream> 
#include <iostream> 

#include "geo.h"

namespace Detail
{
struct Bus;
struct Stop
{
private:
    std::string line;
public:
    Stop ( ):name_stop ( "" ),coordinates ( 0.0,0.0 ){}
    Stop ( std::string_view& );
    std::string name_stop;                      // название остановки
    Coordinates coordinates;                    // координаты остановки
    std::vector < std::string > buses;             // автобусы на остановке
    /* std::unordered_map < std::string_view, Bus *> bus_link; // РЕАЛИЗОВАТЬ ! */ 
    /* bool operator == ( const Stop & ); */
    std::deque < std::pair < std::string, size_t >> distance_stops;
    bool operator == ( const Stop& );
    bool operator != ( const Stop& stop) {return !(*this == stop);};
};


struct Bus
{
/* private: */
/* std::pair < Stop *, Stop *> distance; */
public:
    Bus ( )= default;
    Bus ( std::string& );
    std::string name_bus;                       // название автобуса
    std::vector < std::string > stops;
    std::unordered_map < std::string_view, Stop *> stops_link;
    double StopLength ( );
    bool operator == ( const Bus & );
    bool operator != ( const Bus & );
    /* void AddPairStop ( const std::string_view name_stop ); */
};


std::vector < std::string > GetDataTransport ( std::istream &input );
std::vector < std::string > GetUserAll ( std::istream &input );

Stop ParsingStop ( const std::string & );
Bus  ParsingBus ( const std::string & );

std::ostream &operator << ( std::ostream & out, const Bus& );
std::ostream &operator << ( std::ostream & out, const Stop& );

}

