#include"voting_tree.h"

// f[i][j] indicates the maximum votes one correspondence,
//          which has {ai, bj} as its last point pair
// pre[i][j] indicates the previous choice of point pair
//          if we want to get maximum votes and choose {ai, bj} as its last point p
// Fmax[i][j] = max(f[k][l]) for all k <= i, l <= j
// pre_Fmax[i][j] indicates the pair (i0, j0) that f[i0][j0] == Fmax[i][j]
int pre_f[N][N][2], pre_Fmax[N][N][2], f[N][N], Fmax[N][N];

int MyMax(int x, int y){return (x > y ? x : y);}
int get_ans(int nowA, int nowB);

// export function vote() to main function
void vote(){

    // for(int i = 1; i <= n; ++ i){
    //     for (int j = 1; j <= m; ++ j){
    //         printf("%4d", v[i][j]);
    //     }
    //     printf("\n");
    // }

    // boundary condition
    for (int i = 0; i <= MyMax(n, m); ++ i){

        // initialize the left-most column
        f[i][0] = Fmax[i][0] = 0;
        pre_f[i][0][0] = pre_f[i][0][1] = 0;
        pre_Fmax[i][0][0] = pre_Fmax[i][0][1] = 0;

        // initialize the up-most row
        f[0][i] = Fmax[0][i] = 0;
        pre_f[0][i][0] = pre_f[0][i][1] = 0;
        pre_Fmax[0][i][0] = pre_Fmax[0][i][1] = 0;
    }

    // dynamic programming
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j){

            // update f[i][j] and pre_f[i][j]
            f[i][j] = Fmax[i-1][j-1] + v[i][j];
            pre_f[i][j][0] = pre_Fmax[i-1][j-1][0];
            pre_f[i][j][1] = pre_Fmax[i-1][j-1][1];
            
            // update Fmax[i][j] and pre_Fmax[i][j]
            if (f[i][j] >= Fmax[i-1][j] && f[i][j] >= Fmax[i][j-1]){
                Fmax[i][j] = f[i][j];
                pre_Fmax[i][j][0] = i;
                pre_Fmax[i][j][1] = j;
            }
            else if (Fmax[i-1][j] >= Fmax[i][j-1]){
                Fmax[i][j] = Fmax[i-1][j];
                pre_Fmax[i][j][0] = pre_Fmax[i-1][j][0];
                pre_Fmax[i][j][1] = pre_Fmax[i-1][j][1];
            }
            else{
                Fmax[i][j] = Fmax[i][j-1];
                pre_Fmax[i][j][0] = pre_Fmax[i][j-1][0];
                pre_Fmax[i][j][1] = pre_Fmax[i][j-1][1];
            }
        }

    // get the answer - 'optimal correspondence'
    // Obviously pre_Fmax[n][m] stores the last pair of point in the correspondence getting maximal votes
    optN = get_ans(pre_Fmax[n][m][0], pre_Fmax[n][m][1]) - 1;
}

// use recursive method to get the answer
int get_ans(int nowA, int nowB){
    if (nowA == 0 || nowB == 0) return 1;
    int now_index = get_ans(pre_f[nowA][nowB][0], pre_f[nowA][nowB][1]);
    opt[now_index][0] = nowA;
    opt[now_index][1] = nowB;
    return now_index + 1;
}