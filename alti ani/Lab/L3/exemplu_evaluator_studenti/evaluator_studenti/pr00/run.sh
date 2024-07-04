#!/bin/bash
CURRENT_DIRECTORY=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`realpath $WORK_DIR`
RESULT_DIR="$WORK_DIR/results"
SCRIPTS_DIR="$WORK_DIR/scripts"

cd $WORK_DIR

if ! test -d $RESULT_DIR; then
    mkdir $RESULT_DIR
fi

if ! test -d $SCRIPTS_DIR; then
    mkdir $SCRIPTS_DIR
fi

SUMMARY_RESULT_PATH="$WORK_DIR/summary_result.txt"
cat /dev/null > "$SUMMARY_RESULT_PATH"
IFS_ORIG=$IFS
IFS=$'\n'
for file_script in `ls $SCRIPTS_DIR`; do
    result_path="$RESULT_DIR/$file_script.result.txt"
    script_path="$SCRIPTS_DIR/$file_script"
    total_points=0
    echo "$file_script">"$result_path"

    #for each test
    for test_name in `ls | grep test`; do
	IFS=$IFS_ORIG
        #path defines
        test_path="$WORK_DIR/$test_name"
        execute_path="$test_path/execute"
        setup_script_path="$test_path/setup.sh"
        validate_script_path="$test_path/validate.sh"
        cleanup_script_path="$test_path/cleanup.sh"
        run_path="$test_path/run.sh"
        input_path="$test_path/input"
        input_param_path="$test_path/input_param"
        output_path="$test_path/output"
        output_ok_path="$test_path/output.ok"

        #setup
        if ! test -d "$execute_path"; then
            mkdir "$execute_path"
        fi
        cp "$script_path" "$execute_path"
        cd "$execute_path"
        chmod +x "$file_script"
        "$setup_script_path"
        if test -f "$input_param_path"; then
        	param=`cat "$input_param_path"`
        else
            param=""
        fi


        #execute
        if test -f "$run_path"; then
            "$run_path" "$script_path"
        else
            if ! test -f "$input_path"; then
                touch "$input_path"
            fi
            ./"$file_script" $param <"$input_path" >"$output_path"
        fi
		

        #validate
        if test -f "$validate_script_path"; then
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
        rm -R $execute_path/* 2>/dev/null
        #rmdir "$execute_path"
	IFS=$'\n'
    done
    text="$file_script:$total_points"
    echo "TOTAL for $file_script:$total_points"
    echo $text>>"$SUMMARY_RESULT_PATH"
    cat "$result_path"
done

cd $CURRENT_DIRECTORY

