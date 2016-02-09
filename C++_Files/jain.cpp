#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>

#define MAX 1001

using namespace std;

int cards[MAX];
int max_sums[MAX][MAX];

int sum_max(int i, int j){
    if (i==j){
        return cards[i];
    }
    if (i > j)
        return 0;
    if(max_sums[i][j]!=-1){
        return max_sums[i][j];
    }
    int val1, val2;
    if(cards[j] > cards[i+1]){
        val1 = cards[i] + sum_max(i+1, j-1);
    }
    else{
        val1 = cards[i] + sum_max(i+2, j);
    }

    if(cards[i] >= cards[j-1]){
        val2 = cards[j] + sum_max(i+1, j-1);
    }
    else{
        val2 = cards[j] + sum_max(i, j-2);
    }

    max_sums[i][j] = max(val1, val2);
    return max_sums[i][j];
}

int main(){
    int n, sum, game_number = 0;
    while(1){
        cin >> n;
        if(n == 0){
            break;
        }
        game_number++;
        sum = 0;
        memset(max_sums, -1, sizeof(max_sums));
        for(int i=1; i<=n; i++){
            cin >> cards[i];
            sum += cards[i];
        }
        cout << "In game " << game_number << ", the greedy strategy might lose by as many as " ;
        // sum_max(1,n) - (sum -sum_max(1,n)) -> Points by smart player - points by greedy player
        cout << 2*sum_max(1,n) - sum << " points." << endl;

    }
    return 0;
}
