%CLASSIFY_DATA Classify stress, no stress from accelerometer and heart rate
% data.
%   PRED = CLASSIFY_DATA(DATA) returns 1 if stress is predicted by machine
%   learning algorithm.

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

    % Makes predictions using mapped data features
    pred = int32(get_prediction(features));
end

%% Get Features Function
function features = get_features(dataAcc, dataHr) %#codegen
    % Returns the features of a 5 minute window of accelerometer data (dataACC) and heart rate data. Input
    % data is assumed to be clean, in matrix form, and 5 minutes long.

    % Performs the Hilbert transformation to get signal amplitudes
    amp = abs(hilbert(dataAcc));
    ampHr = abs(hilbert(dataHr));

    % Calculates mean of the data
    avgAxis = mean(dataAcc,1);
    avgHr = mean(dataHr,1);

    % Calculates variance of the data
    varAxis = var(dataAcc,0,1);
    varHr = var(dataHr,0,1);

    % Estimates Gamma shape and scale parameters
    [shpElem,sclElem] = gamfitPAL(amp);
    [shpElemHr,sclElemHr] = gamfitPAL(ampHr);
    
    %dist vecotr
    distAcc = sqrt(shpElem.^2 + sclElem.^2);
    distHr = sqrt(shpElemHr.^2 + sclElem.^2);

    % Formats feature vector for machine learning algorithms
    features = [avgAxis varAxis shpElem sclElem distAcc avgHr varHr shpElemHr sclElemHr distHr];
end

%% Get Prediction Function
function prediction = get_prediction(features) %#codegen
    % Returns the prediction of a 5 minute window for the following categories:
    %   Stress = 1
    %   No Stress = 0
    
    % raw model output: 
    %   No Stress    = 2
    %   Stress       = 3

    % Loads models into the workspace
    ML = loadLearnerForCoder('ML_SvNS.mat');

    pred = char(predict(ML,features)); % Predicts Stress vs No Stress

    % Determines dominant prediction using majority-wins rule
    if (pred == 3)
        prediction = int32(1); % Stress
    else
        prediction = int32(0); % No Stress
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