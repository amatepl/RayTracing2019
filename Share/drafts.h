#ifndef DRAFTS_H
#define DRAFTS_H

//--------------------------------------------------------------------------------------------
//
//          Includes
//
//--------------------------------------------------------------------------------------------

/* General Includes */

#include <complex>
#include <vector>
#include <QLineF>

/* Project Specific */

#include "Product/TreeProduct/mathematicaltreeproduct.h"
#include "Product/RayProduct/mathematicalrayproduct.h"
#include "Share/wholeray.h"

//--------------------------------------------------------------------------------------------
//
//          Defines
//
//--------------------------------------------------------------------------------------------

using namespace std;

//--------------------------------------------------------------------------------------------
//
//          Global Variables
//
//--------------------------------------------------------------------------------------------

double lambda;
double m_power;
double Zvoid;
double Ra;
vector<WholeRay *> m_wholeRays;
QPointF m_pos;

//--------------------------------------------------------------------------------------------
//
//          Methods
//
//--------------------------------------------------------------------------------------------

complex<double> computeDiffractedTreeEfield(vector<QLineF> rayLine)
{

    // Direct distance between the receiver and the transmitter

    double direct_dist = sqrt(pow(rayLine.at(1).p1().x() - rayLine.at(0).p2().x(), 2)
                              + pow(rayLine.at(1).p1().y() - rayLine.at(0).p2().y(), 2)); //convertir px to cm?

    complex<double> Efield = 0.0;
    complex<double> F = 0.0;
    complex <double> i(0.0, 1.0);

    // The length defference between the path going through the tip of the obstacle, and the direct path.

    double delta_r = (rayLine.at(0).length() + rayLine.at(1).length() - direct_dist) * pow(10, -1.0);

    double nu = sqrt(2 * 2 * M_PI / lambda * delta_r / M_PI);
    // The ITU's approximation for |F(nu)|^2

    double absF = pow(10, -6.9 / 40) / sqrt((sqrt(pow(nu - 0.1, 2) + 1) + nu - 0.1));
    double argF = -M_PI / 4 - pow(nu, 2) * M_PI / 2;
    F = absF * exp(i * argF);

    Line *directRay = new Line(rayLine.at(0).p2(), rayLine.at(1).p1());

    double Ia = sqrt(2 * m_power / Ra); // Ia could be changed for Beamforming application (add exp)
    Efield = -i  * ((Zvoid * Ia) / (2 * M_PI)) *
             (exp(-i * (2.0 * M_PI / lambda) * directRay->getMeterLength()) / directRay->getMeterLength());
    Efield = F * Efield;
    delete directRay;
    return Efield;
}


vector<vector<QLineF>> buildTreeRays(QPointF *Rx, MathematicalTreeProduct *tree)
{

    //
    //  Construct the diffracted rays around the tree
    //
    //  Rx: receivers position
    //

    float radius = tree->getRadius();
    QPointF treeCenter;
    treeCenter.setX(tree->getPosX());
    treeCenter.setY(tree->getPosY());

    // The direct path is used in order to build a tree square model perpendicualr to the path
    QLineF directPath(m_pos, *Rx);
    directPath.setAngle(directPath.angle() + 90);
    directPath.translate(treeCenter - m_pos);
    directPath.setLength(radius);

    directPath.setAngle(directPath.angle() + 45);
    QPointF treeCorner1 = directPath.p2();

    directPath.setAngle(directPath.angle() + 90);
    QPointF treeCorner2 = directPath.p2();

    directPath.setAngle(directPath.angle() + 90);
    QPointF treeCorner3 = directPath.p2();

    directPath.setAngle(directPath.angle() + 90);
    QPointF treeCorner4 = directPath.p2();

    QLineF distance1;
    QLineF distance2;

    distance1.setPoints(m_pos, treeCorner1);
    distance2.setPoints(m_pos, treeCorner4);

    vector<vector<QLineF>> wholeRays;
    vector<QLineF> wholeRay1;
    vector<QLineF> wholeRay2;
    vector<QLineF> wholeRay3;

    if (distance1.length() < distance2.length()) {


        //          Rx
        //
        //      4 ----- 3
        //      |       |
        //      |       |
        //      1 ----- 2
        //
        //          Tx


        wholeRay1.push_back(distance1);
        wholeRay1.push_back(QLineF(treeCorner1, treeCorner4));
        wholeRay1.push_back(QLineF(treeCorner4, *Rx));

        wholeRays.push_back(wholeRay1);

        wholeRay2.push_back(QLineF(m_pos, treeCorner2));
        wholeRay2.push_back(QLineF(treeCorner2, treeCorner3));
        wholeRay2.push_back(QLineF(treeCorner3, *Rx));

        wholeRays.push_back(wholeRay2);

        // Top ray

        QPointF edge1;
        directPath.setPoints(m_pos, *Rx);
        directPath.intersects(distance1, &edge1);

        QPointF edge2;
        directPath.intersects(distance2, &edge2);

        QLineF firstDiffractedRay(m_pos, edge1);
        QLineF lastDiffractedRay(m_pos, edge2);

        // Correct the lenght of the first and last diffractrd rays
        wholeRay3.push_back(firstDiffractedRay);
        wholeRay3.push_back(QLineF(edge1, edge2));
        wholeRay3.push_back(lastDiffractedRay);

    } else {


        //         Rx
        //
        //     2 ----- 1
        //     |       |
        //     |       |
        //     3 ----- 4
        //
        //         Tx


        wholeRay1.push_back(QLineF(distance2));
        wholeRay1.push_back(QLineF(treeCorner4, treeCorner1));
        wholeRay1.push_back(QLineF(treeCorner1, *Rx));

        wholeRays.push_back(wholeRay1);

        wholeRay2.push_back(QLineF(m_pos, treeCorner3));
        wholeRay2.push_back(QLineF(treeCorner3, treeCorner2));
        wholeRay2.push_back(QLineF(treeCorner2, *Rx));

        wholeRays.push_back(wholeRay2);

        // Top ray

        QPointF edge1;
        directPath.setPoints(m_pos, *Rx);
        directPath.intersects(distance2, &edge1);

        QPointF edge2;
        directPath.intersects(distance1, &edge2);

        QLineF firstDiffractedRay(m_pos, edge2);
        QLineF lastDiffractedRay(m_pos, edge1);

        // Correct the lenght of the first and last diffractrd rays
        wholeRay3.push_back(firstDiffractedRay);
        wholeRay3.push_back(QLineF(edge2, edge1));
        wholeRay3.push_back(lastDiffractedRay);
    }
    return wholeRays;
}


void computeRayThroughTree(QPointF *Rx, MathematicalTreeProduct *tree)
{
    vector<vector<QLineF>> wholeRays = buildTreeRays(Rx, tree);
    for (unsigned int i = 0; i < m_wholeRays.size(); i++) {
        //        complex<double> EfieldTree = computeDiffractedTreeEfield(wholeRays.at(i));
    }
}

QPointF sceneRectIntersection(const QRectF &rect, const QLineF &line)
{

    //  This function takes a bounding ray (line) of the illumination zone and gives its intersection
    //  with the scene boundaries.
    //

    QLineF boundary1(rect.topLeft(), rect.bottomLeft()),
           boundary2(rect.bottomLeft(), rect.bottomRight()),
           boundary3(rect.bottomRight(), rect.topRight()),
           boundary4(rect.topRight(), rect.topLeft());

    QPointF intersectionPoint;

    if (line.intersects(boundary1, &intersectionPoint) == 1) {}
    else if (line.intersects(boundary2, &intersectionPoint) == 1) {}
    else if (line.intersects(boundary3, &intersectionPoint) == 1) {}
    else if (line.intersects(boundary4, &intersectionPoint) == 1) {}
    return intersectionPoint;
}

double computeElevationScaterringAngle(float heightRx,
                                       float heightTx,
                                       float heightConopy,
                                       float distanceRxTree)
{
    // ???????
    return M_PI / 2 - atan2(heightRx - (heightTx + heightConopy / 2), distanceRxTree);
}


map<string, double> computeIncidenceDepartureAngles(float angleIncidenceConopy,
                                                    float angleAzimuth,
                                                    float angleElevation)
{
    // ????????????
    map<string, double> anglesScttering;
    anglesScttering["incidenceElevation"] = acos(cos(angleElevation) * cos(angleIncidenceConopy)
                                                 - sin(angleElevation) * cos(angleAzimuth));
    return  anglesScttering;
}

#endif // DRAFTS_H
