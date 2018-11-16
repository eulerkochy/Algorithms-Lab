//Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

int max(int a, int b)
{
  return (a>b)?a:b;
}

int min(int a,int b)
{
  return (a<b)?a:b;
}

int findmindays(int n, int t)
{
  int ans;
  
  int **dp=new int*[n+1];
  
  for (int i=0;i<=n;i++)
  {
        dp[i]=new int[t+1];
  }
  for (int i=1;i<=n;i++)
    dp[i][0]=0;
  for (int i=1;i<=t;i++)
    dp[1][i]=i;

  for (int i=2;i<=n;i++)
  {
    for (int j=1;j<=t;j++)
    {
      int m=10000009;
      for (int k=1;k<=j;k++)
        m=min(m,max(dp[i-1][k-1],dp[i][j-k]));
      dp[i][j]=1+m;
    }
  }
  /*
  for (int i=1;i<=n;i++)
  {
    for (int j=1;j<=t;j++)
    {
        cout<<dp[i][j]<<" ";
        }
    cout<<"\n";
 }*/
  
  
  ans=dp[n][t];
  
  for (int i=0;i<=n;i++)
        delete[] dp[i];
  
  delete[] dp;
  
  return ans;
}

int nCr(int n, int r)
{
        int ans=1;
        for (int i=0;i<r;i++)
        {
                ans*=(n-i);
                ans/=(i+1);
        }
        return ans;
}

int sumnCr(int n, int t)
{
        int sum=0;
        for (int j=1;j<=t;j++)
        {
                sum+=nCr(n,j);
        }
        return sum;
}



int findmindaysfaster(int n,int t)
{
  
  int l=1,r=t;
  int m;
  while (l<r)
  {
        m=l+(r-l)/2;

        if (sumnCr(m,n)<t)
                l=m+1;
        else
                r=m;
  }
  return l;  
}

int findmindaysfast(int n, int t)
{
  int ans;
  
  int **dp=new int*[n+1];
  
  for (int i=0;i<=n;i++)
  {
        dp[i]=new int[t+1];
  }
  for (int i=1;i<=n;i++)
    dp[i][0]=0;
  for (int i=1;i<=t;i++)
    dp[1][i]=i;

  for (int i=2;i<=n;i++)
  {
    for (int j=1;j<=t;j++)
    {
      int m=10000009;
      /*for (int k=1;k<=j;k++)
        m=min(m,max(dp[i-1][k-1],dp[i][j-k]));*/
        int l=1,r=j,a,b;
        int mid;
        mid=l+(r-l)/2;
                a=dp[i-1][mid-1];
                b=dp[i][j-mid];
        while (l<r)
        {
                mid=l+(r-l)/2;
                a=dp[i-1][mid-1];
                b=dp[i][j-mid];
                //cout<<a<<"::"<<b<<"\n";
                int c=max(a,b);
                if (m>c)
                        {
                        l=mid+1;
                        m=c;
                        }
                else
                        r=mid;
        }
        
        
        dp[i][j]=(m!=10000009)?1+m:1+min(a,b);
    }
  }
  ans=dp[n][t];
  
  /*for (int i=1;i<=n;i++)
  {
    for (int j=1;j<=t;j++)
    {
        cout<<dp[i][j]<<" ";
        }
    cout<<"\n";
 }*/
  
  for (int i=0;i<=n;i++)
        delete[] dp[i];
  
  delete[] dp;
  
  return ans;
}


int main() {
  int n,t;
  cout<<"Enter n:";
  cin>>n;
  cout<<"Enter t:";
  cin>>t;
  cout<<"ANSWER::"<<findmindays(n,t)<<"\n";
  cout<<"Enter n:";
  cin>>n;
  cout<<"Enter t:";
  cin>>t;
  cout<<"ANSWER using DP::"<<findmindaysfast(n,t)<<"\n";// complexity O((n*T)logT)
  cout<<"ANSWER without DP:"<<findmindaysfaster(n,t)<<"\n";//complexity O((n^2)log T), much better
  
  
  
}
