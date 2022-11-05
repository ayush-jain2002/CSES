#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fr(a,b) for(int i = a; i < b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define mod 1000000007
#define inf (1LL<<60)
#define all(x) (x).begin(), (x).end()
#define prDouble(x) cout << fixed << setprecision(10) << x
#define triplet pair<ll,pair<ll,ll>>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
vector<int>tree[200001];
int dp[200001][2];
void solve(int node,int par){
    vector<int>prefix,suffix;
    dp[node][0]=dp[node][1]=0;
    bool leaf=1;
    for(int child:tree[node]){
      if(child!=par){
        leaf=0;
        solve(child,node);
      }
    }
    if(leaf) return;
    for(int child:tree[node]){
      if(child!=par){
      prefix.push_back(max(dp[child][0],dp[child][1]));
      suffix.push_back(max(dp[child][0],dp[child][1]));
      }
    }
    for(int i=1;i<prefix.size();i++) prefix[i]+=prefix[i-1];
    for(int i=suffix.size()-2;i>=0;i--) suffix[i]+=suffix[i+1];
    dp[node][0]=suffix[0];
    int c=0;
    for(int child:tree[node]){
      if(child==par) continue;
      int lc=(c==0)?0:prefix[c-1];
      int rc=(c==suffix.size()-1)?0:suffix[c+1];
      dp[node][1]=max(dp[node][1],1+lc+rc+dp[child][0]);
      c++;
    }
}
int main(){
  fast_io;
  ll n;
  cin>>n;
  for(int i=1;i<n;i++){
    int u,v;
    cin>>u>>v;
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  solve(1,0);
  cout<<max(dp[1][0],dp[1][1]);

}
