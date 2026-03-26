#include <stdio.h>
#include <stdlib.h>

/**
 * target: The remaining sum we are trying to reach.
 * index: The current position in our input numbers array.
 * nums: The array containing all the numbers from the arguments.
 * n: The total count of numbers in 'nums'.
 * subset: A temporary array to store the numbers we've picked.
 * sel_size: The number of elements currently in the 'subset' array.
 */
void find_subsets(int target, int index, int *nums, int n, int *subset, int sel_size) {
    
    // SUCCESS: If target reaches 0, the current subset adds up to the original target.
    if (target == 0) {
        for (int i = 0; i < sel_size; i++) {
            printf("%d%s", subset[i], (i == sel_size - 1) ? "" : " "); // Print space after each number except the last one
        }
        printf("\n");
        return;
    }

    // BASE CASE: If we've looked at all numbers, stop this branch of the search.
    if (index == n) {
        return;
    }

    // OPTION 1: "INCLUDE" the current number
    // We add nums[index] to our subset and subtract its value from the target.
    subset[sel_size] = nums[index];
    find_subsets(target - nums[index], index + 1, nums, n, subset, sel_size + 1);

    // OPTION 2: "EXCLUDE" the current number
    // We skip nums[index] and try to reach the same target using the remaining numbers.
    find_subsets(target, index + 1, nums, n, subset, sel_size);
}

int main(int argc, char **argv) {
    // We need at least the program name and the target sum.
    if (argc < 2) {
        return (1);
    }

    int target = atoi(argv[1]);
    int n = argc - 2;
    
    // If no numbers are provided after the target, we only handle the target 0 case.
    if (n <= 0) 
    {
        if (target == 0) 
            printf("\n");
        return 0;
    }

    int nums[n];
    int subset[n];

    // Convert the command-line arguments into an integer array.
    for (int i = 0; i < n; i++) {
        nums[i] = atoi(argv[i + 2]);
    }

    // SPECIAL CASE: If target is 0, the 'empty' set is the first valid possibility.
    if (target == 0) {
        printf("\n");
    }

    // Start the recursive search starting from the first number (index 0).
    find_subsets(target, 0, nums, n, subset, 0);

    return 0;
}

//method -2 : no empty set checks

#include <stdio.h>
#include <stdlib.h>

void find_subsets(int target, int index, int *nums, int n, int *subset, int sel_size) {
    if (target == 0)
    {
        for (int i = 0; i < sel_size; i++) {
            printf("%d%s", subset[i], (i == sel_size - 1) ? "" : " ");
        }
        printf("\n"); 
        return;
    }

    if (index == n) 
        return;

    // Include the current number
    subset[sel_size] = nums[index];
    find_subsets(target - nums[index], index + 1, nums, n, subset, sel_size + 1);

    // Exclude the current number
    find_subsets(target, index + 1, nums, n, subset, sel_size);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        return (1);
    }

    int target = atoi(argv[1]);
    int n = argc - 2;

    if (n <= 0) {
        return 0;
    }

    int nums[n];
    int subset[n];

    for (int i = 0; i < n; i++) {
        nums[i] = atoi(argv[i + 2]);
    }

    find_subsets(target, 0, nums, n, subset, 0);

    return 0;
}
