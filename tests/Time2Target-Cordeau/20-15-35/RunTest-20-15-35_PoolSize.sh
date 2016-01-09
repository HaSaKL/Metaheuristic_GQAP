#! /bin/bash

echo "Random Init, first Improvement LS, forward PR with random PoolSelect and greedy selection"

echo "PoolSize = 3"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f --PRPoolSize=3 > /dev/null


echo "PoolSize = 6"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f --PRPoolSize=6 > /dev/null


echo "PoolSize = 10"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f --PRPoolSize=10 > /dev/null


echo "PoolSize = 30"


./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f --PRPoolSize=30 > /dev/null


echo "PoolSize = 60"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f --PRPoolSize=60 > /dev/null


echo "PoolSize = 100"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f --PRPoolSize=100 > /dev/null




echo "Random Init, first Improvement LS, forward PR with random PoolSelect and diverse selection"

echo "PoolSize = 3"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f --PRPoolSize=3 > /dev/null


echo "PoolSize = 6"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f --PRPoolSize=6 > /dev/null


echo "PoolSize = 10"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f --PRPoolSize=10 > /dev/null


echo "PoolSize = 30"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f --PRPoolSize=30 > /dev/null


echo "PoolSize = 60"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f --PRPoolSize=60 > /dev/null


echo "PoolSize = 100"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=d --PRDir=f --PRPoolSize=100 > /dev/null



echo "Random Init, first Improvement LS, forward PR with random PoolSelect and all selection"

echo "PoolSize = 3"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=f --PRPoolSize=3 > /dev/null


echo "PoolSize = 6"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=f --PRPoolSize=6 > /dev/null


echo "PoolSize = 10"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=f --PRPoolSize=10 > /dev/null


echo "PoolSize = 30"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=f --PRPoolSize=30 > /dev/null


echo "PoolSize = 60"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=f --PRPoolSize=60 > /dev/null


echo "PoolSize = 100"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-PoolSize.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=f --PRPoolSize=100 > /dev/null