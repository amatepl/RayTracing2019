#ifndef TRANSMITTERPRODUCT_H
#define TRANSMITTERPRODUCT_H

class TransmitterProduct{
public:
    enum Model{dipole,array};
    virtual ~TransmitterProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;
    virtual double getOrientation() = 0;
    virtual unsigned long getFrequency()= 0;
    virtual double getPower() = 0;
    virtual int getRow()=0;
    virtual int getColumn()=0;
    virtual double getAntennaDistance()=0;
    virtual int getModel()=0;

    virtual void setPosX(int posX) = 0;
    virtual void setPosY(int posY) = 0;
    virtual void setOrientation(double orientation) = 0;
    virtual void setPower(double power) = 0;
    virtual void setFrequency(unsigned long frequency) = 0;
    virtual void setRow(int row) = 0;
    virtual void setColumn(int column) = 0;
    virtual void setAntennaDistance(double distance)=0;
    virtual void setModel(Model model)=0;
};

#endif // TRANSMITTERPRODUCT_H
