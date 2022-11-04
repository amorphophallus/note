#include"voting_tree.h"

double MyMin(double x, double y){return (x < y ? x : y);}
double MyMax(double x, double y){return (x > y ? x : y);}
double dis(double a[], double b[]);
double dot(double a[], double b[]);
void init_geo(int n, double p[N][2], double geo[N][N]);
void init_cen(int n, double geo[N][N], double cen[N]);
void init_ang(int n, double p[N][2], double ang[N][N]);

// export function initialization() to main function
void Initialization(){
    init_geo(n, A, geoA);
    init_geo(m, B, geoB);
    init_cen(n, geoA, cenA);
    init_cen(m, geoB, cenB);
    init_ang(n, A, angA);
    init_ang(m, B, angB);
}

// calculate the geometric distance between two point a and b
double dis(double a[], double b[]){
    return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
}

// calculate the dot product of two vector
double dot(double a[], double b[]){
    return a[0] * b[0] + a[1] * b[1];
}

// pre-calculate geo[i][j]
// geo[i][j] is the minimum geodesic distance between point i and point j
// To be more explicit, 'geodesic' means we go along the edge in the polygon
// instead of go straight from i to j.
// We normalize geo[i][j] to [0, 1] by dividing it by the maximum geodesic distance of individual shape
void init_geo(int n, double p[N][2], double geo[N][N]){

    // C indicates the circumference of the given shape
    double C = 0; 

    // maxGeo indicates the maximum geodesic distance of individual shape
    double maxGeo = 0;

    for (int i = 1; i <= n; ++ i){
        geo[i][i] = 0;
        int nxt = i%n+1;
        geo[i][nxt] = geo[nxt][i] = dis(p[i], p[nxt]);
        C += geo[i][nxt];
        maxGeo = MyMax(maxGeo, geo[i][nxt]);
    }
    for (int i = 1; i < n-1; ++ i)
        for (int j = i+2; j <= n; ++ j){
            geo[i][j] = geo[j][i] = MyMin(geo[i][j-1] + geo[j-1][j], C - (geo[i][j-1] + geo[j-1][j]));
            maxGeo = MyMax(maxGeo, geo[i][j]);
        }

    // normalization
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j){
            geo[i][j] /= maxGeo;
        }
}

// pre-calculate cen[i]
// centricity cen[i] of point i is the average geodesic distance from i to all other node
// cen[i] is normalized to [0, 1] because geo[i][j] is normalized before
void init_cen(int n, double geo[N][N], double cen[N]){
    for (int i = 1; i <= n; ++ i){
        cen[i] = 0;
        for (int j = 1; j <= n; ++ j)
            cen[i] += geo[i][j];
        cen[i] /= n;
    }
}

// pre-calculate ang[i][j]
// ang[i][j] indicates the angle between the vector (p[i] -> p[j]) and the positive x-axis
void init_ang(int n, double p[N][2], double ang[N][N]){
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j){
            // ang[i][i] has no meaning, we don't deal with it.
            if (i == j) continue;
            // use dot product to calculate angle
            // where del[2] indicates the vector (p[j] - p[i])
            // and posX[2] indicates the unit vector (1, 0)
            double del[2], posX[2];
            del[0] = p[j][0] - p[i][0];
            del[1] = p[j][1] - p[i][1];
            posX[0] = 1;
            posX[1] = 0;
            ang[i][j] = acos(dot(del, posX) / dis(p[i], p[j]));
            // value field of acos() is ranged in [0, pi)
            // but we want ang[i][j] to be in [0, 2 * pi), which indicates all the direction
            if (del[1] < 0) ang[i][j] = 2 * (3.1415926535) - ang[i][j];
        }
}