// Koustav Chowdhury 17CS10059

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

struct node
{
        int val;
        node *l,*r,*p;
};

node *newNode(int n)
{
        node *t=new node();
        t->val=n;
        t->l=t->r=t->p=NULL;
}

node *insert(node *root, node *t)
{
        if (root==NULL)
                return t;
        
        if (root->val < t->val)
        {
                root->r=insert(root->r,t);
                root->r->p=root;
        }
        
        else
        {
                root->l=insert(root->l,t);
                root->l->p=root;
        }
        
        return root;
}



void preorder(node *root)
{
        if (root==NULL)
                return;
        cout<<root->val<<" ";
        preorder(root->l);
        preorder(root->r);
}

void inorder(node *root)
{
        if (root==NULL)
                return;
        inorder(root->l);
        cout<<root->val<<" ";
        inorder(root->r);
}

void left_rotate(node **root,node **x)
{
        node *y=(*x)->r;
        (*x)->r=y->l;
        if (y->l!=NULL)
                y->l->p=(*x);
        y->p=(*x)->p;
        if ((*x)->p==NULL)
                *root=y;
        else
        {
                if ((*x)==(*x)->p->l)
                {
                        (*x)->p->l=y;
                }
                else
                {
                        (*x)->p->r=y;
                }
        }
        y->l=(*x);
        (*x)->p=y;
}

void right_rotate(node **root,node **x)
{
        node *y=(*x)->l;
        (*x)->l=y->r;
        if (y->r!=NULL)
                y->r->p=(*x);
        y->p=(*x)->p;
        if ((*x)->p==NULL)
                *root=y;
        else
        {
                if ((*x)==(*x)->p->l)
                {
                        (*x)->p->l=y;
                }
                else
                {
                        (*x)->p->r=y;
                }
        }
        y->r=(*x);
        (*x)->p=y;
        //(*x)=y;
}

void makeRoot(node *&root,node *&x)
{
        if (root==NULL)
                root=x;
                
        else
        {
                node *parent=x->p;
                if (parent->l==x)
                        right_rotate(&root,&parent);
                else
                        left_rotate(&root,&parent);
        }
}

void sameOrientation(node *&n,node *&p,node *&g,node *&root)
{
        if (g->l==p && g->l->l==n)
        {
                right_rotate(&root,&g);
                right_rotate(&root,&p);
        }
        else
        {
                left_rotate(&root,&g);
                left_rotate(&root,&p);
        }
}

void oppositeOrientation(node *&n,node *&p,node *&g, node *&root)
{
        if (p==g->l && n==p->r)
        {
                left_rotate(&root,&p);
                right_rotate(&root,&g);
        }
        else
        {
                right_rotate(&root,&p);
                left_rotate(&root,&g);
        }
}

void insert_sbst(node *&root,int m)
{
        node *n=newNode(m);
        root=insert(root,n);
        
        while (n!=root)
        {
                //Case 1 ::
                node *parent=n->p;
                node *g_parent=parent->p;
                if (g_parent==NULL)
                {
                       makeRoot(root,n); 
                }
                else
                {
                        if ((parent==g_parent->l && n==parent->r)|| (parent==g_parent->r && n==parent->l))
                        {
                                oppositeOrientation(n,parent,g_parent,root);
                        }
                        else
                        {
                                sameOrientation(n,parent,g_parent,root);
                        }
                        
                }
        }   
}

bool search(node *root,int n)
{
        bool found=false;
        node *t=root;
        while (t!=NULL)
        {       
                if (t->val < n)
                        t=t->r;
                else if (t-> val > n)
                        t=t->l;
                else
                        {
                                found=true;
                                break;
                        }
        }
        return found;
}

node *tbd(node *root,int n)
{
        //Assuming n is present and root!=NULL
        node *t=root;
        while (t->val!=n)
        {
                if (t->val < n)
                        t=t->r;
                else
                        t=t->l;
        }
        return t;
}

node *find_max(node *root)
{
        node *curr=root;
        while (curr->r!=NULL)
        {
                curr=curr->r;
        }
        return curr;
}

node *deleteNode(node *&root,int n)
{
        if (root==NULL)
                return NULL;
        if (root->val > n)
                root->l=deleteNode(root->l,n);
        else if (root->val < n)
                root->r=deleteNode(root->r,n);
        else// Found the required node
        {
                // Case 1: No child
                if (root->l==NULL && root->r==NULL)
                {
                        //free(root);
                        root=NULL;
                        return root;
                }
                // Case 2: Only one child
                if (root->l==NULL)
                {
                        node *tmp=root;
                        root=root->r;
                        //free(tmp);
                        return root;
                }
                
                if (root->r==NULL)
                {
                        node *tmp=root;
                        root=root->l;
                        //free(tmp);
                        return root;
                }
                
                // Case 3: Two children
                //Approach used-- Deleting the max node of the left subtree after copying it value
                
                node *t=find_max(root->l);
                root->val=t->val;
                root->l=deleteNode(root->l,t->val);   
                return root;    
        }
}

void delete_sbst(node *&root,int m)
{
        if (!search(root,m))
                cout<<m<<" is not in the tree\n";
        else
        {
               node *del=tbd(root,m);
               node *n=del->p;
               
               while (n!=root)
                {
                        //Case 1 ::
                        node *parent=n->p;
                        node *g_parent=parent->p;
                        if (g_parent==NULL)
                        {
                               makeRoot(root,n); 
                        }
                        else
                        {
                                if ((parent==g_parent->l && n==parent->r)|| (parent==g_parent->r && n==parent->l))
                                {
                                        oppositeOrientation(n,parent,g_parent,root);
                                }
                                else
                                {
                                        sameOrientation(n,parent,g_parent,root);
                                }
                                
                        }
                }
                node *del1=tbd(root,m);
                del1=deleteNode(root,m);
                //n=del1->p;
                
                
               
        }
}


int main()
{
        int n,x;
        cout<<"ENTER THE NUMBER OF NUMBERS :: ";
        cin>>n;
        node *root=NULL;
        cout<<"ENTER THE VALUES\n";
        for (int i=0;i<n;i++)
        {
                cin>>x;
                insert_sbst(root,x);
        }
        

        cout<<"PREORDER TRAVERSAL\n";
        preorder(root);
        cout<<"\n";
        
        cout<<"INORDER TRAVERSAL\n";
        inorder(root);
        cout<<"\n";
        
        cout<<"ENTER THE NUMBER TO BE DELETED :: ";
        cin>>x;

        delete_sbst(root,x);
        
        cout<<"PREORDER TRAVERSAL\n";
        preorder(root);
        cout<<"\n";
        
        cout<<"INORDER TRAVERSAL\n";
        inorder(root);
        cout<<"\n";
        
        
           
}


