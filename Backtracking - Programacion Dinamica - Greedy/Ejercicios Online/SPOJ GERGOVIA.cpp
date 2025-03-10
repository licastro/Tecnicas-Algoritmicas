#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long int minimoEsfuerzo(vector<int>& vecindario, queue<int>& vecinosParaComprar, queue<int>& vecinosParaVender) {

    long long int res = 0;

    while (!vecinosParaComprar.empty()) {
        int comprador = vecinosParaComprar.front(), vendedor = vecinosParaVender.front();
        int demanda = vecindario[comprador], oferta = vecindario[vendedor], neto = demanda+oferta;

        vecindario[comprador] = max(0, neto);
        vecindario[vendedor] = min(0, neto);
        res += abs(comprador - vendedor)*min(demanda, -oferta);

        if (!vecindario[comprador]) vecinosParaComprar.pop();
        if (!vecindario[vendedor]) vecinosParaVender.pop();

    }
    return res;
}

int main() {

    int cantHabitantes;
    scanf("%d", &cantHabitantes);

    while (cantHabitantes) {

        vector<int> vecindario;
        queue<int> vecinosParaComprar, vecinosParaVender;

        for(int habitante = 0; habitante < cantHabitantes; habitante++) {
            int cantidad;
            scanf("%d", &cantidad);

            vecindario.push_back(cantidad);

            if (cantidad >= 0) vecinosParaComprar.push(habitante);
            else vecinosParaVender.push(habitante);
        }
        printf("%lld\n", minimoEsfuerzo(vecindario, vecinosParaComprar, vecinosParaVender));

        scanf("%d", &cantHabitantes);
    }

    return 0;
}