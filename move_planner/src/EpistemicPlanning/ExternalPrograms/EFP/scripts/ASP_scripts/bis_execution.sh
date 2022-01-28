#!/usr/bin/env bash
#This script prints out the time for executing a plan on the same domain with the two version of EFP
#USAGE EXAMPLE (from the project root folder): ". scripts/comparison.sh exp/paper/CC/CC_2_2_3.txt"
#	where "exp/paper/CC/CC_2_2_3.txt" is the path to the domain name


TIMEOUT="30m"
OUT_EXT=".out";

THREADS=4;


#configuration=("auto" "frumpy" "jumpy" "tweety" "handy" "crafty" "trendy" "many");
configuration=("frumpy" "many");

mkdir -p out/ASP_comparison/findingplan/multi_bis/

#REMOVE OLD COPIES
if [ -f out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT" ] ; then
	rm out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT"
fi
echo -e "    	Using planner_$type"

for config in "${configuration[@]}"; do

	echo -e "    		Solving with configuration $config";
	timeout $TIMEOUT clingo asp/testing/planner_multi_bis.lp $@ -t $THREADS --configuration=$config > findingplan_comparison.tmp 2> err_file.tmp
	exit_status=$?;
	TOPRINT="Configuration $config ";
	TOPRINT+="with $THREADS Threads ";
	#TOPRINT+="took "


	if [[ $exit_status -eq 124 ]]; then
		TOPRINT+="TIMED-OUT."
		echo -e "$TOPRINT" >> out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT";
	else
		echo -e "$TOPRINT" >> out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT";
		grep -w "Time" findingplan_comparison.tmp >> out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT";
	fi;

	echo $'\n' >> out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT";
	awk -v RS="\0" -v ORS="" '{gsub(/\s+Time\s+/,"")}7' out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT" > out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})-1.tmp";
	awk -v RS="\0" -v ORS="" '{gsub(/\s*CPU/,", cpu")}7' out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})-1.tmp" > out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*}).tmp";

	rm out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT";
	rm out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})-1.tmp";
	mv out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*}).tmp" out/ASP_comparison/findingplan/multi_bis/"$(basename ${@%%.*})$OUT_EXT"

	mv findingplan_comparison.tmp out/ASP_comparison/findingplan/multi_bis/"plans$OUT_EXT"


	sleep 10s;

done;

rm err_file.tmp;
