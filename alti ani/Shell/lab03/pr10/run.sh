#!/bin/bash
CURRENT_DIRECTORY=`pwd`;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
WORK_DIR=`dirname $0`;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
WORK_DIR=`readlink -f $WORK_DIR`;if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
RESULT_DIR="$WORK_DIR/results";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
SCRIPTS_DIR="$WORK_DIR/scripts";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi

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
for file_script in `ls $SCRIPTS_DIR`; do
    result_path="$RESULT_DIR/$file_script.result.txt";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
    script_path="$SCRIPTS_DIR/$file_script";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
    total_points=0
    echo "$file_script">"$result_path"

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
        cp "$script_path" "$execute_path";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
        cd "$execute_path";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
        chmod +x "$file_script";if [ $? -ne 0 ]; then    echo "eroare => exit";    exit 1;fi
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
            ./"$file_script" $param <"$input_path" >"$output_path" 2> "$stderror_path"
        fi
		

        #validate
	if test -f "$stderror_ok_path"; then
            cmp "$stderror_path" "$stderror_ok_path">/dev/null	
            status=`echo $?`
        elif test -f "$validate_script_path"; then
            status=`"$validate_script_path"; echo $?`
        else
            cmp "$output_path" "$output_ok_path">/dev/null
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
    echo "TOTAL for $file_script:$total_points"
    echo $text>>"$SUMMARY_RESULT_PATH"
    cat "$result_path"
done

cd $CURRENT_DIRECTORY

