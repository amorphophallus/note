#include"voting_tree.h"

int n, m;
double A[N][2], B[N][2], geoA[N][N], geoB[N][N], angA[N][N], angB[N][N], cenA[N], cenB[N];
int v[N][N], opt[N][2], optN;

int main()
{

    // input
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) scanf("%lf%lf", &A[i][0], &A[i][1]);
    for (int i = 1; i <= m; ++ i) scanf("%lf%lf", &B[i][0], &B[i][1]);

    // clock start
    clock_t start, stop;
    double duration;
    start = clock();

    // initialization
    Initialization();

    // search process
    memset(v, 0, sizeof(v));
    search(0);

    // voting and get the answer
    vote();
    for (int i = 1; i <= optN; ++ i) printf("(%d, %d)\n", opt[i][0], opt[i][1]);

    // clock stop
    stop = clock();
    printf("Time = %.2lf(ms)\n", ((double)(stop - start)) / CLOCKS_PER_SEC * 1000);

    return 0;
}