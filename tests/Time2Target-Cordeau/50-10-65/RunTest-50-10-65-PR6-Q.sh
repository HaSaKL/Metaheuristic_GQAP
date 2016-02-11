#! /bin/bash


# Test Single Elements on one problem instance

echo "Reactive Init, first Improvement LS, forward PR with all PoolSelect and GRASP selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR6q.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=G --PRPoolSelect=a --PRDir=f --QuickGRASP=1


echo "Reactive Init, first Improvement LS, backward PR with all PoolSelect and GRASP selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR6q.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=G --PRPoolSelect=a --PRDir=b --QuickGRASP=1


echo "Reactive Init, first Improvement LS, mixed PR with all PoolSelect and GRASP selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR6q.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=G --PRPoolSelect=a --PRDir=m --QuickGRASP=1