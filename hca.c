/*
1. g[0][i] degree of vertex i
2. g[i][j]=g[j][i]=1 if vertex i and vertex j adjacent
3. if (p[0][i]=1) => do not change the color of vertex i during localsearch
4. p[i][j] population i's jth vertex's color 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void localSearch(int *g,int *p,int v,int *c,int l,int k)
{
	int i,j;
    int t[v+1];//count conflict number
	for(i=1;i<=v;i++)
	{
		t[i]=0;
	}
    srand(time(NULL));
    while(l>0)
    {
    	int max=0;//max conflict
    	int maxi=0;//max conflict index
    	for(i=1;i<=v;i++) 
    	{
        	for(j=1;j<=v;j++) 
        	{
        	    if((*(g+i*(v+1)+j)==1)&&(*(c+i)==*(c+j))) 
        	    {
        	        t[i]++;
        	        t[j]++;
        	    }
        	}
    	}
    	for(i=1;i<=v;i++) 
    	{
        	if(*(t+i)>=max) 
        	{
        	    max=*(t+i);
        	    maxi=i;
        	}
    	}
		int temp=rand()%k+1;
    	while(*(c+maxi)==temp)
    	{
			temp=rand()%k+1;
    	}
		*(c+maxi)==temp;
    	l--;
    }
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
int getWorstOne(int *p,int v,int n)
{
	int i,max=*(p+1*(v+1));
	int who=1;
	for(i=2;i<=n;i++)
	{
		if(max<*(p+i*(v+1)))
		{
			max=*(p+i*(v+1));
			who=i;
		}
	}
	return(who);
}
int getBestOne(int *p,int v,int n)
{
	int i,min=*(p+1*(v+1));
	int who=1;
	for(i=2;i<=n;i++)
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
	for(i=1;i<=n;i++)
	{
		sum+=(double)*(p+i*(v+1));
	}
	sum/=n;
	return(sum);
}
void printWorstFitness(int *p,int v,int n)
{
	int worst=getWorstOne(p,v,n);
	printf("Max=%d ",*(p+worst*(v+1)));
}
void printAverageFitness(int *p,int v,int n)
{
	printf("Avg=%.2lf ",getAverageFitness(p,v,n));
}
void printBestFitness(int *p,int v,int n)
{
	int best=getBestOne(p,v,n);
	printf("Min=%d ",*(p+best*(v+1)));
}
void printBestPopulation(int *p,int v,int n)
{
	int i;
	int best=getBestOne(p,v,n);
	for(i=1;i<=v;i++)
	{
		printf("%d",*(p+best*(v+1)+i));
	}
}
void printResult(int *p,int v,int n,int gen)
{
	printf("Generation:%d ",gen);
	printBestFitness(p,v,n);
	printAverageFitness(p,v,n);
	printWorstFitness(p,v,n);
	printBestPopulation(p,v,n);
	printf("\n");
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
	*p1=rand()%n+1;
	*p2=rand()%n+1;
	while(*p1==*p2)
	{
		*p2=rand()%n+1;
	}
}
void uniformArray(int *array,int n)
{
	srand(time(NULL));
	int* base = (int*)malloc(sizeof(int)*(n+1));
	int i,j;
	for(i=1;i<=n;i++)
		base[i]=i;
	for(i=1;i<=n;i++){
		j=rand()%(n+1-i);
		array[i] = base[j];
		base[j] = base[i];
	}
	free(base);
}
void tournamentSelection(int *p,int v,int *pool,int s,int n)
{
	srand(time(NULL));
	int i,j,m;
	int array[n+1];
	int record[n+1];
	for(i=0;i<s;i++)
	{
		for(j=1;j<=n;j++)
		{
			record[j]=0;
		}
		for(j=1;j<=n;j++)//random array
		{
			int s1=rand()%n;
			while(record[s1]==1)
			{
				s1=(s1+1)%n;
			}
			record[s1]=1;
			array[j]=s1;
		}
		for(j=1;j<=n;j+=s)//selection
		{
			int winnerFitness=*(p+array[j]*(v+1));
			int winner=j;
			for(m=1;m<s;m++)
			{
				if(winner>*(p+array[j+m]*(v+1)))
				{
					winnerFitness=*(p+array[j+m]*(v+1));
					winner=j+m;
				}
			}
			int a;
			for(a=0;a<=v;a++)
			{
				*(pool+i*(n/s)*(v+1)+a)=*(p+winner*(v+1)+a);
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=v;j++)
		{
			*(p+i*(v+1)+j)=*(pool+i*(v+1)+j);
		}
	}
	/*
	for(i=0;i<n;i++){
		int winner = randomarray[0][i];
		int WinnderFitness =  *(p+winner*(v+1));
		
		int challenger = randomarray[1][i];
		int ChallengerFitness = *(p+challenger*(v+1));
		if(ChallengerFitness > WinnderFitness){
			winner = challenger;
			WinnderFitness = ChallengerFitness;
		}
		*(pool+i) = winner;
	}
	*/
}
int condition(int *p,int v,int n)
{
	int i;
	for(i=1;i<=n;i++)
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
			if((fgets(temp,100,fp)!=NULL)&&(temp[0]=='p'))
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
					printf("%s\n",tt);
					getchar();
					return(atoi(tt));
				}
			}
		}
	}
}
void setDegree(int *g,int v)
{
	int i,j;
	int degree=0;
	for(i=1;i<=v;i++)
	{
		for(j=1;j<=v;j++)
		{
			*(g+0*(v+1)+i)+=*(g+i*(v+1)+j);
			*(g+i*(v+1))+=*(g+i*(v+1)+j);
		}
	}
}
void fileProcessing2(int *g,int v,char *ptr)//get graph (matrix)
{
	FILE *fp;
	char temp[100];
	fp=fopen(ptr,"r");
	if(fp==NULL);//perror("Error opening file.");
	else
	{
		int i,j;
		for(i=0;i<=v;i++)
		{
			for(j=0;j<=v;j++)
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
				*(g+t*(v+1)+s)=1;
				*(g+s*(v+1)+t)=1;
			}
		}
		fclose(fp);
	}
	setDegree(g,v);
}
int compare(const void *a,const void *b)
{
	return(*(int*)b-*(int*)a);
}
int getDegree(int *g,int v,int x,int *who,int *degree)//get x-th max degree index and value
{
	int i;
	int order[v+1][2];
	for(i=1;i<=v;i++)
	{
		order[i][0]=*(g+0*(v+1)+i);
		order[i][1]=i;
	}
	qsort(order[1],v,sizeof(int)*2,compare);
	*degree=order[x][0];
	*who=order[x][1];

	/*
	for(i=1;i<=v;i++)
	{
		printf("%d %d\n",i,order[i][1]);
	}
	printf("over\n");
	*/
}
void printPopulation(int *p,int n,int v)
{
	int i,j;
	printf("Print Population:\n");
	for(i=0;i<=n;i++)
	{
		printf("%2d ",*(p+i*(v+1)));
		for(j=1;j<=v;j++)
		{
			printf("%d ",*(p+i*(v+1)+j));
		}
		printf("\n");
	}
	printf("Print Population over.\n");
}
void init(int *p,int *g,int n,int v,int k)//do greedy search
{
    int i,j,l,m;
	int colored[v+1];//record colord vertex
	for(i=0;i<=v;i++)
	{
		colored[i]=0;
	}
	int init_index[v+1];
	int init_count=0;
	int max_degree=0;
	int max_who=0;
	srand(time(NULL));
	getDegree(g,v,1,&max_who,&max_degree);
	init_count++;
	init_index[init_count]=max_who;
	colored[max_who]=1;
	for(i=1;i<=n;i++)
	{
		*(p+i*(v+1)+init_index[init_count])=init_count;
	}

	for(i=2;i<=v;i++)
	{
		getDegree(g,v,i,&max_who,&max_degree);
		int flag=1;
		for(j=1;j<=init_count;j++)
		{	
			if(*(g+max_who*(v+1)+init_index[j])==0)
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			init_count++;
			init_index[init_count]=max_who;
			for(j=1;j<=n;j++)
			{
				*(p+j*(v+1)+max_who)=init_count;
			}
			colored[max_who]=1;
		}
		printPopulation(p,n,v);
		/*
		for(j=1;j<=init_count;j++)
		{
			printf("%d ",init_index[j]);
		}
		printf("\n");
		*/
	}
	for(i=1;i<=v;i++)
	{
		printf("%d ",colored[i]);
	}
	printf("\n");
	for(i=1;i<=v;i++)
	{
		if(colored[i]==1)
		{
			*(p+i)=1;
		}
		else
		{
			for(j=1;j<=n;j++)
			{
				int random=rand()%k+1;
				*(p+j*(v+1)+i)=random;
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		*(p+i*(v+1))=fitness(g,p,v,i);
	}
	//printPopulation(p,n,v);
}
int main(int argc,char *argv[])
{
    if(argc!=7)
    {
        printf("population_size repeat_times localsearch_length file_name chromatic_number selection_pressure\n");
        return(-1);
    }
    int n=atoi(argv[1]);							//population size
    int repeat=atoi(argv[2]);						//repeat times
    int lsl=atoi(argv[3]);							//localsearch length
    char *ptr=argv[4];								//file name
    int k=atoi(argv[5]);							//chromatic number
    int s=atoi(argv[6]);							//selection pressure

    int v=fileProcessing1(ptr);						//get vertices number
    int *g=(int*)malloc(sizeof(int)*(v+1)*(v+1));
    fileProcessing2(g,v,ptr);						//get graph (matrix)
    int *p=(int*)malloc(sizeof(int)*(n+1)*(v+1));;	//n population, v = chromosome_length = vertices_number
	int *pool=(int*)malloc(sizeof(int)*(n+1)*(v+1));
    while(repeat>0)									//repeat r times
    {
		int generation=0;
        init(p,g,n,v,k);
		
        while(condition(p,v,n)==1)
        {
            int p1,p2,c1[v+1],c2[v+1];
            //tournamentSelection(p,v,pool,s,n);
            randomSelectParents(n,&p1,&p2);
            simpleCrossover(g,p,p1,p2,c1,c2,v);
            //localSearch(g,p,v,c1,lsl,k);
            //localSearch(g,p,v,c2,lsl,k);
            updatePopulation(p,p1,p2,c1,c2,v);
			generation++;
			printPopulation(p,n,v);
			printResult(p,v,n,generation);
        }
		//printResult(p,v,n,generation);
		repeat--;
    }
    return(0);
}
