/*These are the all data needed to solve GQAP or adjustable by the users.*/

#define BIG_NUMBER  1000000000.0    /*It should be adjusted according to the problem size and other situation.
                                  It should be far bigger than the value of any Fij.*/
#define ODD_NUMBER -1
#define PROCESS_NUM 10
#define LOCATION_NUM 5
#define BIG_IN_FEASIBLE 10000.0
#define EPSILON  0.0000000000001 

  
const char FILE_NAME[]="result_10X5-F-G.txt";  /*for the output of the program*/ 


const double Unit_Transportation_Fee=1;

const double Installation_Cost[PROCESS_NUM][LOCATION_NUM]
              ={{10000,33000,75000,55000,31500},
                {50000,95000,39500,19500,65000},
                {37500,41500,29500,85000,45000},
                {35000,57500,39500,115000,35000},
                {27500,84500,39500,48500,45000},
                {34500,13500,74500,39500,28500},
                {50500,150000,59000,58000,25500},
                {70000,50000,60000,35000,37500},
                {35000,87500,35000,55000,40000},
                {25000,26750,61500,38500,40500},
				 };

const double Flow[PROCESS_NUM][PROCESS_NUM]
               ={{0,10,20,0,15,50,80,50,70,90},            /*row i means ith process, column j means jth process*/
                 {20,0,20,50,25,40,58,35,0,45},            /*Flow[i][j] means the flow from ith process to jth process*/
      	         {60,10,0,30,10,75,0,150,60,0},
                 {0,0,60,0,50,60,10,0,15,25},
                 {70,0,0,0,0,100,50,58,0,10},
                 {0,10,60,30,0,0,50,125,15,60},
                 {50,20,30,10,30,20,0,25,30,0},
                 {0,20,40,70,90,20,50,0,45,60},
                 {30,120,0,110,0,20,0,75,0,70},
                 {0,0,40,30,60,120,50,0,195,0},
           		};


const double Distance[LOCATION_NUM][LOCATION_NUM]
                  ={{0,100,150,100,50},         /*row i means ith location, column j means jth location*/
                     {100,0,80,60,50},          /*Distance[i][j] means the distance from ith location to jth location*/
	             {150,80,0,70,120},
	             {100,60,70,0,60},
	             {50,50,120,60,0},
	            };

const double Space_Need[PROCESS_NUM]={50,45,55,48,56,62,75,59,55,65};

double Space_Avail[LOCATION_NUM]={120,170,105,100,120};
const double Space_Avail_Const[LOCATION_NUM]={120,170,105,100,120};

int  CurrentBestSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};      /*initialize each element to ODD_NUMBER*/
int  CurrentSolution[PROCESS_NUM][2]={{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};

int Unassigned_Process[PROCESS_NUM]={0,1,2,3,4,5,6,7,8,9};   /*for each process*/

