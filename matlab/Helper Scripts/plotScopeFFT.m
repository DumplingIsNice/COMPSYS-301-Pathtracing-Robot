% 10/08/2021
% Callum McDowell - CS301

fileName = uigetfile('*.csv');

% Uncomment this to hardcode:
% fileName = "scope_nofilter10k_tube100Hz.csv";

if (fileName == double(0))
    fprintf("Invalid file name\n");
    return
end

T = readtable(fileName);

%% Find and Plot FFT
headerRows = 2;
logSampleSize = 2000;

startIndex = 1 + headerRows + logSampleSize;

Hz = table2array(T(startIndex:end,1));
dBV = table2array(T(startIndex:end,2));

close
figure
plot(Hz,dBV);
xlabel('Hz')
ylabel('dBV')
title('FFT From Scope');

%% Find and Plot Signal
firstDataIndex = 1 + headerRows;
t = table2array(T(firstDataIndex:startIndex,1));
signal = table2array(T(firstDataIndex:startIndex,2));

figure
subplot(2,1,1)
plot(t,signal);
xlabel('t (s)')
ylabel('V')
title('Signal');

subplot(2,1,2)      % Replot for comparison
plot(Hz,dBV);
xlabel('Hz')
ylabel('dBV')
title('FFT From Scope');

