//Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct
{
        int id; //subpartID;
        int cpd;   //cost_per_day;
        int dur;   //duration;
}subd;//subpart_data

typedef struct
{
        int pid; //predecessorID;
        int sid; //successorID;
}dinfo; //dependencyinfo;

void combine(subd A[],int l,int m,int r)
{
        int s1=m-l+1;
        int s2=r-m;
        
        subd *P=new subd[s1];//first half
        subd *Q=new subd[s2];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        subd *C=new subd[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].cpd*Q[j].dur>Q[j].cpd*P[i].dur)
                        C[k++]=P[i++];
                else
                        C[k++]=Q[j++];
        }
        
        while (i<s1)
        {
                C[k++]=P[i++];
        }
        
        while (j<s2)
        {
                C[k++]=Q[j++];
        }
        
        for (i=l;i<=r;i++)
                A[i]=C[i-l];       
        
        delete []P;
        delete []Q;
        delete []C;
}

void superbsort(subd A[],int l,int r)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsort(A,l,m);
                superbsort(A,m+1,r);
                combine(A,l,m,r);
        }
}

void superbSorting(subd A[],int sizeOfA)
{
        superbsort(A,0,sizeOfA-1);
}

void printschedule(subd *job, int k)
{
        superbSorting(job,k);
        
        //for (int i=0;i<k;i++)
        //        cout<<job[i].id<<" "<<job[i].cpd<<" "<<job[i].dur<<"\n";
        
        int cst=0;
        int days=0;
        
        for (int i=0;i<k;i++)
        {
                days+=job[i].dur;
                
                cst+= (job[i].cpd)*days;
        }
        
        cout<<"Cost = "<<cst<<"\n";   
}

void printschedule1(subd *job, int k, dinfo *d ,int l)
{
        superbSorting(job,k);
        
        bool *vis=new bool[k+1];
        
        for (int i=0;i<=k;i++)
                vis[i]=false;
        
        int days=0;
        int cst=0;
        for (int i=0;i<k;i++)
        {
                int id=job[i].id;
                if (!vis[id])
                {
                        int pre=-1;
  
                        for (int j=0;j<l;j++)
                        {
                                if (d[j].sid==id)
                                {       
                                        pre=d[j].pid;
                                        break;
                                }
                        }
                        
                        if (pre!=-1 && !vis[pre])
                        {
                                for (int j=0;j<k;j++)
                                {
                                        if (job[j].id==pre)
                                        {
                                                days+=job[j].dur;
                                                cst+=(job[j].cpd)*days;
                                                vis[pre]=true;
                                                break;
                                        }
                                }
                        }
                        
                        days+=job[i].dur;
                        cst+=(job[i].cpd)*days;
                        vis[id]=true;    
                           
                }
        }
        
        /*for (int i=1;i<=k;i++)
        {
                if (vis[i])
                        cout<<i<<"$";
        }*/
        //cout<<"\n";
        //cout<<days<<"$\n";
        cout<<"Cost = "<<cst<<"\n";
        
        delete []vis;
}

int main()
{
        int k;
        cin>>k;
        subd *job=new subd[k];
        
        int *dur=new int[k];
        int *cost=new int[k];
        
        for (int i=0;i<k;i++)
                cin>>dur[i];
                
        for (int i=0;i<k;i++)
                cin>>cost[i];
                
        for (int i=0;i<k;i++)
        {
                job[i].id=i+1;
                job[i].cpd=cost[i];
                job[i].dur=dur[i];
        }
        
       printschedule(job,k);
       
        int l;
        cin>>l;
        dinfo *d=new dinfo[l];
        for (int i=0;i<l;i++)
                cin>>d[i].pid>>d[i].sid;
     
        printschedule1(job,k,d,l);
        
}
