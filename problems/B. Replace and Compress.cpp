#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using i128 = __int128;

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
    int N;
    ll K;
    cin >> N >> K;
    ll lowest_unchangable = LLONG_MAX;
    vector<pair<ll, ll>> changable_sums;
    changable_sums.reserve(N);
    for (int i = 0; i < N; ++i) {
        ll x, y, z;
        cin >> x >> y >> z;

        bool addable = !(x == y && y == z && z == x);
        if (addable) {
            ll startup = 0;
            if (max({x - y, x - z, y - z}) < 0) {
                if (x == y || y == z) {
                    startup = 2;
                } else {
                    ll filler = (y - x > z - y) ? z - y : y - x;
                    ++filler;
                    startup = filler * 2;
                }
            }
            if (startup < K)
                changable_sums.push_back({x + y + z, startup});
            else
                lowest_unchangable = min(lowest_unchangable, x + y + z);
        } else {
            lowest_unchangable = min(lowest_unchangable, x + y + z);
        }
    }

    if (changable_sums.empty()) {
        cout << lowest_unchangable << nl;
        return;
    }

    sort(all(changable_sums));

    // first value, compare all ones after to this
    i128 running_sum = changable_sums[0].first;
    for (int i = 1; i < (int)changable_sums.size(); ++i) {
        // check if the previous mean is greater then the current value
        if ((running_sum + K) > (i128)changable_sums[i] * i) {
            running_sum += (i128)changable_sums[i];
        } else {
            // minimum changeable is found
            ll curr_min = (running_sum + K) / i;
            cout << min(lowest_unchangable, curr_min) << nl;
            return;
        }
    }

    // case that the k is distrubted across all values
    ll min_val = (running_sum + K) / (ll)changable_sums.size();
    cout << min(min_val, lowest_unchangable) << nl;
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
