#!/bin/bash
CURRENT_DIRECTORY=`pwd`;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
WORK_DIR=`dirname $0`;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
WORK_DIR=`readlink -f $WORK_DIR`;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
RESULT_DIR="$WORK_DIR/results";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
SCRIPTS_DIR="$WORK_DIR/scripts";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi


#function that will compare to file
#param1 is a file 
#param2
compare_file()
{
    file1=$1
    file2=$2
    if ! test $file1; then
        echo "error in compare_file: $1 is not a file" >&2
        return -1
    fi

    if ! test $file2; then
        echo "error in compare_file: $1 is not a file" >&2
        return -1
    fi

    nr1=$(wc -c "$file1" | cut -d' ' -f 1)
    nr2=$(wc -c "$file2" | cut -d' ' -f 1)
    if [ $nr1 -eq $nr2 ]; then
        cmp "$file1" "$file2">/dev/null
        return $?
    fi
    minim=$nr1
    maxim=$nr2
    if [ $nr2 -lt $minim ]; then
         minim=$nr2
         maxim=$nr1
    fi
 
    dif=$((maxim - minim))
    last_ch1=$(tail -c 1 "$file1")
    last_ch2=$(tail -c 1 "$file2")
    
    if [ $dif -ne 1 ]; then
        return 1
    fi 

    if [ "$last_ch1"="\n" -o "$last_ch1"="\n" ]; then
        cmp -n $minim "$file1" "$file2">/dev/null
        return $?
    fi
    cmp "$file1" "$file2">/dev/null
    return $?
}

cd $WORK_DIR;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi

if ! test -d $RESULT_DIR; then
    mkdir $RESULT_DIR;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
fi

if ! test -d $SCRIPTS_DIR; then
    mkdir $SCRIPTS_DIR;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
fi

SUMMARY_RESULT_PATH="$WORK_DIR/summary_result.txt";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
cat /dev/null > "$SUMMARY_RESULT_PATH"
IFS_ORIG=$IFS
IFS=$'\n'
for file_script in $(ls $SCRIPTS_DIR | grep "\.c$"); do
    file_exe=$(echo "$file_script" | sed "s/c$/exe/g")
    result_path="$RESULT_DIR/$file_script.result.txt";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
    script_path="$SCRIPTS_DIR/$file_script";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
    exe_path="$SCRIPTS_DIR/$file_exe";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
    total_points=0
    echo "$file_script">"$result_path"
    gcc "$script_path" -o "$exe_path" >/dev/null 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "$file_script:Compilation Failed!"
	text="$file_script:$total_points"
	echo "TOTAL for $file_script:$total_points"
	echo $text>>"$SUMMARY_RESULT_PATH"
        continue
    fi

    #for each test
    for test_name in `ls | grep test`; do
	IFS=$IFS_ORIG
        #path defines
        test_path="$WORK_DIR/$test_name"
        execute_path="$test_path/execute"
        setup_script_path="$test_path/setup.sh"
	stderror_path="$test_path/stderror"
	stderror_ok_path="$test_path/stderror.ok"
        validate_script_path="$test_path/validate.sh"
        cleanup_script_path="$test_path/cleanup.sh"
        run_path="$test_path/run.sh"
        input_path="$test_path/input"
        input_param_path="$test_path/input_param"
        output_path="$test_path/output"
        output_ok_path="$test_path/output.ok"

        #setup
        if ! test -d "$execute_path"; then
            mkdir "$execute_path";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
        fi
        cp "$exe_path" "$execute_path";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
        cd "$execute_path";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
        #chmod +x "$file_script";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi

        "$setup_script_path"
        if test -f "$input_param_path"; then
        	param=`cat "$input_param_path"`
        else
            param=""
        fi
        rm "$stderror_path" 2>/dev/null
        rm "$output_path" 2>/dev/null

        #execute
        if test -f "$run_path"; then
            "$run_path" "$script_path"
        else
            if ! test -f "$input_path"; then
                touch "$input_path"
            fi
            ./"$file_exe" $param <"$input_path" >"$output_path" 2> "$stderror_path"
        fi
		

        #validate
	if test -f "$stderror_ok_path"; then
            compare_file "$stderror_path" "$stderror_ok_path"
            status=`echo $?`
        elif test -f "$validate_script_path"; then
            status=`"$validate_script_path"; echo $?`
        else
            compare_file "$output_path" "$output_ok_path"
            status=`echo $?`
        fi
        #convert status into points
        points=`expr $status + 1`
        points=`expr $points % 2`

        total_points=`expr $total_points + $points`
        text="$test_name:$points"
        echo "$text">>"$result_path"

        #cleanup
        "$cleanup_script_path"
        cd "$WORK_DIR"

        test -d $execute_path
	status=`echo $?`; 
	if [ $status -ne 0 ]; then
            echo "Nu exista directorul: '$execute_path'=> exit "
            exit 1
        fi
        rm -R $execute_path/* 2>/dev/null
	IFS=$'\n'
    done
    text="$file_script:$total_points"
    echo $text>>"$SUMMARY_RESULT_PATH"
    cat "$result_path"
    echo "TOTAL for $file_script:$total_points"
    rm "$exe_path" 2>/dev/null
done

cd $CURRENT_DIRECTORY

