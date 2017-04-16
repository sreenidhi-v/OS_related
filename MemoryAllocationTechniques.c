#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct block
{
	int blockid,inuse;;
	char fname[20];
	struct block* next;
	
};

struct i_block		// structure for indexed allocation
{
	int blockid;
	char fname[20];
	struct i_block *next;
	int inuse;
	int index[100];
};
int rand_lim(int limit)
{
/* return a random number between 0 and limit inclusive*/
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}
//contiguous file alloc
void co_alloc(int bcnt,int mmsize,int bsize)
{
	struct block *root,*temp,*pre,*p;
	int i,req_block,flag,opt,size;
	char na[20];
	//list creation starts
	for(i=0;i<bcnt;i++)
	{
		
		temp=malloc(sizeof(struct block));
		temp->blockid=i;
		temp->next=NULL;
		temp->inuse=0;
		if(i==0)root=pre=temp;
		else
		{
			pre->next=temp;
			pre=temp;
		}
	}
	//list creation ends

	do
	{
		printf("\nEnter name of the file: ");
		scanf("%s",na);
		printf("\nEnter size of file: ");
		scanf("%d",&size);
		if(size%bsize!=0)req_block=size/bsize + 1;
		else req_block=size/bsize;
		printf("\nRequired blocks for the file: %d\n",req_block);
		temp=root;
		flag=0;
		
		while(temp!=NULL && flag!=req_block)
		{
			if(!temp->inuse && bcnt-temp->blockid>=req_block)
			{
				
				while(temp!=NULL && flag!=req_block)
				{	printf("Block id: %d\t",temp->blockid); 
					flag++;
					temp->inuse=1;
					strcpy(temp->fname,na);
					temp=temp->next;					
				}
			}	
			if(temp!=NULL)temp=temp->next;
			
		}
		if(flag!=req_block)printf("\nInsufficient memory.");
		else printf("\nAllocated contiguous blocks\n");
		printf("\nDo you have more files to allot? 1/0\n");
		scanf("%d",&opt);
	}while(opt);
}

void l_alloc(int bcnt,int mmsize,int bsize)
{
	int i,j,req_block,size,usedb=0,opt;
	char na[20];
	struct block *pre;
	struct block *list=malloc(bcnt*sizeof(struct block));
	for(i=0;i<bcnt;i++)
	{
		list[i].blockid=i;
	}
	do
	{
		printf("\nEnter name of the file: ");
		scanf("%s",na);
		printf("\nEnter size of file: ");
		scanf("%d",&size);
		if(size%bsize!=0)req_block=size/bsize + 1;
		else req_block=size/bsize;
		printf("\nRequired blocks for the file: %d\n",req_block);
		if(bcnt-usedb>=req_block){
		for(j=0;j<req_block;)
		{		
			i=rand_lim(bcnt-1);
			while(list[i].inuse!=0 && usedb!=bcnt)
			{
				i=rand_lim(bcnt-1);
			}
			if(list[i].inuse==0 && j==0){ list[i].inuse=1;
			printf("Block id: %d\n",list[i].blockid); 
			j++; usedb++; 
			strcpy(list[i].fname,na); 
			list[i].next=NULL; 
			pre=&list[i];
			}
			else if(list[i].inuse==0 && j>0){ list[i].inuse=1; 
			printf("Block id: %d\n",list[i].blockid); 
			j++; usedb++; 
			strcpy(list[i].fname,na); 
			list[i].next=NULL; 
			pre->next=&list[i]; 
			pre=&list[i]; 
			}
		}
		}
		else printf("\nInsufficient memory");
		printf("\nDo you have more files to allot? 1/0\n");
		scanf("%d",&opt);
	}while(opt);
	
}

void i_alloc(int bcnt,int mmsize,int bsize)
{
		int i,opt,j,usedb,req_block,size,start;
		char na[20];
		struct i_block *list,*pre;
		list=malloc(bcnt*sizeof(struct i_block));	
		for(i=0;i<bcnt;i++)list[i].blockid=i;
		
		do
		{
			printf("\nEnter name of the file: ");
			scanf("%s",na);
			printf("\nEnter size of file: ");
			scanf("%d",&size);
			if(size%bsize!=0)req_block=size/bsize + 1;
			else req_block=size/bsize;
			printf("\nRequired blocks for the file: %d\n",req_block);
			if(bcnt-usedb>=req_block){
			for(j=0;j<req_block;)
			{		
				i=rand_lim(bcnt-1);
				while(list[i].inuse!=0 && usedb!=bcnt)
				{
					i=rand_lim(bcnt-1);
				}
				if(list[i].inuse==0 && j==0){ list[i].inuse=1;
				printf("Block id: %d\n",list[i].blockid); 
				j++; usedb++; 
				strcpy(list[i].fname,na); 
				list[i].next=NULL; 
				pre=&list[i];
				start=i;
				}
				else if(list[i].inuse==0 && j>0){ list[i].inuse=1; 
				printf("Block id: %d\n",list[i].blockid); 
				j++; usedb++; 
				strcpy(list[i].fname,na); 
				list[i].next=NULL; 
				pre->next=&list[i]; 
				pre=&list[i]; 
				list[start].index[j-1]=i; 
				
				}
			}
			printf("\nStarting block has following index table:\n");
			for(i=1;i<=req_block-1;i++)
			printf("%d  ",list[start].index[i]);
		}
		else printf("\nInsufficient memory");
		printf("\nDo you have more files to allot? 1/0\n");
		scanf("%d",&opt);
	}while(opt);
}
int main()
{
	int mmsize,bsize,bcnt,opt;
	do
	{	printf("\nFile Allocation Techniques: ");
		printf("\nEnter size of main memory: ");
		scanf("%d",&mmsize);
		printf("\nEnter size of a block: ");
		scanf("%d",&bsize);
		bcnt=mmsize/bsize;
		printf("\nChoose type of memory allocation:\n1.CONTIGUOUS\n2.LINKED\n3.INDEXED\n4.SKIP\n");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:co_alloc(bcnt,mmsize,bsize); break;
			case 2:l_alloc(bcnt,mmsize,bsize); break;
			case 3:i_alloc(bcnt,mmsize,bsize); break;
			default: opt=0;
		}
		printf("\nDo you want to continue with any allocation techniques? 1/0\n");
		scanf("%d",&opt);
	}while(opt);	
		
	return 0;
}		