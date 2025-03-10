#include <iostream> // Para entrada y salida estándar.
#include <vector> // Para representación de matrices y resultados.

using namespace std;
using Tablero = vector<vector<char>>;
int n, m, INF = 1e9, cantPiezas = 0, minCaminoPosible = INF, maxCaminoPosible = -INF;

struct Celda {
    int i;
    int j;
};

/*-------------------funciones auxiliares-----------------*/
bool enRango(int i, int j){
    return (i >= 0 && i < n) && (j >= 0 && j < m);
}

vector<Celda> candidatos_para(Tablero& tablero, Tablero& visitadas, Celda actual, Celda anterior) {
    vector<Celda> candidatos(0);
    Celda arriba = {actual.i - 1, actual.j};
    Celda abajo = {actual.i + 1, actual.j};
    Celda derecha = {actual.i, actual.j + 1};
    Celda izquierda = {actual.i, actual.j - 1};
    
    if(actual.i == 0 && actual.j == 0){    // En la primer celda solo se puede empezar hacia la derecha o hacia abajo
        candidatos.push_back(derecha);
        candidatos.push_back(abajo);
    } else {
        // Primero nos fijamos dada la forma que tiene la pieza a donde se podria mover
        switch(tablero[actual.i][actual.j]){
            case 'L':
                if(actual.i == anterior.i){    // la fila es la misma, entonces se movio hacia la derecha o la izquierda. ahora solo puede moverse arriba o abajo
                    candidatos.push_back(arriba);
                    candidatos.push_back(abajo);    
                } else {    // la columna es la misma, entonces se movio hacia arriba o hacia abajo. ahora solo puede moverse a la derecha o a la izquierda
                    candidatos.push_back(derecha);
                    candidatos.push_back(izquierda);
                }
                break;
            case 'I':
                Celda candidata;
                if(actual.i == anterior.i){    // la fila es la misma, entonces se movio hacia la derecha o la izquierda
                    candidata = {actual.i, actual.j + (actual.j - anterior.j)};    // con esa resta sacamos la direccion a la que se tiene que mover
                } else {    // la columna es la misma, entonces se movio hacia arriba o hacia abajo
                    candidata = {actual.i + (actual.i - anterior.i), actual.j};
                }
                candidatos.push_back(candidata);
                break;
            case '+':
                candidatos.push_back(arriba);
                candidatos.push_back(abajo);
                candidatos.push_back(derecha);
                candidatos.push_back(izquierda);
                break;  
        }
    }
    
    // ahora descartamos las celdas invalidas, las ya visitadas y las vacias
    vector<Celda> res(0);
    int n = tablero.size();
    int m = tablero[0].size();
    int i,j;
    for (int k = 0; k < candidatos.size(); k++){
        i = candidatos[k].i;
        j = candidatos[k].j;
        if(actual.i == n-1 && anterior.i == n-2 && i == n-1 && actual.j == j+1){
            continue; //si llega a la ultima fila desde arriba y se mueve a la izquierda ya no seria un camino valido
        }
        if(actual.j == m-1 && anterior.j == m-2 && j == m-1 && actual.i == i+1){
            continue; //si llega a la ultima columna desde la izquierda y sube ya no es valido
        }
        if(enRango(i, j) && visitadas[i][j] == '0' && tablero[i][j] != '#'){
            res.push_back(candidatos[k]);
        }
    }       
    return res;
}

pair<int, int> sendero(Tablero& tablero, Tablero& visitadas, Celda actual, Celda anterior, int longActual){
    pair<int, int> res(INF, -INF);  // first = minCamino, second = maxCamino
    if(actual.i == n - 1 && actual.j == m - 1){  // caso base
        res.first = longActual;
        res.second = longActual;
    } else if((minCaminoPosible != n+m - 2 && longActual+1 < minCaminoPosible) || maxCaminoPosible != cantPiezas - 1){ 
        // cout << "El min y el max camino son: " << minCaminoPosible << " " << maxCaminoPosible << endl;
        /* solo sigo buscando si:
               todavia no encontramos un camino que use todas las piezas o
               ya encontramos ese camino pero todavia no uno minimo que mida n*m - 1. En este caso solo seguimos buscando si todavia no nos pasamos del minimo posible */
        visitadas[actual.i][actual.j] = '1';
        vector<Celda> candidatos = candidatos_para(tablero, visitadas, actual, anterior);
        if(candidatos.size() > 0){
            pair<int, int> resultados_candidatos[candidatos.size()];
            for(int k = 0; k < candidatos.size(); k++){
                resultados_candidatos[k] = sendero(tablero, visitadas, candidatos[k], actual, longActual + 1);
                res.first = min(res.first, resultados_candidatos[k].first);
                res.second = max(res.second, resultados_candidatos[k].second);
                visitadas[candidatos[k].i][candidatos[k].j] = '0';  // backtracking
            }
        }
    }
    minCaminoPosible = min(minCaminoPosible, res.first);
    maxCaminoPosible = max(minCaminoPosible, res.second);
    return res;
}

int main(){
    //La primera linea indica la cantidad de tests
    int cant_tests;cin>>cant_tests;

    //Ingreso los casos de test:
    while(cant_tests--){
        //La segunda linea del test contiene las dimensiones de la matriz
        cin>>n>>m;
        // La tercera linea contiene el tablero
        Tablero tablero(n, vector<char>(m));
        for(int i = 0; i < n; i++){
            string fila;
            cin >> fila;
            for(int j = 0; j < m; j++){
                tablero[i][j] = fila[j];
            }
        }       
        Tablero visitadas(n, vector<char>(m, '0'));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(tablero[i][j] != '#'){
                    cantPiezas++;    
                }
            }
        }
        Celda primera = {0, 0};
        pair<int, int> res = sendero(tablero, visitadas, primera, primera, 0);
        bool posible = res.first != INF;
        if(posible){
            cout << "POSIBLE " << res.first << " " << res.second << endl;
        } else {
            cout << "IMPOSIBLE" << endl;
        }
    }
    return 0;
}
