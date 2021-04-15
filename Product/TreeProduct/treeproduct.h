#ifndef TREEPRODUCT_H
#define TREEPRODUCT_H


class TreeProduct
{
public:
    virtual ~TreeProduct() {}

    virtual int getPosX() = 0;
    virtual int getPosY() = 0;

    virtual void setPosX(int) = 0;
    virtual void setPosY(int) = 0;

    virtual void newProperties() = 0;
};

#endif // TREEPRODUCT_H
