// https://s3.amazonaws.com/codechef_shared/download/Solutions/COOK72/Tester/CHEFLKJ.cpp
//karanaggarwal
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update


using namespace std;
using namespace __gnu_pbds;



#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

#define si(x) scanf("%d",&x)
#define sll(x) scanf("%lld",&x)
#define pi(x) printf("%d\n",x)
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define LET(x,a) __typeof(a) x(a)
#define TR(v,it) for( LET(it,v.begin()) ; it != v.end(); it++)

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;

typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OS;

struct query {
    int ty;
    int l,r;
};

const int N = 100000;
query Q[N];
int A[N];

map<int,int> M;
OS pos[N];
int T[1<<18];
int L[1<<18]; int R[1<<18];

int find(int x, int l, int r){
    if(x<0)return 0;
    return pos[x].order_of_key(r) - pos[x].order_of_key(l);
}

int ql, qr;
set<int> poss_ans;

void query(int id){
    if(R[id]<= ql or qr<=L[id])return;
    if(L[id]>=ql and R[id]<=qr){
        poss_ans.insert(T[id]);
        return;
    }
    query(2*id);
    query(2*id+1);
}

int main(int argc, char** argv)
{
    int n,q; si(n); si(q);
    assert(n>0 and n<=N and q>0 and q<=N);
    for(int i =0; i<n; i++) {
        si(A[i]);
        M[A[i]];
    }
    for(int i = 0; i < q; i++) {
        si(Q[i].ty);
        si(Q[i].l);
        si(Q[i].r);
        if(Q[i].ty==2){
            Q[i].l--;
        }
        else {
            Q[i].l--;
            M[Q[i].r];
        }
    }

    // remap
    int CNT = 0;
    for(auto &p : M)p.S = CNT++;
    for(int i =0; i<n; i++) A[i] = M[A[i]];
    for( int i =0; i<q; i++) {
        if(Q[i].ty == 1) {
            Q[i].r = M[Q[i].r];
        }
    }

    for(int i = 0; i<n; i++)
        pos[A[i]].insert(i);
    int base = 1; while(base<n)base*=2;
    for(int i = base; i<2*base; i++)
    {
        R[i] = L[i] = i-base; R[i]++;
        if(i-base < n)
            T[i] = A[i-base];
        else
            T[i] = -1;
    }
    for(int i =base -1; i>0; i--) {
        int l = 2*i; int r = l+1;
        L[i] = L[l]; R[i] = R[r];
        int x = T[l]; int y = T[r];
        int cx = find(x,L[i],R[i]);
        int cy = find(y,L[i],R[i]);
        if(cx>cy)T[i] = x; else T[i] = y;
    }

    for(int i = 0; i<q; i++){
        if(Q[i].ty==1){
            int p = Q[i].l;
            pos[A[p]].erase(p);
            A[p] = Q[i].r;
            pos[A[p]].insert(p);
            int id = base+p;
            T[id] = A[p];
            while(id>1){
                id/=2;
                int l = 2*id; int r = 2*id + 1;
                int x = T[l]; int y = T[r];
                int cx = find(x,L[id],R[id]);
                int cy = find(y,L[id],R[id]);
                if(cx>cy)T[id] = x; else T[id] = y;
            }
        } else {
            ql = Q[i].l; qr = Q[i].r;
            poss_ans.clear();
            query(1);
            bool fnd = false;
            for(auto x : poss_ans)
            {
                if(find(x,ql,qr) > (qr-ql)/2)
                {
                    printf("Yes\n");
                    fnd = true;
                    break;
                }
            }
            if(fnd==false)
                printf("No\n");
        }
    }

    return 0;
}
