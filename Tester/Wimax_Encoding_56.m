function [ code_word,syndrome ] = Wimax_Encoding_56( data, expansion)
%WIMAX_ENCODING Summary of this function goes here
% this fucntion encodes the data via back_substitution,
%   Detailed explanation goes here
% this function is very primitive, aka its performance suffers from various
% reasons. However it should get the job done
% Input, data --> data word, expansion --> expansion factor, must be
% divisible by 4 and ranges from 24 to 96
% the size of the data must be interms of 12*expansion

n = 24;
m = 4;
g = 1;


if(size(data)~=(n-m)*expansion)
invalid code word
    return; 
end



model_matrix= [
1 25 55 -1 47 4 -1 91 84 8 86 52 82 33 5 0 36 20 4 77 80 0 -1 -1;
-1 6 -1 36 40 47 12 79 47 -1 41 21 12 71 14 72 0 44 49 0 0 0 0 -1;
51 81 83 4 67 -1 21 -1 31 24 91 61 81 9 86 78 60 88 67 15 -1 -1 0 0;
68 -1 50 15 -1 36 13 10 11 20 53 90 29 92 57 30 84 92 11 66 80 -1 -1 0;
];
%no puncture yet


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

p1 = inv(factor2)*(E*test*A*data_trans+C*data_trans);

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

