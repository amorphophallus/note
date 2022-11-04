#include"voting_tree.h"

// cor[i][0/1] restore every point pairs being chosen on the path
// from root to the current node on the search tree.
int cor[N][2];

int cross(double a[2], double b[2]);
bool Pruning_1(int nowA, int nowB);
bool Pruning_2(int nowA, int nowB, int n);
bool Pruning_3(int nowA, int nowB, int n);
bool Pruning_4(int nowA, int nowB, int n);

// recursive search function
// param n indicates the depth of the current node on the search tree, where root's depth is 0
// return value of search() indicates whether this node on the search tree has one vote, 
// 1 for having vote, 0 for not having one.
int search(int nn){

    // (nowA, nowB) is the point pair chosen by the current node.
    // cnt is the number of correspondences in this subtree
    int nowA = cor[nn][0], nowB = cor[nn][1], cnt = 0;
    // printf("(%d, %d), dep = %d\n", nowA, nowB, nn);

    // expand the search tree
    for (int nxtA = nowA+1; nxtA <= n; ++ nxtA)
        for (int nxtB = nowB+1; nxtB <= m; ++ nxtB){
            cor[nn+1][0] = nxtA;
            cor[nn+1][1] = nxtB;
            // if (Pruning_1(nxtA, nxtB)) continue; // Pruning test 1 is abolished
            if (nn >= 1 && Pruning_2(nxtA, nxtB, nn)) continue;
            if (nn >= 2 && Pruning_3(nxtA, nxtB, nn)) continue;
            // if (nn >= 3 && Pruning_4(nxtA, nxtB, nn)) continue;
            cnt += search(nn+1);
        }
    if (cnt == 0) cnt = 1;
    if (nn > 0) v[nowA][nowB] += cnt;
    return cnt;
}

// Pruning 1: Node Centricity
bool Pruning_1(int nowA, int nowB){
    // printf("pruning 1: %d %d -> %lf\n", nowA, nowB, fabs(cenA[nowA]-cenB[nowB]) * 2 / (cenA[nowA] + cenB[nowB]));
    return (fabs(cenA[nowA]-cenB[nowB]) * 2 / (cenA[nowA] + cenB[nowB]) > eC);
}

// Pruning 2: Path Length
bool Pruning_2(int nowA, int nowB, int n){
    for (int i = 1; i <= n; ++ i){
        double geo1 = geoA[nowA][cor[i][0]] / geoA[cor[1][0]][cor[2][0]];
        double geo2 = geoB[nowB][cor[i][1]] / geoB[cor[1][1]][cor[2][1]];
        if (fabs(geo1 - geo2) * 2 / (geo1 + geo2) > eC) return true;
    }
    return false;
}

// Pruning 3: Path Angle
bool Pruning_3(int nowA, int nowB, int n){
    double del1 = fabs(angA[cor[n+1][0]][cor[n][0]] - angA[nowA][cor[n+1][0]]);
    if (del1 > pi) del1 = 2 * pi - del1; // confine the angle to be an acute angle
    double del2 = fabs(angB[cor[n+1][1]][cor[n][1]] - angB[nowB][cor[n+1][1]]);
    if (del2 > pi) del1 = 2 * pi - del2;
    if (fabs(del1 - del2) > eA) return true;
    return false;
}

int cross(double a[2], double b[2]){
    double ret = a[0] * b[1] - a[1] * b[0];
    return (ret > 0 ? 1 : -1);
}

// pruning test 4: vector direction
bool Pruning_4(int nowA, int nowB, int n){
    // 如果夹角太平了就不用这个剪枝
    double del1 = fabs(angA[cor[n+1][0]][cor[n][0]] - angA[nowA][cor[n+1][0]]);
    if (del1 > pi) del1 = 2 * pi - del1; // confine the angle to be an acute angle
    double del2 = fabs(angB[cor[n+1][1]][cor[n][1]] - angB[nowB][cor[n+1][1]]);
    if (del2 > pi) del1 = 2 * pi - del2;
    if (del1 < eA || del1 > pi - eA || del2 < eA || del2 > pi - eA) return false;
    // 正式开始剪枝
    double delA1[2], delA2[2], delA3[2];
    delA1[0] = A[nowA][0] - A[cor[n][0]][0];
    delA1[1] = A[nowA][1] - A[cor[n][0]][1];
    delA2[0] = A[cor[n][0]][0] - A[cor[n-1][0]][0];
    delA2[1] = A[cor[n][0]][1] - A[cor[n-1][0]][1];
    delA3[0] = A[cor[n-1][0]][0] - A[cor[n-2][0]][0];
    delA3[1] = A[cor[n-1][0]][1] - A[cor[n-2][0]][1];
    double delB1[2], delB2[2], delB3[2];
    delB1[0] = B[nowA][0] - B[cor[n][1]][0];
    delB1[1] = B[nowA][1] - B[cor[n][1]][1];
    delB2[0] = B[cor[n][1]][0] - B[cor[n-1][1]][0];
    delB2[1] = B[cor[n][1]][1] - B[cor[n-1][1]][1];
    delB3[0] = B[cor[n-1][1]][0] - B[cor[n-2][1]][0];
    delB3[1] = B[cor[n-1][1]][1] - B[cor[n-2][1]][1];
    if (cross(delA1, delA2) * cross(delA2, delA3) != cross(delB1, delB2) * cross(delB2, delB3)) return true;
    return false;
}