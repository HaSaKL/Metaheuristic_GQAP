#! /bin/bash


# Test Single Elements on one problem instance

echo "Random Init, best Improvement LS, forward PR with diverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=b --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f

echo "Random Init, no LS, forward PR with diverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=n --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f