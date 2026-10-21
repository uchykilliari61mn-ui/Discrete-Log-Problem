#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;
typedef unsigned long long ull;

// (a * b) % mod без переповнення
ull mulmod(ull a, ull b, ull mod) {
    return (__int128)a * b % mod;
}

// (base^exp) % mod
ull powmod(ull base, ull exp, ull mod) {
    ull result = 1; base %= mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// Baby-step Giant-step: найменше X, де g^X ≡ h (mod q)
ull bsgs(ull g, ull h, ull q) {
    ull m = (ull)ceil(sqrt((double)q));

    // Baby steps: g^j -> j (зберігаємо найменше j для кожного значення)
    unordered_map<ull, ull> table;
    table.reserve(m * 2);
    ull cur = 1;
    for (ull j = 0; j < m; j++) {
        if (table.find(cur) == table.end()) table[cur] = j;
        cur = mulmod(cur, g, q);
    }

    // factor = g^(-m) mod q  (q просте -> інверсія за Ферма)
    ull gm = powmod(g, m, q);
    ull factor = powmod(gm, q - 2, q);

    // Giant steps
    ull gamma = h % q;
    for (ull i = 0; i < m; i++) {
        auto it = table.find(gamma);
        if (it != table.end()) {
            ull x = i * m + it->second;
            if (x > 1) return x;   // за умовою 1 < X
        }
        gamma = mulmod(gamma, factor, q);
    }
    return 0;
}

int main() {
    ull G, H, Q;
    cin >> G >> H >> Q;
    cout << bsgs(G, H, Q) << endl;
    return 0;
}
