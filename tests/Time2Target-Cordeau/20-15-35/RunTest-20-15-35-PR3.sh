#! /bin/bash


# Test Single Elements on one problem instance

echo "Baseline: Reactive Init, first Improvement LS, forward PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=r --PRDir=f

echo "Reactive Init, first Improvement LS, forward PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=r --PRDir=f

echo "Reactive Init, first Improvement LS, forward PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=d --PRDir=f

echo "Reactive Init, first Improvement LS, forward PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=d --PRDir=f




echo "Reactive Init, first Improvement LS, backward PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=r --PRDir=b

echo "Reactive Init, first Improvement LS, backward PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=r --PRDir=b

echo "Reactive Init, first Improvement LS, backward PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=d --PRDir=b

echo "Reactive Init, first Improvement LS, backward PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=d --PRDir=b




echo "Reactive Init, first Improvement LS, mixed PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=r --PRDir=m

echo "Reactive Init, first Improvement LS, mixed PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=r --PRDir=m

echo "Reactive Init, first Improvement LS, mixed PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=r --PRPoolSelect=d --PRDir=m

echo "Reactive Init, first Improvement LS, mixed PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=g --PRPoolSelect=d --PRDir=m