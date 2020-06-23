#include "raytracing.h"

RayTracing::RayTracing(MathematicalTransmitterProduct *transmitter, MathematicalReceiverProduct *receiver)
{
    RayFactory* rayFactory = new RayFactory(true);
    transmitter->setRayFactory(rayFactory);

}

RayTracing::RayTracing(){

}

MathematicalComponent* RayTracing::compute(MathematicalTransmitterProduct* transmitter, MathematicalReceiverProduct* receiver){

}
