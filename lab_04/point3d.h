#ifndef POINT3D_H
#define POINT3D_H

#include <cmath>
#include <vector>

class Point3D
{
public:
    Point3D();
    Point3D(double x);
    Point3D(double x, double y, double z);

    void offset(double dx, double dy, double dz);
    void scale(const Point3D& center, double k);
    void rotateX(const Point3D& center, double angle);
    void rotateY(const Point3D& center, double angle);
    void rotateZ(const Point3D& center, double angle);

    double getX() const;
    double getY() const;
    double getZ() const;

private:
    double scaleOne(double coord, double center, double k);

    double x;
    double y;
    double z;
};

#endif // POINT3D_H
