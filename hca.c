#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void printResult(int *p[])
{}
bool condition(int *p[])
{}
void greedySearch(int p[],int s)
{}
void selectParents(int *p[],int *p1,int *p2)
{}
void crossover(int *p1,int *p2,int *c1,int *c2)
{}
void localSearch(int *c)
{}
void updatePopulation(int *p[],int *c1,int *c2)
{}
int fileProcessing1(char *ptr)
{

}
void fileProcessing2(int *f[])
{

}
void init(int *p[],int n,int v)
{
    int i;
    for(i=0;i<n;i++)
    {
        srand(time(NULL));
        int random=rand()%v;
        greedySearch(p[i],random);//ramdom select a vertex as starting point to color
    }

}
int main(int argc,char *argv[])
{
    if(argc!=6)
    {
        printf("population_size repeat_times localsearch_length file_name chromatic_number\n");
        return(-1);
    }
    int n=atoi(argv[1]);
    int r=atoi(argv[2]);
    int lsl=atoi(argv[3]);
    char *ptr=argv[4];
    int k=atoi(argv[5]);

    //printf("%d %d %d %s %d\n",n,r,lsl,ptr,k);
    int v=fileProcessing1(ptr);//get vertices number
    int *G[v];
    fileProcessing2(G);//get graph
    int *p[n];//n population, v = chromosome_length = vertices_number
    while(r>0)//repeat r times
    {
        init(p,n,v);
        while(condition(p)==true)
        {
            int p1[v],p2[v],c1[v],c2[v];
            selectParents(p,p1,p2);
            crossover(p1,p2,c1,c2);
            localSearch(c1);
            localSearch(c2);
            updatePopulation(p,c1,c2);
        }
        printResult(p);//need to implement; 
    }
    return(0);
}
