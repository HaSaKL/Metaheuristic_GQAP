#! /bin/bash


# Test Single Elements on one problem instance

echo "Baseline: Reactive Init, first Improvement LS, forward PR with randomPoolSelect and GRASP Selecetion"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=G --PRPoolSelect=r --PRDir=f

echo "Reactive Init, first Improvement LS, forward PR with diverse PoolSelect and GRASP Selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=G --PRPoolSelect=d --PRDir=f




echo "Reactive Init, first Improvement LS, backward PR with randomPoolSelect and GRASP Selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --PRMeth=G --PRPoolSelect=r --PRDir=b

echo "Reactive Init, first Improvement LS, backward PR with diverse PoolSelect and GRASP Selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=G --PRPoolSelect=d --PRDir=b




echo "Reactive Init, first Improvement LS, mixed PR with randomPoolSelect and GRASP Selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=G --PRPoolSelect=r --PRDir=m

echo "Reactive Init, first Improvement LS, mixed PR with diverse PoolSelect and GRASP Selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PR1.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10 --PRMeth=G --PRPoolSelect=d --PRDir=m