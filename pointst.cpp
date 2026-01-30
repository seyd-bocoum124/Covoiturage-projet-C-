#include "pointst.h"
#include <cmath>

static const double R = 6371000.0;

PointST::PointST() : latitude(0), longitude(0) {}

PointST::PointST(double lat, double lon)
{
    latitude  = lat * M_PI / 180.0;
    longitude = lon * M_PI / 180.0;
}

double PointST::distance(const PointST& o) const
{
    double dlat = o.latitude - latitude;
    double dlon = o.longitude - longitude;

    double a = sin(dlat/2)*sin(dlat/2)
             + cos(latitude)*cos(o.latitude)
             * sin(dlon/2)*sin(dlon/2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}