// Shalin
#include <bits/stdc++.h>
using namespace std;
#define si(x) scanf("%d",&x)
#define slli(x) scanf("%lld",&x);
#define sc(x) scanf("%c",&x);
#define ss(x) scanf("%s",x);
#define sd(x) scanf("%lf",&x);
#define bitcount __builtin_popcount
#define gcd __gcd
#define llu long long unsigned int
#define lli long long int
#define fi first
#define se second
#define pb push_back
#define mod 1000000007
#define mp make_pair
#define vi vector<int>
#define vlli vector<long long int>
#define pii pair<int,int>

vector<int> addPoly(vector<int> const &a, vector<int> const &b, int p)
{
	vector<int> ret;
	int len1=a.size(),len2=b.size();
	for(int i=0;i<min(len1,len2);i++)
	{
		ret.pb((a[i]+b[i])%p);
		cout<<ret[i]<<" ";
	}
	int maxi=max(len1,len2);
	for(int i=min(len1,len2);i<maxi;i++)
	{
		if(maxi==len1)
			ret.pb(a[i]%p);
		else
			ret.pb(b[i]%p);
		cout<<ret[i]<<" ";
	}
	cout<<endl;
	return ret;
}

vector<int> subtractPoly(vector<int> const &a, vector<int> const &b, int p)
{
	vector<int> ret;
	int len1=a.size(),len2=b.size();
	for(int i=0;i<min(len1,len2);i++)
	{
		ret.pb((a[i]-b[i]+p)%p);
		cout<<ret[i]<<" ";
	}
	int maxi=max(len1,len2);
	for(int i=min(len1,len2);i<maxi;i++)
	{
		if(maxi==len1)
			ret.pb(a[i]%p);
		else
			ret.pb((0-b[i]+p)%p);
		cout<<ret[i]<<" ";
	}
	cout<<endl;
	return ret;
}

vector<int> multiplyPoly(vector<int> const &a, vector<int> const &b, int p)
{
	int len1=a.size(),len2=b.size();
    vector<int> ret(len1+len2-1);
 
   // Multiply two polynomials term by term
 
   // Take ever term of first polynomial
   for (int i=0; i<len1; i++)
   {
     // Multiply the current term of first polynomial
     // with every term of second polynomial.
     for (int j=0; j<len2; j++)
         ret[i+j]=(ret[i+j]+(a[i]*b[j])%p)%p;
   }
   int sz=ret.size();
   for(int i=0;i<sz;i++)
   	cout<<ret[i]<<" ";
   cout<<endl;
   return ret;
}


int main()
{
	//freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    vi poly1,poly2;
	int len1,len2,i,j,k,p;
	si(len1);si(len2);si(p);
	for(i=0;i<len1;i++)
	{
		int temp;
		si(temp);
		poly1.pb(temp);
	}
	for(i=0;i<len2;i++)
	{
		int temp;
		si(temp);
		poly2.pb(temp);
	}
	addPoly(poly1,poly2,p);
	subtractPoly(poly1,poly2,p);
	multiplyPoly(poly1,poly2,p);
}