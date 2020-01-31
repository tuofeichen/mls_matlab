function index = find_converter_index (string_index)

switch string_index
    case 1
        index = [1,5];
    case 2
        index=[2,6];
    case 3
        index = [7 9];
    case 4 
        index=[8 10];
    case 5 
        index = [3 11];
    case 6
        index=[4 12];
    otherwise
        disp('Invalid Index');
        index = 0; 
        
end
end