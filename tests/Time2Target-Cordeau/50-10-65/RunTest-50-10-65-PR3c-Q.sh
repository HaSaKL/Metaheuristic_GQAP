#! /bin/bash

echo "Reactive Init, first Improvement LS, backward PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1qc.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=r --PRDir=b --QuickGRASP=1

echo "Reactive Init, first Improvement LS, backward PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1qc.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=d --PRDir=b --QuickGRASP=1

echo "Reactive Init, first Improvement LS, mixed PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1qc.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=r --PRDir=m --QuickGRASP=1

echo "Reactive Init, first Improvement LS, mixed PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1qc.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=d --PRDir=m --QuickGRASP=1