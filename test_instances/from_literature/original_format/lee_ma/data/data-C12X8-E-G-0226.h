/*These are the all data needed to solve GQAP or adjustable by the users.*/

#define BIG_NUMBER  1000000000.0    /*It should be adjusted according to the problem size and other situation.
                                  It should be far bigger than the value of any Fij.*/
#define ODD_NUMBER -1
#define PROCESS_NUM 12
#define LOCATION_NUM 8
#define BIG_IN_FEASIBLE 10000.0
#define EPSILON  0.0000000000001 

const char FILE_NAME[]="result_C12X8-E-G-0226.txt";

const double Unit_Transportation_Fee=5;

const double Installation_Cost[PROCESS_NUM][LOCATION_NUM]
={{20000,33000,45000,60000,35000,50000,65000,30000},
{55000,31500,67000,90000,76000,46700,25000,55000},
{75000,49500,19500,59870,45600,42000,39800,50000},
{65000,37500,31500,60000,70000,59000,27800,55000},
{59500,85000,45000,34500,50000,74000,42300,65000},
{35000,57500,19500,60000,60000,43200,54000,33000},
{75000,35000,27500,65000,67000,46800,46800,28900},
{84500,39500,48500,52000,50000,55000,67800,53400},
{45000,54500,13500,78900,65000,52100,23100,43600},
{74500,39500,28500,65000,54000,55000,50000,49000},
{50500,70000,59000,49000,60000,65000,25600,63400},
{58000,25500,70000,34200,45000,51000,48000,47600},
		 };


const float Flow[PROCESS_NUM][PROCESS_NUM]
               ={{0,0,20,0,0,50,80,50,70,90,20,100},            /*row i means ith process, column j means jth process*/
                 {20,0,0,50,25,0,58,35,0,45,100,100},            /*Flow[i][j] means the flow from ith process to jth process*/
      	         {60,10,0,0,10,75,0,150,60,0,0,50},
                 {0,0,60,0,50,60,0,0,15,25,55,50},
                 {70,0,0,0,0,100,50,58,0,0,0,65},
                 {0,0,60,30,20,0,0,125,0,60,40,40},
                 {50,0,30,0,30,20,0,25,30,0,20,40},
                 {0,0,40,70,90,0,50,0,45,60,0,50},
                 {30,120,0,110,0,0,0,75,0,70,0,0},
                 {0,0,40,0,60,120,50,0,195,0,20,100},
                 {120,0,0,0,60,0,25,0,65,70,0,0},
                 {70,0,60,30,0,0,250,0,40,0,65,0},
		};

const float Distance[LOCATION_NUM][LOCATION_NUM]
                   ={{0,100,150,100,50,80,100,120},         /*row i means ith location, column j means jth location*/
                     {100,0,80,60,50,100,100,150},          /*Distance[i][j] means the distance from ith location to jth location*/
	             {150,80,0,70,120,70,80,200},
	             {100,60,70,0,60,100,90,20},
	             {50,50,120,60,0,80,100,40},
                 {80,100,70,100,80,0,80,90},
                 {100,100,80,90,100,80,0,90},
                 {120,150,200,20,40,90,90,0},
	            };

const float Space_Need[PROCESS_NUM]={10,20,30,40,50,65,70,100,80,90,60,55};

float Space_Avail[LOCATION_NUM]={250,130,100,160,360,80,90,100};

int  CurrentBestSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};      /*initialize each element to ODD_NUMBER*/
int  CurrentSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

int Unassigned_Process[PROCESS_NUM]={0,1,2,3,4,5,6,7,8,9,10,11};   /*for each process*/

