#! /bin/bash


# Test Single Elements on one problem instance

echo "Baseline: Random Init, first Improvement LS, forward PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=r --PRDir=f

echo "Random Init, first Improvement LS, forward PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f

echo "Random Init, first Improvement LS, forward PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=d --PRDir=f

echo "Random Init, first Improvement LS, forward PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f




echo "Random Init, first Improvement LS, backward PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=r --PRDir=b

echo "Random Init, first Improvement LS, backward PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=b

echo "Random Init, first Improvement LS, backward PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=d --PRDir=b

echo "Random Init, first Improvement LS, backward PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=b




echo "Random Init, first Improvement LS, mixed PR with randomPoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=r --PRDir=m

echo "Random Init, first Improvement LS, mixed PR with random PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=m

echo "Random Init, first Improvement LS, mixed PR with diverse PoolSelect and random selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=r --PRPoolSelect=d --PRDir=m

echo "Random Init, first Improvement LS, mixed PR with dirverse PoolSelect and greedy selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="Test-50-10-65-PR1.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=m