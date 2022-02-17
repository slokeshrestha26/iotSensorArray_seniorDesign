%CLASSIFY_DATA Classify stress, no stress, and craving accelerometer data.
%   PRED = CLASSIFY_DATA(DATA) returns the class predicted by three machine
%   learning models using the majority wins rule when provided
%   accelerometer data from a Garmin Forerunner watch. The following data
%   features are used by the machine learning models for classification:
%   1. Mean for each signal channel
%   2. Variance for each signal channel
%   3. Gamma shape parameter for each signal channel
%   4. Gamma scale parameter for each signal channel
%   5. Distance constant D-K for each signal channel
%
%   DATA should be a 4-column matrix of accelerometer and heart rate data representing a
%   five-minute window.
%
%   PRED will be a numeric value representing the following classes:
%   Craving      = 1
%   No Stress    = 2
%   Stress       = 3
%   Undetermined = 0
%
%   For information on the shape and scale values:
%   See also GAMFIT.

% Authors: Sloke Shrestha, Dr. Premananda Indic, Joshua Stapp
% The University of Texas at Tyler
% Department of Electrical Engineering
% Version 4.0

%% Classify Data Function
function pred = classify_data(data) %#codegen
% Returns the prediction value for a 5 minute data segment after evaluating
% predictions from 3 machine learning models.

% Exctracts features from accelerometer data
features = get_features(data);

% Maps Garmin features to Empatica E4 format
new_features = map_features(features);

% Makes predictions using mapped data features
pred = int32(get_prediction(new_features));
end

%% Get Features Function
function features = get_features(data) %#codegen
% Returns the features of a 5 minute window of accelerometer data. Input
% data is assumed to be clean, in matrix form, and 5 minutes long.

% Performs the Hilbert transformation to get signal amplitudes
amp = abs(hilbert(data)); 

% Calculates mean of the data
avgAxis = mean(data,1);

% Calculates variance of the data
varAxis = var(data,0,1);

% Estimates Gamma shape and scale parameters
[shpElem,sclElem] = gamfitPAL(amp);

% Formats feature vector for machine learning algorithms
features = [avgAxis varAxis shpElem sclElem];
end

%% Map Features Function
function new_features = map_features(features) %#codegen
% Returns data features mapped from Garmin format to Empatica E4 format.

% Initializes new feature vector
new_features = zeros(1,length(features) + 3);

% Maps Garmin axis mean features to Empatica E4 format
new_features(1) = 1.90770314*features(1) + 8.04472341;
new_features(2) = 1.97913774*features(2) - 1.05064168;
new_features(3) = 2*features(3) - 4 ;

% Maps Garmin axis variance features to Empatica E4 format
new_features(4) = 3.80290914*features(4) + 14.76397674;
new_features(5) = 4.3*features(5) - 2.96821221;
new_features(6) = 3.25*features(6) + 4.64261691;

% Maps Garmin axis shape features to Empatica E4 format
new_features(7) = 0.9*features(7);
new_features(8) = 0.9*features(8);
new_features(9) = 0.84*features(9);

% Maps Garmin axis scale features to Empatica E4 format
new_features(10) = 2.15*features(10);
new_features(11) = 2.15*features(11);
new_features(12) = 2*features(12);

% Calculates new distance constant in the Empatica E4 format
new_features(13) = sqrt(new_features(7)^2 + new_features(10)^2);
new_features(14) = sqrt(new_features(8)^2 + new_features(11)^2);
new_features(15) = sqrt(new_features(9)^2 + new_features(12)^2);
end

%% Get Prediction Function
function prediction = get_prediction(features) %#codegen
% Returns the prediction of a 5 minute window for the following categories:
%   Craving      = 1
%   No Stress    = 2
%   Stress       = 3
%   Undetermined = 0

% Loads models into the workspace
ML_CvNS = loadLearnerForCoder('ML_CvNS.mat');
ML_CvS  = loadLearnerForCoder('ML_CvS.mat');
ML_SvNS = loadLearnerForCoder('ML_SvNS.mat');

pred_CNS = char(predict(ML_CvNS,features)); % Predicts Craving vs No Stress
pred_CS  = char(predict(ML_CvS,features));  % Predicts Craving vs Stress
pred_SNS = char(predict(ML_SvNS,features)); % Predicts Stress vs No Stress

% Determines dominant prediction using majority-wins rule
if (pred_CNS == pred_CS)
    prediction = int32(1); % Craving
elseif (pred_CNS == pred_SNS)
    prediction = int32(2); % No Stress
elseif (pred_SNS == pred_CS)
    prediction = int32(3); % Stress
else
    prediction = int32(0); % Undetermined
end
end

%% PAL gamfit Estimation Function
function [sh,sc] = gamfitPAL(x) %#codegen
% Estimates the gamma shape and scale parameters of a dataset.

% Makes any zeros nonzero to prevent invalid logarithmic operations
x(x == 0) = 1e-5;

% Calculates variables for closed form gamma parameter estimation
N = int32(length(x));
sumX = sum(x,1);
num = double(N)*sumX;
den = double(N)*sum(x.*log(x),1) - sum(log(x),1).*sumX;

% Estimates closed form shape and scale values
sh = num./den;
sc = 1/double(N^2)*den;
end