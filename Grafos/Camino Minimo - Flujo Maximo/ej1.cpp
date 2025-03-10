#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> memo, pasadizosDesde;
int n;

int minCamino(int i, int pasadizosUsados){
    if(i == n){
        return 0;
    }
    if(pasadizosUsados == 3){
        return n - i;
    }
    if(memo[i][pasadizosUsados] != -1){
        return memo[i][pasadizosUsados];
    }
    int res = 1 + minCamino(i+1, pasadizosUsados);
    for(int k = 0; k < pasadizosDesde[i].size(); k++){
        res = min(res, 2 + minCamino(pasadizosDesde[i][k], pasadizosUsados+1));
    }
    memo[i][pasadizosUsados] = res;
    return res;
}

int main(){

    //La primera linea indica la cantidad de tests
    int cant_tests;
    scanf("%d", &cant_tests);
    int cantPasadizos;
    //Ingreso los casos de test:
    while(cant_tests--){
        //La segunda linea del test contiene la cantidad de vertices, aristas y personas
        scanf("%d %d", &n, &cantPasadizos);
        memo.clear();
        pasadizosDesde.clear();
        memo.resize(n, vector<int>(3, -1));
        pasadizosDesde.resize(n, vector<int>());
        int desde, hasta;
        for(int i = 0; i < cantPasadizos; i++){
            scanf("%d %d", &desde, &hasta); 
            pasadizosDesde[desde].push_back(hasta);
        }
        int res = minCamino(0, 0);
        printf("%d\n", res);
    }
    return 0;
}
