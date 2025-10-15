#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;

ll fpow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

ll phi(ll n) {
    if (n == 1) return 1;
    ll ans = n;
    if (n % 2 == 0) {
        ans = ans / 2;
        while (n % 2 == 0) {
            n = n / 2;
        }
    }
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) {
                n = n / i;
            }
        }
    }
    if (n > 1) {
        ans = ans / n * (n - 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        ll total = 0;
        for (ll d = 1; d * d <= n; d++) {
            if (n % d != 0) continue;
            ll k = n / d;
            ll term1 = fpow(n, d-1) * phi(k) % mod;
            total = (total + term1) % mod;
            if (k != d) {
                ll term2 = fpow(n, k-1) * phi(d) % mod;
                total = (total + term2) % mod;
            }
        }
        //ll inv_n = fpow(n, mod - 2);
        //ll ans = total * inv_n % mod;
        cout << total << '\n';
    }
    return 0;
}