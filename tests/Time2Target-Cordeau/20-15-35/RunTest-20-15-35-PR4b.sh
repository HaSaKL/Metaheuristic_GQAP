#! /bin/bash


# Test Single Elements on one problem instance

echo "Reactive Init, first Improvement LS, forward PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR2.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=r --PRPoolSelect=a --PRDir=f

echo "Reactive Init, first Improvement LS, forward PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR2.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=g --PRPoolSelect=a --PRDir=f




echo "Reactive Init, first Improvement LS, backward PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR2.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=a --PRDir=b

echo "Reactive Init, first Improvement LS, backward PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR2.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=g --PRPoolSelect=a --PRDir=b




echo "Reactive Init, first Improvement LS, mixed PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR2.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=a --PRDir=m

echo "Reactive Init, first Improvement LS, mixed PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR2.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=g --PRPoolSelect=a --PRDir=m