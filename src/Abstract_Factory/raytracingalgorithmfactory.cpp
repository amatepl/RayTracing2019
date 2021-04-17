#include "raytracingalgorithmfactory.h"

RayTracingAlgorithmFactory::RayTracingAlgorithmFactory()
{

}

AlgorithmInterface* RayTracingAlgorithmFactory::createAlgorithm(Tx* /*transmitter*/, Rx* /*receiver*/){
    //RayTracing* rayTracing = new RayTracing(transmitter, receiver);
    //return rayTracing;
    return nullptr;
}
