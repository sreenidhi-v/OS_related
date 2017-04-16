#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct frame
{
	int x,timer;
	struct frame *next;
};

void fifo_or_lru(int n,int l,int s[],int option)
{
	
	//linked list creation start
	struct frame *root,*temp,*pre;
	int i=0,j;
	while(i<n)
	{
		temp=malloc(sizeof(struct frame));
		temp->next=NULL;
		temp->timer=-1;
		temp->x=-1;
		if(i==0)pre=root=temp;
		else
		{			
			pre->next=temp;
			pre=temp;
		}
		i++;
	}
	//linked list creation stop
	temp=root,i=0;
	int flag,replace=9999;
	for(i=0;i<l;i++)
	{	
		temp=root;flag=0;
		while(temp!=NULL)
		{
			if(temp->x==s[i]){ if(option==2)temp->timer=i; flag=1; break; }
			temp=temp->next;
		}
		if(!flag)	
		{	//page fault has occured
			temp=root;replace=9999; int check=0;
			while(temp!=NULL)
			{
				if(temp->x==-1)
				{	temp->x=s[i],temp->timer=i; check=1; break;
				}
				else
				{
					if(replace>temp->timer)replace=temp->timer,pre=temp;
					temp=temp->next;
				}
			}
			if(!check)pre->x=s[i],pre->timer=i;
			temp=root;
			while(temp!=NULL)
			{
				if(temp->x==-1)printf("_  ");
				else printf("%d  ",temp->x);
				temp=temp->next;
			}
			printf("\n");
		}
		
	}		
}
			
void optimal(int n,int *s,int l)
{
	//linked list creation start
	struct frame *root,*temp,*pre;
	int i=0,j;
	while(i<n)
	{
		temp=malloc(sizeof(struct frame));
		temp->next=NULL;
		temp->timer=-1;
		temp->x=-1;
		if(i==0)pre=root=temp;
		else
		{			
			pre->next=temp;
			pre=temp;
		}
		i++;
	}
	//linked list creation stop
	temp=root,i=0;
	int flag,replace=9999,found;
	for(i=0;i<l;i++)
	{	
		temp=root;flag=0;
		while(temp!=NULL)
		{
			if(temp->x==s[i]){ temp->timer=i; flag=1; break; }
			temp=temp->next;
		}
		if(!flag)	
		{	//page fault has occured
			temp=root;replace=9999; int check=0;
			while(temp!=NULL)
			{
				if(temp->x==-1)
				{	temp->x=s[i],temp->timer=i; check=1; break;
				}
				temp=temp->next;
			}
			if(!check)
			{
				temp=root;replace=-9999;
				while(temp!=NULL)	
				{
					for(j=i+1,found=0;j<l;j++)
					{
						if(temp->x==s[j]){
							found=1;  if(j>replace)replace=j,pre=temp; break;
						}
					}
					if(!found){	pre=temp; break; }		
					temp=temp->next;
				}
				pre->x=s[i],pre->timer=i;
			}

			temp=root;
			while(temp!=NULL)
			{
				if(temp->x==-1)printf("_  ");
				else printf("%d  ",temp->x);
				temp=temp->next;
			}
			printf("\n");
		}
		
	}		
		

}
int main()
{
	int opt=0,n,*s,i,l; char ch;
	s=malloc(30*sizeof(int));
	do
	{
		
		printf("\nEnter your choice:-\n1.Input data\n2.FIFO\n3.LRU\n4.Optimal page replacement\n5.Exit\n");
		scanf("%d",&opt);
		
		switch(opt)
		{
			case 1:	printf("\nEnter number of frames at a time: ");
				scanf("%d",&n);
				printf(" n is %d",n);
				printf("\nEnter size of string: ");
				scanf("%d",&l);
				printf("l is %d",l);
				printf("\nEnter reference string: ");
				for(i=0;i<l;i++)
				{
					scanf("%d",&s[i]);
				}
				
				break;
			case 2: fifo_or_lru(n,l,s,1);
				break;
			case 3: fifo_or_lru(n,l,s,2);
				break;
			case 4: optimal(n,s,l);
				break;
			case 5: opt=0;
				break;
			default:printf("Enter a valid choice.\n");
		}
	}while(opt);
	return 0;
}
