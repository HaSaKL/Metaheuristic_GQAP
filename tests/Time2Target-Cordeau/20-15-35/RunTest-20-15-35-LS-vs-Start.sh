#! /bin/bash
# Test Single Elements on one problem instance

echo "Random Init, best improvement, greedy pool select, mixed PR-dir and ALL pool selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-Start_LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=b --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m

echo "GRASP Init, best improvement, greedy pool select, mixed PR-dir and ALL pool selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-Start_LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=b --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2

echo "Quick GRASP Init, best improvement, greedy pool select, mixed PR-dir and ALL pool selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-Start_LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=b --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1


echo "Random Init, first improvement, greedy pool select, mixed PR-dir and ALL pool selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-Start_LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=b --StartSol=r --PRMeth=g --PRPoolSelect=a --PRDir=m

echo "GRASP Init, first improvement, greedy pool select, mixed PR-dir and ALL pool selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-Start_LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=b --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2

echo "Quick GRASP Init, first improvement, greedy pool select, mixed PR-dir and ALL pool selection"
./GRASP_Solver_T2T --seed=19141108 --problemFile="20-15-35.txt" -r=250 --resultsFile="Test-20-15-35-Start_LS.csv" --stoppingCriterion=v -v=1471896 --LSStrategy=b --StartSol=R --PRMeth=g --PRPoolSelect=a --PRDir=m --minAlpha=0 --maxAlpha=1 --numAlpha=10 --itsReCalcAlpha=2 --QuickGRASP=1