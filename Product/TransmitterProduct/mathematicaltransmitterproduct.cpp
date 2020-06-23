#include "mathematicaltransmitterproduct.h"
MathematicalTransmitterProduct::MathematicalTransmitterProduct(TransmitterProduct* graphic)
{
    m_type = "Transmitter";
    setTransmitterProduct(graphic);
}

MathematicalTransmitterProduct::MathematicalTransmitterProduct(int posX, int posY):QPointF(posX,posY)
{
    m_type = "Transmitter";
}

MathematicalTransmitterProduct::~MathematicalTransmitterProduct(){

}

void MathematicalTransmitterProduct::newProperties(){
    //m_mathematicalfactory->receiveTransmitterProduct(this,m_graphic);
}

double MathematicalTransmitterProduct::computeGain(double theta,double phi, double frequency, int row,int column,double antennaDistance){
    complex <double> dipolefactor(0.0,0.0);
    complex <double> xarray(0.0,0.0);
    complex <double> yarray(0.0,0.0);
    complex <double> arrayfactor(0.0,0.0);
    complex <double> i(0.0,1.0);
    complex <double> psy(0.0,0.0);
    complex <double> qsy(0.0,0.0);

    double c = 3.0e9;
    double lambda = c/frequency;
    double d = lambda*antennaDistance;
    double k = 2.0*M_PI/lambda;
    double gain;

    psy = i*k*d*sin(phi*M_PI/180)*sin(theta*M_PI/180);
    qsy = i*k*d*sin(phi*M_PI/180)*cos(theta*M_PI/180);
    xarray = (exp(qsy*double(row))-1.0)/(exp(qsy)-1.0);
    yarray = (exp(psy*double(column))-1.0)/(exp(psy)-1.0);

    if (psy == 0.0+0.0*i){
        yarray = double(column) +0.0*i;
    }
    if(qsy == 0.0+0.0*i){
        xarray = double(row)+0.0*i;
    }

    arrayfactor = xarray*yarray;
    if (phi == 0.0 || phi == 180.0) dipolefactor = 0.0;
    else dipolefactor = cos(0.5*M_PI*cos(phi*M_PI/180))/sin(phi*M_PI/180);
    gain = 16.0/(3.0*M_PI)*abs(arrayfactor)*abs(dipolefactor);
    return gain;
}

void MathematicalTransmitterProduct::drawRays(){

}

TransmitterProduct* MathematicalTransmitterProduct::getTransmitterProduct(){
    return m_graphic;
}


unsigned long MathematicalTransmitterProduct::getFrequency(){
    return m_frequency;
}

double MathematicalTransmitterProduct::getPower(){
    return m_power;
}

int MathematicalTransmitterProduct::getRow(){
    return m_row;
}

int MathematicalTransmitterProduct::getColumn() {
    return m_column;
}


void MathematicalTransmitterProduct::setPosX(int posX){
    m_posx = posX;
    setX(m_posx);
}

void MathematicalTransmitterProduct::setPosY(int posY){
    m_posy = posY;
    setY(m_posy);
}

void MathematicalTransmitterProduct::setPower(double power){
    m_power = power;
}

void MathematicalTransmitterProduct::setFrequency(unsigned long frequency){
    m_frequency = frequency;
}

void MathematicalTransmitterProduct::setRow(int row){
    m_row = row;
}

void MathematicalTransmitterProduct::setColumn(int column) {
    m_column = column;
}



void MathematicalTransmitterProduct::setTransmitterProduct(TransmitterProduct *transmitterproduct){
    m_graphic = transmitterproduct;
    setPosX(m_graphic->getPosX());
    setPosY(m_graphic->getPosY());
//    setOrientation(m_graphic->getOrientation());
//    setAntennaDistance(m_graphic->getAntennaDistance());
}

MathematicalComponent* MathematicalTransmitterProduct::toMathematicalComponent(){
    return this;
}

void MathematicalTransmitterProduct::notify(const QPointF &pos){
    //m_EMfield = 0;
    //m_power = 0;
    cout<<"Transmitter position: "<<m_posx<<", "<< m_posy <<endl;

    m_wholeRays.erase(m_wholeRays.begin(),m_wholeRays.end());
    //if(m_zone.containsPoint(pos,Qt::OddEvenFill)){
        vector<MathematicalRayProduct> *wholeRay = new vector<MathematicalRayProduct>;
        QPointF m_pos(m_posx,m_posy);
        MathematicalRayProduct newRay = *(m_rayFactory->createRay(*this,pos));
        wholeRay->push_back(newRay);
        m_wholeRays.push_back(wholeRay);
        m_EMfield += computeEMfield(wholeRay);
        //m_power = m_scene->computePrx(m_EMfield,this);
        //m_receiver->addWholeRay(wholeRay);
//        switch(m_mode){
//            case RayTracing:m_scene->drawChosenRays(&m_wholeRays,this);
//        }
    //}
}

double MathematicalTransmitterProduct::computeReflexionPer(double thetaI, double epsilonR){
    //double R = (cos(thetaI) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)))/(cos(thetaI) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(sin(thetaI),2)));
    /*
     * Now in the code thatai is the angle between the ray and the wall and not between the ray and the normal to the wall.
     * Basicly thetai = pi/2 - thetai.
     * Because of that cos and sin are inverted and we take their absolute value because of the angles given by Qt.
     */

    double R = (abs(sin(thetaI)) - sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(cos(thetaI),2)))/(abs(sin(thetaI)) + sqrt(epsilonR)*sqrt(1 - (1/epsilonR)*pow(cos(thetaI),2)));
    return R;
}

complex <double> MathematicalTransmitterProduct::computeEMfield(vector<MathematicalRayProduct> *rayLine){
    /* One vector<ray*> is one multi-path componant, the size of the vector determine the n-level we are in, for each ray only the power in the last ray is transmitted to
     * the receptor. As seen in the power formula, n rays -> n-1 additions to the power.
     *
     * This function gives the electrical field, generated by one MPC, at the receiver. The electric field is // to the dipole antenna since we only consider relections
     * off the buildings. The electric field is not // for the reflexion with the ground though. This is taken into account in the function computePrx.
     */

    complex <double> i(0.0, 1.0);
    int amountSegment = rayLine->size();
    double completeLength = 0.0;
    double theta = 0.0;
    double R = 1;
    complex <double> Efield = 0.0;
    MathematicalRayProduct currentRay;
    for (int i=0; i<amountSegment; i++){
        currentRay = rayLine->at(i);
        theta = currentRay.getTheta();
        if((i != amountSegment-1)){   // The last segment, the one that reach the receptor does not have a rebound
            double thetaI = abs(currentRay.getTetai());
            R *= computeReflexionPer(thetaI,epsilonWallRel);
        }
        completeLength += currentRay.getMeterLength(); // Get each length of each ray segment after the meter conversion (1px == 1dm)
    }
    double Ia = sqrt(2.0*m_power/Ra); // Ia could be changed for Beamforming application (add exp)
    double a = R * ((Zvoid*Ia)/(2.0*M_PI))/completeLength;
    Efield = i * a * exp(-i*(2.0*M_PI/lambda)*completeLength);

    /*
     * This part needs to be reviewed for the new architecture
     *
    if(amountSegment==1){
        this->minLength = completeLength; // for delay spread computation
        this->LOS = pow(a,2);
    } else{
        this->NLOS += pow(a,2);
    }
    if(completeLength > this->maxLength){
        this->maxLength = completeLength; // for delay spread computation
    }
    // Store ray parameter for Physical impulse response
    if(computePhysicalResponse){
        // Store attenuation a and distance completeLength
        channelData[rayNumber] = R/completeLength;
        channelData[rayNumber+20] = completeLength;
        double degangle = round((theta+direction)*180/M_PI);
        double radangle = degangle*M_PI/180;
        spectrumField[specNumber] = Efield;
        spectrumAngle[specNumber] = (2.0*M_PI/lambda)*speedReal*cos(radangle);
        int save = specNumber;
        for (int j = 0; j < save; j++){
            if (spectrumAngle[j] == spectrumAngle[save]){
                spectrumField[j] += Efield;
                specNumber -= 1;
            }
        }
        specNumber += 1;
        rayNumber += 1;
    }*/
    return Efield;
}

vector<vector<MathematicalRayProduct> *> MathematicalTransmitterProduct::getRays(){
    return m_wholeRays;
    }

void MathematicalTransmitterProduct::setRayFactory(AbstractRayFactory *rayFactory){
    m_rayFactory = rayFactory;
}

void MathematicalTransmitterProduct::attachObservable(ModelObservable *modelObservable){
    m_model = modelObservable;
}

int MathematicalTransmitterProduct::getPosX(){return x();}
int MathematicalTransmitterProduct::getPosY(){return y();}
