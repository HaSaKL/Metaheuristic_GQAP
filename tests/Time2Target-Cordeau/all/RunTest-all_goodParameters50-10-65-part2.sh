#! /bin/bash


# Test some Exsamples with the best known parameter kombination (yielded from 50-10-65)

./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-35.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=4456670 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-35.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=4456670 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-35.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=4456670 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-55.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=4639128 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-55.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=4639128 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-55.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=4639128 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-75.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=6301723 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-75.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=6301723 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-75.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=6301723 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-95.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=6670264 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-95.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=6670264 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="35-15-95.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=6670264 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="40-07-75.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=7405793 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="40-07-75.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=7405793 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="40-07-75.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=7405793 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


./GRASP_Solver_T2T --seed=19141108 --problemFile="40-09-95.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=7667719 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m
./GRASP_Solver_T2T --seed=19141108 --problemFile="40-09-95.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=7667719 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2
./GRASP_Solver_T2T --seed=19141108 --problemFile="40-09-95.txt" -r=100 --resultsFile="RunTest_all_part2.csv" --stoppingCriterion=v -v=7667719 --LSStrategy=f --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1