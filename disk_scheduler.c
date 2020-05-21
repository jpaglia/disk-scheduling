/**
 * Disk Scheduler
 * Author: Julia Paglia
 */

#include <stdio.h>
#include <stdlib.h>

//*********************************
// FILE NAMES CAN BE CHANGED HERE
//*********************************
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
//*********************************
#define CYLINDERS 100
#define CYL_REQUESTS 25
#define INITIAL_HEAD_POS 33

//Prototypes
void fcfs(void);
void scan(void);
void c_scan(void);
void quicksort(int l, int h);

int inputs[CYL_REQUESTS];

int main(int argc, char *argv[])
{
    //Save cylinder numbers from INPUT_FILE into an array of size 25
    FILE *in_file = fopen(INPUT_FILE, "r");
    char line[sizeof(int)];
    int i = 0;
    while (fgets(line, sizeof(line), in_file)) {
        inputs[i] = atoi(line);
        i++;
    }
    fclose(in_file);

    printf("Running FCFS on %s...\n", INPUT_FILE);
    fcfs();
    //******************************************
    //Sort the inputs array for SCAN and C_SCAN
    quicksort(0, CYL_REQUESTS - 1);
    //******************************************
    printf("Running SCAN on %s...\n", INPUT_FILE);
    scan();
    printf("Running C_SCAN on %s...\n", INPUT_FILE);
    c_scan();
    printf("Finished running disk scheduling algorithms. Check %s for results.\n", OUTPUT_FILE);
} 

void fcfs(void) {
    FILE *out_file = fopen(OUTPUT_FILE, "w+");
    //Print initial info to OUTPUT_FILE
    fprintf(out_file, "\nFCFS Algorithm");
    fprintf(out_file, "\nInitial head position = %d", INITIAL_HEAD_POS);
    fprintf(out_file, "\nSeek Sequence is:");

    //The inputs array is already in FCFS ordering
    //Track the head movements
    int total_head_moves = 0;
    int curr_head = INITIAL_HEAD_POS;

    for (int f = 0; f < CYL_REQUESTS; f++) {
        if (curr_head > inputs[f]) {
            total_head_moves += curr_head - inputs[f];
        } else {
            total_head_moves += inputs[f] - curr_head;
        }
        fprintf(out_file, "\n%d", inputs[f]);
        curr_head = inputs[f];
    }
    printf("Total head movement for FCFS = %d\n", total_head_moves);
    fprintf(out_file, "\nTotal head movement for FCFS = %d", total_head_moves);
    fclose(out_file);
}

void scan(void) {
    FILE *out_file = fopen(OUTPUT_FILE, "a+");
    //Append initial info to OUTPUT_FILE
    fprintf(out_file, "\n\nSCAN Algorithm");
    fprintf(out_file, "\nInitial head position = %d", INITIAL_HEAD_POS);
    fprintf(out_file, "\nSeek Sequence is:");

    //Track the head movements
    int total_head_moves = 0;
    int curr_head = INITIAL_HEAD_POS;

    //Iterate through the sorted array in the order of the SCAN algorithm
    //Move head toward 0 end of disk first

    //STEP 1: Get the index of where the head begins
    int head_index = 0;
    while ((head_index < CYL_REQUESTS - 1) && (inputs[head_index + 1] <= INITIAL_HEAD_POS)) {
        head_index++;
    }

    //STEP 2: Iterate through the array in DECREASING ORDER
    //        Start from the head and move until index 0 is reached
    //        Calculate the running sum of head movements
    for (int i = head_index; i >= 0; i--) {
        fprintf(out_file, "\n%d", inputs[i]);
        if (curr_head > inputs[i]) {
            total_head_moves += curr_head - inputs[i];
        } else {
            total_head_moves += inputs[i] - curr_head;
            //Handle edge case when the head index input is > INITIAL_HEAD_POS
            if (inputs[head_index] > INITIAL_HEAD_POS) {
                total_head_moves += 2 * curr_head;
            }
        }
        curr_head = inputs[i];
    }

    //STEP 3: Edge case for head movement, head is changing directions on the disk
    //        If it is NOT the last element, the head movement will change directions
    if (head_index < CYL_REQUESTS - 1) {
        if ((inputs[head_index] <= INITIAL_HEAD_POS) && (inputs[head_index] <= inputs[head_index + 1])) {
            total_head_moves += 2 * curr_head;
        }

        //STEP 4: Iterate through the array in INCREASING ORDER
        //        Start from the head position + 1 and move until last element is reached
        //        Calculate the running sum of head movements
        for (int j = head_index + 1; j < CYL_REQUESTS; j++) {
            fprintf(out_file, "\n%d", inputs[j]);
            if (curr_head > inputs[j]) {
                total_head_moves += curr_head - inputs[j];
            } else {
                total_head_moves += inputs[j] - curr_head;
            }
            curr_head = inputs[j];
        }
    }
    printf("Total head movement for SCAN = %d\n", total_head_moves);
    fprintf(out_file, "\nTotal head movement for SCAN = %d", total_head_moves);
    fclose(out_file);
}

void c_scan(void) {
    FILE *out_file = fopen(OUTPUT_FILE, "a+");
    //Append initial info to OUTPUT_FILE
    fprintf(out_file, "\n\nC_SCAN Algorithm");
    fprintf(out_file, "\nInitial head position = %d", INITIAL_HEAD_POS);
    fprintf(out_file, "\nSeek Sequence is:");

    //Track the head movements
    int total_head_moves = 0;
    int curr_head = INITIAL_HEAD_POS;

    //Iterate through the sorted array in the order of the C_SCAN algorithm
    //Move head toward 99 end of disk first

    //STEP 1: Get the index of where the head begins
    int head_index = 0;
    while ((head_index < CYL_REQUESTS - 1) && (inputs[head_index] < INITIAL_HEAD_POS)) {
        head_index++;
    }

    //STEP 2: Iterate through the array in INCREASING ORDER
    //        Start from the head and move until index 24 is reached
    //        Calculate the running sum of head movements
    for (int i = head_index; i < CYL_REQUESTS; i++) {
        if (head_index < CYL_REQUESTS - 1) {
            fprintf(out_file, "\n%d", inputs[i]);
            if (curr_head < inputs[i]) {
                total_head_moves += inputs[i] - curr_head;
                curr_head = inputs[i];
            }
        } else {
            curr_head = INITIAL_HEAD_POS;
        }
    }

    //STEP 3: Edge case for head movement, head is changing directions on the disk
    //        If it is NOT the last element, the head movement will change directions
    if (head_index > 0) {
        //Handle edge case when the head index input is < INITIAL_HEAD_POS
        if ((inputs[head_index] <= inputs[head_index + 1]) | (inputs[head_index] <= INITIAL_HEAD_POS )) {
            total_head_moves += (CYLINDERS - 1 - curr_head);
            total_head_moves += CYLINDERS - 1;
            total_head_moves += inputs[0];
        }
    }
    //STEP 4: Iterate through the array in INCREASING ORDER
    //        Start from the head position + 1 and move until last element is reached
    //        Calculate the running sum of head movements
    for (int j = 0; j < head_index; j++) {
        fprintf(out_file, "\n%d", inputs[j]);
        if (curr_head <= inputs[j]) {
            total_head_moves += inputs[j] - curr_head;
        }
        curr_head = inputs[j];
    }
    if (head_index == CYL_REQUESTS - 1) {
        fprintf(out_file, "\n%d", inputs[head_index]);
        total_head_moves += inputs[head_index] - curr_head;
    }

    printf("Total head movement for C_SCAN = %d\n", total_head_moves);
    fprintf(out_file, "\nTotal head movement for C_SCAN = %d", total_head_moves);
    fclose(out_file);
}

void quicksort(int l, int h) {
    if (l < h) {
        int piv = inputs[h];
        int index_low = l - 1;
        //Create a partition for the next recursive call
        for (int index_high = l; index_high <= h - 1; index_high++) {
            //If current element is less than pivot element
            if (inputs[index_high] < piv) {
                index_low++;
                int temp1 = inputs[index_low];
                inputs[index_low] = inputs[index_high];
                inputs[index_high] = temp1;
            }
        }
        int temp2 = inputs[index_low + 1];
        inputs[index_low + 1] = inputs[h];
        inputs[h] = temp2;
        int partition = index_low + 1;

        //Recursive call for before the partition
        quicksort(l, partition - 1);   
        //Recursive call for after the partition
        quicksort(partition + 1, h);
    }
}


