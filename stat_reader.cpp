#include <algorithm>
#include <array> 
#include <exception>
#include <iomanip> 
#include <iostream> 
#include <ostream> 
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector> 
#include <deque> 
#include "transport_catalogue.h"
#include "stat_reader.h"

using namespace std; 
/* using namespace TransportGuide; */

/* namespace Detail */

void Detail::PrintInfo (TransportGuide::TransportCatalogue &TC)
{
    for ( auto [index, name]: TC.GetDataUser())
    {
        if (index == "Bus")
        {
            Detail::PrintInfoBus (TC, name);
        }
        if (index == "Stop")
        {
            Detail::PrintInfoStop(TC, name);
        }
    }
}


void Detail::PrintInfoBus ( TransportGuide::TransportCatalogue &TC, const string& name )
{
        /* { */
           Detail::Bus bus = TC.GetBuses (name);
           if (TC.StatusUserBus (bus))
           {
               size_t distance = TC.RouteBusDistance(bus);

                cout<< "Bus " << name << ": "
                    << bus.stops.size( ) << " stops on route, "
                    << bus.stops_link.size( ) << " unique stops, "
                    << distance <<" route length, "
                    << fixed <<std::setprecision ( 6 ) <<distance/ TC.LengthBusStops( name )
                    << " curvature"
                    << endl;
           }
           else
           {
               cout << "Bus " << name << ": not found"<< endl;
           }
        /* } */
}

void Detail::PrintInfoStop(TransportGuide::TransportCatalogue &TC, const std::string &name)
{
    cout << "Stop "<< name <<": ";

    if ( TC.GetStop(name).name_stop != name )
    {
        cout << "not found";
    }

    try
    {
        // вывести список автобусов
        std::unordered_set<std::string_view> buse = TC.BusesOnStop(name);
        std::vector<std::string> sorted_buses(buse.begin(), buse.end());
        std::sort(sorted_buses.begin(), sorted_buses.end(), [](const auto& a, const auto& b) {
                return a < b;
                });

        if (sorted_buses.size()>0)
        {
            cout << "buses";
            for (auto bus_name: sorted_buses)
            {
                cout <<" "<< bus_name;
            }

        }

        if ( TC.GetStop(name).name_stop == name  && sorted_buses.size()==0)
        {
            cout << "no buses";
        }

    } catch(std::exception & ex)
    {
    }



    cout << endl;
}


