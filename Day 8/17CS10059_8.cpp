// Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
using namespace std;

typedef struct score{
        int mscore;
        int escore;
}score, *scorelist;

void combinex(score A[],int l,int m,int r)
{
        int s1=m-l+1;
        int s2=r-m;
        
        score *P=new score[s1];//first half
        score *Q=new score[s2];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        score *C=new score[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].mscore<Q[j].mscore)
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

void superbsortx(score A[],int l,int r)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsortx(A,l,m);
                superbsortx(A,m+1,r);
                combinex(A,l,m,r);
        }
}

void combiney(score A[],int l,int m,int r)
{
        int s1=m-l+1;
        int s2=r-m;
        
        score *P=new score[s1];//first half
        score *Q=new score[s2];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        score *C=new score[s1+s2];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].escore<Q[j].escore)
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

void superbsorty(score A[],int l,int r)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsorty(A,l,m);
                superbsorty(A,m+1,r);
                combiney(A,l,m,r);
        }
}

int dist(score a, score b)
{
        return abs(a.mscore-b.mscore)+abs(a.escore-b.escore);
}

int combine(scorelist s, int n, int d, score *s1, score *s2)
{
        int curr_min=d;
        
        for (int i=0;i<n;i++)
        {
                for (int j=i+1;j<n && (s[j].escore-s[i].escore)<curr_min ;j++)
                {
                        int cmin=dist(s[j],s[i]);
                        if (cmin<curr_min && cmin>0 )
                        {
                                curr_min=cmin;
                                if (cmin < dist(*s1,*s2))
                                                {
                                                        *s1=s[i];
                                                        *s2=s[j];
                                                }
                                //cout<<curr_min<<":"<<s1->mscore<<","<<s1->escore<<":"<<s2->mscore<<","<<s2->escore<<"$\n";
                        }
                }
        }       
        
        return curr_min;
}

int near(scorelist Tx, scorelist Ty, int n, score *s1, score *s2)
{
        if (n<=3)
        {
                int min=5000;
                
                for (int i=0;i<n;i++)
                {
                        for (int j=i+1;j<n;j++)
                        {
                                int d=dist(Tx[i],Tx[j]);
                                if (d<min && d>0)
                                        {
                                                min=d;
                                                if (min < dist(*s1,*s2))
                                                {
                                                        *s1=Tx[i];
                                                        *s2=Tx[j];
                                                }
                                                //cout<<min<<":"<<s1->mscore<<","<<s1->escore<<":"<<s2->mscore<<","<<s2->escore<<"#\n";
                                        }
                        }
                }
                
                return min;
        }
        
        
    int mid = n/2; 
    score midPoint = Tx[mid]; 
    
    score *Tyl=new score[mid+1];   
    score *Tyr=new score[n-mid-1];
    
    int li = 0, ri = 0;
     
    for (int i = 0; i < n; i++) 
    { 
      if (Ty[i].mscore <= midPoint.mscore) 
         Tyl[li++] = Ty[i]; 
      else
         Tyr[ri++] = Ty[i]; 
    } 
 
    int dl = near(Tx, Tyl, mid,s1,s2); 
    int dr = near(Tx + mid, Tyr, n-mid,s1,s2); 
    int d = (dl<dr)? dl:dr; 
  
    score *strip=new score[n]; 
    
    int j = 0; 
    for (int i = 0; i < n; i++) 
        if (abs(Ty[i].mscore - midPoint.mscore) < d) 
            strip[j++] = Ty[i];
    
    score s3,s4;
             
    int ds=combine(strip, j, d, s1, s2);
    
    int min1;
    
    if (ds<d)
    {
        min1=ds;
    }
    else
    {
        min1=d;
        }
    
    return min1;         
        
}

int nearestProfiles(scorelist T, int n, score *s1, score *s2)
{
        scorelist fx=(scorelist)malloc(n*sizeof(score));//sorted according to mscore
        scorelist fy=(scorelist)malloc(n*sizeof(score));//sorted according to escore   
        for (int i=0;i<n;i++)
                fx[i]=fy[i]=T[i];
        
        superbsortx(fx,0,n-1);
        superbsorty(fy,0,n-1);
        
        return near(fx,fy,n,s1,s2);
        
     
}

int clustDist(scorelist P, int n, scorelist Q, int m, score *s1, score *s2)
{
        int min=5000;
        
        for (int i=0;i<n;i++)
        {
                for (int j=0;j<m;j++)
                {
                        int d=dist(P[i],Q[j]);
                        if (d<min && d>0)
                        {
                                min=d;
                                
                                if (min< dist(*s1,*s2))
                                {
                                        *s1=P[i];
                                        *s2=Q[j];
                                }
                        }
                }
        }
        
        return min;
}

/*
void combinex1(score2 A[],int l,int m,int r)
{
        int s1=m-l+1;
        int s2=r-m;
        
        score2 *P=new score2[10000];//first half
        score2 *Q=new score2[10000];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        score2 *C=new score2[20000];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].mscore<Q[j].mscore)
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
        //free(P),free(Q),free(C);
}

void superbsortx1(score2 A[],int l,int r)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsortx1(A,l,m);
                superbsortx1(A,m+1,r);
                combinex1(A,l,m,r);
        }
}

void combiney1(score2 A[],int l,int m,int r)
{
        int s1=m-l+1;
        int s2=r-m;
        
        score2 *P=new score2[10000];//first half
        score2 *Q=new score2[10000];//second half
        
        for (int i=l;i<=m;i++)
                P[i-l]=A[i];
        
        for (int i=m+1;i<=r;i++)
                Q[i-m-1]=A[i];
                
        score2 *C=new score2[20000];
        
        int i=0,j=0,k=0;
        
        while (i<s1 && j<s2)
        {
                if (P[i].escore<Q[j].escore)
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
        
       //free(P),free(Q),free(C);
        delete []P;
        delete []Q;
        delete []C;
}

void superbsorty1(score2 A[],int l,int r)
{
        if (l<r)
        {
                int m=l+(r-l)/2;
                superbsorty1(A,l,m);
                superbsorty1(A,m+1,r);
                combiney1(A,l,m,r);
        }
}

int dist1(score2 a, score2 b)
{
        return abs(a.mscore-b.mscore)+abs(a.escore-b.escore);
}

int combine1(scorelist2 s, int n, int d, score2 *s1, score2 *s2)
{
        int curr_min=d;
        
        for (int i=0;i<n;i++)
        {
                for (int j=i+1;j<n && (s[j].escore-s[i].escore)<curr_min ;j++)
                {
                        int cmin=dist1(s[j],s[i]);
                        if (cmin<curr_min && cmin>0 && (s[j].bucket^s[i].bucket)==1)
                        {
                                curr_min=cmin;
                                if (cmin < dist1(*s1,*s2))
                                                {
                                                        *s1=s[i];
                                                        *s2=s[j];
                                                }
                                //cout<<curr_min<<":"<<s1->mscore<<","<<s1->escore<<":"<<s2->mscore<<","<<s2->escore<<"$\n";
                        }
                }
        }       
        
        return curr_min;
}

int near1(scorelist2 Tx, scorelist2 Ty, int n, score2 *s1, score2 *s2)
{
        if (n<=3)
        {
                int min=5000;
                
                for (int i=0;i<n;i++)
                {
                        for (int j=i+1;j<n;j++)
                        {
                                int d=dist1(Tx[i],Tx[j]);
                                if (d<min && d>0 && (Tx[i].bucket ^ Tx[j].bucket)==1) //USING PROPERTIES OF XOR FOR BIPARTTITE MATCHING
                                        {
                                                min=d;
                                                if (min < dist1(*s1,*s2))
                                                {
                                                        *s1=Tx[i];
                                                        *s2=Tx[j];
                                                }
                                                //cout<<min<<":"<<s1->mscore<<","<<s1->escore<<":"<<s2->mscore<<","<<s2->escore<<"#\n";
                                        }
                        }
                }
                
                return min;
        }
        
        
    int mid = n/2; 
    score2 midPoint = Tx[mid]; 
    
    score2 *Tyl=new score2[mid+1];   
    score2 *Tyr=new score2[n-mid-1];
    
    int li = 0, ri = 0;
     
    for (int i = 0; i < n; i++) 
    { 
      if (Ty[i].mscore <= midPoint.mscore) 
         Tyl[li++] = Ty[i]; 
      else
         Tyr[ri++] = Ty[i]; 
    } 
 
    int dl = near1(Tx, Tyl, mid,s1,s2); 
    int dr = near1(Tx + mid, Tyr, n-mid,s1,s2); 
    int d = (dl<dr)? dl:dr; 
  
    score2 *strip=new score2[n]; 
    
    int j = 0; 
    for (int i = 0; i < n; i++) 
        if (abs(Ty[i].mscore - midPoint.mscore) < d) 
            strip[j++] = Ty[i];
    
    score s3,s4;
             
    int ds=combine1(strip, j, d, s1, s2);
    
    int min1;
    
    if (ds<d)
    {
        min1=ds;
    }
    else
    {
        min1=d;
        }
    
    return min1;         
        
}

int nearestProfiles1(scorelist2 T, int n, score2 *s1, score2 *s2)
{
        scorelist2 fx=(scorelist2)malloc(n*sizeof(score2));//sorted according to mscore
        scorelist2 fy=(scorelist2)malloc(n*sizeof(score2));//sorted according to escore   
        for (int i=0;i<n;i++)
                fx[i]=fy[i]=T[i];
        
        superbsortx1(fx,0,n-1);
        superbsorty1(fy,0,n-1);
        
        return near1(fx,fy,n,s1,s2);
        
     
}


int clustDist(scorelist P, int n, scorelist Q, int m, score *s1, score *s2)
{
        //int min=5000;
        
        //score f1,f2,g1,g2;
        
        scorelist2 C=new score2[n+m];
        
        for (int i=0;i<n;i++)
        {
                C[i].mscore=P[i].mscore;
                C[i].escore=P[i].escore;
                C[i].bucket=0;
        }
        
        for (int i=0;i<m;i++)
        {
                C[n+i].mscore=Q[i].mscore;
                C[n+i].escore=Q[i].escore;
                C[n+i].bucket=1;
        }
        
        score2 p1,p2;
        
        
        
        p1.mscore=-1;
        p1.escore=-1;
        
        p2.mscore=101;
        p2.escore=101;
        
        
        int d1=nearestProfiles1(C,n+m,&p1,&p2);
        
        s1->mscore=p1.mscore;
        s1->escore=p1.escore;
        
        s2->mscore=p2.mscore;
        s2->escore=p2.escore;
        
        /*g1.mscore=-1;
        g1.escore=-1;
        
        g2.mscore=101;
        g2.escore=101;
        
        int d2=nearestProfiles(Q,m,&g1,&g2);
        
        scorelist fx=(scorelist)malloc(n*sizeof(score));//sorted according to mscore
        scorelist fy=(scorelist)malloc(n*sizeof(score));//sorted according to escore   
        for (int i=0;i<n;i++)
                fx[i]=fy[i]=P[i];
        
        superbsortx(fx,0,n-1);
        superbsorty(fy,0,n-1);
        
        delete []C;

        return d1;
}

*/



int main()
{
        int n,m;
        cout<<"Enter the number of students:";
        cin>>n;
        
        scorelist f=(scorelist)malloc(n*sizeof(score));
        
        
        int a,b;
        for (int i=0;i<n;i++)
        {
                //cout<<"Enter math and english scores:";
                cin>>a>>b;
                f[i].mscore=a;
                f[i].escore=b; 
                //fx[i]=fy[i]=f[i];
        }
        
        
        
        score s1,s2;
        
        s1.mscore=-1;
        s1.escore=-1;
        
        s2.mscore=101;
        s2.escore=101;
        
        int d=nearestProfiles(f,n,&s1,&s2);
        
        cout<<"Closest pair : ("<<s1.mscore<<","<<s1.escore<<") and ("<<s2.mscore<<","<<s2.escore<<").\n";
        cout<<"Distance :"<<d<<"\n";
        
        
        /*cout<<"X\n";
        for (int i=0;i<n;i++)
        {
                cout<<fx[i].mscore<<","<<fx[i].escore<<"\n";
        }
        
        cout<<"Y\n";
        for (int i=0;i<n;i++)
        {
                cout<<fy[i].mscore<<","<<fy[i].escore<<"\n";
        }*/
        
        cout<<"Enter the size of the second cluster :";
        cin>>m;
        
        scorelist g=new score[m];
        
        for (int i=0;i<m;i++)
        {
                //cout<<"Enter math and english scores:";
                cin>>a>>b;
                g[i].mscore=a;
                g[i].escore=b;
        }
        
        score s3,s4;
        
        s3.mscore=-1;
        s3.escore=-1;
        
        s4.mscore=101;
        s4.escore=101;
        
        int d2=clustDist(f,n,g,m,&s3,&s4);
        
        cout<<"Closest pair : ("<<s3.mscore<<","<<s3.escore<<") and ("<<s4.mscore<<","<<s4.escore<<").\n";
        cout<<"Distance :"<<d2<<"\n";

}
