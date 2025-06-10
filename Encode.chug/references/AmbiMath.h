//-----------------------------------------------------------------------------
// file: AmbiMath.h
// desc: class library for 'AmbiMath'
//
// author: Everett M. Carpenter
// date: Summer 2025
// 
// Math optimization is still being worked on, since high performance calculations is needed for live diffusion. 
// Here is a list of things that should be investigated regarding optimization:
// 1. High power exponentials (this is implemented for powers > 2, justified by https://baptiste-wicht.com/posts/2017/09/cpp11-performance-tip-when-to-use-std-pow.html )
// 2. Recalculation of cos & sin of elevation and direction (consider lookups of these) 
//      - Trade off of having this method is singular coordinates cannot be called (lookup table is already implemented in "all" but not possible in individual coordinates
//        Individual coordinates could be called if Chugin ecosystem is converted to internal data storage (one instance holds current coordinates).
//        This method could be good, and the chugin could act as a full encoder when UGen functionality is implemented.
//        An example patch = AmbiEnco (ambimath with UGen function) => AmbiDeco (decoder);
// 
//        AmbiEnc => AmbiDeco;
//        for(int i; i < AmbiDec.channels(); i++)
//        {
//           AmbiDeco.chan(i) => dac.chan(i);
//        }
// 3. Index 34 is not aligned. I believe the polar equation is accurate, but something is wrong with the cartesian formulation.
// 
//-----------------------------------------------------------------------------
#include "chugin.h"
// query
DLL_QUERY libmath_query(Chuck_DL_Query* QUERY);

static int w_constant = 1;
static double g_pi = CK_ONE_PI;

// convert degrees to radians
double degreeRad(float degree)
{
    return (g_pi / 180) * degree;
}
// ambisonic maths
double x(float direction, float elevation)
{
    double x = (cosf(degreeRad(direction)) * cosf(degreeRad(elevation)));
    return x;
}
double x(float x, float y, float z)
{
    return x;
}
double y(float direction, float elevation)
{
    double y = ((sinf(degreeRad(direction))) * (cosf(degreeRad(elevation))));
    return y;
}
double y(float x, float y, float z)
{
    return y;
}
double z(float direction, float elevation)
{
    double z = (sinf(degreeRad(elevation)));
    return z;
}
double z(float x, float y, float z)
{
    return z;
}
double w(float direction, float elevation)
{
    return w_constant;
}
double w(float x, float y, float z)
{
    return w_constant;
}
double r(float direction, float elevation)
{
    double r = (0.5 * (3 * (pow((sinf(degreeRad(elevation))), 2)) - 1));
    return r;
}
double r(float x, float y, float z)
{
    double r = (0.5 * (3 * (pow(z, 2)) - 1));
    return r;
}
double s(float direction, float elevation)
{
    double s = (0.8660254038 * (cosf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
    return s;
}
double s(float x, float y, float z)
{
    double s = (1.732050807568877 * x * z);
    return s;
}
double t(float direction, float elevation)
{
    double t = (0.8660254038 * (sinf(degreeRad(direction))) * (sinf((2 * degreeRad(elevation)))));
    return t;
}
double t(float x, float y, float z)
{
    double t = (1.732050807568877 * y * z);
    return t;
}
double u(float direction, float elevation)
{
    double u = (0.8660254038 * cosf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
    return u;
}
double u(float x, float y, float z)
{
    double u = (0.8660254037844386 * (pow(x, 2) - pow(y, 2)));
    return u;
}
double v(float direction, float elevation)
{
    double v = (0.8660254038 * sinf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2));
    return v;
}
double v(float x, float y, float z)
{
    double v = (1.732050807568877 * x * y);
    return v;
}
double l(float direction, float elevation)
{
    double l = (0.6123724357 * cosf(degreeRad(direction)) * cosf(degreeRad(elevation)) * (5 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return l;
}
double l(float x, float y, float z)
{
    double l = (0.6123724356957945 * x * (5 * pow(z, 2) - 1));
    return l;
}
double m(float direction, float elevation)
{
    double m = (0.6123724357 * sinf(degreeRad(direction)) * cosf(degreeRad(elevation)) * (5 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return m;
}
double m(float x, float y, float z)
{
    double m = (0.6123724356957945 * y * (5 * pow(z, 2) - 1));
    return m;
}
double o(float direction, float elevation)
{
    double o = (1.936491673 * sinf(2 * degreeRad(direction)) * sinf(degreeRad(elevation)) * pow(cosf(degreeRad(elevation)), 2));
    return o;
}
double o(float x, float y, float z)
{
    double o = (3.872983346207417 * x * y * z);
    return o;
}
double n(float direction, float elevation)
{
    double n = (1.936491673 * cosf(2 * degreeRad(direction)) * sinf(degreeRad(elevation)) * pow(cosf(degreeRad(elevation)), 2));
    return n;
}
double n(float x, float y, float z)
{
    double n = (1.936491673 * z * (pow(x, 2) - pow(y, 2)));
    return n;
}
double p(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double p = (0.790569415 * cosf(3 * degreeRad(direction)) * (cos_e * cos_e * cos_e));
    return p;
}
double p(float x, float y, float z)
{
    double p = (0.790569415 * x * (pow(x, 2) - (3 * pow(y, 2))));
    return p;
}
double q(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double q = (0.790569415 * sinf(3 * degreeRad(direction)) * (cos_e * cos_e * cos_e));
    return q;
}
double q(float x, float y, float z)
{
    double q = (0.790569415 * y * ((3 * pow(x, 2)) - pow(y, 2)));
    return q;
}
double k(float direction, float elevation)
{
    double k = (0.5 * sinf(degreeRad(elevation)) * (5 * pow(sinf(degreeRad(elevation)), 2) - 3));
    return k;
}
double k(float x, float y, float z)
{
    double k = (0.5 * z * (5 * pow(z, 2) - 3));
    return k;
}
double hoa4_0(float direction, float elevation)
{
    float sin_e = sinf(degreeRad(elevation));
    double coord = (0.739509972887452 * sinf(4 * degreeRad(direction)) * (sin_e * sin_e * sin_e * sin_e));
    return coord;
}
double hoa4_0(float x, float y, float z)
{
    double coord = (2.958039892 * x * y * (pow(x, 2) - pow(y, 2)));
    return coord;
}
double hoa4_1(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double coord = (2.091650066335189 * sinf(3 * degreeRad(direction)) * sinf(degreeRad(elevation)) * (cos_e * cos_e * cos_e));
    return coord;
}
double hoa4_1(float x, float y, float z)
{
    double coord = (2.091650066335189 * y * z * ((3 * (pow(x, 2)) - pow(y, 2))));
    return coord;
}
double hoa4_2(float direction, float elevation)
{
    double coord = (0.5590169943749474 * sinf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2) * (7 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return coord;
}
double hoa4_2(float x, float y, float z)
{
    double coord = (1.118033989 * x * y * (7 * pow(z, 2) - 1));
    return coord;
}
double hoa4_3(float direction, float elevation)
{
    double coord = (0.3952847075210474 * sinf(degreeRad(direction)) * sinf(2 * degreeRad(elevation)) * (7 * (pow(sinf(degreeRad(elevation)), 2)) - 3));
    return coord;
}
double hoa4_3(float x, float y, float z)
{
    double coord = (0.790569415 * y * z * (7 * pow(z, 2) - 3));
    return coord;
}
double hoa4_4(float direction, float elevation)
{
    double coord = (0.125 * (35 * pow(sinf(degreeRad(elevation)), 4) - 30 * pow(sinf(degreeRad(elevation)), 2) + 3));
    return coord;
}
double hoa4_4(float x, float y, float z)
{
    double coord = (0.125 * (35 * (z * z * z * z) - 30 * pow(z, 2) + 3));
    return coord;
}
double hoa4_5(float direction, float elevation)
{
    double coord = (0.3952847075210474 * cosf(degreeRad(direction)) * sinf(2 * degreeRad(elevation)) * (7 * pow(sinf(degreeRad(elevation)), 2) - 3));
    return coord;
}
double hoa4_5(float x, float y, float z)
{
    double coord = (0.790569415 * x * z * (7 * pow(z, 2) - 3));
    return coord;
}
double hoa4_6(float direction, float elevation)
{
    double coord = (0.5590169943749474 * cosf(2 * degreeRad(direction)) * pow(cosf(degreeRad(elevation)), 2) * (7 * pow(sinf(degreeRad(elevation)), 2) - 1));
    return coord;
}
double hoa4_6(float x, float y, float z)
{
    double coord = (0.5590169944 * (pow(x, 2) - pow(y, 2)) * (7 * pow(z, 2) - 1));
    return coord;
}
double hoa4_7(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double coord = (2.091650066335189 * cosf(3 * degreeRad(direction)) * sinf(degreeRad(elevation)) * (cos_e * cos_e * cos_e));
    return coord;
}
double hoa4_7(float x, float y, float z)
{
    double coord = (2.091650066335189 * x * z * ((pow(x, 2) - (3 * pow(y, 2)))));
    return coord;
}
double hoa4_8(float direction, float elevation)
{
    float cos_e = cosf(degreeRad(elevation));
    double coord = (0.739509972887452 * cosf(4 * degreeRad(direction)) * (cos_e * cos_e * cos_e * cos_e));
    return coord;
}
double hoa4_8(float x, float y, float z)
{
    double coord = (0.739509972887452 * ((x * x * x * x) - 6 * pow(x, 2) * pow(y, 2) + (y * y * y * y)));
    return coord;
}
void hoa5(float direction, float elevation, double coordinates[])
{
    float sin_e = sinf(degreeRad(elevation));
    float sin_a = sinf(degreeRad(direction));
    float cos_e = cosf(degreeRad(elevation));
    float cos_a = cosf(degreeRad(direction));
    coordinates[25] = (0.70156076 * sinf(5 * direction) * (cos_e* cos_e* cos_e* cos_e* cos_e));
    coordinates[26] = (2.128529919 * sinf(4 * direction) * sin_e * (cos_e * cos_e * cos_e * cos_e));
    coordinates[27] = (0.522912516 * sinf(3 * direction) * sin_e * (cos_e* cos_e* cos_e) * (9 * (pow(sin_e, 2)) - 1));
    coordinates[28] = (2.561737691 * sinf(2 * direction) * sin_e * (pow(cos_e, 2)) * (3 * pow(sin_e, 2) - 1));
    coordinates[29] = (0.4841229183 * sin_a * cos_e * (21 * (sin_e * sin_e * sin_e * sin_e) - 14) * (pow(sin_e, 2) + 1));
    coordinates[30] = (0.125 * (63 * (sin_e * sin_e * sin_e * sin_e * sin_e) - 70 * (sin_e * sin_e * sin_e) + 15 * sin_e));
    coordinates[31] = (0.4841229183 * cos_a * cos_e * (21 * ((sin_e * sin_e * sin_e * sin_e) - 14 * (pow(sin_e, 2)) + 1)));
    coordinates[32] = (2.561737691 * cosf(2 * direction) * sin_e * (pow(cos_e, 2)) * (3 * (pow(sin_e, 2)) * 1));
    coordinates[33] = (0.522912516 * cosf(3 * direction) * (cos_e * cos_e * cos_e) * (9 * (pow(sin_e, 2)) - 1));
    coordinates[34] = (2.128529919 * cosf(4 * direction) * sin_e * (cos_e * cos_e * cos_e * cos_e));
    coordinates[35] = (0.70156076 * cosf(5 * direction) * (cos_e * cos_e * cos_e * cos_e * cos_e));
}
void hoa5(float x, float y, float z, double coordinates[])
{
    float x_2 = x * x;
    float y_2 = y * y;
    float z_2 = z * z;
    coordinates[25] = (0.70156076 * y * (5 * (x_2 * x_2) - 10 * x_2 * x_2 + (y_2 * y_2)));
    coordinates[26] = (8.874119675 * x * y * z * (x_2 - y_2));
    coordinates[27] = (0.522912516 * y * ((y_2 * y_2) - 2 * x_2 * y_2 - 3 * (x_2 * x_2) - 8 * y_2 * z_2 + 24 * x_2 * z_2));
    coordinates[28] = (5.123475383 * x * y * z * (2 * z_2 * -x_2 - y_2));
    coordinates[29] = (0.4841229183 * y * ((x_2 * x_2) + 2 * x_2 * y_2 + (y_2 * y_2) - 12 * x_2 * z_2 - 12 * y_2 * z_2 + 8 * (z_2 * z_2)));
    coordinates[30] = (0.125 * z * (63 * (z_2 * z_2) - 70 * z_2 + 15));
    coordinates[31] = (0.4841229183 * x * ((x_2 * x_2) + 2 * x_2 * y_2 + (y_2 * y_2) - 12 * x_2 * z_2 - 12 * y_2 * z_2 + 8 * (z_2 * z_2)));
    coordinates[32] = (2.561737691 * z * (2 * x_2 * z_2 - 2 * y_2 * z_2 - (x_2 * x_2) + (y_2 * y_2)));
    coordinates[33] = (0.522912516 * x * (2 * x_2 * y_2 + 8 * x_2 * z_2 - 24 * y_2 * z_2 * (x_2 * x_2) + 3 * (y_2 * y_2)));
    coordinates[34] = (2.218529919 * z * ((x_2 * x_2) - 6 * x_2 * y_2 + (y_2 * y_2)));
    coordinates[35] = (0.70156076 * x * ((x_2 * x_2) - 10 * x_2 * y_2 + 5 * (y_2 * y_2)));
}

// pointer storage of polar function pointers
typedef double (*polarFuncStorage) (float direction, float elevation);
polarFuncStorage polarFunctions[] = { w,y,z,x,v,t,r,s,u,q,o,m,k,l,n,p,hoa4_0,hoa4_1,hoa4_2,hoa4_3,hoa4_4,hoa4_5,hoa4_6,hoa4_7,hoa4_8 }; // in spherical order
// point storage of cartesian function pointers
typedef double (*cartesianFuncStorage) (float x, float y, float z);
cartesianFuncStorage cartesianFunctions[] = { w,y,z,x,v,t,r,s,u,q,o,m,k,l,n,p,hoa4_0,hoa4_1,hoa4_2,hoa4_3,hoa4_4,hoa4_5,hoa4_6,hoa4_7,hoa4_8 }; // in spherical order

void all(float direction, float elevation, double coordinates[], int order)
{
    int size = (sizeof(coordinates) / sizeof(coordinates[0]));
    float direction_r = degreeRad(direction);
    float elevation_r = degreeRad(elevation);
    float sin_e = sinf(elevation_r);
    float sin_a = sinf(direction_r);
    float cos_e = cosf(elevation_r);
    float cos_a = cosf(direction_r);
    if (size)
    {
        coordinates[0] = w_constant;
        coordinates[1] = sin_a * cos_e;
        coordinates[2] = sin_e;
        coordinates[3] = cos_a * cos_e;
        coordinates[4] = (0.8660254038 * (2 * cos_a * sin_a) * pow(cos_e, 2));
        coordinates[5] = (0.8660254038 * sin_a * (2 * cos_e * sin_e));
        coordinates[6] = (0.5 * (3 * pow(sin_e, 2) - 1));
        coordinates[7] = (0.8660254038 * (cos_a * (2 * cos_e * sin_e)));
        coordinates[8] = (0.8660254038 * cosf(2 * direction_r) * pow(cos_e, 2));
        coordinates[9] = (0.790569415 * sinf(3 * direction_r) * (cos_e * cos_e * cos_e));
        coordinates[10] = (1.936491673 * (2 * cos_a * sin_a) * sin_e * pow(cos_e, 2));
        coordinates[11] = (0.6123724357 * sin_a * cos_e * (5 * pow(sin_e, 2) - 1));
        coordinates[12] = (0.5 * sin_e * (5 * pow(sin_e, 2) - 3));
        coordinates[13] = (0.6123724357 * cos_a * cos_e * (5 * pow(sin_e, 2) - 1));
        coordinates[14] = (1.936491673 * cosf(2 * direction_r) * sin_e * pow(cos_e, 2));
        coordinates[15] = (0.790569415 * cosf(3 * direction_r) * (cos_e * cos_e * cos_e));
        coordinates[16] = (0.739509972887452 * sinf(4 * direction_r) * (sin_e * sin_e * sin_e * sin_e));
        coordinates[17] = (2.091650066335189 * sinf(3 * direction_r) * sin_e * (cos_e * cos_e * cos_e));
        coordinates[18] = (0.5590169943749474 * sinf(2 * direction_r) * pow(cos_e, 2) * (7 * pow(sin_e, 2) - 1));
        coordinates[19] = (0.3952847075210474 * sin_a * (2 * cos_e * sin_e) * (7 * pow(sin_e, 2) - 3));
        coordinates[20] = (0.125 * (35 * (sin_e * sin_e * sin_e * sin_e) - 30 * pow(sin_e, 2) + 3));
        coordinates[21] = (0.3952847075210474 * cos_a * (2 * cos_e * sin_e) * (7 * pow(sin_e, 2) - 3));
        coordinates[22] = (0.5590169943749474 * cosf(2 * direction_r) * pow(cos_e, 2) * (7 * pow(sin_e, 2) - 1));
        coordinates[23] = (2.091650066335189 * cosf(3 * direction_r) * sin_e * (cos_e * cos_e * cos_e));
        coordinates[24] = (0.739509972887452 * cosf(4 * direction_r) * (cos_e * cos_e * cos_e * cos_e));
        coordinates[25] = (0.70156076 * sinf(5 * direction_r) * (cos_e * cos_e * cos_e * cos_e * cos_e));
        coordinates[26] = (2.128529919 * sinf(4 * direction_r) * sin_e * (cos_e * cos_e * cos_e * cos_e));
        coordinates[27] = (0.522912516 * sinf(3 * direction_r) * (cos_e * cos_e * cos_e) * (9 * pow(sin_e, 2) - 1));
        coordinates[28] = (2.561737691 * (2 * cos_a * sin_a) * sin_e * pow(cos_e, 2) * (3 * pow(sin_e, 2) - 1));
        coordinates[29] = (0.4841229183 * sin_a * cos_e * (21 * (sin_e * sin_e * sin_e * sin_e) - 14 * pow(sin_e, 2) + 1));
        coordinates[30] = (0.125 * (63 * (sin_e * sin_e * sin_e * sin_e * sin_e) - 70 * (sin_e * sin_e * sin_e) + 15 * sin_e));
        coordinates[31] = (0.4841229183 * cos_a * cos_e * (21 * (sin_e * sin_e * sin_e * sin_e) - 14 * pow(sin_e, 2) + 1));
        coordinates[32] = (2.561737691 * cosf(2 * direction_r) * sin_e * pow(cos_e, 2) * (3 * pow(sin_e, 2) * 1));
        coordinates[33] = (0.522912516 * cosf(3 * direction_r) * (cos_e * cos_e * cos_e) * (9 * pow(sin_e, 2) - 1));
        coordinates[34] = (2.218529919 * cosf(4 * direction_r) * sin_e * (cos_e * cos_e * cos_e * cos_e));
        coordinates[35] = (0.70156076 * cosf(5 * direction_r) * (cos_e * cos_e * cos_e * cos_e * cos_e));
    }
}

void all(float x, float y, float z, double coordinates[], int order)
{
    int size = (sizeof(coordinates) / sizeof(coordinates[0]));
    float r = sqrt((x * x) + (y * y) + (z * z)); // this ensures we stay within our defined sphere, normalizing the coordinates.
    x /= r; // later on, coordinates that are calculated before normalization can be used to derive distance
    y /= r;
    z /= r;
    float x_2 = x * x;
    float y_2 = y * y;
    float z_2 = z * z;
    if (size)
    {
        coordinates[0] = w_constant; // w
        coordinates[1] = y; // y
        coordinates[2] = z; // z 
        coordinates[3] = x; // x 
        coordinates[4] = (1.732050807568877 * x * y); //v 
        coordinates[5] = (1.732050807568877 * y * z); // t
        coordinates[6] = (0.5 * (3 * z_2 - 1)); // r
        coordinates[7] = (1.732050807568877 * x * z); // s
        coordinates[8] = (0.8660254037844386 * (x_2 - y_2)); // u
        coordinates[9] = (0.790569415 * y * ((3 * x_2) - y_2)); // q
        coordinates[10] = (3.872983346207417 * x * y * z); // o
        coordinates[11] = (0.6123724356957945 * y * (5 * z_2 - 1)); // m
        coordinates[12] = (0.5 * z * (5 * z_2 - 3)); // k
        coordinates[13] = (0.6123724356957945 * x * (5 * z_2 - 1)); // l
        coordinates[14] = (1.936491673 * z * (x_2 - y_2)); // n
        coordinates[15] = (0.790569415 * x * (x_2 - (3 * y_2))); // p
        coordinates[16] = (2.958039892 * x * y * (x_2 - y_2));
        coordinates[17] = (2.091650066335189 * y * z * ((3 * (x_2)-y_2)));
        coordinates[18] = (1.118033989 * x * y * (7 * z_2 - 1));
        coordinates[19] = (0.790569415 * y * z * (7 * z_2 - 3));
        coordinates[20] = (0.125 * (35 * (z * z * z * z) - 30 * z_2 + 3));
        coordinates[21] = (0.790569415 * x * z * (7 * z_2 - 3));
        coordinates[22] = (0.5590169944 * (x_2 - y_2) * (7 * z_2 - 1));
        coordinates[23] = (2.091650066335189 * x * z * ((x_2 - (3 * y_2))));
        coordinates[24] = (0.739509972887452 * ((x_2 * x_2) - 6 * x_2 * y_2 + (y_2 * y_2)));
        coordinates[25] = (0.70156076 * y * (5 * (x_2 * x_2) - 10 * x_2 * x_2 + (y_2 * y_2)));
        coordinates[26] = (8.874119675 * x * y * z * (x_2 - y_2));
        coordinates[27] = (0.522912516 * y * ((y_2 * y_2) - 2 * x_2 * y_2 - 3 * (x_2 * x_2) - 8 * y_2 * z_2 + 24 * x_2 * z_2));
        coordinates[28] = (5.123475383 * x * y * z * (2 * z_2 - x_2 - y_2));
        coordinates[29] = (0.4841229183 * y * ((x_2 * x_2) + 2 * x_2 * y_2 + (y_2 * y_2) - 12 * x_2 * z_2 - 12 * y_2 * z_2 + 8 * (z_2 * z_2)));
        coordinates[30] = (0.125 * z * (63 * (z_2 * z_2) - 70 * z_2 + 15));
        coordinates[31] = (0.4841229183 * x * ((x_2 * x_2) + 2 * x_2 * y_2 + (y_2 * y_2) - 12 * x_2 * z_2 - 12 * y_2 * z_2 + 8 * (z_2 * z_2)));
        coordinates[32] = (2.561737691 * z * (2 * x_2 * z_2 - 2 * y_2 * z_2 - (x_2 * x_2) + (y_2 * y_2)));
        coordinates[33] = (0.522912516 * x * (2 * x_2 * y_2 + 8 * x_2 * z_2 - 24 * y_2 * z_2 * (x_2 * x_2) + 3 * (y_2 * y_2)));
        coordinates[34] = (2.218529919 * z * ((x_2 * x_2) - (6 * x_2 * y_2) + (y_2 * y_2)));
        coordinates[35] = (0.70156076 * x * ((x_2 * x_2) - 10 * x_2 * y_2 + 5 * (y_2 * y_2)));
    }
}

// impl
CK_DLL_MFUN(x_CoordinatePolar);
CK_DLL_MFUN(y_CoordinatePolar);
CK_DLL_MFUN(z_CoordinatePolar);
CK_DLL_MFUN(r_CoordinatePolar);
CK_DLL_MFUN(s_CoordinatePolar);
CK_DLL_MFUN(t_CoordinatePolar);
CK_DLL_MFUN(u_CoordinatePolar);
CK_DLL_MFUN(v_CoordinatePolar);
CK_DLL_MFUN(l_CoordinatePolar);
CK_DLL_MFUN(m_CoordinatePolar);
CK_DLL_MFUN(n_CoordinatePolar);
CK_DLL_MFUN(o_CoordinatePolar);
CK_DLL_MFUN(p_CoordinatePolar);
CK_DLL_MFUN(q_CoordinatePolar);
CK_DLL_MFUN(k_CoordinatePolar);
CK_DLL_MFUN(x_CoordinateCartesian);
CK_DLL_MFUN(y_CoordinateCartesian);
CK_DLL_MFUN(z_CoordinateCartesian);
CK_DLL_MFUN(r_CoordinateCartesian);
CK_DLL_MFUN(s_CoordinateCartesian);
CK_DLL_MFUN(t_CoordinateCartesian);
CK_DLL_MFUN(u_CoordinateCartesian);
CK_DLL_MFUN(v_CoordinateCartesian);
CK_DLL_MFUN(l_CoordinateCartesian);
CK_DLL_MFUN(m_CoordinateCartesian);
CK_DLL_MFUN(n_CoordinateCartesian);
CK_DLL_MFUN(o_CoordinateCartesian);
CK_DLL_MFUN(p_CoordinateCartesian);
CK_DLL_MFUN(q_CoordinateCartesian);
CK_DLL_MFUN(k_CoordinateCartesian);
CK_DLL_MFUN(HOA4_0);
CK_DLL_MFUN(HOA4_1);
CK_DLL_MFUN(HOA4_2);
CK_DLL_MFUN(HOA4_3);
CK_DLL_MFUN(HOA4_4);
CK_DLL_MFUN(HOA4_5);
CK_DLL_MFUN(HOA4_6);
CK_DLL_MFUN(HOA4_7);
CK_DLL_MFUN(HOA4_8);
CK_DLL_MFUN(all_CoordinatePolar);
CK_DLL_MFUN(all_CoordinateCartesian);