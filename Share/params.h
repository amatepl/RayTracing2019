#ifndef PARAMS_H
#define PARAMS_H

#include <tuple>

using namespace std;

/*!
 * \class AntenaPrams
 * \brief The AntenaParams class
 */
class AntenaParams
{
public:
    static AntenaParams *getInstance();

    double frequency {26e9}; // [GHz]
    double bandwidth {100e6};// [MHz]

private:
    AntenaParams(){};
    ~AntenaParams(){};
    static AntenaParams *antenaParams;
};

AntenaParams *AntenaParams::antenaParams = nullptr;

AntenaParams *AntenaParams::getInstance(){
    if(antenaParams==nullptr){
        antenaParams = new AntenaParams();
    }
    return antenaParams;
};

/*!
 * \class MapPrams
 * \brief The MapParams class
 */
class MapParams
{
public:
    static MapParams *getInstance();

    double street_denisity  {100};
    tuple<int, int> size    {500, 500};
    double car_density      {100};
    double car_speed        {30};

private:
    MapParams(){};
    ~MapParams(){};
    static MapParams *mapParams;
};

MapParams *MapParams::mapParams = nullptr;

MapParams *MapParams::getInstance(){
    if(mapParams==nullptr){
        mapParams = new MapParams();
    }
    return mapParams;
};

/*!
 * \class RayTracingParams
 * \brief The RayTracingParams class
 */
class RayTracingParams
{
public:
    static RayTracingParams *getInstance();

    double reflections_nbr {3};

private:
    RayTracingParams(){};
    ~RayTracingParams(){};
    static RayTracingParams *rayTracingParams;
};

RayTracingParams *RayTracingParams::rayTracingParams = nullptr;

RayTracingParams *RayTracingParams::getInstance(){
    if(rayTracingParams==nullptr){
        rayTracingParams = new RayTracingParams();
    }
    return rayTracingParams;
};

/*!
 * \class CoverageParams
 * \brief The CoverageParams class
 */
class CoverageParams
{
public:
    static CoverageParams *getInstance();

    double reflections_nbr  {3};
    double density          {100};

private:
    CoverageParams(){};
    ~CoverageParams(){};
    static CoverageParams *coverageParams;
};

CoverageParams *CoverageParams::coverageParams = nullptr;

CoverageParams *CoverageParams::getInstance(){
    if(coverageParams==nullptr){
        coverageParams = new CoverageParams();
    }
    return coverageParams;
};

#endif // PARAMS_H
