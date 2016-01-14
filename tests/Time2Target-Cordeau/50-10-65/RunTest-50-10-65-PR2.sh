#! /bin/bash


# Test Single Elements on one problem instance

echo "Random Init, first Improvement LS, forward PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR2.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=a --PRDir=f

echo "Random Init, first Improvement LS, forward PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR2.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=f




echo "Random Init, first Improvement LS, backward PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR2.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=a --PRDir=b

echo "Random Init, first Improvement LS, backward PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR2.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=b




echo "Random Init, first Improvement LS, mixed PR with all PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR2.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=a --PRDir=m

echo "Random Init, first Improvement LS, mixed PR with all PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR2.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m