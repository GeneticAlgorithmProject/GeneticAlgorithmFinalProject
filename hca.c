#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void localSearch(int *p,int *g,int *c)
{

}
void paste(int *p,int p1,int *c1,int v)
{
	int i;
	for(i=0;i<=v;i++)
	{
		*(p+p1*(v+1)+i)=*(c1+i);
	}
}
void updatePopulation(int *p,int p1,int p2,int *c1,int *c2,int v)
{
	if((*c1)<(*(p+p1*(v+1))))
	{
		paste(p,p1,c1,v);
		if((*c2)<(*(p+p2*(v+1))))
		{
			paste(p,p2,c2,v);
		}
	}
	else if((*c2)<(*(p+p1*(v+1))))
	{
		paste(p,p1,c2,v);
		if((*c1)<(*(p+p2*(v+1))))
		{
			paste(p,p2,c1,v);
		}
	}
	else;
}
int getBestFitness(int *p,int v,int n)
{
	int i,min=*p;
	int who=0;
	for(i=1;i<n;i++)
	{
		if(min>*(p+i*(v+1)))
		{
			min=*(p+i*(v+1));
			who=i;
		}
	}
	return(who);
}
double getAverageFitness(int *p,int v,int n)
{
	int i;
	double sum=0.0;
	for(i=0;i<n;i++)
	{
		sum+=(double)*(p+i*(v+1));
	}
	sum/=n;
	return(sum);
}
void printResult(int *p,int v,int n)
{
	int best=getBestFitness(p,v,n);
	printf("Avg=%lf Best=%d ",getAverageFitness(p,v,n),*(p+best*(v+1)));
	int i;
	for(i=0;i<=v;i++)
	{
		printf("%d",*(p+best*(v+1)+i));
	}
	printf("\n");
}
void printAverageFitness(int *p,int v,int n)
{
	printf("Average Fitness=%lf\n",getAverageFitness(p,v,n));
}
int fitness(int *g,int *p,int v,int x)
{
	int i,j;
	int f=0;
	for(i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			if(i==j)continue;
			if((*(g+i*(v+1)+j)==1)&&(*(p+x*(v+1)+i)==*(p+x*(v+1)+j)))
			{
				f++;
				break;
			}
		}
	}
	return(f);
}
void simpleCrossover(int *g,int *p,int p1,int p2,int *c1,int *c2,int v)
{
	int i,r;
	srand(time(NULL));
	for(i=1;i<=v;i++)
	{
		r=rand()%2;
		if(r==0)
		{
			*(c1+i)=*(p+p1*(v+1)+i);
			*(c2+i)=*(p+p2*(v+1)+i);
		}
		else
		{
			*(c1+i)=*(p+p2*(v+1)+i);
			*(c2+i)=*(p+p1*(v+1)+i);
		}
	}
	*(c1)=fitness(g,c1,v,0);
	*(c2)=fitness(g,c2,v,0);
}
void randomSelectParents(int n,int *p1,int *p2)
{
	srand(time(NULL));
	*p1=rand()%n;
	*p2=rand()%n;
	while(*p1==*p2)
	{
		*p2=rand()%n;
	}
}
int condition(int *p,int v,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(*(p+i*(v+1))==0)
		{
			return(0);
		}
	}
	return(1);
}
int fileProcessing1(char *ptr)//get v
{
	FILE *fp;
	char temp[100];
	fp=fopen(ptr,"r");
	if(fp==NULL)perror("Error opening file.");
	else
	{
		while(!feof(fp))
		{
			if((fgets(temp,100,fp)!=NULL)&&(strcmp(temp,"p")==1))
			{
				char *tt;
				tt=strtok(temp," ");
				tt=strtok(NULL," ");
				if(strcmp(tt,"edge")==1)
				{
					//???
				}
				else
				{
					tt=strtok(NULL," ");
					fclose(fp);
					return(atoi(tt));
				}
			}
		}
	}
}
void fileProcessing2(int *g,int v,char *ptr)//get graph (matrix)
{
	FILE *fp;
	char temp[100];
	fp=fopen(ptr,"r");
	if(fp==NULL)perror("Error opening file.");
	else
	{
		int i,j;
		for(i=0;i<=v;i++)
		{
			*(g+i*(v+1))=v;
			for(j=1;j<=v;j++)
			{
				*(g+i*(v+1)+j)=0;
			}
		}
		while(!feof(fp))
		{
			if(fgets(temp,100,fp)==NULL)
			{
				break;
			}
			char *tt,*ss;
			tt=strtok(temp," ");
			if(strcmp(tt,"e")==0)
			{
				tt=strtok(NULL," ");
				ss=strtok(NULL," ");
				int t=atoi(tt);
				int s=atoi(ss);
				//printf("t=%d s=%d\n",t,s);
				*(g+t*(v+1)+s)=1;
				//printf("g[%d][%d]=%d\n",t,s,*(g+t*v+s));
			}
		}
		fclose(fp);
	}
}
int findDegree(int *g,int v,int l)
{
	int i;
	int degree=0;
	for(i=1;i<=v;i++)
	{
		degree+=*(g+l*(v+1)+i);
	}
	return(degree);
}
int findMaxDegree(int *g,int v,int *who)
{
	int i;
	int degree;
	int	max_degree=findDegree(g,v,*who);
	for(i=1;i<=v;i++)
	{
		degree=findDegree(g,v,i);
		if(max_degree<degree)
		{
			max_degree=degree;
			*who=i;
		}
	}
	return(max_degree);
}
void printPopulation(int *p,int n,int v)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<=v;j++)
		{
			printf("%d",*(p+i*v+j));
		}
		printf("\n");
	}
	printf("\n");
}
void init(int *p,int *g,int n,int v,int k)//do greedy search
{
    int i,j,l,m;
	srand(time(NULL));
	int max_degree=0;
	int max_who=0;
	max_degree=findMaxDegree(g,v,&max_who);
	
    for(i=0;i<n;i++)
    {
        //srand(time(NULL));
        int random;
		int record[v+1];
		int color[k+1];
		for(l=1;l<=v;l++)
		{
			record[l]=0;
			*(p+i*(v+1)+l)=0;
		}
		*(p+i*(v+1)+max_who)=1;//the vertex with max degree color 1
		record[max_who]=1;
		for(j=1;j<v;j++)
		{
			for(m=1;m<=k;m++)
			{
				color[m]=0;
			}
			//random select a vertex to color
			int r;
			r=rand()%v+1;
			while(record[r]==1)
			{
				r=r%v+1;
			}
		
			//check the neighbor adjacent to this vertex if colored
			for(m=1;m<=v;m++)
			{
				if((*(g+r*(v+1)+m)==1)&&(record[m]==1))//adjacent and colored neighbor
				{
					color[(*(p+i*(v+1)+m))]=1;
				}
				else if(*(g+r*(v+1)+m)==0)//not adjacent 
				{
					color[(*(p+i*(v+1)+m))]=-1;//ignore
				}
				else;//adjacent but not colored keep 0
			}

			int flag=0;
			for(m=1;m<=k;m++)
			{
				if(color[m]==0)//this color is not appeared in neighbor
				{
					*(p+i*(v+1)+r)=m;
					flag=1;
					break;
				}
			}
			if(flag==0)//color is exhausted
			{
				random=rand()%k+1;
				*(p+i*(v+1)+r)=random;
			}
			record[r]=1;
		}
		*(p+i*(v+1))=fitness(g,p,v,i);
    }
	printPopulation(p,n,v);
}
int main(int argc,char *argv[])
{
    if(argc!=6)
    {
        printf("population_size repeat_times localsearch_length file_name chromatic_number\n");
        return(-1);
    }
    int n=atoi(argv[1]);							//population size
    int repeat=atoi(argv[2]);						//repeat times
    int lsl=atoi(argv[3]);							//localsearch length
    char *ptr=argv[4];								//file name
    int k=atoi(argv[5]);							//chromatic number

    int v=fileProcessing1(ptr);						//get vertices number
    int *g=(int*)malloc(sizeof(int)*(v+1)*(v+1));
    fileProcessing2(g,v,ptr);						//get graph (matrix)
    int *p=(int*)malloc(sizeof(int)*n*(v+1));;		//n population, v = chromosome_length = vertices_number
    while(repeat>0)									//repeat r times
    {
        init(p,g,n,v,k);
        while(condition(p,v,n)==1)
        {
            int p1,p2,c1[v],c2[v];
            randomSelectParents(n,&p1,&p2);
            simpleCrossover(g,p,p1,p2,c1,c2,v);
            //localSearch(p,g,c1);
            //localSearch(p,g,c2);
            updatePopulation(p,p1,p2,c1,c2,v);
			//printPopulation(p,n,v);
			printResult(p,v,n);
        }
		repeat--;
    }
    return(0);
}
