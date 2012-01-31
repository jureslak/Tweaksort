Tutorial and examples for tweaksort library.

#############################
#     TEHNICAL DETAILS.     #
#############################

There are a lot of files in this folder. MOST IMPORTANT ARE:

- sort.hpp
- learn.hpp
- conf.hpp
- exceptions.hpp

This four files represent the tweaksort library and are the only files needed.
The main two are sort.hpp and learn.hpp. They both include the other two, so no need to
include them manually.

Other described here are:
X.hpp for X = {i, s, q, m, h} (sorting algorithms implementation)
learn.cpp (learn)
test.cpp (test)
run.py
plot.py
average.py
out (temp file from run.py - auto generated
*.conf (conf files - auto generated)
rtext.txt (source file for random text)

############################
#     LEARN TUTORIAL       #
############################

Usage:

learn.hpp - finds the optimal conf for given data

#include "learn.hpp"
... 

using namespace tweaksort;

int main(){
    // let TESTDATA be a shuffled vector of size n 
    // and let all the other constants exist
   
    cont_f conf = learn(M, Compare(ITER, LIMIT, ACC, TESTDATA));
    
    return 0;
}

Yes it is so simple.

Program that does is for you is learn (learn.cpp).

Usage:

param 1: M ........ upper bound for learning
param 2: ITER ..... how many iterations to make
param 3: ACC ...... how much to increment the distance every time
param 4: LIMIT .... how many elements are allowed in memory
param 5: TYPE ..... int, string, huge or slow 1 if yes 0 otherwise
TYPE example: 1011 will learn for int, huge and slow

The confiugration is saved in the appropriate conf file.

#############################
#      SORT TUTORIAL        #
#############################

Usage:

#include "sort.hpp"
... 

using namespace tweaksort;

int main(){
    // let a be a shuffled vector of size n 
    // and let conf_file exist
    

    cont_f conf ("conf_in_string");
   
    sort(a.begin(), a.end(), conf);
    
    // now a is sorted   
 
    return 0;
}

Program that does it for you is test (test.cpp)

param 1: [L = 0] ...................... lower bound for sorting
param 2: M ............................ upper bound for sorting
param 3: [step = 1] ................... what steps to take for plot
param 4: [iter = 1] ................... how many iterations to make
param 5: [limit = M * iter] ........... how many iterations to make
param 6: [type = 1111] ................ int, string, huge or slow 1 if yes 0 otherwise
[means  optional] example type 1001 means?     (int and slow)

Output is not meant to read, but to process via python scripts. Good to save using
for example command 

./test 0 1000 10 10 10000 1000 > out.

 That saves output to out, but
still prints a counter for easier waiting.

#########################
#     PLOT TUTORIAL     #
#########################

command python plot.py
Used to plot:
flags:
-t type (int, string, slow, huge) (one type only) 
-s sort (i, q, h, m, c, t, s) - first letter of english name (multiple args ok, none means all)

note: 
an input file or read from stdin. recomend using

./test  ... | python plot.py -t int -s q h t i  (read from stdin via | )
or better
./test ... > out; python plot.py -t int -s ... < out (data is saved in out)

#########################
#        RUN.PY         #
#########################

command python run.py
combined plot and test

syntax
python run.py [L] M [step] [iter] [limit] -t ... -s ... 

actually runs appropriate ./test > out; python plot.py ... < out combination.
data is saved to output

for interesting and nice and fast plot run:
python run.py 0 1000 10 10 -t int -s

#########################
#     AVERAGE.PY        #
#########################

command python average.py
the simplest.
no arguments.
Calculates the sum of data points given.
Asks for filename, write whole path.
Prints ordered values with appropriate metadata.

Jure Slak
========================================================================



              .~7Z8MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM.                       
              . M$++M$,:,:,:,,:,::::::,:::::,,,,::,:DM7:MM                      
              .MM?M:=~=MMMMMMMMMMMMMMMMMMMMMMMMMM$M?==:MM,,                     
              .MMM,==DMI7777777777777777777777777777OM~=,M:                     
              .MMM:==MI777I77777777777777777777777777D~=:::                      
              .MM+:==77777777777777777777777777777777+=:,+.                     
              .MM,:==7I7777777777777777777777777777777=::$.                     
              .MM::==777777777777777777777777777777778=::D.                     
              .MM::==77777777777777777777777777777777N=::M.                     
              .MM::==Z7777777777777777777777777777777M=::M.                     
              .MM::=~I7777777777777777777777777777777M=::M                      
              .MM::=8I7777777777777777777777777777777M=::M                      
              .MM::=M7777777777777777777777777777777OM=::M                      
              .MM::=M7777777777777777777777777777I77MI=.,M                      
              .MM::=D7I777777777777777777777777I7777M~=M:M                      
               MM,:=~M777777777777777777777777777IIOM=~M:M.                     
              .MNN::=~MM77I7I77777777777777777777IMM~=:M:M.                     
              .M8M+::===DMMMMMMMMMMMMMMMMMMMMMMMMMM=::M::M                      
              .MZ:~M7::::,::,::::::::,::::::::::,,,,=M.,~M                      
               MM8ONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM.                     
                     M::::~~~~==========D,::::M===7M                            
                     .MM:,:,,,:,::,:::::::::::,:,:MM                            
                      . MNMMMMMMMMMMMMMMMMMMMMMMMM.                             
                      .M=7M:,:::::::~~~~~====M=?M.                              
                     .,M~~MN:::::::::::::::+MM==M                               
                     .M8=~=7MMMMMMMMMMMMMMMM=~=~~M                              
                     $M:,:====~==~==========~::::D$.                            
        .MMMMMMMMMMMMMMMD888O777$++++++++::::::::,M...........                  
       .M:::,::::::::::,,::::::::::::::,,,,,,:::,:,::::,:?7ODMM                
       M,:=MM88N8MM8M,MM8D$OMM8M~MM8DM:::NMM8M::MMD=MM8+MM8$,::M                
     .M::~M~~==++==~~N~~==++====M~====,,:?,:,=::?==~~=~~~O~~~:,MN              
     NM,:MZ,::?M,:,~M$,:~=M:,,~M$::,~=::~M8,:~:::M::~MI:~7M:,::,MMMMMD          
    OM::=MMMD~7MMM$=MMMN=+MMM?=MMMD==::::=MMM$=:,:MMM=IMM8~MMM~:MM    DMMM     
    M,,=M:,:~M,:,,~M::,=N~:,:?M,:,==:::::MN:::=:,:M::~=M::=D,,~::M     ..+MM.   
 . M,:~~=~~~======:~~===~~=~=~==~=~~:::::~:,,,:,:::=~=~~==~====~:MM.       =MI  
 .M:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::M.        .M  
 I$::::~+++++$$$$$88888MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM        .M: 
  M==================~========~=============~============~=========M        ,M  
  NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM        M 
                                                                        .,MD  
                                                                   .=MMM7     
                                                              .MMM77         
                                               ?MN~.M:::OM..IMM7               
                                           ,NM::::8I:~=MD,M:MM                  
                                          7M~:::::,MMZ~D?,,=M?M                 
                                         =M,:::::::,::,M~=MN:,MD.               
                                         M:::::::::::::~::::,M=M                
                                         MM:::::::::::::::,M=+M                 
                                         M?MMN,,:::::,=M8==IM.                  
                                          +M+==I$Z?~~==MMO.                     
                                              7OMNO+.                           
