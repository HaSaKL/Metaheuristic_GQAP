#! /bin/bash

echo "Random Init, first Improvement LS, mixed PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-rerun3.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=r --PRDir=m

echo "Random Init, first Improvement LS, mixed PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-rerun3.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=d --PRDir=m

echo "Random Init, first Improvement LS, mixed PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-rerun3.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=a --PRDir=m
