import numpy as np
import json

max_gen = 1000  # number of iterations. enter even number
dim = (2, max_gen*2+1) 
cellular = np.zeros(dim)  # create array of 0s and 1s
dim2 = (1, max_gen*2+1) 
blank = np.zeros(dim2)  # empty row array to delete the second row after copying to first row


cellular[0][max_gen] = 1  # initial state in the middle

# These rules are not needed
# rule_1 = [1, 1, 1]  # 0 
# rule_2 = [1, 1, 0]  # 0
# rule_3 = [1, 0, 1]  # 0
# rule_8 = [0, 0, 0]  # 0

# These rules are needed
rule_4 = [1, 0, 0]  # 1
rule_5 = [0, 1, 1]  # 1
rule_6 = [0, 1, 0]  # 1
rule_7 = [0, 0, 1]  # 1


x = 1 # used to go through each column
y = 0 # used to go through each row
bias = 1 # used to go to next row
middle_data = [1]

while x < max_gen*2:  # go through each column
    if np.array_equal(cellular[0][x-1:x+2], rule_4):  # apply rules
        cellular[1][x] = 1
    elif np.array_equal(cellular[0][x-1:x+2], rule_5):
        cellular[1][x] = 1
    elif np.array_equal(cellular[0][x-1:x+2], rule_6):
        cellular[1][x] = 1
    elif np.array_equal(cellular[0][x-1:x+2], rule_7):
        cellular[1][x] = 1
    if bias == max_gen*2-1:  # switch to next row if at the end of row
        x = 1
        bias = 1
        y += 1
        middle_data.append(int(cellular[1, max_gen])) # append new center value to list
        cellular[0, :] = cellular[1, :] # move second row to first row
        cellular[1, :] = blank[0, :] # delete second row
    else:                 # else go to next column  
        x += 1
        bias += 1
    if y == max_gen-1:  # end at last row
        break # exit loop

# print(middle_data) # if you want result in terminal

with open('output.txt', 'w') as filehandle:  # save list to txt file
    json.dump(middle_data, filehandle)
