clear all;

fh=fopen('S1.sgn','r');
str=fgetl(fh);
str=fgetl(fh);
str=fgetl(fh);
str=fgetl(fh);

values=fread(fh,10,'uint32');
fclose(fh);