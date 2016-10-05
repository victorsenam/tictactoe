#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 3;

int curr[N][N];
int curr_mov;
int rnd;

int victory () {
    int cnt;
    int sett = 0;
    for (int i = 0; i < N; i++) {
        cnt = 0;
        for (int j = 0; j < N; j++) {
            cnt += curr[i][j];
            sett += !!curr[i][j];
        }
        if (abs(cnt) == N) return cnt/N;

        cnt = 0;
        for (int j = 0; j < N; j++)
            cnt += curr[j][i];
        if (abs(cnt) == N) return cnt/N;
    }

    cnt = 0;
    for (int i = 0; i < N; i++)
        cnt += curr[i][i];
    if (abs(cnt) == N) return cnt/N;

    cnt = 0;
    for (int i = 0; i < N; i++)
        cnt += curr[i][N-i-1];
    if (abs(cnt) == N) return cnt/N;

    return 0;
}

void printboard () {
    for (int i = 0; i < N; i++) {
        printf("| ");
        for (int j = 0; j < N; j++) {
            if (curr[i][j] == 0)
                printf("%d | ", i*N+j);
            else
                printf("%c | ", "o x"[curr[i][j]+1]);
        }
        printf("\n");
    }
}

int minimax (int pl) {
    if (int curr_vic = victory()) return curr_vic;

    int zer = -1;
    int win = -1;
    int mov = -1;
    curr_mov = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (curr[i][j]) continue;
            mov = i*N+j;
            curr[i][j] = pl;
            int loc = minimax(-pl);
            if (loc == pl) {
                win = i*N+j;
            } else if (loc == 0) {
                zer = i*N+j;
            }
            curr[i][j] = 0;
        }
    }

    if (win != -1) {
        curr_mov = win;
        return pl;
    } else if (zer != -1 || mov == -1) {
        curr_mov = zer;
        return 0;
    } 
    curr_mov = mov;
    return -pl;
}

void endit (int pl) {
    printf("Acabou!\n");
    if (pl == 1)
        printf("Eu ganhei!\n");
    else if (pl == -1)
        printf("Você ganhou!\n");
    else
        printf("Empate.\n");
    exit(0);
}

int main () {
    rnd = 0;

    printboard();
    while (rnd < N*N) {
        if (int curr_vic = victory()) {
            endit(curr_vic);
        }

        if (!(rnd&1)) {
            int movem;
            scanf("%d", &movem);
            if (curr[movem/N][movem%N]) {
                printf("Jogada inválida\n");
                rnd--;
            } else {
                curr[movem/N][movem%N] = -1;
            }

        } else {
            minimax(1);
            assert(curr_mov != -1);
            
            curr[curr_mov/N][curr_mov%N] = 1;
            printboard();
        }

        rnd++;
    }

    endit(victory());
}
