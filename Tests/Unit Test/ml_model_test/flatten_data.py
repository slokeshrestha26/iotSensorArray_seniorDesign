#!/usr/bin/env python3

"""Flattes the 6 columns data that is stored in the SD card to make it ready for mahcine learning model."""

import pandas as pd
import csv


data = pd.read_csv("Tests/Unit Test/ml_model_test/5_Minute_Data_1.csv", header = None)

# Extract data parameters
epoch_data = data.iloc[:,0]
hr = data.iloc[:,1]
accx = data.iloc[:,2]
accy = data.iloc[:,3]
accz = data.iloc[:,4]

# Drop gaps in heart rate
hr.dropna(inplace=True)
# flatten data
data_for_embedded_acc = accx.tolist() + accy.tolist() + accz.tolist()
data_for_embedded_hr = hr.tolist()

# Write the flat data
with open("5_Minute_Data_1_embedded_acc.csv", "w") as f:
    write = csv.writer(f)
    write.writerows([data_for_embedded_acc])

with open("5_Minute_Data_1_embedded_hr.csv", "w") as f:
    write = csv.writer(f)
    write.writerows([data_for_embedded_hr])