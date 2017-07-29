function [ code_word,syndrome ] = Wimax_Encoding( data, expansion)
%WIMAX_ENCODING Summary of this function goes here
% this fucntion encodes the data via back_substitution,
%   Detailed explanation goes here
% this function is very primitive, aka its performance suffers from various
% reasons. However it should get the job done
% Input, data --> data word, expansion --> expansion factor, must be
% divisible by 4 and ranges from 24 to 96
% the size of the data must be interms of 12*expansion

if(size(data)~=12*expansion)
%invalid code word
    return; 
end



model_matrix= [
-1 94 73 -1 -1 -1 -1 -1 55 83 -1 -1 7 0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1;
-1 27 -1 -1 -1 22 79 9 -1 -1 -1 12 -1 0 0 -1 -1 -1 -1 -1 -1 -1 -1 -1;
-1 -1 -1 24 22 81 -1 33 -1 -1 -1 0 -1 -1 0 0 -1 -1 -1 -1 -1 -1 -1 -1;
61 -1 47 -1 -1 -1 -1 -1 65 25 -1 -1 -1 -1 -1 0 0 -1 -1 -1 -1 -1 -1 -1;
-1 -1 39 -1 -1 -1 84 -1 -1 41 72 -1 -1 -1 -1 -1 0 0 -1 -1 -1 -1 -1 -1;
-1 -1 -1 -1 46 40 -1 82 -1 -1 -1 79 0 -1 -1 -1 -1 0 0 -1 -1 -1 -1 -1;
-1 -1 95 53 -1 -1 -1 -1 -1 14 18 -1 -1 -1 -1 -1 -1 -1 0 0 -1 -1 -1 -1;
-1 11 73 -1 -1 -1 2 -1 -1 47 -1 -1 -1 -1 -1 -1 -1 -1 -1 0 0 -1 -1 -1;
12 -1 -1 -1 83 24 -1 43 -1 -1 -1 51 -1 -1 -1 -1 -1 -1 -1 -1 0 0 -1 -1;
-1 -1 -1 -1 -1 94 -1 59 -1 -1 70 72 -1 -1 -1 -1 -1 -1 -1 -1 -1 0 0 -1;
-1 -1 7 65 -1 -1 -1 -1 39 49 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 0 0;
43 -1 -1 -1 -1 66 -1 41 -1 -1 -1 26 7 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 0;
];

%no puncture yet

n = 24;
m = 12;
g = 1;

final = [];

column = [];

for i = 1:n
    %clear column
    column = [];
    
    for j = 1:m

        
       if(model_matrix(j,i) >= 0)    
           %puncture included
          column = vertcat(column,circshift(eye(expansion),floor(model_matrix(j,i)*expansion/96),2));
       else
          column = vertcat(column,zeros(expansion));    
       end
    end

    final = horzcat(final,column);
    
end


n = n*expansion;
m = m*expansion;
g = g*expansion;


A = final(1:m-g,1:n-m);

B = final(1:m-g,n-m+1:n-m+g);

C = final(m-g+1:m,1:n-m);

D = final(m-g+1:m,n-m+1:n-m+g);

E = final(m-g+1:m,n-m+g+1:n);

T = final(1:m-g,n-m+g+1:n);

test = inv(T);

test = test.^2;

factor2 = E*test*B+D;

factor2 = factor2.^2;

factor2 = mod(factor2,2);



data_trans = transpose(data);

p1 = (factor2)\(E*test*A*data_trans+C*data_trans);

p2 = test*(A*data_trans+B*p1);

code_word = [data,transpose(p1),transpose(p2)];

code_word = mod(code_word.^2,2);

%output using files 

fileID = fopen('code_word.txt','a');

for i = 1:n
    fprintf(fileID,'%d',code_word(i));
end

fclose(fileID);
    
syndrome = transpose(final*transpose(code_word));

syndrome = mod(syndrome.^2,2);

for i = 1:m
    if(syndrome(i)~=0)
        disp('fail');
    end
end


end

