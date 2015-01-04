//main
void crossover(int *p,int v,int n);
void tournamentSelection(int *p,int v,int s,int n);
int calculate(int *g,int *p,int v,int k,int x);
void outsideFitness(int *g,int *p,int n,int v,int k);
void function1(int *g,int *chrom,int v,int k);
void function2(int *g,int *chrom,int v,int k);
void function3(int *g,int *chrom,int v,int k);
//important
int fitness(int *g,int *p,int v,int x);
//init
int fileProcessing1(char *ptr);
void fileProcessing2(int *g,int v,char *ptr);
void init(int *p,int *g,int n,int v,int k);
void init_new(int *g,int *p, int n,int v,int k,int a);
//small
int compare(const void *a,const void *b);
void setDegree(int *g,int v);
void getDegree(int *g,int v,int x,int *who,int *degree);
int condition(int *p,int v,int n);
void paste(int *p,int p1,int *c1,int v);
void uniformArray(int *array,int n);
//result
int getWorstOne(int *p,int v,int n);
int getBestOne(int *p,int v,int n);
double getAverageFitness(int *p,int v,int n);
void printWorstFitness(int *p,int v,int n);
void printAverageFitness(int *p,int v,int n);
void printBestFitness(int *p,int v,int n);
void printBestPopulation(int *p,int v,int n);
void printResult(int *p,int v,int n,int gen);
void printPopulation(int *p,int n,int v);
//not used now
void updatePopulation(int *p,int p1,int p2,int *c1,int *c2,int v);
void localSearch(int *g,int *p,int v,int *c,int l,int k);
void randomSelectParents(int n,int *p1,int *p2);
void simpleCrossover(int *g,int *p,int p1,int p2,int *c1,int *c2,int v);