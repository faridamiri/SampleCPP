/*
 * DupCsvNcr.hpp
 *
 *  Created on: Feb 7, 2016
 *      Author: farid amiri
 */

#ifndef DUPCSVNCR_HPP_
#define DUPCSVNCR_HPP_

/*
 *
 */
#include<iostream>
#include<set>
#include<map>
#include<string>
#include<iterator>
#include<fstream>
#include<sstream>
#include<regex>
#include<ctime>
#include<typeinfo>
#include<cstddef>


const int INT_ONLY_WHITE_SPACE=1 ;
const int INT_INVALID_CHARACTER= 2;
const int INT_MISSING_DELIMETER= 3;
const int INT_MISSING_NUMBER= 4;

#define STR_ONLY_WHITE_SPACE "The line  contain only white space";
#define STR_INVALID_CHARACTER "The line  contain some unexpected character e.g. alphabet";
#define STR_MISSING_DELIMETER "In the line some number is not divided by comma";
#define STR_MISSING_NUMBER  "In the line before/between/after comma missed a digit";




typedef std::map<std::string,int>							map__String_Int;
typedef std::map<std::multiset<int>,int>							map__Multiset_Int;
typedef std::pair< std::multiset<int>,int>	 						pair__Multiset_Int;
typedef std::pair< std::string,int> 	  					pair__String_Int;
typedef std::pair< std::map<std::string,int>::iterator,bool> pair___Map__String_Int___bool;
typedef std::pair<std::map<std::multiset<int>,int>::iterator,bool>	pair___Map__Multiset_Int___bool;

class DupCsvNcr {

public:
	friend std::ostream& operator<< (std::ostream & ,  DupCsvNcr&  );
	DupCsvNcr();
	//DupCsvNcr(const DupCsvNcr&);
	DupCsvNcr(std::istream&);
	virtual ~DupCsvNcr();
	bool add(std::string);
	bool add(std::istream& );
	bool clear();
	std::string listMostFreqDuplicate(void);
	std::string info();
	std::string reportInvalidInputs(void);
    template <class T>									//make a Read Only members
    	class proxy {
        friend class DupCsvNcr;
    	private:
        	T number;
        	T operator=(const T& arg) { number = arg; return number; }
    	public:
        	operator const T&() const { return number; }
    	};

   proxy<int> maxDuplicateNumber;
   proxy<int> numberOfDuplicate;
   proxy<int> numberOfNonDuplicate;


private:
	bool parseCsv(std::string);
	bool addSingleLine(std::string);

	map__String_Int					inValidContainer ;
	map__Multiset_Int            	 	validContainer ;

	pair__Multiset_Int 				 	setCsvValid;
	pair__String_Int					setCsvInvalid;

	pair___Map__String_Int___bool	retInvalid;
	pair___Map__Multiset_Int___bool	 	retValid;

	map__Multiset_Int				 	mostFrequentDuplicate ;

};






#endif /* DUPCSVNCR_HPP_ */
