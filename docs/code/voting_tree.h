#ifndef VOTING_TREE_H
#define VOTING_TREE_H

#include<bits/stdc++.h>

/*--------------------shared values--------------------*/
const int N = 211;
const double pi = 3.1415926535;
const double eC = 0.2; // eC is the threshold of spatial distance
const double eA = pi / 4; // eA is the threshold of angular difference
extern int n, m;
extern double A[N][2], B[N][2], geoA[N][N], geoB[N][N], angA[N][N], angB[N][N], cenA[N], cenB[N];
extern int v[N][N], opt[N][2], optN;

/*---------------------init.cpp------------------------*/
void Initialization();

/*---------------------search.cpp----------------------*/
int search(int n);

/*---------------------vote.cpp------------------------*/
void vote();
void vote_greedy();

#endif