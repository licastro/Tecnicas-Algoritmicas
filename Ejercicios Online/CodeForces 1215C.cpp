#include <iostream>
#include <string>
#include <vector>

using namespace std;

void intercambiarPosiciones(vector<int>& s_a, vector<int>& s_b, int impar){

    int res = s_a.size()/2 + impar + s_b.size()/2 + impar;
    printf("%d\n", res);

    for (int i = 0; i < s_a.size()-impar; i+=2) printf("%d %d\n", s_a[i], s_a[i+1]);
    for (int j = 0; j < s_b.size()-impar; j+=2) printf("%d %d\n", s_b[j], s_b[j+1]);

    if (impar) printf("%d %d\n%d %d\n", s_a.back(), s_a.back(), s_a.back(), s_b.back());

}

int main() {

    int longitud;
    scanf("%d", &longitud);
    string s, t;
    cin >> s >> t;
    vector<int> s_a, s_b;

    for (int i = 0; i < longitud; i++) {
        if (s[i] != t[i]) {
            if (s[i] == 'a') s_a.push_back(i+1);
            else s_b.push_back(i+1);
        }
    }

    if (s_a.size()%2 != s_b.size()%2) printf("%d\n", -1);
    else intercambiarPosiciones(s_a, s_b, s_a.size()%2);

    return 0;
}