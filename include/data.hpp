#pragma once
#include "project_headers.hpp"
#include <array>
namespace data {

   
    namespace fuel {

    }


    namespace ship {

    }

    namespace terrain {
        
    }


    constexpr std::size_t totalVertices = fuel::verticesCount + ship::verticesCount + terrain::verticesCount;
    constexpr std::size_t totalIndicies = fuel::indiciesCount + ship::indiciesCount + terrain::indiciesCount;
}