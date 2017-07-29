%this script is used to generate code word with the assistance of file 
%Wimax_Encoding.m

expansion = 96;



%file clean up
fID = fopen('code_word.txt','w');
fclose(fID);

for i = 1:1000

data = randi([0,1],1,20*expansion);

code_word = Wimax_Encoding_56(data,expansion);
    

end