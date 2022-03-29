A sample data is passed to ML to 

- check for any errors.
- is the output an expected data type (a bit)?


Test 1: Compilation Error
    Check for compilation error when #include "classify_data.h" exists in the code
    Pass case: 
        - No compilation error encountered

Test 2: Run Time Error
    Check for run time errors when a window of data is passed through the model.
    Pass case:
        - The model either returns 0 or 1. 
        - There are no division by 0 errors.


RESULTS:

Test 1: Compilation Error: Pass
Test 2: Runtime Error: 

