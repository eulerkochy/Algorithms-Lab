#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct treenode
{
        char word[100];
        struct treenode *left;
        struct treenode *right;
        struct treenode *parent;
}node;

node *newNode(char str[])
{
        node *t=new node();
        int i=0;
        while (str[i]!='\0')
        {
                t->word[i]=str[i];
                i++;
        }
        t->word[i]='\0';
        t->left=t->right=t->parent=NULL;
}

node *insert(node *root,char str[])
{
        if (root==NULL)
                root=newNode(str);
                
        if (strcmp(root->word,str)>0)
        {
                root->left=insert(root->left,str);
                root->left->parent=root;        
        }
        
        if (strcmp(root->word,str)<0)
        {
                root->right=insert(root->right,str);
                root->right->parent=root;
        }
        return root;
}

void inorder(node *root)
{
        if (root==NULL)
                return ;
        inorder(root->left);
        printf("%s ",root->word);
        inorder(root->right);
}

bool isPrefix(char a[],char b[])
{
        //check if a is a prefix of b
        int sza=0,szb=0;
        while (a[sza++]!='\0');
        while (b[szb++]!='\0');
        sza--;
        szb--;
        //cout<<sza<<"$$"<<szb<<endl;
        //assert(sza<=szb);
        if (szb<sza)
                return false;
        for (int i=0;i<sza;i++)
                if (a[i]!=b[i])
                        return false;
        return true;
}

void find_extensions(node *root,char str[])
{
        node *x,*y,*z;
        x=root;
        //asumming str is the prefix of atleast one argument
 
        if(root == NULL)
                return; 
 
          x= root;
          while (x!= NULL)
          {                 
            if (x->left == NULL)
            {
              if (isPrefix(str,x->word))
                        cout<<x->word<<" ";        
              x=x->right;      
            }    
            else
            {
              y=x->left;//stores the pointer where it diverges
              while (y->right !=NULL && y->right != x) //either reach the right-most node or the diverging point
                y= y->right;
              if (y->right == NULL)
              {
                //using the property that right-most node will have it's right pointer empty, to store the diverging point
                y->right=x;
                x= x->left;
              }  
              else 
              {
                y->right = NULL;
                if (isPrefix(str,x->word))
                        cout<<x->word<<" ";
                x=x->right;      
              }
            } 
          }  
}

node *find_max(node *root)
{
        node *curr=root;
        while (curr->right!=NULL)
        {
                curr=curr->right;
        }
        return curr;
}

node *deleteNode(node *root,char str[])
{
        if (root==NULL)
                return NULL;
        if (strcmp(root->word,str)>0)
                root->left=deleteNode(root->left,str);
        else if (strcmp(root->word,str)<0)
                root->right=deleteNode(root->right,str);
        else// Found the required node
        {
                // Case 1: No child
                if (root->left==NULL && root->right==NULL)
                {
                        //free(root);
                        root=NULL;
                        return root;
                }
                // Case 2: Only one child
                if (root->left==NULL)
                {
                        node *tmp=root;
                        root=root->right;
                        //free(tmp);
                        return root;
                }
                
                if (root->right==NULL)
                {
                        node *tmp=root;
                        root=root->left;
                        //free(tmp);
                        return root;
                }
                
                // Case 3: Two children
                //Approach used-- Deleting the max node of the left subtree after copying it value
                
                node *t=find_max(root->left);
                strcpy(root->word,t->word);
                root->left=deleteNode(root->left,root->word);   
                return root;    
        }
}

/*
node *delete_prefix(node *root, char str[])
{
        node *x,*y,*z;
        x=root;
        //asumming str is the prefix of atleast one argument
 
        if(root == NULL)
                return NULL; 
 
          x= root;
          while (x!= NULL)
          {                 
            if (x->left == NULL)
            {
              node *t=x->right;
              if (isPrefix(str,x->word))
                        root=deleteNode(root,x->word);              
              x=t;      
            }    
            else
            {
              y=x->left;//stores the pointer where it diverges
              while (y->right !=NULL && y->right != x) //either reach the right-most node or the diverging point
                y= y->right;
              if (y->right == NULL)
              {
                //using the property that right-most node will have it's right pointer empty, to store the diverging point
                y->right=x;
                x= x->left;
              }  
              else 
              {
                y->right = NULL;
                node *t=x->right;
                if (isPrefix(str,x->word))
                        root=deleteNode(root,x->word);
                x=t;      
              }
            } 
          } 
}
*/
void delete_prefix(node **root, char str[])
{
        if (*root==NULL)
                return;
       delete_prefix(&((*root)->left),str);
       if (isPrefix(str,(*root)->word))
                *root=deleteNode(*root,(*root)->word);
       delete_prefix(&((*root)->right),str);
}


int main()
{
        int n;
        cin>>n;
        node *root=NULL;
        char in[100];
        for (int i=0;i<n;i++)
        {
                scanf("%s",in);
                root=insert(root,in);
        }
        
        cout<<"\nInorder traversal:\n";
        inorder(root);
        cout<<endl;
        char pat[100];
        scanf("%s",pat);
        cout<<"\nAll extensions of '"<<pat<<"' in lexicographic order:\n";
        find_extensions(root,pat);
        cout<<endl;
        
        for (int i=0;i<n;i++)
                delete_prefix(&root,pat);
        cout<<"\nInorder traversal after delete:\n";
        inorder(root);
        cout<<endl;
    
}

