#include "Drawer3D.h"
#include "math.h"
#include "vecmat.h"
#include <iostream>


Drawer3D::Drawer3D(wxPanel* WxPanel)  {
    this->WxPanel = WxPanel;
    initializeVectors();
}
Drawer3D::Drawer3D(const Drawer3D& orig) {
}

Drawer3D::~Drawer3D() {
//    deleteVectors();
}

void Drawer3D::initializeVectors() {
    rotAngleV = new Vector4();
    rotAngleRAW = new Vector4();
    rotationMatrixComplete = new Matrix4();
    rotationMatrixX = new Matrix4();
    rotationMatrixY = new Matrix4();
    rotationMatrixZ = new Matrix4();
}

void Drawer3D::deleteVectors() {
    delete rotAngleV;
    delete rotationMatrixComplete;
    delete rotationMatrixX;
    delete rotationMatrixY;
    delete rotationMatrixZ;
}

Matrix4 Drawer3D::getRotationMatrix(Vector4 *rotAngle) {
    rotationMatrixX->data[0][0] = 1;
    rotationMatrixX->data[1][1] = cos(rotAngle->GetX());
    rotationMatrixX->data[1][2] = -sin(rotAngle->GetX());
    rotationMatrixX->data[2][1] = sin(rotAngle->GetX());
    rotationMatrixX->data[2][2] = cos(rotAngle->GetX());

    rotationMatrixY->data[0][0] = cos(rotAngle->GetY());
    rotationMatrixY->data[0][2] = sin(rotAngle->GetY());
    rotationMatrixY->data[1][1] = 1;
    rotationMatrixY->data[2][0] = -sin(rotAngle->GetY());
    rotationMatrixY->data[2][2] = cos(rotAngle->GetY());

    rotationMatrixZ->data[0][0] = cos(rotAngle->GetZ()); 
    rotationMatrixZ->data[0][1] = -sin(rotAngle->GetZ());
    rotationMatrixZ->data[1][0] = sin(rotAngle->GetZ());
    rotationMatrixZ->data[1][1] = cos(rotAngle->GetZ());
    rotationMatrixZ->data[2][2] = 1;

    *rotationMatrixComplete = (*rotationMatrixX) * (*rotationMatrixY) * (*rotationMatrixZ);
    return *rotationMatrixComplete;

}


void Drawer3D::setPerspective(Vector4 *point3D, double d) {
    point3D->Set(point3D->GetX() / (1 + point3D->GetZ() / d), point3D->GetY() / (1 + point3D->GetZ() / d), point3D->GetZ());
}

void Drawer3D::Repaint() {
    int w, h, w2, h2;
    double d = 8;
    wxClientDC dcOld(WxPanel);
    wxBufferedDC dc(&dcOld);
    Matrix4 finalTransformationMatrix;
    Vector4 startVect, endVect;
    WxPanel->GetSize(&w, &h);
    dc.Clear();
    dc.SetDeviceOrigin(w / 2, h / 2);
    rotAngleV->Set((M_PI * rotAngleRAW->GetX()) / 180.0, (M_PI * rotAngleRAW->GetY()) / 180.0, (M_PI * rotAngleRAW->GetZ()) / -180.0);
    finalTransformationMatrix =  getRotationMatrix(rotAngleV);

    int x_start_size = x_start.size();

    for (int i = 0; i < x_start_size; ++i) {
        startVect.Set(x_start[i], y_start[i], -z_start[i]);
        endVect.Set(x_end[i], y_end[i], -z_end[i]);
        startVect = finalTransformationMatrix * startVect;
        endVect = finalTransformationMatrix * endVect;
        if (startVect.GetZ() > -d && endVect.GetZ() > -d) {
            setPerspective(&startVect, d);
            setPerspective(&endVect, d);
            dc.SetPen(wxPen(wxColour(R.at(i), G.at(i), B.at(i))));
            startVect.Set(startVect.GetX() * w / 2, startVect.GetY() * h / 2, startVect.GetZ());
            endVect.Set(endVect.GetX() * w / 2, endVect.GetY() * h / 2, endVect.GetY());
            dc.DrawLine(startVect.GetX(), -startVect.GetY(), endVect.GetX(), -endVect.GetY());
        }
    }
   

}
void Drawer3D::AddVector(Vector4 &startVect, Vector4 &endVect, Vector4 &colorVect) {
    x_start.push_back(startVect.GetX());
    y_start.push_back(startVect.GetY());
    z_start.push_back(startVect.GetZ());
    x_end.push_back(endVect.GetX());
    y_end.push_back(endVect.GetY());
    z_end.push_back(endVect.GetZ());
    R.push_back(colorVect.GetX());
    G.push_back(colorVect.GetY());
    B.push_back(colorVect.GetZ());
}
 void Drawer3D::Clear() {
    x_start.clear();
    y_start.clear();
    z_start.clear();
    x_end.clear();
    y_end.clear();
    z_end.clear();
    R.clear();
    G.clear();
    B.clear();
 }
 
 void Drawer3D::UpdateRotation(Vector4 &rotateVector) {
     //rotAngleRAW->Set(rotateVector.GetX(), rotateVector.GetY(), rotateVector.GetZ());
     *rotAngleRAW = rotateVector;
 }


