% Read the data from the text file as a table
dataTable = readtable('C:\Users\acer\OneDrive - Faculty of Electrical Engineering Sarajevo\Desktop\GNU OCTAVE\VSCode_\Srees\example1.txt', 'Delimiter', '\t');

% Access the columns of the table
column1 = dataTable(:, 1);
column2 = dataTable(:, 2);

t = table2array(column1);
i = table2array(column2);

plot(t, i);
grid on;

