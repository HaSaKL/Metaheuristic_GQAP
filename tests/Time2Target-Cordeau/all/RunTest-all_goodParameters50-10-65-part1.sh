#! /bin/bash


# Test some Exsamples with the best known parameter kombination (yielded from 50-10-65)

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=1953188 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m 
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=1953188 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=1953188 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-06-95.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=5160920 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-06-95.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=5160920 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-06-95.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=5160920 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-07-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=4383923 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-07-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=4383923 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-07-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=4383923 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-08-55.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3501695 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-08-55.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3501695 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-08-55.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3501695 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-10-65.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3620959 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-10-65.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3620959 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-10-65.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3620959 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-35.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3379359 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-35.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3379359 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-35.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3379359 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-55.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3593105 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-55.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3593105 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-55.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=3593105 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=4050938 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=4050938 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-75.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=4050938 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-95.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=5710645 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-95.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=5710645 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="30-20-95.txt" -r=100 --resultsFile="RunTest_all_part1.csv" --stoppingCriterion=v -v=5710645 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1