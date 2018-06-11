function delta_rel = PCM_Error(Ffile, Mfile, comparator)

%Calculates the relative error between the data in file1 and file2 (PCM output). 

% F = dlmread(Ffile, '', 23, 0); %Fortran file
% M = dlmread(Mfile, '', 34, 0); %Matlab file

MfileID = fopen(Mfile);
M = textscan(MfileID, '%f %f %f %f %f %f', 'Delimiter', ' ', 'MultipleDelimsAsOne', 1, 'Headerlines', 36);
fclose(MfileID);

FfileID = fopen(Ffile);
F = textscan(FfileID, '%f %f %f %f %f %f %f %f %f %f', 'Delimiter', ' ', 'MultipleDelimsAsOne', 1, 'Headerlines', 23);
fclose(FfileID);

if strcmp(comparator, 'Twat') %Chooses the relevant column vectors from the matrices
	C1 = 3; %Fortran
	C2 = 2; %Matlab
elseif strcmp(comparator, 'TPCM');
	C1 = 4;
	C2 = 3;
elseif strcmp(comparator, 'Ewat');
	C1 = 6;
	C2 = 5;
elseif strcmp(comparator,'EPCM');
	C1 = 5;
	C2 = 4;
elseif strcmp(comparator, 'Etot');
	C1 = 7;
	C2 = 6;
else strcmp(comparator, 'TwatNoP');
	C1 = 9;
	C2 = 2;
	end

Ftime = F{1};
Mtime = M{1};

Fvector = F{C1};
Mvector = M{C2};

delta_rel = errorCalc(Ftime, Mtime, Fvector, Mvector);

