/*
 1. g[0][i]=g[i][0] degree of vertex i
 2. g[i][j]=g[j][i]=1 if vertex i and vertex j adjacent
 3. if (p[0][i]=1) => do not change the color of vertex i during localsearch
 4. p[i][j] population i's jth vertex's color
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"hca.h"
void get_graph()
{
	
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
int calculate(int *g,int *p,int v,int k,int x)
{
	int i,j;
	int chrom[v+1];
	for(i=0;i<=v;i++)
	{
		chrom[i]=0;
	}
		//printf("why\n");
	for(i=1;i<=v;i++)
	{
		//printf("====function=%d\n",*(p+x*(v+1)+i));
		//for(j=1;j<=v;j++)
		//	printf("chrom[%d]=%d\n",j,chrom[j]);
		//printf("----\n");
		if(*(p+x*(v+1)+i)==1)
			function2(g,chrom,v,k);
		else if(*(p+x*(v+1)+i)==2)
			function2(g,chrom,v,k);
		else if(*(p+x*(v+1)+i)==3)
			function3(g,chrom,v,k);
		//for(j=1;j<=v;j++)
		//		printf("chrom[%d]=%d\n",j,chrom[j]);
		//printf("====function=%ddone\n",*(p+x*(v+1)+i));
		//getchar();getchar();
	}
	return(fitness(g,chrom,v,0));
}
void outsideFitness(int *g,int *p,int n,int v,int k)
{
    int i;
    for(i=1;i<=n;i++)
    {
        *(p+i*(v+1))=calculate(g,p,v,k,i);
    }
}
void tournamentSelection(int *p,int v,int s,int n)
{
    srand(time(NULL));
    int i,j,m;
    int array[n+1];
    int record[n+1];
    int *pop=(int*)malloc(sizeof(int)*(n+1)*(v+1));
    int count=1;
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=v;j++)
        {
            *(pop+i*(v+1)+j)=0;
        }
    }
    for(i=0;i<s;i++)
    {
        for(j=1;j<=n;j++)
        {
            record[j]=0;
        }
        for(j=1;j<=n;j++)//random array
        {
            array[j]=j;
        }
        for(j=1;j<=n;j++)
        {
            int r=rand()%n+1;
            int temp=array[j];
            array[j]=array[r];
            array[r]=temp;
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
                *(pop+count*(v+1)+a)=*(p+array[winner]*(v+1)+a);
            }
            count++;
        }
    }
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=v;j++)
        {
            *(p+i*(v+1)+j)=*(pop+i*(v+1)+j);
        }
    }
    /* be comment;
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
void function1(int *g,int *chrom,int v,int k)
{
    int i,j,x=0, y=0;
    for (i=1; i<=v; i++) 
	{
        if (chrom[i]==0)
            y++;
        else
            x++;
    }
    int* m = (int*)malloc(sizeof(int)*(x));
    int* n = (int*)malloc(sizeof(int)*(y));
    for (i=1; i<=v; i++)
	{
        if (chrom[i]==0)
		{
            m[y++]=i;
        }
        else
		{
            n[x++]=i;
        }
    }
    int* o = (int*)malloc(sizeof(int)*(v+1));
    int r=0;//not neibor
    for (i=1; i<=y; i++)
	{
        for(j=1; j<=x; j++)
		{
            if (*g+(n[i]*(v+1)+m[j])==1) 
				break;
            else
                if (j==x) 
				{
                    o[r]=i;
					r++;
                }
        }
    }
    int* t = (int*)malloc(sizeof(int)*(r));
    int max=0, f=0;
    for (i=0; i<r; i++)
	{
        for (j=1; j<=v; j++) 
		{
            if ((*g+o[i]*(v+1)+j)==1)
                t[i]++;
        }
    }
    for (i=0; i<r; i++) 
	{
        if (t[i]>max)
		{
            f=i;
            max=t[i];
        }
    }
    *(chrom+(f))=rand()%k+1;
}
void function2(int *g,int *chrom,int v,int k)
{
	//printf("this is function2\n");
	int max_degree=0;
	int max_who=0;
	int order =1;
	int i;
	int colored_bool = 0;
	int colored[k] ;
	srand(time(NULL));
	for(i=0;i<k;i++)colored[i]=0;
	for(order=1;order<=v;order++){
	 	getDegree(g,v,order,&max_who,&max_degree);
		//printf("order=%d,max_who=%d\n",order,max_who);
	 	if(*(chrom+(max_who))!=0)continue;
	 	for(i=1;i<=v;i++){
	 		if((*(g+i*(v+1)+max_who))==0)continue;
	 		if(*(chrom+(i))!=0)
	 			colored[*(chrom+(i))] = colored[*(chrom+(i))]+1;
	 	}
		//printf("no continue\n");for(i=0;i<k;i++)printf("color[%d]=is %d\n",i+1,colored[i]);
	 	for(i=0;i<k;i++){
	 		if(colored[i]==0){
				*(chrom+max_who) = i+1;
				colored_bool = 1;
				//printf("color=%d\n",i);
				break;
			}
		}
		if(colored_bool ==1)break;
	 	if(i==k)
			*(chrom+max_who) = (rand()%k)+1;
 	}
}
void function3(int *g,int *chrom,int v,int k)
{
    srand(time(NULL));
    int i,r;
    r=rand()%v+1;
    while(chrom[r]!=0||r==0)
    {
        r=(r+1)%(v+1);
    }
    chrom[r]=rand()%k+1;
}
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
        *(c+maxi)=temp;
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

void crossover(int *p,int v,int n)
{
    int i,j;
    for(i=1;i<=n;i+=2)
    {
        for(j=1;j<=v;j++)
        {
            int r=rand()%2;
            if(r==1)
            {
                int temp=*(p+i*(v+1)+j);
                *(p+i*(v+1)+j)=*(p+(i+1)*(v+1)+j);
                *(p+(i+1)*(v+1)+j)=temp;
            }
        }
    }
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
	printf("file start\n");
    FILE *fp;
    int v=0;
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
                    v=(atoi(tt));
			break;
                }
            }
        }
    }
	printf("return\n");
    return v;
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
void getDegree(int *g,int v,int x,int *who,int *degree)//get x-th max degree index and value
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

void init_new(int *g,int *p, int n,int v,int k,int a)
{
    srand(time(NULL));
    int i,j;
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=v;j++)
        {
            *(p+i*(v+1)+j)=0;
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=v;j++)
        {
            int temp=rand()%3+1;
            *(p+i*(v+1)+j)=temp;
        }
    }
    outsideFitness(g,p,n,v,k);
}
