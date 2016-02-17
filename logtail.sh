#/bin/bash

# this script used as  watcher to identify new log files in the file path and bring them into tail output. it kills the current tail process job and start new job.

	# Location of the log files

FILE_PATH="/home/orugam01/tal_test"

	# this flag variable used for checking new files created. initially set to 0.

files_found=0

	# this function used to tail the log files output to stdout. it runs in background continuesly.

tail_process_begin(){

	while true
	do
		tail -f $FILE_PATH/* 
	done
}



# this function checks any new log files created at FILE_PATH.

new_files_checking(){


        NUM_FILES_INITIAL=`ls -l $FILE_PATH/*txt| wc -l | awk '{print $1}'` 

	# sleeping for 50 sec.
        
	sleep 50
 
        NUM_FILES_CURRENT=`ls -l $FILE_PATH/*txt| wc -l | awk '{print $1}'` 

        if [ "$NUM_FILES_CURRENT" -gt "$NUM_FILES_INITIAL" ]; then
		
		files_found=1
        fi
	
}




	#Main Program starts here.
	#echo "PID of the Main script: $$"


	# Start Job in the Background

tail_process_begin &

	# Get the Job_ID

TAIL_JOB_ID=$!

# echo "Background JOB_ID is:"$TAIL_JOB_ID



while true

do

	new_files_checking  

	if [ "$files_found" == 1 ]
	then

	
#		echo "................Identified new Log files. killing Current Job and restarting tail Process...................." 

		kill $TAIL_JOB_ID > /dev/null 2>&1 
	
		files_found=0

		# clear the screen
		clear

		# start the job again

		tail_process_begin &

		TAIL_PROCESS_ID=$!

		#echo "New Background JOB_ID is:"$TAIL_PROCESS_ID

	fi
	
	
done
