#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
float sum, max, min, avg, median, sd; 	/* this data is shared by the thread(s) */

void *worker_sum(void *p); 		/* threads call this function */
void *worker_max(void *p); 
void *worker_min(void *p);
void *worker_avg(void *p);
void *worker_median(void *p);
void *worker_sd(void *p);

struct input
{ 
	char **data;
	 int count;
}in;

int main(int argc, char *argv[])
{
		int i;
		pthread_t tid,tid1,tid2,tid3,tid4,tid5; /* the thread identifier */

		pthread_attr_t attr;     /* set of thread attributes */

		/* get the default attributes */
		pthread_attr_init(&attr);
		/* create the thread */
		in.data=argv;
		in.count=argc;
		pthread_create(&tid5,&attr,worker_median,&in);
		pthread_create(&tid4,&attr,worker_sd,&in);
		pthread_create(&tid3,&attr,worker_avg,&in);
		pthread_create(&tid2,&attr,worker_min,&in);
		pthread_create(&tid1,&attr,worker_max,&in);
		pthread_create(&tid,&attr,worker_sum,&in);
		
		
		/* wait for the thread to exit */
		
		
		pthread_join(tid5,NULL);
		pthread_join(tid4,NULL);
		pthread_join(tid3,NULL);
		pthread_join(tid2,NULL);
		pthread_join(tid1,NULL);
		pthread_join(tid,NULL);
		
		
		printf("sum = %f\n\n",sum);
		printf("max = %f\n\n",max);
		printf("min = %f\n\n",min);
		printf("avg = %f\n\n",avg);
		
		printf("In sorted order: \n");
		for(i=1;i<in.count;i++)
		{
			printf("%s  ",in.data[i]);
		}
		printf("\nmedian = %f\n\n",median);
		printf("standard deviation = %f\n\n",sd);

}

/* The thread will begin control in this function */

void *worker_sum(void *param)
{
	struct input *t=(struct input *)param;
	int i;
	sum = 0;
	for (i = 1; i < t->count; i++)
	sum += atoi(t->data[i]);
	pthread_exit(0);

}

void *worker_max(void *param)
{
	struct input *t=(struct input *)param;	
	int i;
	max = atoi(t->data[1]);
	for (i = 2; i < t->count; i++)
	if (atoi(t->data[i])>max)
 	max=atoi(t->data[i]);
	pthread_exit(0);
}

void *worker_min(void *param)
{
	struct input *t=(struct input *)param;
	int i; 
	min=atoi(t->data[1]);
	for(i=2;i<t->count;i++)
	{
		if(atoi(t->data[i])<min)
		{
			min=atoi(t->data[i]);
		}
	}	
	pthread_exit(0);
}

void *worker_avg(void *param)
{
	struct input *t=(struct input *)param;
	avg=sum/(t->count - 1);
	pthread_exit(0);
}

void *worker_median(void *param)
{
	struct input *t=(struct input *)param;
	int i,j; char *temp;
	for(i=2;i<t->count;i++)
	{
		j=i-1; temp=t->data[i];
		while(j>=1 && atoi(t->data[j])>atoi(temp))
		{
			t->data[j+1]=t->data[j];
			j--;
		}
		t->data[j+1]=temp;
	}
		
	if((t->count-1)%2)
	{
		median=atoi(t->data[(t->count-1)/2 + 1]);
	}
	else
	{
		median=atoi(t->data[(t->count-1)/2])+atoi(t->data[(t->count-1)/2 + 1]);
		median/=2;
	}
	pthread_exit(0);
}
	
void *worker_sd(void *param)
{
	struct input *t=param;
	int i;  float s=0;
	for(i=1;i<t->count;i++)
	{
		s+=(atoi(t->data[i])-avg)*(atoi(t->data[i])-avg);
	}
	sd=sqrt(s/(t->count-1));
}	