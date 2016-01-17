This project contains all source files and test for the GQAP in the paper "Solving Facility Location Problems and Service Modularization Problems using Greedy Adaptive Randomized Search Procedures"
by Hagen Salewski

The folder "algorithm" holds all source codes to compile a couple of test instances and a GRASP-based applications which solves the Generalized Quadratic Assignment Problem

To compile, you need to have version 2.0.1 of ParadisEO (http://paradiseo.gforge.inria.fr/index.php?n=Doc.Install) and all it requirements installed. Then:
- mkdir algorithm/build
- cd algorithm/build
- cmake ..
- make

After the compilation all applications can be found in "algorithms/build/applications"

The application GRASP_Solver_T2T is used to solve the test instances.

A documentation of the command line parameters can be found in the file CLI.txt

The folder "tests" is self contained and holds all tests, compiled GQAP_TimeToTarget, R-Scripts and Bash-Scrips required to run the tests. Examine the Bash-Skrips to see what test are run. Test results are summarized in *.csv-files.


For question please contact the author:
Dr. Hagen Salewski
Department of Business Administration and Production Management
University of Kaiserslautern
Gottlieb-Daimler-Str. 42
67663 Kaiserslautern
Germany

Email: salewski@wiwi.uni-kl.de
