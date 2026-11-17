#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()
#define nl '\n'

#ifdef LOCAL
template <class A, class B> void dbg_print(const pair<A, B> &p);

template <class T, class = void> struct has_ostream : false_type {};
template <class T>
struct has_ostream<T, void_t<decltype(declval<ostream &>() << declval<const T &>())>> : true_type {
};

template <class T, class = void> struct is_iterable : false_type {};
template <class T>
struct is_iterable<
    T, void_t<decltype(begin(declval<const T &>())), decltype(end(declval<const T &>()))>>
    : true_type {};

template <class T> void dbg_print(const T &x) {
    if constexpr (has_ostream<T>::value) {
        cerr << x;
    } else if constexpr (is_iterable<T>::value) {
        cerr << '[';
        string sep;
        for (const auto &elem : x) {
            cerr << sep;
            dbg_print(elem);
            sep = ", ";
        }
        cerr << ']';
    } else {
        cerr << "<unprintable>";
    }
}

template <class A, class B> void dbg_print(const pair<A, B> &p) {
    cerr << '(';
    dbg_print(p.first);
    cerr << ", ";
    dbg_print(p.second);
    cerr << ')';
}

void dbg_out() {
    cerr << '\n';
}
template <class Head, class... Tail> void dbg_out(const Head &H, const Tail &...T) {
    cerr << ' ';
    dbg_print(H);
    dbg_out(T...);
}
#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define debug(...) ((void)0)
#endif

void solve() {
    ll N, K;
    cin >> N >> K;

    vector<ll> arr(N);
    for (auto &a : arr) {
        cin >> a;
    }

    vector<ll> prefix_sum(N + 1, 0);
    ll sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += arr[i];

        prefix_sum[i + 1] = sum % K;
    }

    vector<ll> freq(K, 0);
    ll counter = 0;

    for (int i = K + 1; i <= N; ++i) {
        freq[prefix_sum[i - K - 1]]++;  // the valid growing window on the right appears
        counter += freq[prefix_sum[i]]; // counts the previous values wheere the mod k can
                                        // cancel out and create a new value
    }

    cout << counter << nl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
