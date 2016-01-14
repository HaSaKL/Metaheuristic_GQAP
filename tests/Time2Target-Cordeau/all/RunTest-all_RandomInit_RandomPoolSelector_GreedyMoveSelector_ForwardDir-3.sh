#! /bin/bash


# Test some Exsamples with the best known parameter kombination (yielded from 20-15-75)

./GRASP_Solver_T2T --seed=19141108 --problemFile="40-10-65.txt" -r=250 --resultsFile="RunTest_all_3.csv" --stoppingCriterion=v -v=7265559 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f

./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-65.txt" -r=250 --resultsFile="RunTest_all_3.csv" --stoppingCriterion=v -v=10513029 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f

./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-75.txt" -r=250 --resultsFile="RunTest_all_3.csv" --stoppingCriterion=v -v=11217503 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f

./GRASP_Solver_T2T --seed=19141108 --problemFile="50-10-95.txt" -r=250 --resultsFile="RunTest_all_3.csv" --stoppingCriterion=v -v=12845598 --LSStrategy=f --StartSol=r --PRMeth=g --PRPoolSelect=r --PRDir=f