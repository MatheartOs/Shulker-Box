#include <bits/stdc++.h>
using namespace std;
const long long mod=19260817;
long long n,m,x,l,r;
long long dis[200005];
long long pos[200005];
long long s[200005];
long long tmp; //由于最终核心公式和前缀和处理阶段都不需要存储下来每一个a[i]和d[i]，所以我们这里直接用tmp当做输入变量，用于前缀和处理阶段
int main()
{
	cin>>n>>m;
	for(int i=2;i<=n;i++) //这里直接从dis[2]开始处理是因为其代表1到2的距离，显然1到1的距离为0，因此从2开始处理
	{
		cin>>tmp; //读入d[i]的值
		dis[i]=((dis[i-1]%mod)+(tmp%mod))%mod;
	}
	//处理第一项
	cin>>tmp;
	s[1]=tmp; s[1]%=mod;
	pos[1]=((tmp%mod)*(dis[1]%mod))%mod;
	for(int i=2;i<=n;i++)
	{
		cin>>tmp; //读入a[i]的值
		pos[i]=(pos[i-1]%mod+((tmp%mod)*(dis[i]%mod))%mod)%mod;
		s[i]=((s[i-1]%mod)+(tmp%mod))%mod;
	}
	while(m--)
	{
		cin>>x>>l>>r;
		if(x>l&&x<r)
		{
			long long l1=l;
			long long r1=x-1;
			long long l2=x+1;
			long long r2=r;
			long long cost=0;
			cost+=((dis[x]*(s[r1]-s[l1-1])-(pos[r1]-pos[l1-1])+(pos[r2]-pos[l2-1])-dis[x]*(s[r2]-s[l2-1]))%mod+mod)%mod;
			cout<<cost<<endl;
			continue;
		}
		if(x>=r)
		{
			long long l1=l;
			long long r1=r;
			long long cost=0;
			cost+=((dis[x]*(s[r1]-s[l1-1])-(pos[r1]-pos[l1-1]))%mod+mod)%mod;
			cout<<cost<<endl;
			continue;
		}
		if(x<=l)
		{
			long long l2=l;
			long long r2=r;
			long long cost=0;
			cost+=(((pos[r2]-pos[l2-1])-dis[x]*(s[r2]-s[l2-1]))%mod+mod)%mod;
			cout<<cost<<endl;
			continue;
		}
	}
	return 0;
}
