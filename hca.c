#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void printResult(int *p,int v)
{}
bool condition(int *p,int v)
{}
void greedySearch(int *p,int *g,int v,int random)
{
	
}
void selectParents(int *p,int *g,int v,int *p1,int *p2)
{}
void crossover(int *g,int *p1,int *p2,int *c1,int *c2)
{}
void localSearch(int *p,int *g,int *c)
{}
void updatePopulation(int *p,int v,int *c1,int *c2)
{}
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
		for(i=0;i<v;i++)
		{
			for(j=0;j<=v;j++)
			{
				*(g+i*v+j)=0;
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
				*(g+t*v+s)=1;
				//printf("g[%d][%d]=%d\n",t,s,*(g+t*v+s));
			}
		}
		fclose(fp);
	}
}
int find_degree(int *g,int v,int l)
{
	int i;
	int degree=0;
	for(i=1;i<=v;i++)
	{
		degree+=*(g+l*v+i);
	}
	return(degree);
}
void init(int *p,int *g,int n,int v,int k)//do greedy search
{
    int i,j,l,m;
	srand(time(NULL));
	int degree[v+1];
	int max_degree=0;
	int max_who=0;
	for(l=1;l<=v;l++)
	{
		degree[l]=find_degree(g,v,l);
		if(max_degree<degree[l])
		{
			max_degree=degree[l];
			max_who=l;
		}
	}
    for(i=0;i<n;i++)
    {
        //srand(time(NULL));
        int random;
		int record[v+1];
		int color[k+1];
		for(l=1;l<=v;l++)
		{
			record[l]=0;
			*(p+i*v+l)=0;
		}
		*(p+i*v+max_who)=1;//the vertex with max degree color 1
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
				if((*(g+r*v+m)==1)&&(record[m]==1))//adjacent and colored neighbor
				{
					color[(*(p+i*v+m))]=1;
				}
				else if(*(g+r*v+m)==0)//not adjacent 
				{
					color[(*(p+i*v+m))]=-1;//ignore
				}
				else;//adjacent but not colored keep 0
			}

			int flag=0;
			for(m=1;m<=k;m++)
			{
				if(color[m]==0)//this color is not appeared in neighbor
				{
					*(p+i*v+r)=m;
					flag=1;
					break;
				}
			}
			if(flag==0)//color is exhausted
			{
				random=rand()%k+1;
				*(p+i*v+r)=random;
			}
			record[r]=1;
		}
		
		for(j=1;j<=v;j++)
		{
			printf("%d",*(p+i*v+j));
		}
		printf("\n");		
    }
}
int main(int argc,char *argv[])
{
    if(argc!=6)
    {
        printf("population_size repeat_times localsearch_length file_name chromatic_number\n");
        return(-1);
    }
    int n=atoi(argv[1]);//population size
    int repeat=atoi(argv[2]);//repeat times
    int lsl=atoi(argv[3]);//localsearch length
    char *ptr=argv[4];//file name
    int k=atoi(argv[5]);//chromatic number

    //printf("%d %d %d %s %d\n",n,r,lsl,ptr,k);
    int v=fileProcessing1(ptr);//get vertices number
    int *g=(int*)malloc(sizeof(int)*(v+1)*(v+2));
    fileProcessing2(g,v,ptr);//get graph (matrix)
    int *p=(int*)malloc(sizeof(int)*n*(v+1));;//n population, v = chromosome_length = vertices_number
    while(repeat>0)//repeat r times
    {
        init(p,g,n,v,k);
		/*
        while(condition(p,v)==true)
        {
            int p1[v],p2[v],c1[v],c2[v];
            selectParents(p,g,v,p1,p2);
            crossover(g,p1,p2,c1,c2);
            localSearch(p,g,c1);
            localSearch(p,g,c2);
            updatePopulation(p,v,c1,c2);
        }
        printResult(p,v);//need to implement; 
		*/
		repeat--;
    }
    return(0);
}
