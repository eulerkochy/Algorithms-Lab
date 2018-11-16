// Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

#define MAX_SIZE 100

struct job {
        int jobId;
        int startTime;
        int jobLength;
        int remLength;
};

struct heap {
        job list[MAX_SIZE];
        int numJobs;
};

int prnt(int i)
{
        return (i/2);
}

int lch(int i)
{
        return 2*i;
}

int rch(int i)
{
        return 2*i+1;
}

bool check(job a, job b)
{
        if (a.remLength < b.remLength)
                return true;
        if (a.remLength == b.remLength)
                {
                        if (a.jobId < b.jobId)
                                return true;
                        else
                                return false;
                }
        return false;
}

void heapify_up(heap *H, int id)
{
        int i=id; 
        while (i>1 && !(check(H->list[prnt(i)],H->list[i])))
        {
                //swapping two jobs
                job t=H->list[prnt(i)];
                H->list[prnt(i)]=H->list[i];
                H->list[i]=t;
                
                i=prnt(i);
        }        
                
}

void heapify_down(heap *H, int i)
{
        int n=H->numJobs;
        int sm=i;
        int l=lch(i),r=rch(i);
        if (l<=n && check(H->list[l],H->list[sm]))
                sm=l;
        if (r<=n && check(H->list[r],H->list[sm]))
                sm=r;
        if (sm!=i)
        {
                //swapping two jobs
                job t=H->list[sm];
                H->list[sm]=H->list[i];
                H->list[i]=t;
                
                heapify_down(H,sm);
        }
}

void initHeap(heap *H)
{
        H->numJobs=0;
}

void insertJob(heap *H, job j)
{
        H->list[++(H->numJobs)]=j;
        heapify_up(H,H->numJobs);
}

int extractMinJob(heap *H, job *j)
{
        if (H->numJobs==0)
                return -1;
        
        H->list[1]=H->list[(H->numJobs)--];
        heapify_down(H,1);  
        return 0;   
}

void printheap(heap *H)
{
        int n=H->numJobs;
        cout<<"Printing heap containing "<<n<<" elements ::\n";
        for (int i=1;i<=n;i++)
        {
                cout<<(H->list[i]).remLength<<" :: "<<(H->list[i]).jobId<<"\n";
        }
}

void scheduler(job jl[],int n)
{
        // the scheduler will run for atmost the job time + summation of all jobLength
        int T=0;
        int i=0,curr=0;
        heap *H=new heap();
        initHeap(H);
        int trn=0;
        
        cout<<"Jobs scheduled at each timestep are:\n";
        while (i!=n || H->numJobs!=0)
        {
        
                if (T==jl[i].startTime)
                {
                        if (curr==0)//no jobs are running
                                {
                                        insertJob(H,jl[i]);
                                        curr=H->list[1].jobId;
                                }
                        else
                        {
                                insertJob(H,jl[i]);
                                curr=H->list[1].jobId;
                        }
                        i++;           
                }
                
                cout<<curr<<" ";
                if (H->list[1].remLength==H->list[1].jobLength)
                        {
                                //cout<<T+1<"$\n";
                                trn+=(T-H->list[1].startTime);
                        }
                
                (H->list[1]).remLength--;
                
                if (H->list[1].remLength==0)  
                {
                        job min;
                        if (extractMinJob(H,&min)==-1)
                                curr=0;
                                
                        else
                        {
                                min=H->list[1];
                                curr=min.jobId;
                        }
                }      
                T++; 
        }
        cout<<"\nAverage Turnaround Time is "<<double((1.0*trn)/n);
        cout<<"\n";
}

int main()
{
        int n;
        
        cout<<"Enter no. of jobs (n):";
        cin>>n;
        
        job jl[n];
        
        //heap *H=new heap();
        //initHeap(H);
        cout<<"Enter the jobs:\n";
        int a,b,c;
        for (int i=0;i<n;i++)
        {
                cin>>a>>b>>c;
                jl[i].jobId=a;
                jl[i].startTime=b;
                jl[i].jobLength=jl[i].remLength=c;
                //insertJob(H,jl[i]);
                //printheap(H);
        }
        
        //sorting jl according to value of startTime
        
        for (int i=0;i<n;i++)
        {
                for (int j=0;j<n-i-1;j++)
                {
                        if (jl[j].startTime > jl[j+1].startTime )
                        {
                                job t=jl[j+1];
                                jl[j+1]=jl[j];
                                jl[j]=t;
                        }
                }
        }
        
        /*//testing if the startTime is sorted
        
        for (int i=0;i<n;i++)
        {
                cout<<jl[i].startTime<<" ";
                cout<<"\n";
        }  */
        
        /*for (int i=0;i<n;i++)
        {
                insertJob(H,jl[i]);
                printheap(H);
        }     */
        
        scheduler(jl,n);
        
}
