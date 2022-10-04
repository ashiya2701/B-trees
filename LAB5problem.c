//Name: ASHIYA KANDHWAY ENTRY NO=2020mcb1231
//All the following fucntions are implemented above main function
// • B-TREE-CREATE,
//• B-TREE-SPLIT-CHILD,
//• B-TREE-INSERT, (10 marks)
//• B-TREE-INSERT-NONFULL,
//• B-TREE-SEARCH, (5 marks)
//• B-TREE-MIN, (2 marks)
//• B-TREE-INORDER-TRAVERSE: this should traverse the B-tree and
//prints the keys of the B-tree in sorted order. (3 marks)
#include <stdio.h>
#include <stdlib.h>
//structure of Btree Node
typedef struct btreeNode{
	int *keys;
	int n;
	int leaf;
	struct btreeNode **C;
}btreeNode;
//structure of btree
struct btree{
	int t;
	btreeNode *root;	
};
//function tp create a btree
struct btree* create_tree(int tt){
	struct btree* r=(struct btree*)malloc(sizeof(struct btree));
	r->root=NULL;
	r->t=tt;
	return r;
}

// function to create nodes of btree
//• B-TREE-CREATE
btreeNode* create_node(struct btree* T){
    int t=T->t;
	btreeNode* x;
	x=(btreeNode*)malloc(sizeof(btreeNode));
	x->leaf=1;
	x->keys=(int*)malloc((2*t-1)*sizeof(int));
	x->C=(btreeNode**)malloc((2*t)*sizeof(btreeNode*));
	x->n=0;
	return x;
}
//• B-TREE-SPLIT-CHILD,
void split_child(btreeNode* x, int i,struct btree* T){
	int t=T->t;
	btreeNode* z;
	z=create_node(T);
	btreeNode* y= x->C[i];
	z->leaf=y->leaf;
	z->n=t-1;
	int j;
	for(j=0;j<t-1;j++){
		z->keys[j]=y->keys[j+t];
    }
	if(y->leaf!=1){
		for(j=0;j<t;j++){
			z->C[j]=y->C[j+t];
		}
	}
	y->n=t-1;
	for(j=x->n;j>=i+1;j--){
		x->C[j+1]=x->C[j];
	}
	x->C[i+1]=z;
	for(j=x->n-1;j>=i;j--){
		x->keys[j+1]=x->keys[j];
	}
	x->keys[i]=y->keys[t-1];
	x->n=x->n+1;
	
	
	
}
//• B-TREE-INSERT-NONFULL,

void insert_non_full(btreeNode* x,int k,struct btree* T){
	int t=T->t;
	int i=x->n-1;
	if(x->leaf==1){
		while(i>=0 && k<x->keys[i]){
			x->keys[i+1]=x->keys[i];
			i=i-1;
			
		}
		x->keys[i+1]=k;
		x->n=x->n+1;
		
	}
	else{
		while(i>=0 && k<x->keys[i]){
			i=i-1;
		}
		i=i+1;
		if(x->C[i]->n==2*t-1){
			split_child(x,i,T);
			if(k>x->keys[i])i=i+1;
			
		}
		insert_non_full(x->C[i],k,T);
	}
}
//• B-TREE-INSERT
btreeNode* insert(int k,struct btree* T){
	btreeNode* r=T->root;
	btreeNode* s;
	int t= T->t;
	if(T->root==NULL){
		btreeNode* rr=create_node(T);
		T->root=rr;
		T->root->keys[0]=k;
		T->root->n=1;
		
	}
	else{
		if(r->n==2*t-1){
			s=create_node(T);
			T->root=s;
			s->leaf=0;
			s->n=0;
			s->C[0]=r;
			split_child(s,0,T);
			insert_non_full(s,k,T);
	    }
	    else insert_non_full(r,k,T);
    }
	return T->root;
}
//• B-TREE-INORDER-TRAVERSE:
void InOrder(btreeNode* r){
	
	int i;
	if(r!=NULL){
		for(i=0;i<r->n;i++){
	//		printf(" leaf : %d \n",r->leaf);
	
			if(r->leaf==0)
		    InOrder(r->C[i]);
		    printf(" %d",r->keys[i]);
		}
		if(r->leaf==0)
		    InOrder(r->C[i]);
    }
	
}
//• B-TREE-SEARCH,
int BTree_Search(int k,btreeNode* r){
	int i=0;
	while(i<r->n && k>r->keys[i] )i++;
	if(r->keys[i]==k){
		return 1;
	}
	else if(r->leaf==1)return 0;
	return BTree_Search(k,r->C[i]);
}
//• B-TREE-MIN
int minimum_btree(btreeNode* r){
	if( r==NULL ){
		printf("Empty tree\n");
	//	return;
	}
	else if(r->leaf==1)return r->keys[0];
	else {
		int k=minimum_btree(r->C[0]);
		return k;
	} 
	
}

int main(){
	  printf("Enter the minimum degree of the B-tree t: ");
	  int t;
	  scanf("%d",&t);
	  printf("Enter A or B:");
	  char buff;
	  scanf("%c",&buff);
	  char c;
	  scanf("%c",&c);
	  struct btree* T=create_tree(t);
	  
	  
	  int i;
	  if(c=='A'){
	  	 for(i=100;i>=1;i--){
	  	 	T->root=insert(i,T);
	  	 	
		   }
		   InOrder(T->root);
		   printf("\n");
		   printf("Enter an element to search: ");
		   int s;
		   scanf("%d",&s);
		   int f=BTree_Search(s,T->root);
		   if(f==1)printf("Element is Present\n");
		   else if(f==0)printf("NOT PRESENT\n");
		   
	  }
	  else if(c=='B'){
	  	 // printf("Options: I for insertion, S for search, M for finding minimum, T for traversing the B-tree, E for exit:");
	  	  char ch;
	  	 
	  	 while(1){
	  	 	  printf("Options: I for insertion, S for search, M for finding minimum, T for traversing the B-tree, E for exit:");
	  	      char buff;
	  	      scanf("%c",&buff);
	          scanf("%c",&ch);
	  	  if(ch=='I'){
	  	  	printf("Enter number of elements you wanted to enter: ");
	  	  	int n;
	  	  	scanf("%d",&n);
	  	  	int j;
	  	  	printf("Enter the elements you wanted to enter: ");
	  	  	for(j=0;j<n;j++){
	  	  		int nn;
	  	  		scanf("%d",&nn);
	  	  		T->root=insert(nn,T);
	  	  		
				}
			}
		else if(ch=='T'){
			if(T->root==NULL){
				printf("Empty btree\n");
			}
			else{
			
			printf("Inorder traversal is:");
			InOrder(T->root);
			printf("\n");
			}
		}
		else if(ch=='S'){
		   if(T->root==NULL){
				printf("Empty btree\n");
			}
		   else{
		   
		   printf("Enter an element to search: ");
		   int ss;
		   scanf("%d",&ss);
		   int f=BTree_Search(ss,T->root);
		   if(f==1)printf("Element is Present\n");
		   else if(f==0)printf("NOT PRESENT\n");
		   }
		}
		else if(ch=='M'){
			if(T->root==NULL){
				printf("Empty btree\n");
			}
			else{
			
			int min=minimum_btree(T->root);
			printf("Minimum element is: %d\n",min);
		   }
		}
		else if(ch=='E'){
			break;
		}	
		else {
			printf("INVALID INPUT");
		}	
		}
	  }
	  else{
	      printf("Inavlid input");
	  }
  
	
}
// hello monu
