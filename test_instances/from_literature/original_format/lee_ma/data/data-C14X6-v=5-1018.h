/*These are the all data needed to solve GQAP or adjustable by the users.*/

#define BIG_NUMBER  1000000000.0    /*It should be adjusted according to the problem size and other situation.
                                  It should be far bigger than the value of any Fij.*/
#define ODD_NUMBER -1
#define PROCESS_NUM 14
#define LOCATION_NUM 6
#define BIG_IN_FEASIBLE 10000.0
#define EPSILON  0.0000000000001 

const char FILE_NAME[]="result_C14X6-E-G-1018.txt";

const double Unit_Transportation_Fee=5;

const double Installation_Cost[PROCESS_NUM][LOCATION_NUM]
={{20000,23000,75000,160000,35000,50000},
{55000,131500,67000,19000,76000,46700},
{95000,39500,19500,59870,45600,42000},
{35000,37500,31500,130000,70000,59000},
{19500,85000,45000,114500,50000,74000},
{35000,57500,19500,60000,110000,43200},
{115000,35000,17500,55000,67000,28900},
{124500,39500,48500,12000,50000,55000},
{125000,34500,13500,78900,23100,43600},
{74500,19500,128500,65000,50000,99000},
{50500,150000,59000,89000,13000,63400},
{58000,25500,70000,34200,45000,147600},
{15000,135000,37500,45000,120000,39000},
{54500,39500,68500,92000,152000,49000},
		 };


const float Flow[PROCESS_NUM][PROCESS_NUM]
               ={{0,0,20,0,0,0,80,0,0,90,0,180,80,0},            /*row i means ith process, column j means jth process*/
                 {0,0,0,50,0,40,58,0,0,0,100,0,0,100},            /*Flow[i][j] means the flow from ith process to jth process*/
      	         {60,0,0,30,0,75,0,150,60,0,0,50,0,50},
                 {0,0,60,0,50,60,0,0,0,0,55,0,0,50},
                 {0,0,70,0,0,100,50,58,0,0,0,65,0,50},
                 {0,0,60,30,0,0,50,125,0,60,40,0,40,0},
                 {50,0,80,0,0,30,0,25,30,0,0,0,40,0},
                 {0,0,110,0,90,0,50,0,45,60,0,50,0,150},
                 {0,150,0,110,0,0,0,75,0,70,0,0,0,50},
                 {0,0,40,0,60,120,50,0,195,0,0,100,0,0},
                 {60,0,0,0,0,0,0,65,70,0,0,80,0,0},
                 {70,0,60,0,0,0,250,0,0,0,65,0,0,50},
                 {0,100,30,0,110,0,0,150,0,50,0,0,0,0},
                 {0,0,100,0,0,0,100,75,0,70,0,0,40,0},

		};

const float Distance[LOCATION_NUM][LOCATION_NUM]
                   ={{0,100,150,100,50,80},         /*row i means ith location, column j means jth location*/
                     {100,0,80,60,50,100},          /*Distance[i][j] means the distance from ith location to jth location*/
	             {150,80,0,70,120,70},
	             {100,60,70,0,60,100},
	             {50,50,120,60,0,80},
                 {80,100,70,100,80,0},
                 };

const float Space_Need[PROCESS_NUM]={30,125,110,35,115,85,40,75,55,30,105,40,50,85};

float Space_Avail[LOCATION_NUM]={275,160,345,80,70,90};

int  CurrentBestSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};      /*initialize each element to ODD_NUMBER*/
int  CurrentSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

int Unassigned_Process[PROCESS_NUM]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};   /*for each process*/

