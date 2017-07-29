%this is used to debug the tanner graph grabbing function
function  tanner_graph_debug_56(check_node_id,expansion,code_word)


model_matrix= [
1 25 55 -1 47 4 -1 91 84 8 86 52 82 33 5 0 36 20 4 77 80 0 -1 -1;
-1 6 -1 36 40 47 12 79 47 -1 41 21 12 71 14 72 0 44 49 0 0 0 0 -1;
51 81 83 4 67 -1 21 -1 31 24 91 61 81 9 86 78 60 88 67 15 -1 -1 0 0;
68 -1 50 15 -1 36 13 10 11 20 53 90 29 92 57 30 84 92 11 66 80 -1 -1 0;
];
%no puncture yet


n = 24;

m = 4;

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

for k = 1:n
    if(final(check_node_id+1,k)==1)
        text = sprintf('The check_node %d has a 1 in position %d',check_node_id,k-1);
        disp(text);
    end
    
    

end

disp('The code worod is ');

for k = 1:n
    if(final(check_node_id+1,k)==1)
        disp(code_word(k))
    end
end