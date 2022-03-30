#!/usr/bin/env python3

"""Flattes the 6 columns data that is stored in the SD card to make it ready for mahcine learning model."""

import pandas as pd
import csv


data = pd.read_csv("5_Minute_Data_1.csv", header = None)
len_data = len(data)

# Extract data parameters
start_idx = 0
end_idx = start_idx + round(len_data/5)

epoch_data = data.iloc[start_idx:end_idx,0]
hr = data.iloc[start_idx:end_idx,1]
accx = data.iloc[start_idx:end_idx,2]
accy = data.iloc[start_idx:end_idx,3]
accz = data.iloc[start_idx:end_idx,4]

# Drop gaps in heart rate
hr.dropna(inplace=True)
# flatten data
data_for_embedded_acc = accx.tolist() + accy.tolist() + accz.tolist()
data_for_embedded_hr = hr.tolist()

# Write the flat data
with open("1_Minute_Data_1_embedded_acc.csv", "w") as f:
    write = csv.writer(f)
    write.writerows([data_for_embedded_acc])

with open("1_Minute_Data_1_embedded_hr.csv", "w") as f:
    write = csv.writer(f)
    write.writerows([data_for_embedded_hr])