#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,m,opt,i,j,k,cnt,flag,pid,x;
	int maxr[20],avai[20];					//maxr-maximum intances of each resource, avai-availability of resources
	int alloc[10][10],mneed[10][10],need[10][10];   // alloc- allocated resources, mneed- max need of every process, need=mneed-alloc
	int check[20];
	while(1)
	{
	printf("\n1.ENTER DETAILS\n2.PRINT DATA\n3.SAFETY SEQUENCE\n4.REQUEST BY A PROCESS\n5.EXIT\n");
	scanf("%d",&opt);
	switch(opt)
	{
		case 1:	printf("\nEnter the number of processes: ");	
			scanf("%d",&n);
			printf("\nEnter the number of resources: ");
			scanf("%d",&m);

			printf("\nEnter the maximum number of instances available for each resource:\n");
			for(i=0;i<m;i++)
			{
				printf("%d: ",i);
				scanf("%d",&maxr[i]);
			}
			printf("\nEnter the maximum requirements for every process against a resource:\n");
			for(i=0;i<n;i++)
			{
				for(j=0;j<m;j++)
				{
					scanf("%d",&mneed[i][j]); avai[j]=0; 
				}
				check[i]=0;
			}
		
			printf("\nEnter the allocated resources to each process against the resource:\n");
			for(i=0;i<n;i++)
			{
				for(j=0;j<m;j++)
				{
					scanf("%d",&alloc[i][j]);
					avai[j]+=alloc[i][j];
				}
				
			}		
			//finding avai[]
			for(i=0;i<m;i++)
			{
				avai[i]=maxr[i]-avai[i];
			}
			// finding need[][]
			for(i=0;i<n;i++)
			{
				for(j=0;j<m;j++)
				{
					need[i][j]=mneed[i][j]-alloc[i][j];
				}
			}	
			break;
		case 2: 
			printf("\n\nMaximum need table:\n");
			for(i=0;i<m;i++)
			{
				printf("     %d",i);
			}
			printf("\n");
			for(i=0;i<n;i++)
			{
				printf("P%d : ",i);
				for(j=0;j<m;j++)
				{
					printf("%d    ",mneed[i][j]);
				}
				printf("\n");
			}

			printf("\n\nAllocated table :\n");         
			for(i=0;i<m;i++)
			{
				printf("     %d",i);
			}
			printf("\n");
			for(i=0;i<n;i++)
			{
				printf("P%d : ",i);
				for(j=0;j<m;j++)
				{
					printf("%d    ",alloc[i][j]);
				}
				printf("\n");
			}
			printf("\n\nNeed table:\n");
			for(i=0;i<m;i++)
			{
				printf("     %d",i);
			}
			printf("\n");
			for(i=0;i<n;i++)
			{
				printf("P%d : ",i);
				for(j=0;j<m;j++)
				{
					printf("%d    ",need[i][j]);
				}
				printf("\n");
			}
			printf("\n");
			break;
		case 3: 
				// Banker's algorithm for collision avoidance.
				for(i=0,x=0,cnt=0;cnt!=n;x++)
				{
						for(flag=0,j=0;j<m && !check[i];j++)
						{
							if(need[i][j]>avai[j])
							{
								flag=1; break;
							}
						}
						if(!flag && !check[i])
						{
							printf("Process %d\n",i);
							check[i]=1;
							cnt++;
							
							for(k=0;k<m;k++)
							{
								avai[k]+=alloc[i][k];
							}
						}
						if(i==n-1)i=0;
						else i++;
						if(x==n*n && cnt!=n)
						{
							printf("\nSystem is unsafe\n");
							break;
						}

				}
			break;
		case 4: printf("\nEnter the process id of the process making a request: ");
			scanf("%d",&pid);
			printf("\nEnter the requirements of the process: ");
			for(j=0,flag=1;j<m;j++)
			{
				scanf("%d",&x);
				if(avai[j]>=x)
				{
					avai[j]-=x;
					alloc[pid][j]+=x;
					need[pid][j]-=x;
				}
				else
				{	flag=0;
					printf("\nRequested allocation can't be done since resources are insufficient!\n");
					break;
				}
			}
			if(!flag)break;
			else
			{
				for(i=pid,x=0,cnt=0;cnt!=n;x++)
				{
						if(i==n-1)i=0;
						else i++;
						for(flag=0,j=0;j<m && !check[i];j++)
						{
							if(need[i][j]>avai[j])
							{
								flag=1; break;
							}
						}
						if(!flag && !check[i])
						{
							printf("Process %d\n",i);
							check[i]=1;
							cnt++;
							
							for(k=0;k<m;k++)
							{
								avai[k]+=alloc[i][k];
							}
						}
						
						if(x==n*n*n && cnt!=n)
						{
							printf("\nSafety sequence can't be reached.\n");
							break;
						}	
				}
			}
			break;		
		case 5: exit(0);
	}
	}	
	
	return 0;
}	
 
