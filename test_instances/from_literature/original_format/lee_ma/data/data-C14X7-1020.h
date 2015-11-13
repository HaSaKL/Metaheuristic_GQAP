/*These are the all data needed to solve GQAP or adjustable by the users.*/

#define BIG_NUMBER  100000000000.0    /*It should be adjusted according to the problem size and other situation.
                                  It should be far bigger than the value of any Fij.*/
#define ODD_NUMBER -1
#define PROCESS_NUM 14
#define LOCATION_NUM 7
#define BIG_IN_FEASIBLE 10000.0
#define EPSILON  0.0000000000001 

const char FILE_NAME[]="result_C14X7-1020.txt";

const double Unit_Transportation_Fee=5;

const double Installation_Cost[PROCESS_NUM][LOCATION_NUM]
={{50000,133000,75000,160000,35000,50000,30000},
{55000,131500,167000,90000,276000,46700,119550},
{95000,189500,119500,59870,145600,42000,139800},
{25000,37500,31500,150000,70000,99000,127800},
{29500,185000,145000,34500,150000,74000,122300},
{75000,120500,19500,60000,210000,33200,133000},
{115000,35000,27500,65000,97000,46800,56800},
{84500,39500,28500,72000,250000,95000,67800},
{25000,34500,113500,78900,65000,52100,23100},
{74500,39500,20500,65000,84000,55000,29000},
{50500,150000,39000,89000,220000,65000,25600},
{58000,75500,70000,34200,45000,51000,27600},
{25000,135000,37500,45000,157000,36800,120000},
{34500,239500,78500,92000,145000,65000,22000},
		 };


const float Flow[PROCESS_NUM][PROCESS_NUM]
               ={{0,0,20,0,0,50,80,0,70,90,0,100,80,0},            /*row i means ith process, column j means jth process*/
                 {0,0,0,50,0,40,58,0,0,45,100,0,0,100},            /*Flow[i][j] means the flow from ith process to jth process*/
      	         {60,0,0,30,0,75,0,150,60,0,0,50,0,50},
                 {0,0,60,0,50,60,0,0,0,25,0,35,0,50},
                 {70,0,0,0,0,100,50,58,0,0,0,65,0,50},
                 {0,0,60,30,0,0,50,125,0,60,40,0,40,0},
                 {50,0,30,0,30,0,0,0,30,0,0,0,40,0},
                 {0,0,40,70,90,0,50,0,45,60,0,50,0,0},
                 {0,120,0,110,0,0,0,75,0,70,30,0,0,50},
                 {0,0,40,30,60,120,50,0,195,0,0,100,0,100},
                 {120,0,0,0,60,0,25,0,65,70,0,0,80,0},
                 {70,0,60,30,0,0,250,0,0,0,65,0,0,50},
                 {0,100,30,0,110,0,0,150,0,50,0,0,0,50},
                 {0,0,100,0,0,0,100,75,0,70,0,0,40,0},

		};

const float Distance[LOCATION_NUM][LOCATION_NUM]
                   ={{0,60,150,60,50,80,160},         /*row i means ith location, column j means jth location*/
                     {60,0,80,40,90,120,100},          /*Distance[i][j] means the distance from ith location to jth location*/
	             {150,80,0,70,120,70,80},
	             {60,40,70,0,60,80,90},
	             {50,90,120,60,0,50,100},
                 {80,120,70,80,50,0,60},
                 {160,100,80,90,100,60,0},
                  };

const float Space_Need[PROCESS_NUM]={30,120,110,40,140,95,40,75,65,55,110,40,50,85};

float Space_Avail[LOCATION_NUM]={270,80,100,360,70,140,90};

int  CurrentBestSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};      /*initialize each element to ODD_NUMBER*/
int  CurrentSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

int Unassigned_Process[PROCESS_NUM]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};   /*for each process*/

