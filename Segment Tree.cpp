#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=3e5;
int a[MAXN+1]={-1},segMax[4*(MAXN+1)],segSum[4*(MAXN+1)];

void build(int v, int tl,int tr)
{
    if(tl==tr)
    {
        segMax[v]= a[tr];
        segSum[v]= a[tr];
        return ;
    }
    int tm= (tr+tl)/2;
    build(2*v+1, tl, tm);
    build(2*v+2, tm+1, tr);
    segMax[v] = max( segMax[2*v+1], segMax[2*v+2]);
    segSum[v] = segSum[2*v+1]+  segSum[2*v+2];
}

int query(int v  , int  tl ,int tr ,int l, int r)
{
    if( tl>=l && tr<=r )
        return    segMax[v];
    if(tl>r || tr<l)
        return INT_MIN;
    int tm    =  tl +   (tr-tl)  /2;
    int left=query(2*v+1,tl,tm,l,r);
    int right=query(2*v+2,tm+1,tr,l,r);
    return max(left,right);
}
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && r == tr) {
        return segSum[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2+1, tl, tm, l, min(r, tm))
           + sum(v*2+2, tm+1, tr, max(l, tm+1), r);
}
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        segMax[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2+1, tl, tm, pos, new_val);
        else
            update(v*2+2, tm+1, tr, pos, new_val);
        segMax[v] = max(segMax[v*2+1] , segMax[v*2+2]);
    }
}
signed main()
{
    int n,k;
    cin>>n>>k;
    int b[n];
    for(int i=0;i<n;i++)cin>>b[i];
    int max_=*max_element(b,b+n);
    build(0,0,max_);

    int ans=0;
    for(int i=0;i<n;i++)
    {
        int l=max(0LL,b[i]-k);
 		int r=b[i]+k+1;
        int res=query(0,0,max_,l,r);
        ans=max(ans,res+1);
        update(0,0,max_,b[i],res+1);
    }

    cout<<ans<<endl;


}
