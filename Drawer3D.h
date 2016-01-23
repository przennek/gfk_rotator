#ifndef DRAWER3D_H
#define DRAWER3D_H
#include <wx/panel.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wx/dcbuffer.h>
class Vector4;
class Matrix4;
/**
 *  This class generate 3D view of calculated vectors 
 */
class Drawer3D {
public:
    /**
    * Default constructor
    */
    Drawer3D(){}
    /**
    * Constructor that takes wxPanel context for draw on it
    */
    Drawer3D(wxPanel* WxPanel);
    /**
    * A copy constructor 
    */
    Drawer3D(const Drawer3D& orig);
    /**
    * Virtual destructor 
    */
    virtual ~Drawer3D();
    /**
    * Method which redraw all vectors
    */
    void Repaint();
    /**
    * Update rotation vector
    * @param rotateVector new rotation vector 
    */
    void UpdateRotation(Vector4 &rotateVector);
    /**
    * Add new vector to collection of vectors to draw 
    * @param startVect coordinates of start point
    * @param endVect coordinates of end point   
    * @param colorVect RGB color of vector   
    */
    void AddVector(Vector4 &startVect, Vector4 &endVect, Vector4 &colorVect);
    /**
    * Method which clean collection of vectors to draw
    */
    void Clear();
private:
    void initializeVectors();
    void deleteVectors();
    Matrix4 getRotationMatrix(Vector4 *rotAngle);
    void setPerspective(Vector4 *point3D, double d);
    
    wxPanel *WxPanel;
    Vector4 *rotAngleV, *rotAngleRAW;
    Matrix4 *rotationMatrixComplete,  *rotationMatrixX, *rotationMatrixY, *rotationMatrixZ;
    std::vector <double> x_start, x_end, y_start, y_end, z_start, z_end;
    std::vector <int> R, G, B; 
    double d = -2.0;

};

#endif /* DRAWER3D_H */

