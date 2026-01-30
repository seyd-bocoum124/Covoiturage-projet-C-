#ifndef POINTST_H
#define POINTST_H

class PointST {
public:
    PointST();
    PointST(double lat, double lon);

    double distance(const PointST& other) const;

private:
    double latitude;
    double longitude;
};

#endif