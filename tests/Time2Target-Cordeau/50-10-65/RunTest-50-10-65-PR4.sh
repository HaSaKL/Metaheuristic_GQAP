#! /bin/bash


# Test Single Elements on one problem instance

echo "Reactive Init, first Improvement LS, forward PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR4.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=a --PRDir=f

echo "Reactive Init, first Improvement LS, forward PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR4.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=a --PRDir=f




echo "Reactive Init, first Improvement LS, backward PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR4.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=a --PRDir=b

echo "Reactive Init, first Improvement LS, backward PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR4.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=a --PRDir=b




echo "Reactive Init, first Improvement LS, mixed PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR4.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=a --PRDir=m

echo "Reactive Init, first Improvement LS, mixed PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR4.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=a --PRDir=m