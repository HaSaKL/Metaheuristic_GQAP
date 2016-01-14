#! /bin/bash


# Test Single Elements on one problem instance

echo "Random Init, first Improvement LS no PR"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-woPR.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --PRMeth=n --StartSol=r



echo "Reactive GRASP, first Improvement LS no PR"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-woPR.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --PRMeth=n --StartSol=R --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2



echo "Uniform Random GRASP, first Improvement LS no PR"

./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-woPR.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=f --PRMeth=n --StartSol=U --minAlpha=0 --maxAlpha=1 --numAlpha=10