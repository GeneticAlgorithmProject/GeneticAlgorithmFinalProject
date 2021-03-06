#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"hca.h"
int main(int argc,char *argv[])
{
    if(argc!=8)
    {
        printf("population_size repeat_times localsearch_length file_name chromatic_number selection_pressure algorithm_number\n");
        return(-1);
    }
    int n=atoi(argv[1]);							//population size
    int repeat=atoi(argv[2]);						//repeat times
    int lsl=atoi(argv[3]);							//localsearch length
    char *ptr=argv[4];								//file name
    int k=atoi(argv[5]);							//chromatic number
    int s=atoi(argv[6]);							//selection pressure
	int a=atoi(argv[7]);
    int v=fileProcessing1(ptr);						//get vertices number
    int *g=(int*)malloc(sizeof(int)*(v+1)*(v+1));
    fileProcessing2(g,v,ptr);						//get graph (matrix)
    int *p=(int*)malloc(sizeof(int)*(n+1)*(v+1));	//n population, v = chromosome_length = vertices_number
    while(repeat>0)									//repeat r times
    {
		int generation=0;
        init(p,g,n,v,k);
		//init_new(g,p,n,v,k,a);
		//printPopulation(p,n,v);
        do
        {
            int p1,p2,c1[v+1],c2[v+1];
            tournamentSelection(p,v,s,n);
			crossover(g,p,v,n);
			//outsideFitness(g,p,n,v,k);
            //randomSelectParents(n,&p1,&p2);
			flip2(g,p,v,n,k);
            //simpleCrossover(g,p,p1,p2,c1,c2,v);
            //updatePopulation(p,p1,p2,c1,c2,v);

            //localSearch(g,p,v,c1,lsl,k);
            //localSearch(g,p,v,c2,lsl,k);
			generation++;
			//printPopulation(p,n,v);
			printResult(p,v,n,generation);
			//getchar();
			int Best=getBestOne(p,v,n);
			draw_graph(g,p+Best*(v+1),v,"Best.dot");
        }while(condition(p,v,n)==1);
		printResult(p,v,n,generation);
		repeat--;
    }
    return(0);
}
