#ifndef RAYTRACINGALGORITHMFACTORY_H
#define RAYTRACINGALGORITHMFACTORY_H

#include "Abstract_Factory/abstractalgorithmfactory.h"
#include "Model/raytracing.h"

class RayTracingAlgorithmFactory: public AbstractAlgorithmFactory
{
public:
    RayTracingAlgorithmFactory();

    //AbstractAlgorithmFactory
    AlgorithmInterface * createAlgorithm(Tx *, Rx *) override;
};

#endif // RAYTRACINGALGORITHMFACTORY_H
