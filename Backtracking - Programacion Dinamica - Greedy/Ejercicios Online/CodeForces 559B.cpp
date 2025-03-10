#include <iostream>
#include <string>

using namespace std;

bool equivalentes(const string& A, const string& B, int iA, int fA, int iB, int fB) {
    bool res = A.compare(iA, fA-iA+1, B, iB, fB-iB+1) == 0;
    if (res || (fA-iA)%2 == 0) return res;
    else {
        int midA = (fA+iA)/2, midB = (fB+iB)/2;
        return (equivalentes(A, B, iA, midA, midB+1, fB) && equivalentes(A, B, midA+1, fA, iB, midB)) || (equivalentes(A, B, iA, midA, iB, midB) && equivalentes(A, B, midA+1, fA, midB+1, fB));
    }
}

int main() {

    string A, B;
    cin >> A >> B;

    if (equivalentes(A, B, 0, A.length()-1, 0, B.length()-1)) cout << "YES";
    else cout << "NO";

    return 0;
}