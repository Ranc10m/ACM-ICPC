#include <cmath>
#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
const int N = 10000000;
const int inv = 500000004;

int prime[N + 1], Phi[N + 1];
void prePhi() {
    Phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!prime[i]) {
            prime[++prime[0]] = i;
            Phi[i] = i - 1;
        }
        for (int j = 1; j <= prime[0] && i <= N / prime[j]; j++) {
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                Phi[i * prime[j]] = Phi[i] * prime[j];
                break;
            } else {
                Phi[i * prime[j]] = Phi[i] * (prime[j] - 1);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        Phi[i] = (Phi[i] + Phi[i - 1]) % mod;
    }
}

map<ll, int> mp;
int calPhi(ll n) {
    if (n <= N) return Phi[n];
    if (mp[n]) return mp[n];
    int ret;
    if (n % 2)
        ret = (n + 1) / 2 % mod * (n % mod) % mod;
    else
        ret = n / 2 % mod * ((n + 1) % mod) % mod;
    int r = sqrt(n);
    ret = (ret - (n - n / 2) % mod) % mod;
    for (int i = 2; i <= r; i++) {
        ret = ((ll) ret - calPhi(n / i) -
               (n / i - n / (i + 1)) % mod * calPhi(i) % mod) %
              mod;
    }
    if (n / r < (r + 1)) ret = (ret + calPhi(r)) % mod;
    return mp[n] = ret;
}

int main() {
    prePhi();
    ll n;
    cin >> n;
    int ans = 0;
    int r = sqrt(n);
    for (int i = 1; i <= r; i++) {
        ans = ((n / i + n / (i + 1) + 1) % mod * ((n / i - n / (i + 1)) % mod) %
                   mod * inv % mod * calPhi(i) % mod +
               (ll) i * calPhi(n / i) % mod + ans) %
              mod;
    }
    if (n / r < (r + 1)) ans = (ans - (ll) r * calPhi(n / r) % mod) % mod;
    ans = ans * 2 % mod;
    ans =
        ((ans - (n % mod) * (n % mod + 1) % mod * inv % mod) % mod + mod) % mod;
    cout << ans << endl;
    return 0;
}