/*These are the all data needed to solve GQAP or adjustable by the users.*/

#define BIG_NUMBER  100000000.0    /*It should be adjusted according to the problem size and other situation.
                                  It should be far bigger than the value of any Fij.*/
#define ODD_NUMBER -1
#define PROCESS_NUM 12
#define LOCATION_NUM 4
#define BIG_IN_FEASIBLE 10000.0
#define EPSILON  0.0000000000001 

const char FILE_NAME[]="result_C12X4-F-H.txt";

const double Unit_Transportation_Fee=5;

const double Installation_Cost[PROCESS_NUM][LOCATION_NUM]
={{10000,33000,75000,60000},
{55000,31500,50000,90000},
{95000,39500,19500,59870},
{65000,37500,41500,100000},
{29500,85000,45000,34500},
{35000,57500,39500,60000},
{115000,35000,27500,65000},
{84500,39500,48500,12000},
{45000,34500,13500,78900},
{74500,39500,28500,65000},
{50500,150000,59000,89000},
{58000,25500,70000,34200},
		 };


const double Flow[PROCESS_NUM][PROCESS_NUM]
               ={{0,10,20,0,15,50,80,50,70,90,20,100},            /*row i means ith process, column j means jth process*/
                 {20,0,20,50,25,40,58,35,0,45,100,0},            /*Flow[i][j] means the flow from ith process to jth process*/
      	         {60,10,0,30,10,75,0,150,60,0,0,50},
                 {0,0,60,0,50,60,10,0,15,25,55,35},
                 {70,0,0,0,0,100,50,58,0,0,10,65},
                 {0,10,60,30,0,0,50,125,15,60,40,0},
                 {50,20,30,10,30,20,0,25,30,0,20,0},
                 {0,20,40,70,90,20,50,0,45,60,0,50},
                 {30,120,0,110,0,20,0,75,0,70,30,0},
                 {0,0,40,30,60,120,50,0,195,0,20,100},
                 {120,20,0,10,60,0,25,0,65,70,0,0},
                 {70,10,60,30,0,0,250,0,0,10,65,0},
		};

const double Distance[LOCATION_NUM][LOCATION_NUM]
                   ={{0,100,150,100},         /*row i means ith location, column j means jth location*/
                     {100,0,80,60},          /*Distance[i][j] means the distance from ith location to jth location*/
	             {150,80,0,70},
	             {100,60,70,0},
	            };

const double Space_Need[PROCESS_NUM]={50,75,50,80,55,55,50,70,65,70,80,55};

double Space_Avail[LOCATION_NUM]={190,200,175,195};
const double Space_Avail_Const[LOCATION_NUM]={190,200,175,195};

int  CurrentBestSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};      /*initialize each element to ODD_NUMBER*/
int  CurrentSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

int Unassigned_Process[PROCESS_NUM]={0,1,2,3,4,5,6,7,8,9,10,11};   /*for each process*/

