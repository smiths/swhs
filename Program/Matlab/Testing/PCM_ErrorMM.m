function delta_rel = PCM_ErrorMM(Mfile1, Mfile2, comparator)

%Calculates the relative error between the data in file1 and file2 (PCM output). 

MfileID1 = fopen(Mfile1);
M1 = textscan(MfileID1, '%f %f %f %f %f %f', 'Delimiter', ' ', 'MultipleDelimsAsOne', 1, 'Headerlines', 35);
fclose(MfileID1);

MfileID2 = fopen(Mfile2);
M2 = textscan(MfileID2, '%f %f %f %f %f %f', 'Delimiter', ' ', 'MultipleDelimsAsOne', 1, 'Headerlines', 35);
fclose(MfileID2);

if strcmp(comparator, 'Twat') %Chooses the relevant column vectors from the matrices
	C1 = 2; %Matlab
elseif strcmp(comparator, 'TPCM');
	C1 = 3;
elseif strcmp(comparator, 'Ewat');
	C1 = 5;
elseif strcmp(comparator,'EPCM');
	C1 = 4;
else strcmp(comparator, 'Etot');
	C1 = 6;
	end

M1time = M1{1};
M2time = M2{1};

M1vector = M1{C1};
M2vector = M2{C1};

delta_rel = errorCalc(M1time, M2time, M1vector, M2vector);

