#include "sched.h"

void FCFS(Process list[], int listSize) {
    //Sorting all the processes based on arrival time
    for (size_t i = 0; i < listSize - 1; i++) {
        for (size_t j = 0; j < listSize - 1; j++) {
            if (list[j].ArrivalTime > list[j+1].ArrivalTime) {
                Process temp = list[j+1];
                list[j+1] = list[j];
                list[j] = temp;
            }
        }
    }
    //loop through the processes according to the sorted list and add wait time based on time passed minust the arrival time.
    int timePassed = 0;
    for (size_t i = 0; i < listSize; i++) {
        list[i].WaitTime = 0;
        list[i].WaitTime = timePassed - list[i].ArrivalTime;
        timePassed += list[i].BurstTime;
        printf("PID:%d\nWait time:%d\nTurn over time:%d\n\n",list[i].PID, list[i].WaitTime, list[i].BurstTime + list[i].WaitTime);
    }

        
}

void SJF(Process list[], int listSize) {
    //Sorting processes based on arrival time
    for (size_t i = 0; i < listSize - 1; i++) {
        for (size_t j = 0; j < listSize - 1; j++) {
            if (list[j].ArrivalTime > list[j+1].ArrivalTime) {
                Process temp = list[j+1];
                list[j+1] = list[j];
                list[j] = temp;
            }
        }
    }

    //Sorting processes based on burst time making sure not to mess with processes with different arrival times
    for (size_t i = 0; i < listSize - 1; i++) {
        for (size_t j = 0; j < listSize - 1; j++) {
            if (list[j].ArrivalTime == list[j+1].ArrivalTime && list[j].BurstTime > list[j+1].BurstTime) {
                Process temp = list[j+1];
                list[j+1] = list[j];
                list[j] = temp;
            }
        }
    }

    int timePassed = 0;
    for (size_t i = 0; i < listSize; i++) {
        list[i].WaitTime = 0;
        list[i].WaitTime = timePassed - list[i].ArrivalTime;
        timePassed += list[i].BurstTime;
        printf("PID:%d\nWait time:%d\nTurn over time:%d\n\n",list[i].PID, list[i].WaitTime, list[i].BurstTime + list[i].WaitTime);
        list[i].ArrivalTime = __INT16_MAX__;
        //Every time a process is run it gets moved to the back of the list using __INT16_MAX__ and the list gets sorted again
        for (size_t k = 0; k < listSize - 1; k++) {
            for (size_t j = 0; j < listSize - 1; j++) {
                if (list[j].ArrivalTime <= timePassed && list[j+1].ArrivalTime <= timePassed &&list[j].BurstTime > list[j+1].BurstTime) {
                    Process temp = list[j+1];
                    list[j+1] = list[j];
                    list[j] = temp;
                }
            }
        }
    }
}

void RR(Process list[], int listSize, int quantum) {
//    for (size_t i = 0; i < listSize - 1; i++) {
//        for (size_t j = 0; j < listSize - 1; j++) {
//            if (list[j].ArrivalTime > list[j+1].ArrivalTime) {
//                Process temp = list[j+1];
//                list[j+1] = list[j];
//                list[j] = temp;
//            }
//        }
//    }

    //RoundRobin Queue
    int queue[listSize];
    for (size_t i = 0; i < listSize; i++) {
        queue[i] = -1;
    }

    int doneRunning = 0; //Counts how many processes have finished
    int queueFull = 0; //Boolean Checks if all processes are added to the queue
    int timePassed = 0; //Keeps track of how much time has passed
    int thingsInQueue = 0; //Boolean for if the queue is empty or not (if no process has an arival time of 0 this avoid infinitely sorting -1)
    while(listSize - doneRunning != 0) {
        //If the queue isn't full we wan't to add a new process
        if (!queueFull) {
            for (size_t i = 0; i < listSize; i++) {
                //If the process has an arrival time less than or equal to the time that has passed then it will be added to the queue
                if (list[i].ArrivalTime <= timePassed) {
                    int inList = 0;
                    //Makes sure we don't add the same process more than once
                    for (size_t j = 0; j < listSize; j++) {
                        if (list[i].PID == queue[j]) {
                            inList = 1;
                        }
                    }
                    //If the process wasn't already in the list we add it to the queue
                    if (!inList) {
                        //Flips boolean value to make sure we know something is in the queue
                        thingsInQueue = 1;
                        for (size_t j = 0; j < listSize; j++) {
                            if (queue[j] == -1) {
                                //Add the PID to the queue and initialize values
                                queue[j] = list[i].PID;
                                list[i].TimeRun = 0;
                                list[i].WaitTime = 0;
                                list[i].RanLast = 0;
                                //If all processes have been added then we set that the queue is full and we no longer loop to add processes.
                                if (j == listSize - 1 - doneRunning) {
                                    queueFull = 1;
                                }
                                break;
                            }           
                        }
                    }
                }
            }  
        }
        //If there are things in the queue but no other process was added we pick the process back up from where it left off
        while (thingsInQueue && queue[0] == -1) {
            int temp = queue[0];
            for (size_t j = 0; j < listSize - 1; j++) {
                queue[j] = queue[j+1];
            }
            queue[listSize-1] = temp;
        }
        
        for (size_t i = 0; i < listSize; i++) {
            //Loop through until we find the process for the corresponding PID in the queue
            if (queue[0] == list[i].PID) {
                //If the process can finish right away or has enough time run that it can reach it's burst time in this quantum step this if block will finish the process
                if (quantum >= list[i].BurstTime - list[i].TimeRun) {
                    int timeLeft = list[i].BurstTime - list[i].TimeRun;
                    list[i].TimeRun = list[i].BurstTime;
                    if (list[i].RanLast == 0) {
                        list[i].WaitTime = timePassed - list[i].ArrivalTime;
                    } else {
                        list[i].WaitTime += timePassed - list[i].RanLast; 
                    }
                    
                    doneRunning++;
                    int temp = queue[0];
                    for (size_t j = 0; j < listSize - 1; j++) {
                        queue[j] = queue[j+1];
                    }
                    queue[listSize-1] = temp;
                    timePassed += timeLeft - 1;
                //If the process couldn't finish it will proceed forward with the next quantum step
                } else {
                    list[i].TimeRun += quantum;
                    int waittime = list[i].WaitTime;
                    int ranlast = list[i].RanLast;


                    if (list[i].RanLast != 0) {
                        list[i].WaitTime += timePassed - list[i].RanLast;
                    } else {
                        list[i].WaitTime += timePassed - list[i].ArrivalTime;
                    }
                    list[i].RanLast = timePassed + quantum;
                    int temp = queue[0];
                    int flag = 0;
                    for (size_t j = 0; j < listSize - doneRunning - 1; j++) {
                        queue[j] = queue[j+1];
                    }
                    queue[listSize-doneRunning-1] = temp;
                    timePassed += quantum - 1;
                }
                break;
            }
        }
        timePassed++;
    }

    for (size_t i = 0; i < listSize; i++) {
        printf("PID:%d\nWait time:%d\nTurn over time:%d\n\n",list[i].PID, list[i].WaitTime, list[i].WaitTime + list[i].BurstTime);
    }
}

int main(int argc, char const *argv[]) {
    const char* filename = 0;
    const char* algorithm = 0;
    int quantum = 0;
    int f = 1, a = 1, q = 1; //Booleans
    int mode = 0;
    FILE *infile;

    if (argc < 5 || argc % 2 == 0) {
        printf("You entered an incorrect amount of flags\n");
        return 1;
    }

    for (size_t i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'f' && f) {
                filename = argv[++i];
                f = 0;
            } else if (argv[i][1] == 'a' && a) {
                algorithm = argv[++i];
                a = 0;
            } else if (argv[i][1] == 'q' && q) {
                quantum = atoi(argv[++i]);
                q = 0;
            } else {
                printf("The flags you've entered don't work. Please use one \"-f\" flag before the filename and one \"-a\" flag for the algorithm\nPlease only use the \"-q\" flag when you select RR as algorithm\n");
                return 1;
            }
        }    
    }

    if (f || a) {
        printf("The program can't run without a valid \"-f\" or \"-a\" entry");
        return 1;
    }

    if (!strcmp(algorithm, "FCFS")) {
        mode = 1;
    } else if (!strcmp(algorithm, "SJF")) {
        mode = 2;
    } else if (!strcmp(algorithm, "RR")) {
        mode = 3;
        if (q) {
            printf("You must enter a milisecond value to \"-q\" if you want to use the RR algorithm\n");
            return 1;
        }
    } else {
        printf("No valid algorithm was selected please enter \"FCFS\" or \"SJF\" or \"RR\"\n");
        return 1;
    }

    if (!(infile = fopen(filename, "r"))) {
        printf("Could not find file of name %s!\nPlease enter a valid file name!\n",filename);
        return 1;
    }

    int lines = 0;
    char temp[15];
    while (fscanf(infile, "%s", temp) != EOF) {
        lines++;
    }
    Process processList[lines];
    rewind(infile);
    int currentLine = 0;
    while (fscanf(infile, "%s", temp) != EOF) {
        char buff[16] = "";
        int counter = 0;
        int recievedInputs = 0;
        for (size_t i = 0; temp[i] != '\0'; i++) {
            if (temp[i] == ',' || temp[i] == '\n') {
                buff[counter] = '\n';
                if (recievedInputs == 0) {
                    processList[currentLine].PID = atoi(buff);
                    recievedInputs++;
                } else {
                    processList[currentLine].ArrivalTime = atoi(buff);
                }
                counter = 0;
            } else {
                buff[counter++] = temp[i];
            }
        }
        buff[counter] = '\n';
        processList[currentLine].BurstTime = atoi(buff);
        currentLine++;
    }

    if (mode == 1) {
        FCFS(processList, lines);
    } else if (mode == 2) {
        SJF(processList, lines);
    } else {
        RR(processList, lines, quantum);
    }

    return 0;
}