#pragma once
#include <string_view>
#include "transport_catalogue.h"


namespace Detail
{
/* Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length */
/* Bus 751: not found */
void PrintInfoBus(TransportGuide::TransportCatalogue &TC, const std::string &);
/* void PrintInfoBus(TransportCatalogue &TC); */

/* Stop Samara: not found */
/* Stop Prazhskaya: no buses */
/* Stop Biryulyovo Zapadnoye: buses 256 828 */
void PrintInfoStop(TransportGuide::TransportCatalogue &TC, const std::string &);

        
// выдача информации в очередности ввода запроса пользователя.
// остановки и автобуса
// запросы могут чередоваться
void PrintInfo (TransportGuide::TransportCatalogue &TC);

}
