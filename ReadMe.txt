
Dear Reader,
this code is written due to "C++ Qualification Test". 



programming language :c++

IDE:eclipse/cdt

Compiler setting: 
   GCC C++ Compiler:g++  option:-O0 -g3 -Wall -c -fmessage-length=0 -std=c++11



I am making the following assumptions :

    
  The field terminator is only comma sign “,” .

  The fields are integer( c++ int), if any.
    
  The fields are No enclosures.
    
  The parser can handle sets where fields are always number .
    
  There is no need class::init() .
    
  There is no need delimiter set.

  
Header : DupCsvNcr.hpp	

  Class  : DupCsvNcr.cpp	

  Test   : DupCsvNcr.cpp	



constructor:
   DupCsvNcr();
  
   DupCsvNcr(std::istream&);
	    
   deconstructor  ~DupCsvNcr();



add sets:
	
			
  bool add(std::string);
			
  bool add(std::istream& );


  dealete data:
			
  bool clear();

Members:

      string listMostFreqDuplicate(void);

	    string info(void);

	    string reportInvalidInputs(void);

 	    read only int maxDuplicateNumber;

      read only int numberOfDuplicate;

      read only int numberOfNonDuplicate;



data structure :
				
  invalid sets  map<string,string>							
                
  valid sets    map<std::multiset<int>,int>							


Maps are associative containers, are implemented as Red_Black trees.

In case of real project it's better to use Hash_Map, or(depend on duplicated set rate ).



Complexity   map::insert :O(log n), alogarithmic in size.
  multiset(Multiple-key set) : Multisets (as map) are typically implemented as binary search
 trees,so   multiset::insert (first version )   Complexity:O(log n), logarithmic in size.


DupCsvNcr::parseCsv()   complexity:
 regex complexity is O(2^m) m is the size of the regex,
 running a string through it is linear in the length of the fields - O(n),n  is fields 
 length.A replacement on a match found in the string should be constant time,, 
 I suppose O(2^m + n).

So overall, parse to CSV format  g1(n)=O(n) where n is length of string(set),  so  g1(n)=C. 


add to maps and to multiset: g2(n)=log(m)*log(f) = log(m*f)=log(n),
m=number of set , f=number of fields , so it should be f(n)=g1(n)+g2(n)=log(n) .





memory(space) complexity:

multiset and map space complexity of B_Tree is o(n) where
 "n" is number of data,so should be linear in the number and size of keys ,but 
algorithm keep only one time duplicated data, so it should be O(n/r) where "r" 
is  average of duplicated data number.

parseCsv() doesn't have any recursive function,
add() function pass only one line to parseCsv(),and add(stream&) take only address so 
space complpexity is constant to length of string ,

So overall, in worse case space complexity is O(n) where n is lenght of message.


develop time table 

1 hour study case 
1 hour  develop class
1 hour develop test unit
3 hour update class and code
30' write this file!





Farid Amiri
frdamiri@gmail.com
7/2/2016











