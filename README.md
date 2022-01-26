# IoT Wearable Sensor Array

## Summary of the Project
Current wearable sensor arrays require the use of smartphone for data processing and health inference. While this smartphone-oriented paradigm for health application is adequate for most users, certain demographics, especially elderly population and ones with mental illness, are barred from current mobile health technology. Therefore, we propose a wearable sensor array framework with a wearable processing unit to process data and provide health inference. 

This proposed system consists of two modules: a) processing module which is wearable on the waist and b) physiological data acquisition module which is wearable on the wrist. This system is intended to be scalable for more sensor modules as user needs. That is, the user could add Electroencephalography (EEG), Electrocardiography (ECG), Electrodermal Activity (EDA) as per their needs. The system uses TinyScreen+ (with Atmel SAMD21 32-bit ARM processor) which is wearable on the wrist and Teensy 4.1 (ARM M7 core) which is wearable on the waist. Tri-axis accelerometer and heart data is be collected from the wrist. The collected data is used to train a machine learning model to detect stress in the users. The model is embedded in the Teensy 4.1 to provide health inference on the edge. Relevant health inference is displayed in the OLED display on the wrist. 


## Assembly for Wristband
We highly encourage you to go through the [webpage from tinycircuits](https://tinycircuits.com/blogs/learn/custom-fitness-tracker?_pos=3&_sid=c4ce48fce&_ss=r) where they explain a fitness tracker implementation using the hardware components we are using. 

