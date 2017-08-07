// Shalin Shah

#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef vector<lli> polynomial;

// TODO: Pass references to vectors instead of entire vectors to speed up the code

// Modpow in O(logn)
lli fp(lli a,lli n,lli mod)
{
    if(n==0) return 1;
    if(n==1) return a;
    
    lli half=fp(a,n/2,mod);
    if(n%2==0)
        return (half*half)%mod;
    else return (a*((half*half)%mod))%mod;
}

// Modular inverse of x when p is a prime is x^(p-2) mod p
lli modInverse(lli x,lli p)
{
	return fp(x,p-2,p);
}

// Removes leading zeroes from the polynomial and reduces it's size. 
polynomial trimZeros(polynomial fx)
{
	lli len=fx.size(),i,j,k;
	polynomial ret;
	for(i=0;i<len;i++)
	{
		if(fx[i]!=0)
			break;
	}
	for(j=i;j<len;j++)
		ret.pb(fx[j]);
	return ret;
}

// Divides fx by gx
// TODO: Insert assert statements to check if leading coefficient of divisor is 1
pair<polynomial,polynomial> dividePolynomials(polynomial fx,polynomial gx,lli p)
{
	polynomial quot,rem;
	lli len1=fx.size(),len2=gx.size(),i,j,k;
	lli quotsize=len1-len2+1;
	for(i=0;i<quotsize;i++)
	{
		quot.pb(fx[i]);
		for(j=0;j<len2;j++)
		{
			fx[i+j]=(fx[i+j]-(quot[i]*gx[j])%p+p)%p;
		}
	}
	rem=fx;
	return mp(quot,rem);
}

// Euclid's algorithm for GCD of two polynomials
polynomial gcdPolynomials(polynomial fx,polynomial gx,lli p)
{
	lli len1=fx.size(),len2=gx.size(),i,j,k;
	if(len1<len2)
	{
		polynomial temp=fx;
		fx=gx;
		gx=temp;
		swap(len1,len2);
	}

	// This loop stops when the divisor becomes 0
	// FIXME: Here if size becomes 0, then gx[0] gives a segfault. 
	while(gx.size()>1 or gx[0]>0)
	{
		if(gx[0]!=1)
		{
			lli invmod=modInverse(gx[0],p);
			for(i=0;i<fx.size();i++)
			{
				fx[i]=(fx[i]*invmod)%p;
			}
			for(i=0;i<gx.size();i++)
			{
				gx[i]=(gx[i]*invmod)%p;
			}
		}
		pair<polynomial,polynomial> quotrem=dividePolynomials(fx,gx,p);

		fx=gx;
		gx=quotrem.se;

		fx=trimZeros(fx);
		gx=trimZeros(gx);
	}
	return fx;
}

// Calculates f(x+a) from f(x)
polynomial shiftPolynomial(polynomial fx,lli a,lli p)
{
	lli i,j,k,len=fx.size();
	polynomial ret;
	ret.pb(fx[0]);
	for(i=1;i<len;i++)
	{
		polynomial temp=ret;
		temp.pb(fx[i]);
		for(j=0;j<ret.size();j++)
		{
			temp[j+1]=(temp[j+1]+(ret[j]*a)%p)%p;
		} 
		ret=temp;
	}
	return ret;
}

polynomial factorizePolynomial(polynomial fx,lli p,lli shift)
{
	lli i,j,k,len=fx.size();

	// Generate a random number
	lli randomNumber=rand()%p;

	// Shift the polynomial f(x) to f(x+randomNumber)
	polynomial shiftedPoly=shiftPolynomial(fx,randomNumber,p);

	// Repeat the process recursively
	polynomial halfRoots((p+1)/2,0);
	halfRoots[0]=1;
	halfRoots[(p-1)/2]=p-1;
	polynomial gcd=gcdPolynomials(shiftedPoly,halfRoots,p);
	pair<polynomial,polynomial> remainingPoly=dividePolynomials(shiftedPoly,gcd,p);

	lli sz=gcd.size();
	polynomial factors;
	if(sz==2)
	{
		factors.pb((p-gcd[1]+randomNumber+shift)%p);
	}
	else if(sz>2)
	{
		polynomial remainingFactors=factorizePolynomial(gcd,p,(randomNumber+shift)%p);
		factors.insert(factors.end(),remainingFactors.begin(),remainingFactors.end());
	}
	sz=remainingPoly.fi.size();
	if(sz==2)
	{
		factors.pb((p-remainingPoly.fi[1]+randomNumber+shift)%p);
	}
	else if(sz>2)
	{
		polynomial remainingFactors=factorizePolynomial(remainingPoly.fi,p,(randomNumber+shift)%p);
		factors.insert(factors.end(),remainingFactors.begin(),remainingFactors.end());
	}
	return factors;
}

polynomial addPolynomials(polynomial fx,polynomial gx,lli p)
{
	lli i,j,k,len1=fx.size(),len2=gx.size();
	reverse(fx.begin(),fx.end());
	reverse(gx.begin(),gx.end());
	polynomial ret;
	for(i=0;i<max(len1,len2);i++)
	{
		lli temp=0;
		if(i<len1)
			temp=(temp+fx[i])%p;
		if(i<len2)
			temp=(temp+gx[i])%p;
		ret.pb(temp);
	}
	reverse(ret.begin(),ret.end());
	return ret;
}

polynomial subtractPolynomials(polynomial fx,polynomial gx,lli p)
{
	lli i,j,k,len1=fx.size(),len2=gx.size();
	reverse(fx.begin(),fx.end());
	reverse(gx.begin(),gx.end());
	polynomial ret;
	for(i=0;i<max(len1,len2);i++)
	{
		lli temp=0;
		if(i<len1)
			temp=(temp+fx[i])%p;
		if(i<len2)
			temp=(temp-gx[i]+p)%p;
		ret.pb(temp);
	}
	reverse(ret.begin(),ret.end());
	return ret;
}

// TODO: Speed it up by using FFT in O(nlogn) instead of brute-force in O(n^2)
polynomial multiplyPolynomials(polynomial fx,polynomial gx,lli p)
{
	lli i,j,k,len1=fx.size(),len2=gx.size();
	polynomial ret(len1+len2-1);
	for(i=0;i<len1;i++)
	{
		for(j=0;j<len2;j++)
		{
			ret[i+j]=(ret[i+j]+(fx[i]*gx[j])%p)%p;
		}
	}
	return ret;
}

// TODO: Pretty print the polynomial
void printPolynomial(polynomial fx)
{
	int i,j,k,len=fx.size();
	for(i=0;i<len;i++)
		cout<<fx[i]<<" ";
	cout<<endl;
}

// Primality Testing
bool isPrime(lli n)
{
	if(n<=3)
		return (n>1);
	else if(n%2==0 || n%3==0)
		return 0;
	else
	{
		lli i,root=sqrt(n)+1;
		for(i=5;i<root;i=i+6)
		{
			if(n%i==0 || n%(i+2)==0)
				return 0;
		}
	}
	return 1;
}

int main()
{
	while(1)
	{
		cout<<endl<<endl<<endl;
		// Menu
		cout<<"1: Add two polynomials\n2: Subtract two polynomials\n3: Multiply two polynomials\n4: Divide two polynomials\n5: Find GCD of two polynomials\n6: Factorize a polynomial\n7: Exit\nChoose: ";
		lli input;
		cin>>input;
		if(input>=1 and input<=5)
		{
			lli p,i,j,k;
			cout<<"Enter a prime: ";
			cin>>p;

			// Check if the number entered is a prime or not
			if(!isPrime(p))
			{
				cout<<"It is not a prime."<<endl;
				continue;
			}
			polynomial fx,gx;
			lli deg1,deg2;
			cout<<"Enter degree of fx: ";
			cin>>deg1;
			cout<<"Enter degree of gx: ";
			cin>>deg2;
			cout<<"Enter coefficients of fx in decreasing order of power: ";
			for(i=0;i<=deg1;i++)
			{
				lli temp;
				cin>>temp;
				while(temp<0)
					temp+=p;
				temp%=p;
				fx.pb(temp);
			}
			cout<<"Enter coefficients of gx in decreasing order of power: ";
			for(i=0;i<=deg2;i++)
			{
				lli temp;
				cin>>temp;
				while(temp<0)
					temp+=p;
				temp%=p;
				gx.pb(temp);
			}
			polynomial poly;

			// TODO: Make it cleaner by adding switch cases instead of if-else

			if(input==1)
			{
				poly=addPolynomials(fx,gx,p);
				cout<<"The addition is: ";
				printPolynomial(poly);
			}
			else if(input==2)
			{
				poly=subtractPolynomials(fx,gx,p);
				cout<<"The subtraction is: ";
				printPolynomial(poly);
			}
			else if(input==3)
			{
				poly=multiplyPolynomials(fx,gx,p);
				cout<<"The multiplication is: ";
				printPolynomial(poly);
			}
			else if(input==4)
			{
				// For ease of implementation, we multiply both the polynomials by the modular inverse of leading coefficient of divisor.
				if(gx[0]!=1)
				{
					lli invmod=modInverse(gx[0],p);
					for(i=0;i<fx.size();i++)
					{
						fx[i]=(fx[i]*invmod)%p;
					}
					for(i=0;i<gx.size();i++)
					{
						gx[i]=(gx[i]*invmod)%p;
					}
				}
				pair<polynomial,polynomial> quotrem=dividePolynomials(fx,gx,p);
				cout<<"The quotient is: ";
				printPolynomial(quotrem.fi);
				cout<<"The remainder is: ";
				printPolynomial(quotrem.se);
			}
			else if(input==5)
			{
				poly=gcdPolynomials(fx,gx,p);
				cout<<"The GCD is: ";
				printPolynomial(poly);
			}
		}
		else if(input==6)
		{
			lli p;
			cout<<"Enter a prime: ";
			cin>>p;
			if(!isPrime(p))
			{
				cout<<"It is not a prime."<<endl;
				continue;
			}
			polynomial poly;
			lli deg,i,j,k;
			cout<<"Enter degree of the polynomial: ";
			cin>>deg;
			cout<<"Enter coefficients of the polynomial in decreasing order of power: ";
			for(i=0;i<deg+1;i++)
			{
				lli temp;cin>>temp;
				while(temp<0)
					temp+=p;
				temp%=p;
				poly.pb(temp);
			}
			bool isZeroRoot=(poly[deg]==0);
			polynomial allRoots(p,0);
			allRoots[0]=1;
			allRoots[p-1]=p-1;

			// Finding gcd(fx, x^(p-1)-1)
			polynomial gcd=gcdPolynomials(poly,allRoots,p);

			polynomial factors;
			lli sz=gcd.size();
			if(sz==2)
			{
				factors.pb(p-gcd[1]);
			}
			else if(sz>2)
			{
				srand(time(NULL));
				factors=factorizePolynomial(gcd,p,0);
			}
			if(isZeroRoot)
				factors.pb(0);
			sz=factors.size();
			if(sz==0)
			{
				cout<<"No factors"<<endl;
			}
			else
			{
				sort(factors.begin(),factors.end());
				cout<<"The factors are: ";
				for(i=0;i<sz;i++)
					cout<<factors[i]<<" ";
				cout<<endl;
			}
		}
		else if(input==7)
			break;
	}
	return 0;
}
