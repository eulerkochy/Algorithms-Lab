//Name:Koustav Chowdhury Roll no.17CS10059 PC no.15

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

/*

The subproblem that this program addresses is the following:
        dp[i][j] is the maximum success probability for completing i-th component of the project by j people

Recursive formulation used :

        Base case : for completing the first component, dp[1][j]=p[1][j], for 1<=j<=p
                                                                =0      , for j=0 
        dp[i][j]=0.0, if(j <i)
                =maximum for all k<=j (dp[i-1][j-k]*p[i][k]) ,otherwise
                
*/


int main()
{
        int n,p;
        cout<<"Enter N:";
        cin>>n;
        cout<<"Enter P:";
        cin>>p;
        double prob[1+n][1+p];
        double dp[1+n][1+p];
        int comp[1+n][1+p];
        
        cout<<"Enter the probabilities:\n";
        for (int i=1;i<=n;i++)
        {
                for (int j=1;j<=p;j++)
                        cin>>prob[i][j];
        }
        
        memset(dp,0.0,sizeof(dp));
        
        for (int i=1;i<=p;i++)
                dp[1][i]=prob[1][i],comp[1][i]=i;
        
        //for (int i=1;i<=n;i++)
        //        dp[i][0]=0.0;
                
        for (int i=2;i<=n;i++)
        {
                for (int j=1;j<=p;j++)
                {
                        for (int k=1;k<j;k++)
                        {
                                dp[i][j]=max(dp[i][j],dp[i-1][j-k]*prob[i][k]);
                                if (dp[i][j]==dp[i-1][j-k]*prob[i][k])
                                {
                                      //cout<<i<<"$"<<j<<"$"<<i-1<<"#"<<j-k<<"#"<<k<<"\n";
                                      comp[i][j]=k;
                                }
                        }
                }
        }
        cout<<"The maximum success probability is "<<dp[n][p]<<"\n";
        
        /*for (int i=1;i<=n;i++)
        {
                for (int j=1;j<=p;j++)
                        cout<<dp[i][j]<<" * ";
                cout<<"\n";
        }*/
        
        cout<<"Assignment of people for max probability:\n";
        int ans[n+1];
        
        int i=n,j=p;
        while (i!=1)
        {
                ans[i]=comp[i][p];
                p-=ans[i];
                i--;
        }
        ans[i]=p;
        
        for (int i=1;i<=n;i++)
                cout<<"Component "<<i<<": "<<ans[i]<<"\n";
        
}
