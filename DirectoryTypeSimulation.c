#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct file
{
	char name[30];
	float size;
};
struct directory_s		// single level
{
	char name[30];
	int count;
	struct file list[20];
};
struct directory_t		// two level
{
	char name[30];
	int fcnt,dcnt;
	struct file flist[20];
	struct directory_s dlist[10];
};
struct treedir
{
	char name[30];
	int fcnt,dcnt,lcnt;
	struct file flist[5];	// file list
	struct file duplist[5]; // duplicate files/linked files
	char opath[5][30];	//original path <-> duplist[]
	struct treedir* dlist;  // directory list
};

void dir_s_level(struct directory_s* s)
{
	int opt=1,i;
	
	while(opt)
	{
		printf("\n1.Create a file\n2.List the files\nAny other number to go back.\n");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1: printf("\nEnter name of file: ");
				scanf("%s",s->list[s->count].name);
				printf("\nEnter size of file: ");
				scanf("%f",&s->list[s->count].size);
				s->count++;
				break;
			case 2: if(s->count==0)printf("\nNo files to be listed.");
				for(i=0;i<s->count;i++)
				{
					printf("\nNAME: %s",s->list[i].name);
					printf("\nSIZE: %f",s->list[i].size);
				}
				break;
			default: opt=0;
		}
	}
}
void dir_t_level(struct directory_t *s)
{
	int opt=1,i;
	while(opt)
	{
		printf("\n1.Create directory\n2.Create a file\n3.List all files\n4.List all directories\nAny other number to Go back\n");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1: printf("\nEnter directory name: ");
				scanf("%s",s->dlist[s->dcnt].name); s->dlist[s->dcnt].count=0;
				dir_s_level(&s->dlist[s->dcnt]);
				s->dcnt++;	
				break;
			case 2: printf("\nEnter file name: ");
				scanf("%s",s->flist[s->fcnt].name); 
				printf("\nEnter file size:");
				scanf("%f",&s->flist[s->fcnt].size);
				s->fcnt++;
				break;
			case 3: for(i=0;i<s->fcnt;i++)
				{
					printf("\nNAME: %s",s->flist[i].name);
					printf("\nSIZE: %f",s->flist[i].size);
				}
				break;
			case 4: for(i=0;i<s->dcnt;i++)
				{
					printf("\nNAME: %s",s->dlist[i].name);
				}
				break;
			default: opt=0;
		}
	}
}	
void dir_tree(struct treedir *s)
{
	int opt,ch,i;
	s->dlist=malloc(sizeof(struct treedir)*5);
	do
	{
		printf("\nCurrent directory: %s\n1.Create a file\n2.Create a directory\n3.List all files\n4.List all directories\nAny other number to Go back\n",s->name);
		scanf("%d",&opt);
		switch(opt)
		{
			case 1: printf("\nEnter name of file: ");
				scanf("%s",s->flist[s->fcnt].name);
				printf("\nEnter size of file: ");		
				scanf("%f",&s->flist[s->fcnt].size);
				s->fcnt++;
				break;
			case 2: 
				printf("\nEnter name of directory: ");
				scanf("%s",s->dlist[s->dcnt].name); s->dlist[s->dcnt].dcnt=0,s->dlist[s->dcnt].fcnt=0;
				printf("\nDo you want work on this directory? 1/0: ");
				scanf("%d",&ch); 
				if(ch)dir_tree(&s->dlist[s->dcnt]);
				s->dcnt++;
				break;
			case 3: for(i=0;i<s->fcnt;i++)
				printf("\nNAME: %s\nSIZE: %f",s->flist[i].name,s->flist[i].size);
				break;
			case 4: for(i=0;i<s->dcnt;i++)
				printf("\nNAME: %s",s->dlist[i].name);
				break;
			default:opt=0;
		}
	}while(opt);
}	
void dir_dag(struct treedir *s)
{
	int opt,ch,i;
	char temp[30];
	s->dlist=malloc(sizeof(struct treedir)*5);
	do
	{
		printf("\nCurrent directory: %s\n1.Create a file\n2.Create a directory\n3.List all files\n4.List all directories\n5.Link a file in some other directory\nAny other number to Go back\n",s->name);
		scanf("%d",&opt);
		switch(opt)
		{
			case 1: printf("\nEnter name of file: ");
				scanf("%s",s->flist[s->fcnt].name);
				printf("\nEnter size of file: ");		
				scanf("%f",&s->flist[s->fcnt].size);
				s->fcnt++;
				break;
			case 2: 
				printf("\nEnter name of directory: ");
				scanf("%s",s->dlist[s->dcnt].name); s->dlist[s->dcnt].dcnt=0,s->dlist[s->dcnt].fcnt=0;
				printf("\nDo you want work on this directory? 1/0 :");
				scanf("%d",&ch); 
				if(ch)dir_tree(&s->dlist[s->dcnt]);
				s->dcnt++;
				break;
			case 3: for(i=0;i<s->fcnt;i++)
				printf("\nNAME: %s\nSIZE: %f",s->flist[i].name,s->flist[i].size);
				break;
			case 4: for(i=0;i<s->dcnt;i++)
				printf("\nNAME: %s",s->dlist[i].name);
				break;
			case 5: printf("\nEnter the name of the file to be linked: ");
				scanf("%s",s->duplist[s->lcnt].name);
				
				printf("\nEnter directory the file exists in: ");
				scanf("%s",temp);
				strcpy(s->opath[s->lcnt],temp);
				strcat(s->opath[s->lcnt],"/");
				strcat(s->opath[s->lcnt],s->duplist[s->lcnt].name);
				printf("\nOriginal path to ");
				printf("%s",s->duplist[s->lcnt].name); 
				printf(" is %s .",s->opath[s->lcnt++]); break;
			default:opt=0;
		}
	}while(opt);
}			
int main()
{
	int opt;
	struct directory_s s1;
	struct directory_t s2;
	struct treedir s3;
	struct treedir s4;
	do
	{
		printf("\nCreate a directory of type:\n1.Single level directory\n2.Two level directory\n3.Tree-structured directory\n4.DAG\nAny other number to EXIT\n");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1: printf("\nEnter directory name: ");
				scanf("%s",s1.name); s1.count=0;
				dir_s_level(&s1);
				break;
			case 2: printf("\nEnter directory name: ");
				scanf("%s",s2.name); s2.fcnt=s2.dcnt=0;
				dir_t_level(&s2);
				break;
			case 3: printf("Enter directory name: ");
				scanf("%s",s3.name); s3.fcnt=s3.dcnt=0;
				dir_tree(&s3);
				break;
			case 4: printf("Enter directory name: ");
				scanf("%s",s4.name); s4.fcnt=s4.dcnt=s4.lcnt=0;
				dir_dag(&s4); 
				break;
			default:opt=0;
		}
	}while(opt);
	return 0;
}
