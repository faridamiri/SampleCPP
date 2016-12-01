/*
 * DupCsvNcr_test.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: farid amiri
 */

#include "DupCsvNcr.hpp"
using namespace std;

void test1(DupCsvNcr&);  //test Valid inputs
void test2(DupCsvNcr&);  //test Invalid inputs
void test3(DupCsvNcr&);  //test diff type input and diff construction
void test4(DupCsvNcr&);  //test max duplicate sets and number of duplicated and non-duplicated
void test5(DupCsvNcr&);	 // maximum Number duplicate of sets ,maximum duplicate list , info() test
void test6(DupCsvNcr&);	 // invalid input report

int  test7(DupCsvNcr&,int recordNum=1000,int fieldNum=10,int averageRepeat=1);//add random record and check time

void test8(DupCsvNcr&,string filename="testfile.txt"); //add random data to file and read, add to container

void test9(DupCsvNcr&,int minRecordNum=1,int maxRecordNum=10000,     //relation between time and record
		              int minFieldNum=10,int maxFieldNum=100,        // number,fields number, and
		              int minAverageRepeat=1,int maxAverageRepeat=10);//duplicate average


void printHeaderCout(string);
void printResultIntoCout(string,bool,bool);           //print on cout result of

int main() {



//	DupCsvNcr* cdc=new DupCsvNcr;
	DupCsvNcr cdp;



//		  test1(*cdc) ;


    	test1(cdp);
        test2(cdp);

	cout<<"functional test:"<<endl;
	cout<<cdp;
	cout<<	cdp.reportInvalidInputs();
	cout<< cdp.info();
	cout<< cdp.listMostFreqDuplicate();

       test3(cdp);
      test4(cdp);
       test5(cdp);
       test6(cdp);
// 	test7(cdp);
//    test7(cdp,2000,10,3);
   //     test8(cdp);

    //    test9(cdp,1,5000,10,10,1,1);
		test9(cdp,0,1000,10,10,1,1);
		test9(cdp,100,100,0,20,1,1);

		test9(cdp,100,100,5,5,1,10);

	return 0;
}


void printHeaderCout(string name){
	cout << string(100, '*') << endl;
	cout<< string(40, ' ')<<name<<endl;
	cout << string(100, '*') << endl;
}
void printResultIntoCout(string msg,bool result,bool expected){
	cout<<msg<<" result= "<<std::boolalpha<<result<<",  expected=True  ?=";
	if(result==expected){
		cout<<"   OK"<<endl;
	}else {
			cout<<"ERROR"<<endl;
		}
}



/***************************************************************
 * 								test1 valid input
 ****************************************************************/

void test1(DupCsvNcr& cdc){

	printHeaderCout("test 1");
	string msg="test add valid data:  ";
	bool result,expected=true;
	std::vector<string> test={"41","41","0","11,25","0,-25","-0,+25","     0 ,  25 ,	10	","\t 0,25\t ,10\n","  4","5,4 \n 2,3"};
	for (unsigned int i = 0; i < test.size(); i++) {
		result=cdc.add(test[i]);

		printResultIntoCout(msg,result, expected);


	}
	cout<< string(30, '*')<<"End of Test 1" << string(30, '*')<<endl;
}





/*********************************************************************
 * 								test2 Invalid input
 ***********************************************************************/

void test2(DupCsvNcr& cdc){
	bool result,expected;
	string msg="test add Invalid data:";
	std::vector<string> test;
 	expected=false;
 	printHeaderCout("test 2");

	 test ={""," ",",","\n","14,s,2","\t",",24","25, ","0 26", " 0,27 , ","0,   *28","0,   ",
			 "29*2","'0', 2","\n, 2","abc,3","41a,4","4a41,6","\\,7","5 a, 8","5 ,, 10",
	 	 	 "1.2","5 a, 8","5 ,, 10" };
	 for (unsigned int i = 0; i < test.size(); i++) {
		result=cdc.add(test[i]);
		printResultIntoCout(msg,result, expected);
	}
	 cout<< string(30, '*')<<"End of Test 2" << string(30, '*')<<endl;
}







/****************************************************************************************
 * 										test 3: diff type & construction
 *
 *****************************************************************************************/


void test3(DupCsvNcr& cdc){
	bool result,expected;
	std::vector<string> test;
	string msg="test construction and diff type";
 	expected=true;
 	printHeaderCout("test 3: diff type & construction ");
 /*
  *                				 test diff type
  */
	const char* dataCStar="142,245";
	result=cdc.add(dataCStar);
	cout<<"const char*="<<endl;
	printResultIntoCout(msg,result, expected);
	char data2[256]="1,5 ,4";
	result=cdc.add(data2);
	cout<<"array[]"<<endl;
	printResultIntoCout(msg,result, expected);
	ofstream out("inputtest.txt");
	out<<"10,25,4"<<endl;
	out<<"10,25,4"<<endl;
/*
 * 								 test construction by valid stream
 */
	ifstream in("inputtest.txt");
	result=cdc.add(in);
	out.close();
	cout<<"from file stream"<<endl;
	printResultIntoCout(msg,result, expected);
	in.close();
/*
 * 								 test construction by invalid stream
 */
	expected=false;
	ifstream anotherIn("unknownfile.txt");
	result=cdc.add(anotherIn);
	cout<<"from file stream undefined"<<endl;
	printResultIntoCout(msg,result, expected);
	anotherIn.close();

	cout<< string(30, '*')<<"End of Test 3" << string(30, '*')<<endl;
}








/*****************************************************************************************
 * 						               test to get
 * 						number of duplicate set and non-duplicate set
 *****************************************************************************************/

void test4(DupCsvNcr& cdc){
	bool result=false,expected=true;
	std::vector<string> test;
	string msg="test number of duplicate, non-duplicate sets";
	printHeaderCout("test 4");

		int testNumberMaximum=9;

		string mostDuplicatedSet="1,1,2,3,5,8,13,21";
		for (int var = 0; var < testNumberMaximum; ++var) {
			cdc.add(mostDuplicatedSet);
		}
		cout<<"maxDuplicateNumber test"<<endl;
		result=(cdc.maxDuplicateNumber==testNumberMaximum);  //check number of maximum
		printResultIntoCout(msg,result, expected);

		cout<<"numberOfDuplicate test"<<endl;
		cdc.add("1,1,1,1,1");
		int testnumberOfDuplicate=cdc.numberOfDuplicate;
		int testnumberOfNonDuplicate=cdc.numberOfNonDuplicate;
		cdc.add("1,1,1,1,1");
		result=(cdc.numberOfDuplicate==testnumberOfDuplicate+1);
		printResultIntoCout(msg,result, expected);
		cout<<"numberOfDuplicate test"<<endl;
		result=(cdc.numberOfNonDuplicate==testnumberOfNonDuplicate-1);
		printResultIntoCout(msg,result, expected);
		cout<< string(30, '*')<<"End of Test 4" << string(30, '*')<<endl;
}

/******************************************************************************************
 *		                      test function listMostFreqDuplicate()
 *								Maximum duplicate number  and info()
 ******************************************************************************************/


void test5(DupCsvNcr& cdc){
    bool result=false;
    bool expected=true;
    string msg="test of function ";
    int  testnumberOfDuplicate=20;
	string mostDuplicatedSet1="0,1,2,3,5,7,13,17,19";
	string mostDuplicatedSet2="1,2,3,5,7,13,17,19";

	string listMFS;
	stringstream sslistMFS;



	for (int var = 0; var < testnumberOfDuplicate; ++var) {//add  many times sets
				cdc.add(mostDuplicatedSet1);
				cdc.add(mostDuplicatedSet2);
	}

	printHeaderCout("test 5: listMostFreqDuplicate() reportInvalidInputs()");

	result=(cdc.maxDuplicateNumber==testnumberOfDuplicate);  //check number of duplicate set
	printResultIntoCout(msg+"maxDuplicateNumber: ",result, expected);

	result =false;
	sslistMFS<< cdc.listMostFreqDuplicate();
	listMFS=sslistMFS.str();
    size_t posSampleMFS = listMFS.find(mostDuplicatedSet1);// find position of most DuplicatedSet1
    if(posSampleMFS<listMFS.length())result =true;
    printResultIntoCout(msg+"Most Duplicate Sets: ",result, expected);

    result =false;
    posSampleMFS = listMFS.find(mostDuplicatedSet2); // find position of most DuplicatedSet2
    if(posSampleMFS<listMFS.length())result =true;
    printResultIntoCout(msg+"Most Duplicate sets: ",result, expected);


    result =false;
	string testInfo;
	sslistMFS<< cdc.info() ;
	testInfo=sslistMFS.str();
	posSampleMFS = testInfo.find(mostDuplicatedSet1); // find position of most Dup in info
    if(posSampleMFS<listMFS.length())result =true;

    printResultIntoCout(msg+"Info() function :: ",result, expected);
    cout<< string(30, '*')<<"End of Test 5" << string(30, '*')<<endl;

}






/*************************************************************************
 * 									test6: invalid report
 *
************************************************************************* */

void test6(DupCsvNcr& cdc){
	 bool result=false;
	 bool expected=true;
	 string sInvalidReport;
	 stringstream ssInvalidReport;
	 string msg="test of invalid report by set 1: ";
	 string inValidSet1="0 1,2,3,5,7,13,17,19";
	 string inValidSet2= "25 12 , 25";

	 printHeaderCout("test 6: reportInvalidInputs()");

	for (int var = 0; var < 5; ++var) {
		cdc.add(inValidSet1);

	}



	cdc.add(inValidSet2);
	ssInvalidReport<<cdc.reportInvalidInputs();
	sInvalidReport=ssInvalidReport.str();

   result =false;
   size_t posSampleMFS = sInvalidReport.find(inValidSet1); // find position of most DuplicatedSet2
   if(posSampleMFS< sInvalidReport.length())result =true;

   printResultIntoCout(msg,result, expected);
   result =false;
   posSampleMFS = sInvalidReport.find(inValidSet2); // find position of most DuplicatedSet2
   if(posSampleMFS< sInvalidReport.length())result =true;
   printResultIntoCout(msg,result, expected);


   cout<< string(30, '*')<<"End of Test 6" << string(30, '*')<<endl;

}

/*****************************************************************************
*                             test7: make random valid sets and write it in a stringstream
* 							  	     then read it again and add this records to container
* 								     get time and number of record
****************************************************************************/


void aid4test(DupCsvNcr& cdc,int recordNum,int fieldNum,int averageRepeat){


	stringstream sStream;

	srand (time(NULL));
	if(recordNum<averageRepeat)averageRepeat=1;
	int Averep=1;
	int recordTracker=0;
	for (int var = 0; recordTracker < recordNum; ++var) {
			stringstream ssRecord;
			ssRecord<< (rand()%1000);
			for (int var2 = 0; var2 < fieldNum; ++var2) {
				ssRecord<<","<<(rand()%1000);
			}
			ssRecord<<endl;

			Averep=(rand()%(averageRepeat*2))+1;
			for (int var1 = 0; var1 < Averep; ++var1) {
				sStream<<ssRecord.str() ;
				recordTracker++;
			}
	}

	cdc.add(sStream);
}


/*****************************************************************************
*                             test7: make random valid sets and write it in a stringstream
* 							  	     then read it again and add this records to container
* 								     get time and number of record
****************************************************************************/





int test7(DupCsvNcr& cdc,int recordNum,int fieldNum,int averageRepeat){

	printHeaderCout("test 7: write to stream and read,add,print");
	cout<<"Make a Stream by about "<<recordNum<<" records and "<<fieldNum<<" Fields"<<endl;
	time_t timeStart,timeEnd;
	cout<<"Stream made in :" << (difftime(timeEnd,timeStart)) <<".Sec"<<endl;
	cout<<"Container Information before Add:"<<recordNum<<" records" <<endl;
	cout<<"making Container by add new random " <<endl;
	time(&timeStart);
	aid4test(cdc,recordNum,fieldNum,averageRepeat);
	time(&timeEnd);
	int timeOfAdding=(difftime(timeEnd,timeStart));
	cout<<"Container made in :" << timeOfAdding <<".Sec"<<endl;
	cout<< string(30, '*')<<"End of Test 7" << string(30, '*')<<endl;
	return timeOfAdding;
}


/*****************************************************************************
*
*         test8 make a random valid sets and write it in a TXT file
*              then read it again and add is records to container
****************************************************************************/

void test8(DupCsvNcr& cdc,string filename){

	printHeaderCout("test 8: write to filename.txt and again read,add,print");

	time_t timeStart,timeEnd;
	srand (time(NULL));
	stringstream sStream;
	int recordNum=100;
	int fieldNum=10;
	int averageRepeat=3;
	if(recordNum<averageRepeat)averageRepeat=1;
	int Averep=1;

									// make a stream
	cout<<"Make a Stream by about"<<recordNum<<" records and "<<fieldNum<<" Fields"<<endl;
	time(&timeStart);
	for (int var = 0; var < recordNum/averageRepeat; ++var) {
			stringstream ssRecord("");
			ssRecord<< (rand()%1000);
			for (int var2 = 0; var2 < fieldNum; ++var2) {
				ssRecord<<","<<(rand()%1000);
			}
			ssRecord<<endl;

			Averep=(rand()%(averageRepeat*2))+1;
			for (int var1 = 0; var1 < Averep; ++var1) {
				sStream<<ssRecord.str() ;
			}
	}

	cout<<"Stream made in :" << (difftime(timeEnd,timeStart)) <<".Sec"<<endl;
	cout<<"Redirecting cout's output through its stream buffer" <<endl;
												//write stream to a text file
	time(&timeStart);

	ofstream outFile(filename);
	outFile << sStream.rdbuf();
	outFile.close();
	time(&timeEnd);
	cout<<"rdbuf made in :" << (difftime(timeEnd,timeStart)) <<".Sec"<<endl;
	cout<<"Reading istream from file and make set Container" <<endl;
												//read file again
	ifstream inFile(filename);
	time(&timeStart);
												//add to container
	cdc.add(inFile);
	time(&timeEnd);
	inFile.close();
	cout<<"Container made in :" << (difftime(timeEnd,timeStart)) <<".Sec"<<endl;
	cout<< string(30, '*')<<"End of Test 8" << string(30, '*')<<endl;


}



/*****************************************************************************
*                 test9: increase record  number for test 9 and  to check
*                 relation between time and records,Fields ,repeat rate,
****************************************************************************/

void test9(DupCsvNcr& cdc,int minRecordNum,int maxRecordNum,
		              int minFieldNum,int maxFieldNum,
		              int minAveRepeat,int maxAveRepeat){

	int timeOfAdding=0;
	int exTime=0;
	int intervalR=((maxRecordNum-minRecordNum)/10);
	int intervalF=((maxFieldNum - minFieldNum)/5);
	int intervalA=((maxAveRepeat-minAveRepeat)/20);
	time_t timeStart,timeEnd;

	if(intervalR<1)intervalR=1;
	if(intervalF<1)intervalF=1;
	if(intervalA<1)intervalA=1;

	printHeaderCout("test 9: Record and Time relation");

	cout<<"Records,Repeat,    Fields ,      Time ,     Diff Rec  ,   Diff Field   ,  Diff Rep  ,  Diff Time"<<endl;
	cout<< string(100, '-')<<endl;

	for (int aveRepeat = minAveRepeat; aveRepeat <= maxAveRepeat;aveRepeat=aveRepeat+intervalA) {
			for (int fieldNum = minFieldNum; fieldNum <= maxFieldNum;fieldNum=fieldNum+intervalF) {
					for (int recordNum = minRecordNum; recordNum <= maxRecordNum;recordNum=recordNum+intervalR ) {


						time(&timeStart);

						aid4test(cdc,recordNum,fieldNum,aveRepeat);

						time(&timeEnd);
						timeOfAdding=(difftime(timeEnd,timeStart));
						cdc.clear();

						cout<<recordNum<<"\t"<<aveRepeat<<"\t\t"
							<<fieldNum<<"\t"<<timeOfAdding<<".sec"<<"\t"
							<< intervalR<<"\t\t"<< intervalF<<"\t\t"<< intervalA<<"\t\t"
							<<timeOfAdding-exTime<<".sec"<<endl;

						exTime=timeOfAdding;

					}
				}
		}
	cout<< string(30, '*')<<"End of Test 9" << string(30, '*')<<endl;
}



