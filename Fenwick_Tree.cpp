#include<bits/stdc++.h>
using namespace std;
class Fenwick{
    int n;
    vector<int> table;
    public:
    Fenwick(int length)
    {
        n=length;
        while(length--)
            table.push_back(0);
    }
    public:
    void add(int pos, int val)
    {
        while(pos<n)
        {
            table[pos]+=val;
            pos+=(pos&-pos);
        }
    }
    public:
    int prefix(int pos)
    {
        int pre=0;
        while(pos>0)
        {
            pre+=table[pos];
            pos-=(pos&-pos);
        }
        return pre;
    }
    public:
    int query(int i,int j)
    {
        return prefix(j)-prefix(i-1);
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Fenwick fenwick(13);
    for(int i=1;i<=9;i++)
    {
        fenwick.add(i,i);
    }
    cout<<fenwick.query(6,8);

}
