#! /bin/bash

echo "Reactive Init, first Improvement LS, mixed PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1qb.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=r --PRDir=m --QuickGRASP=1

echo "Reactive Init, first Improvement LS, mixed PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1q.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=d --PRDir=m --QuickGRASP=1