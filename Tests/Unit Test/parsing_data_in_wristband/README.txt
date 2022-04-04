This test uses a trivial model to classify the data

Test 1: DATA POPULAION TEST. This test checks if the data array is populated before sending it to the model.. This test checks if the data array is populated before sending it to the model.

    Pass Cases:
        a) The contents of data_acc at indexes: [1557, 1558, 1559, 3117, 3118, 3119, 4677, 4678, 4679] are [-504,-504,-504, 504, 504,504,-504,-504,-504] resectively.
        b) The content of data_hr at index [57, 58,59] are [504,504,504]

Test 2: INDEX RESET TEST. This test checks if the void reset_idx(int& accx, int& accy, int& accz, int& hr);

    Pass Cases:
        Before reset_idx is called:
            a) idx_acc: 1550
            b) idx_accy: 3120
            c) idx_accz: 4680
            d) idx_hr: 60
        After reset_idx is called:
            a) idx_acc: 0
            b) idx_accy: 1560
            c) idx_accz: 3120
            d) idx_hr: 0


OUTPUT ON SERIAL MONITOR:

    =======Test 1: DATA POPULAION TEST=========
    Contents of data_acc at indexes: [1557, 1558, 1559, 3117, 3118, 3119, 4677, 4678, 4679] are: -504.00,-504.00,-504.00,504.00,504.00,504.00,-504.00,-504.00,-504.00,

    The content of data_hr at index [57, 58,59]: 504.00,504.00,504.00,


    =======Test 2: INDEX RESET TEST=========
    Before reset_idx is called: 
    idx_accx: 1560
    idx_accy: 3120
    idx_accz: 4680
    idx_hr: 1559
    After reset_idx is called: 
    idx_accx: 0
    idx_accy: 1560
    idx_accz: 3120
    idx_hr: 4680

RESULTS:
    Test 1: PASSED
        a) PASSED
        B) PASSED

    Test 2: PASSED
        Before reset_idx is called
            a) PASSED
            b) PASSED
            c) PASSED
            d) PASSED
        After reset_idx is called
            a) PASSED
            b) PASSED
            c) PASSED
            d) PASSED


