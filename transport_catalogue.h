#pragma once  
// в 3м задании нужно будет добавить словарь до соседних остановок 
        // ключ имя значение расстояние до остановок.(их может быть несколько)
        // здесь это делать не эффективно так как идет двойной поиск. 
        // вначале поиск этой остановке а затем искать соседнюю остановку
        // ниже мы это сделаем через pair < Stop *, Stop *> = distance
        // надо реализовать свой хеш где он должен понять запись А и Б   Б и А это одно и тоже или нет
        // но у нас может быть что расстояния будут разные от А до Б и от Б до А т.к. автобус может идти другой дорогой до этой же остановки
        // operator ( Stop * A, Stop * B )-> генерация хеша тип size_t
        // при инициализации строки pair < Stop *, Stop *> нам надо указать хешер как третий параметр
        // std::unordered_map < pair < Stop *,Stop *>,size_t ( расстояние), hash >
#pragma once 
#include <iostream> 
#include <ostream> 
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector> 
#include <deque> 
#include "geo.h"
#include "input_reader.h"

namespace TransportGuide
{
class TransportCatalogue
{
    private:
        //TODO проинициализировать в bus все distance_;
        //не знаю в какой момент подключить обратную равернство.
        struct Hasher {
            size_t operator()(const std::pair<Detail::Stop*, Detail::Stop*>& data) const {
                std::size_t h1 = std::hash<Detail::Stop*>{}(data.first);
                std::size_t h2 = std::hash<Detail::Stop*>{}(data.second);
                return h1 ^ (h2 << 1);
            }
        };

     /* struct PairHash { */
       /* std::size_t operator ( )( const std::pair < Stop *, Stop *>& p ) const { */
       /*         return std::hash < Stop *> ( )( p.first )^ std::hash < Stop *> ( )( p.second ); */
       /* }}; */

        std::pair < Detail::Stop *, Detail::Stop *> distance;
        void AddPairStop (const std::string_view name_stop);

        std::deque < Detail::Bus > buses;
        std::deque < Detail::Stop > stops;
        std::vector < std::string > data_catalog;    // ввод данных

        std::vector < std::pair < std::string, std::string >> data_user_all;       // запрос пользователя

        std::unordered_map < std::string_view, Detail::Bus *> bus_map;    // быстрый доступ к Bus из deque
        std::unordered_map < std::string_view, Detail::Stop *> stops_map;

        std::unordered_map < std::string_view,  std::unordered_set < std:: string_view >> buses_on_stop;
        /* void InitBusesOnStop ( ); */


    public:
       std::unordered_map < std::pair < Detail::Stop *, Detail::Stop *>, size_t, Hasher > distance_;



        /* TransportCatalogue ( std::istringstream & ); */
        TransportCatalogue ( std::istream & ); const std::deque < Detail::Bus > GetBuses ( ) const { return buses;}
        Detail::Bus* GetBusLink (const std::string_view busname){return bus_map.at(busname);}
        Detail::Stop* GetStopLink (const std::string_view stopname){return stops_map.at(stopname);}
        Detail::Bus GetBuses ( const std::string& ) const;
        Detail::Stop GetStop ( const std::string& ) const;

        /* const std::deque < Stop > GetStop ( ) const { return stops;} */

        double LengthBusStops ( const std::string & bus ); // остановки где останавливается автобус
        bool StatusUserBus ( const Detail::Bus& );
        bool StatusUserStop ( const Detail::Stop& );
        /* bool StatusUserBus ( const std::string& ); */
        const std::vector < std::pair < std::string, std::string >> GetDataUser ( ) const { return data_user_all;}
        std::unordered_set < std::string_view > BusesOnStop ( const std::string_view &);
         
        std::unordered_map < std::pair < Detail::Stop *, Detail::Stop *>, size_t, Hasher>GetDistance(){return distance_;};
        void ShowDistance();
        size_t RouteBusDistance (const Detail::Bus& bus);

};

}

