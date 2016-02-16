#! /bin/bash


# Test some Exsamples with the best known parameter kombination (yielded from 20-15-75)

./GRASP_Solver_T2T --seed=19141108 --problemFile="40-10-65.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=7265559 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="40-10-65.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=7265559 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="40-10-65.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=7265559 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-75.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=11217503 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-75.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=11217503 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-75.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=11217503 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-95.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=12845598 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-95.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=12845598 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-95.txt" -r=100 --resultsFile="RunTest_all_part3.csv" --stoppingCriterion=v -v=12845598 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1