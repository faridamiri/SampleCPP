/*
 * DupCsvNcr.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: farid amiri
 */

#include "DupCsvNcr.hpp"


DupCsvNcr::DupCsvNcr() {
	maxDuplicateNumber=0;
	numberOfDuplicate=0;
	numberOfNonDuplicate=0;
	std::clog<<std::endl<<"class constructed"<<std::endl;
}


DupCsvNcr::DupCsvNcr(std::istream& inputFile) {
	DupCsvNcr();
	if(add(inputFile)){
	}else{
		std::clog<<"something wrong! in  add(istream&)"<<std::endl;
		std::cerr<<"something wrong! in  add(istream&)"<<std::endl;;
	}


}


DupCsvNcr::~DupCsvNcr() {

	if(clear())
	std::clog<<"Memory is cleaned !"<<std::endl;
	else{
		std::clog<<"some data remain in Memory "<<std::endl;
		std::cerr<<"some data remain in Memory "<<std::endl;
	}
}

bool DupCsvNcr::clear(){
	try{
		maxDuplicateNumber=0;
		numberOfDuplicate=0;
		numberOfNonDuplicate=0;
		this->inValidContainer.clear();
		this->validContainer.clear();
		this->mostFrequentDuplicate.clear();

	}catch(...){
		return false;
	}
return true;
}



bool DupCsvNcr::add(std::istream& csvStream){
	bool addedRecord=false;
	std::string csvRecord;

		if(csvStream.bad()) return(false);
		while(std::getline(csvStream,csvRecord)){
				addedRecord|=(DupCsvNcr::addSingleLine(csvRecord));//if any 1 record is parsed add()
			}													   // will return true

return (addedRecord);
}

bool DupCsvNcr::add(std::string csvString){
	bool addedRecord=true;
	if(csvString.empty())return(false);
	std::istringstream is(csvString);
	addedRecord=add(is);
	return(addedRecord);

}



bool DupCsvNcr::addSingleLine(std::string csvString){


	bool isValid=false;


			if(csvString.empty())return(false);
			setCsvValid.first.clear();
			setCsvValid.second=0;
			setCsvInvalid.first.clear();
			setCsvInvalid.second=0;
/*
 * 												check single line is CSV format
 */

				isValid=parseCsv(csvString);




/*
                                                If  line is not CSV format return false
                                                fill to  pair< string,string> and insert that to
                                                Invalid Container set
 */


			if(!isValid){
			//	setCsvInvalid.first=csvString;
			//	setCsvInvalid.second="bad syntax";
				retInvalid=inValidContainer.insert(setCsvInvalid);


				return(false);
			}
/*
 **********************************************Else if is CSV format fill pair< std::multiset<int>,int>
 * 										  			insert to valid Container Set
 *		 										    if it exist already(check return iterator)
 * 			  									 		  than increase second item MAX and MIN duplicate
 * 			  									 		  set can be performed here
 */
			setCsvValid.second=1;
			retValid=validContainer.insert(setCsvValid);
			if(!retValid.second ){

					(retValid.first->second)++;

					if((retValid.first->second)==2){
							 numberOfDuplicate=numberOfDuplicate+1;
							 numberOfNonDuplicate=numberOfNonDuplicate-1;
					 }
			}else{
				  numberOfNonDuplicate=numberOfNonDuplicate+1;
			}
/*				                                    If its duplicate Number is bigger than
 * 							                        Most duplicated set will be updated
 *
 */

			if((int)(retValid.first->second) >= maxDuplicateNumber){
				if((int)(retValid.first->second) > maxDuplicateNumber){
							maxDuplicateNumber=retValid.first->second;
							mostFrequentDuplicate.clear();
							}
				mostFrequentDuplicate.insert(std::make_pair(setCsvValid.first,maxDuplicateNumber));

			}

	return(true);
}




bool  DupCsvNcr::parseCsv(std::string csvString){
	/*
	 * 												because of stupidity of getline delimited by
	 * 												comma as last character push back a space to string
	 * 												Check string by regex if it  look like CSV format
	 * 												split it by comma
	 * 												sscanf read the numbers , check result of scanf
	 * 												insert to a pair<multiset<int>,int>    	 												than
	 */

	char delimiter=',';
	int iData=0,res=1,iCheck=0;
    std::stringstream csvRecord(csvString);
    std::string       csvField;
    std::string MistakeMsg;
    csvString.push_back(' ');

    	 std::regex csvRegex1(  "[[:space:]]*"  );
    	 if ((std::regex_match(csvString,csvRegex1))){
    		 setCsvInvalid.first=(csvString);
    		 setCsvInvalid.second=INT_ONLY_WHITE_SPACE;
    		 return false;
    	 }



    	 std::regex csvRegex2(  "([[:space:]]*[',']*[[:space:]]*(\\+|-)?[[:digit:]]+[[:space:]]*)+[',']*[[:space:]]* "  );
    	 if (!(std::regex_match(csvString,csvRegex2))){
    		 setCsvInvalid.first=(csvString);
    		 setCsvInvalid.second=INT_INVALID_CHARACTER;
    		 return false;
    	 }

    	 while(std::getline(csvRecord,csvField,delimiter)){
 			 iCheck=0;iData=0;res=0;
  			 res=sscanf (csvField.c_str() ,"%d %d",&iData,&iCheck);

  			if(res!=1){
  				setCsvInvalid.first=(csvString);
  				if(res>1) setCsvInvalid.second=INT_MISSING_DELIMETER;
  				if(res<1) setCsvInvalid.second=INT_MISSING_NUMBER;
  				return(false);
  			}else{
 			 setCsvValid.first.insert(iData);
 			 setCsvValid.second=1;
  			}
		}

	return(true);
}

/************************************************************************************
 *                                   brief info about container                     *
 *************************************************************************************/


std::string DupCsvNcr::info(void){
	std::stringstream info;

	info<<"Information on number of duplicates and non-duplicates "<<std::endl;
	info<<"Number of duplicates is:"<<numberOfDuplicate <<std::endl;
	info<<"Number of non-duplicates is:"<<numberOfNonDuplicate<<std::endl;
	return(info.str());

}

/********************************************************************************
 * 				       create a string by list of Most Freq Duplicate set		*
 ********************************************************************************/


std::string DupCsvNcr::listMostFreqDuplicate(void){
	std::stringstream listMFD;
	listMFD<<"list Of Most Frequent Duplicate sets: "<<std::endl;
	bool flag=false;
	for (pair__Multiset_Int x:mostFrequentDuplicate ) {
			listMFD<<"Duplicated number of set is:" <<x.second <<"  set={" ;
			for (std::multiset<int>::const_iterator itt(x.first.begin()), end(x.first.end());
					itt != end; ++itt){

					if(flag) listMFD<< ",";
					listMFD << (*itt) ;
					flag=true;
			}
			flag=false;
			listMFD<<"}"<<std::endl;
		}

		listMFD<<std::endl;

	return(listMFD.str() );

}

/********************************************************************************
 * 			       create a string by list of Invalid Inputs data		        *
 ********************************************************************************/


std::string DupCsvNcr::reportInvalidInputs(void){
	std::stringstream listInvalidInput;
	listInvalidInput<<"Report on list of invalid inputs"<<std::endl;

	for (pair__String_Int x:inValidContainer ) {
				listInvalidInput<<"invalid set is: " <<"  set={" ;
				listInvalidInput<<x.first;
				listInvalidInput<<"}"<<std::endl;
				listInvalidInput<<"Note:mismatch CSV syntax : ";
				switch(x.second){
				case (INT_ONLY_WHITE_SPACE):
						listInvalidInput<<STR_ONLY_WHITE_SPACE;
						break;
				case (INT_INVALID_CHARACTER):
						listInvalidInput<<STR_INVALID_CHARACTER;
						break;
				case (INT_MISSING_DELIMETER) :
						listInvalidInput<<STR_MISSING_DELIMETER;
						break;
				case (INT_MISSING_NUMBER) :
						listInvalidInput<<STR_MISSING_NUMBER;
						break;

				default:
					listInvalidInput<<"BAD SYNTAX";

				}
				listInvalidInput<<std::endl<<std::endl;

		}

	listInvalidInput<<std::endl;
	return(listInvalidInput.str() );
}



std::ostream& operator<< (std::ostream& os,  DupCsvNcr& dcn){

	bool flag=false;
	for (pair__Multiset_Int x:dcn.validContainer ) {
		os<<"Duplicate number of set is:" <<x.second <<"  set={" ;
		for (std::multiset<int>::const_iterator itt(x.first.begin()), end(x.first.end());
				itt != end; ++itt){

				if(flag) os<< ",";
				os << (*itt) ;
				flag=true;
		}
		flag=false;
		os<<"}"<<std::endl;
	}


			return os;
}




