/////////////////////////////////////////////////////////////////////
// Test.cpp -   Test stub for Test Project                       //
// ver 1.0                                                         //
// Language:    C++, Visual Studio 2017                            //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018   //
/////////////////////////////////////////////////////////////////////

/*

Class Test : HAs the main function kick all the test cases.
Class CodeRepoProvider - IT helps in sharing code repo instance accross test cases as it stores the reference.

Required Files:
* ---------------
* Executive.h,PayLoad.h
* CodeRepo.h
* Maintenance History:
* --------------------
* ver 1.0 : 2 Mar 2018
* 
*/


#include "Test.h"
#include "../NoSQLDB/Executive/Executive.h"
#include "../NoSQLDB/PayLoad/PayLoad.h"
#include "../CodeRepo/CodeRepo.h"


using namespace NoSqlDb;
//This file has test cases for the project and one test stub which imolements the functionality mentioned in this file only.

//IT used to create empty lines in output , a substitute of \n
auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
	Utilities::putline(n, out);
};

//This is my classProvider which helps me in sharing commom code repo among test cases. It stores the refrence of CodeRepo instance
// And it returns the code repo instance. It helps in using single Code Repo instance among test cases.
class CodeRepoProvider
{
public:
	CodeRepo<PayLoad>& cr() { return cr_; }
private:
	static CodeRepo<PayLoad> cr_;
};

CodeRepo<PayLoad> CodeRepoProvider::cr_;

//This is the test case to show 1st reuirement that c++ 11 is being used.
bool testR1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.";
	putLine();
	return true; // would not compile unless C++11
}

//----< demo requirement #2 >------------------------------------------

//this test cases just mention that in this proejct new and delete operators are used to create instance.
bool testR2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	putLine();
	return true;
}

//This is the test whhich is called in the end to persisit CodeRepo DB and dependency Map into two respective XMLs.
//These xml files can be used to reload Code Repo DB and Dependency Map during starting of project.
bool TC9()
{
	CodeRepoProvider crp;
	CodeRepo<PayLoad> c;
	c = crp.cr();
	std::cout << "\n\n--------******---------Persisting CodeRepo DB and Depedency Map------******---------";
	
	//Creating a demo element to check In File in closed state.
	DbElement<PayLoad> test5_dbElement;
	test5_dbElement.name("TC9_Author");
	test5_dbElement.descrip("This file containes the code of Version.h");
	test5_dbElement.dateTime(DateTime().now());
	test5_dbElement.payLoad().value("../Version/Version.h");
	test5_dbElement.payLoad().categories().push_back("Version1");
	test5_dbElement.payLoad().nmspc("NameSpaceVersion");
	test5_dbElement.payLoad().objstatus(0);
	c.checkIn(test5_dbElement);
	//Creating a demo element to check In File in closed state.
	DbElement<PayLoad> test6_dbElement;
	test6_dbElement.name("TC9_Author");
	test6_dbElement.descrip("This file containes the code of Version.cpp");
	test6_dbElement.dateTime(DateTime().now());
	test6_dbElement.payLoad().value("../Version/Version.cpp");
	test6_dbElement.payLoad().categories().push_back("Version1");
	test6_dbElement.payLoad().nmspc("NameSpaceVersion");
	test6_dbElement.payLoad().objstatus(0);
	c.checkIn(test6_dbElement);

	test5_dbElement.payLoad().objstatus(1);
	c.checkIn(test5_dbElement);

	test6_dbElement.payLoad().objstatus(0);
	test6_dbElement.children().push_back("NameSpaceVersion::Version.h.2");
	c.checkIn(test6_dbElement);

	c.saveDB(); //This is function which is called to store Code Repo DB to XML.
	c.saveMaptoXML(); //This is the function which is called to store Code Repo Dependency Map to XML.
	std::cout << "\n\nCheck ../DB_Output.xml (Absolute Path "+ FileSystem::Path::getFullFileSpec("../DB_Output.xml") + ")and ../Dependency_Map_Output.xml (Absolute Path - "+FileSystem::Path::getFullFileSpec("../Dependency_Map_Output.xml")+")\n\n";
	crp.cr() = c; //Storing back the changes in Code Repo to Code Repo Provider.
	return true;
}

//This test case shows a reuirement where Files are displayed on basis of category and specifc name.
//User either gives the vector of category or specific filename.
//Make sure to process any key after notepd opens to display any file by name.
bool TC8()
{
	CodeRepoProvider crp;
	CodeRepo<PayLoad> c;
	c = crp.cr();
	std::cout << "\n \n -----******Requirement 5 **********-------------Showing Results by Category and showing one key out of them in notepad ----------------\n\n";
	std::vector<std::string> vector_of_Category;
	vector_of_Category.push_back("Browse2");
	DbCore<PayLoad> temp_db;
	temp_db = c.BrowseByCategory(vector_of_Category); //This function class search the entire DB and return the keys which has the categories mentioned Vector.
	showDb(temp_db);
	auto it = temp_db.dbStore().begin();
	it++; 
	it++;//Iterating to target the second file to be displayed on notepad.
	std::string key = it->first;
	size_t indexofdot = key.find_last_of(".");
	std::string dstfilename = key.substr(0, indexofdot);
	std::string version = key.substr(indexofdot + 1); //Extraction filename and verion number from user inout key.
	std::stringstream stream(version);
	size_t version_int = 0;
	stream >> version_int;
	std::cout << "/n Showing random selection - version 2 of Browse.h in notepad";
	c.browseSpecificFile(dstfilename, version_int); //This function class copies code repo file to some stage location and show it on notepad.
	std::cout << "\n \n ------------------Showing Results by FileName and showing it in notepad ----------------\n\n";
	std::cout << "/n Showing latest version of Browse.cpp in notepad";
	c.browseSpecificFile("NameSpaceBrowse::Browse.cpp");//This function class copies code repo file to some stage location and show it on notepad.
	crp.cr() = c;
	return true;
}

//This test case shows the checkout reuirement in two ways.
//1. showing latest version of file provided by user with its dependencies, if user does not specify version number.
//2. If user specifies specific file version , then Code Repo checks out that specific version for user and stores it in stage folder.
bool TC7()
{
	std::cout << "\n\n------------******REQUIREMENT 2 - CheckOut*********-- All checkout files are at ../stage (Absolute Path)" + FileSystem::Path::getFullFileSpec("../stage/") + "-------------";
	CodeRepoProvider crp;
	CodeRepo<PayLoad> c;
	c = crp.cr();

	std::cout << "\n1. Check Out Specific Version - NameSpaceProcess::Process.h.1 at ../stage/Process.h";
	c.checkOut("NameSpaceProcess::Process.h",1);


	std::cout << "\n 2. Check Out latest version of NameSpaceCheckOut::CheckOut.cpp with dependenies at ../stage/FileMgr.cpp , ../stage/CheckIn.cpp) ";
	c.checkOut("NameSpaceCheckOut::CheckOut.cpp");
	

	crp.cr() = c;
	return true;
}

//This is the the thord part of dependency test case. In ths test case , 2 files are in closing state because of 1 File which is in open,
//When that 1 file goes into close state , other teo files are also sent to closing state.
//And in this test Dependency Map used is the one created in the TC3 when Code Repo DB and Code Repo Dependency map is read via XML.
bool TC6Part3()
{
	std::cout << "\n\n------- DEPENDENCY MAP PERSISTANCE -> SWITCHING BACK TO ORIGINAL DB TO USE Depedency MAP WHICH WAS READ FROM XML IN TC3-----";
	std::cout << "\n\n Scenario 3 : Where 2 Files are not closed becasue of 1 File";
	std::cout << "\n FileMAnager.ccp.2 and FileMAnager.h.2 could not be closed becasue CheckIn.cpp.2 is in open state";
	CodeRepoProvider crp;
	CodeRepo <PayLoad> c = crp.cr();
	std::cout << "\n Let me show you DB Below-> which is persistant - here FileMAnager.ccp.2 and FileMAnager.h.2 are in closing state (2) becasue CheckIn.cpp.2 is in open state (1)  ";
	c.showCodeRepoDb();

	DbElement<PayLoad> test5_dbElement;
	test5_dbElement.name("Vijay");
	test5_dbElement.descrip("This file containes the code of Payload");
	test5_dbElement.dateTime(DateTime().now());
	test5_dbElement.payLoad().value("../CheckIn/CheckIn.cpp");
	test5_dbElement.payLoad().categories().push_back("Category3");
	test5_dbElement.payLoad().nmspc("CheckIn");
	
	test5_dbElement.payLoad().objstatus(PayLoad::status::closed);
	c.checkIn(test5_dbElement); //v2 //When user checks in this file , it will close other two files as well.

	std::cout << "\nDB Below-> CheckIn.cpp.2 is closed (0) which inturn closed (0) FileMAnager.ccp.2 and FileMAnager.h.2";
	std::cout << "\n All checked in Files are ../root/CheckIn";
	c.showCodeRepoDb();
	crp.cr() = c;
	return true;
}

//This function is helper for TC6 Part2 to just the DBElements ready for TC6Part2. TC6Part2 does action od DBelemnts created 
//in this function.
void createDBElementsforTC6Part2(DbElement<PayLoad> & test3_dbElement, DbElement<PayLoad> & test4_dbElement, DbElement<PayLoad> & test5_dbElement)
{

	test3_dbElement.name("TC6_P2_Author");
	test3_dbElement.descrip("This file containes the code of FileMgr.cpp");
	test3_dbElement.dateTime(DateTime().now());
	test3_dbElement.payLoad().value("../FileMgr/FileMgr.cpp");
	test3_dbElement.payLoad().categories().push_back("FileMgr2");
	test3_dbElement.payLoad().nmspc("NameSpaceFileManager");
	test3_dbElement.payLoad().objstatus(0);

	test4_dbElement.name("TC6_P2_Author");
	test4_dbElement.descrip("This file containes the code of FileMgr.h");
	test4_dbElement.dateTime(DateTime().now());
	test4_dbElement.payLoad().value("../FileMgr/FileMgr.h");
	test4_dbElement.payLoad().categories().push_back("FileMgr2");
	test4_dbElement.payLoad().nmspc("NameSpaceFileManager");
	test4_dbElement.payLoad().objstatus(0);

	test5_dbElement.name("TC6_P2_Author");
	test5_dbElement.descrip("This file containes the code of CheckIn.cpp");
	test5_dbElement.dateTime(DateTime().now());
	test5_dbElement.payLoad().value("../CheckIn/CheckIn.cpp");
	test5_dbElement.payLoad().categories().push_back("CheckIn3");
	test5_dbElement.payLoad().nmspc("NameSpaceCheckIn");
	test5_dbElement.payLoad().objstatus(0);
}

//This is Part 2 of TC6 in which one file is dependendents on two differnts and both the dependents file are in opened state.
// When user tries to close that one file , it goes to closing state because dependents are open.
//When 1 dependendent closes , it could not close that 1 file.
//When 2 dependent closes , it could close that 1 file because dependencies are closed.
bool TC6Part2(CodeRepo<PayLoad> c)
{
	std::cout << "\n\n Scenario 2 : One File is dependent on other two Files";
	std::cout << "\n FileMgr.cpp.4 is dependent on FileMgr.h.4 and CheckIn.cpp.4 and both of them are in open state";
	std::cout << "\n FileMgr.h.4 closes but FileMgr.cpp.4 does not close becuase it is till dependent on CheckIn.cpp.4";
	std::cout << "\n CheckIn.cpp.4 closes and at same time FileMgr.cpp.4 closes";
	DbElement<PayLoad> test3_dbElement, test4_dbElement, test5_dbElement;
	createDBElementsforTC6Part2(test3_dbElement, test4_dbElement, test5_dbElement);
	c.checkIn(test3_dbElement); // v3
	c.checkIn(test4_dbElement); //v3
	c.checkIn(test5_dbElement); //v3
	test4_dbElement.payLoad().objstatus(PayLoad::status::open);
	c.checkIn(test4_dbElement); //v4
	test5_dbElement.payLoad().objstatus(PayLoad::status::open);
	c.checkIn(test5_dbElement); //v4
	std::cout << "\n Below DB -> shows FileMgr.h.4 , CheckIn.cpp.4 are in open state";
	c.showCodeRepoDb();
	test3_dbElement.payLoad().objstatus(PayLoad::status::closed);
	test3_dbElement.children().push_back("NameSpaceFileManager::FileMgr.h.4");
	test3_dbElement.children().push_back("NameSpaceCheckIn::CheckIn.cpp.4");
	c.checkIn(test3_dbElement); //v4
	std::cout << "\n *Below DB -> User tried to close FileMgr.ccp with dependencies but went to closing state(2) FileMgr.h.4 , CheckIn.cpp.4 are in open state*";
	c.showCodeRepoDb();
	test4_dbElement.payLoad().objstatus(PayLoad::status::closed);
	c.checkIn(test4_dbElement); //v4
	std::cout << "\n *Below DB -> User tried to close FileMgr.h.4 but FileMgr.cpp are in open state becasue of CheckIn.cpp.4*";
	c.showCodeRepoDb();
	test5_dbElement.payLoad().objstatus(PayLoad::status::closed);
	c.checkIn(test5_dbElement); //v4
	std::cout << "\n *Below DB -> User closed CheckIn.cpp.4 which inturn closed FileMgr.cpp*";
	c.showCodeRepoDb();
	std::cout << "\n All check in Files at ../root/NameSpaceCheckIn , ../root/NameSpaceFileManager";
	TC6Part3();
	return true;
}

//This function creates the DB Elements for TC6 Part 1. TC6 Part1  uses the DBElements created here to do actions on them.
void createDBElementsforTC6(DbElement<PayLoad> & test3_dbElement, DbElement<PayLoad> & test4_dbElement, DbElement<PayLoad> & test5_dbElement, DbElement<PayLoad> & test6_dbElement)
{
	test3_dbElement.name("TC6_Author");
	test3_dbElement.descrip("This file containes the code of FileMgr.cpp");
	test3_dbElement.dateTime(DateTime().now());
	test3_dbElement.payLoad().value("../FileMgr/FileMgr.cpp");
	test3_dbElement.payLoad().categories().push_back("FileMgr1");
	test3_dbElement.payLoad().nmspc("NameSpaceFileManager");
	test3_dbElement.payLoad().objstatus(0);
	
	test4_dbElement.name("TC6_Author");
	test4_dbElement.descrip("This file containes the code of FileMgr.h");
	test4_dbElement.dateTime(DateTime().now());
	test4_dbElement.payLoad().value("../FileMgr/FileMgr.h");
	test4_dbElement.payLoad().categories().push_back("FileMgr2");
	test4_dbElement.payLoad().nmspc("NameSpaceFileManager");
	test4_dbElement.payLoad().objstatus(0);

	test5_dbElement.name("TC6_Author");
	test5_dbElement.descrip("This file containes the code of CheckIn.cpp");
	test5_dbElement.dateTime(DateTime().now());
	test5_dbElement.payLoad().value("../CheckIn/CheckIn.cpp");
	test5_dbElement.payLoad().categories().push_back("CheckIn1");
	test5_dbElement.payLoad().nmspc("NameSpaceCheckIn");
	test5_dbElement.payLoad().objstatus(0);

	test6_dbElement.name("TC6_Author");
	test6_dbElement.descrip("This file containes the code of CheckIn.h");
	test6_dbElement.dateTime(DateTime().now());
	test6_dbElement.payLoad().value("../CheckIn/CheckIn.h");
	test6_dbElement.payLoad().categories().push_back("CheckIn2");
	test6_dbElement.payLoad().nmspc("NameSpaceCheckIn");
	test6_dbElement.payLoad().objstatus(0);
}

//Here in test case multilevel dependency is shown , File 1 depends on File 2 which is in open state.
//Fil2 depends on File3.
//File3 depends on File 4.
// When File4 wants to close it can not becasue tree above him is opem.
//When user closes file 2.
//IT closes all the File2 , File 3 in one go because they were part of depednecy map becasue of File 1.
bool TC6()
{
	std::cout << "\n\n--------******REQUIREMENT 4********-----A check In can only be closed if its dependent packages are presnt with closed check ins------*******------";
	std::cout << "\n Scenario 1 : Multilevel Dependencies - CheckIn.cpp.2 depends upon CheckIn.h.2 , CheckIn.h.2 depnds upon FileMgr.h.2 , FileMgr.h.2 depends upon FileMgr.cpp.2 ";//Files are interdepedent File3 could not clode becuase of File 2 , File 2 could not cloase because of File 1, so when File 1 is closed 
	std::cout << "\n CheckIn.cpp.2 , CheckIn.h.2 , FileMgr.h.2 went to closing state becasue their dependencies are open";
	std::cout << "\n all files will be cosed when FileMgr.cpp.2 is cosed\n";
	std::cout << "***SHOWING THIS TEST CASE WITH ONE MORE INSTANCE OF CODEREPO BECAUSE IT WILL BE DIFFICULT TO CHECK OUTPUT WITH LARGE DB****";
	DbElement<PayLoad> test3_dbElement,test4_dbElement,test5_dbElement,test6_dbElement;
	createDBElementsforTC6(test3_dbElement, test4_dbElement, test5_dbElement, test6_dbElement);
	CodeRepo<PayLoad> c;
	c.checkIn(test3_dbElement);
	c.checkIn(test4_dbElement);
	c.checkIn(test5_dbElement);
	c.checkIn(test6_dbElement);
	test3_dbElement.payLoad().objstatus(PayLoad::status::open);
	c.checkIn(test3_dbElement);
	test4_dbElement.payLoad().objstatus(PayLoad::status::open);
	c.checkIn(test4_dbElement);
	test5_dbElement.payLoad().objstatus(PayLoad::status::open);
	c.checkIn(test5_dbElement);
	c.showCodeRepoDb();
	std::cout << "\n\n*Below DB -> CheckIn.cpp.2 , CheckIn.h.2 , FileMgr.h.2 went to closing state becasue their paremts are open showin children of specific key\n*";
	test6_dbElement.children().push_back("NameSpaceCheckIn::CheckIn.cpp.2");
	test6_dbElement.payLoad().objstatus(PayLoad::status::closed);
	c.checkIn(test6_dbElement);
	test5_dbElement.children().push_back("NameSpaceFileManager::FileMgr.h.2");
	test5_dbElement.payLoad().objstatus(PayLoad::status::closed);
	c.checkIn(test5_dbElement);
	test4_dbElement.children().push_back("NameSpaceFileManager::FileMgr.cpp.2");
	test4_dbElement.payLoad().objstatus(PayLoad::status::closed);
	c.checkIn(test4_dbElement);
	test3_dbElement.payLoad().objstatus(PayLoad::status::closed);
	c.showCodeRepoDb();
	c.checkIn(test3_dbElement);
	std::cout << "\n\n*Below DB -> CheckIn.cpp.2 , CheckIn.h.2 , FileMgr.h.2 closed when FileMgr.cpp.2 went to closed state*";
	c.showCodeRepoDb();
	std::cout << "\n All check in Files at ../root/NameSpaceCheckIn , ../root/NameSpaceFileManager";
	TC6Part2(c);
	return true;
}

//This is actually a start of Test Case by reading the XML which has CodeRepo DB from last session.
// And dependency Map from last session.
//This test cases reads them , create a instance of CodeRepo and store DB and dependency Map.
//That CodeRepo instance is given to CodeRepoProvider.
bool TC3()
{
	std::cout << "\n\n-------**REQUIREMENT6**----------Read an XML db_input (../db_input.xml) (absolutePath of you machine - "+ FileSystem::Path::getFullFileSpec("../db_input.xml") +") to make Db with some Files are in opened(1) and closed(0) state---------\n ";
	std::cout << "\n\n And also Reading Dependency XML (used in Requirement 4 , TC6 , Part3 Scenario 3 ) for files in closing state (2) and there respective dependencies due to which they could not close in through XML File ../Dependency_Map_Input.xml and absolute Path of your machine " + FileSystem::Path::getFullFileSpec("../Dependency_Map_Input.xml");
	CodeRepoProvider crp;
	CodeRepo<PayLoad> c = crp.cr();
	c.writeDB();
	c.readMapfromXML();
	c.showCodeRepoDb();
	std::cout << "\n Showing Dependency Map read from XML\n";
	c.showDependencyMap();
	crp.cr() = c; //Browse.cpp.1 , Browse.cpp.2 , Browse.h.1 , Process.cpp.1 , Process.h.1, Process.h.2
	return true;
}

//This test case demonstatre when ever first file checks in it checks in open state.
bool TC4Part0()
{
	std::cout << "0. User is check in File for the first time ../MyExecute/MyExecute.cpp and its in open state (1) , MyExecute.cpp.1 in open state\n";
	std::cout << "1. Server status is closed(0), user is sending close(0)--version shoudld increase by 1 Process.cpp.1 --> Process.cpp.2\n";
	std::cout << "2. Server status is open(1), user is sending close(0)--version shoudld remain same and get close Process.h.2 --> Process.h.2 and description changed (Version Same,Process.h) to show overriding\n  ";
	std::cout << "3. Server status is closed(0), user is sending open(1)--version shoudld increae by 1 and Browse.h.1 --> Browse.h.2\n";
	std::cout << "4. Server status is open(1), user is sending open(1)--version shoudld remain same and Browse.cpp.2 --> Browse.cpp.2 and description changed (Version Same,Browse.cpp) to show overriding\n";
	CodeRepoProvider crp;
	CodeRepo<PayLoad> c = crp.cr();	
	DbElement<PayLoad> test1_dbElement;
	test1_dbElement.name("Author1_REQ2");
	test1_dbElement.descrip("This file containes the code of MyExecute.cpp");
	test1_dbElement.dateTime(DateTime().now());
	test1_dbElement.payLoad().value("../MyExecute/MyExecute.cpp");
	test1_dbElement.payLoad().categories().push_back("MyExecute1");
	test1_dbElement.payLoad().nmspc("NameSpaceExecute");
	c.checkIn(test1_dbElement); 
	crp.cr() = c;
	return true;
}

//This test case perfrom 4 scenarios of check in , when server is open and user is sending open , 
//server is closed and user is sending open.
//server is open and user is sending close.
//server is closed and user is sending closed.
//These actions are operated on existing DB entries read during First Test Case.
bool TC4()
{
	std::cout << "\n\n------------*****REQ 2*****-CheckIn Versioning 4 scenarios , File are copied in respective Namespace ../root/NameSpaceProcess/,../root/NameSpaceBrowse/  folder-------*************--------\n";
	TC4Part0();
	CodeRepoProvider crp;
	CodeRepo<PayLoad> c = crp.cr();
	
	DbElement<PayLoad> test1_dbElement;
	test1_dbElement.name("Author1_REQ2");
	test1_dbElement.descrip("This file containes the code of Process.cpp");
	test1_dbElement.dateTime(DateTime().now());
	test1_dbElement.payLoad().value("../Process/Process.cpp");
	test1_dbElement.payLoad().categories().push_back("Process2");
	test1_dbElement.payLoad().nmspc("NameSpaceProcess");
	test1_dbElement.payLoad().objstatus(0);
	c.checkIn(test1_dbElement); //Process.cpp.2 in closed state.
	DbElement<PayLoad> test2_dbElement;
	test2_dbElement.name("Author1_REQ2");
	test2_dbElement.descrip("Version Same,Process.h");
	test2_dbElement.dateTime(DateTime().now());
	test2_dbElement.payLoad().value("../Process/Process.h");
	test2_dbElement.payLoad().categories().push_back("Process1");
	test2_dbElement.payLoad().nmspc("NameSpaceProcess");
	test2_dbElement.payLoad().objstatus(0);
	c.checkIn(test2_dbElement); //Process.h.2 in closed state.
	DbElement<PayLoad> test3_dbElement;
	test3_dbElement.name("Author2_REQ2");
	test3_dbElement.descrip("This file containes the code of Payload");
	test3_dbElement.dateTime(DateTime().now());
	test3_dbElement.payLoad().value("../Browse/Browse.h");
	test3_dbElement.payLoad().categories().push_back("Browse2");
	test3_dbElement.payLoad().nmspc("NameSpaceBrowse");
	test3_dbElement.payLoad().objstatus(1);
	c.checkIn(test3_dbElement); //XmlDocument.h.2 is in open state;
	DbElement<PayLoad> test4_dbElement;
	test4_dbElement.name("Author2_REQ2");
	test4_dbElement.descrip("Version Same,Browse.cpp");
	test4_dbElement.dateTime(DateTime().now());
	test4_dbElement.payLoad().value("../Browse/Browse.cpp");
	test4_dbElement.payLoad().categories().push_back("Browse2");
	test4_dbElement.payLoad().nmspc("NameSpaceBrowse");
	test4_dbElement.payLoad().objstatus(1);
	c.checkIn(test4_dbElement); //XMLDocument.cpp.2 is in open state;
	c.showCodeRepoDb();
	std::cout << "\n\nCheck all check in files at ../root/NameSpaceProcess/ , ../root/NameSpaceBrowse/ , ../root/NameSpaceExecute";
	std::cout << "\n Absolute Path starts at - " + FileSystem::Path::getFullFileSpec("../root/");
	crp.cr() = c;
	return true;
}

//This TC demonstrate user can send a package of files in forma of vector and all will be checked in as per 
// DB lements stored in the vector.
bool TC5()
{
	std::cout << "\n\n ------****-----Test Case to demonstrate mutiple files can be check in together in a single package--------*****-------";
	std::cout << "\n1. ../CheckOut/CheckOut.cpp in ../root/NameSpaceCheckOut/ with status as closed (0)";
	std::cout << "\n2. ../CheckOut/CheckOut.h in ../root/NameSpaceCheckOut with status as closed (0) ";
	CodeRepoProvider crp;
	CodeRepo<PayLoad> c = crp.cr();

	std::vector<DbElement<PayLoad>> vec_of_dbElements;
	DbElement<PayLoad> test1_dbElement;
	test1_dbElement.name("Author_TC5");
	test1_dbElement.descrip("This file containes the code of Checkout.cpp");
	test1_dbElement.dateTime(DateTime().now());
	test1_dbElement.payLoad().value("../CheckOut/CheckOut.cpp");
	test1_dbElement.payLoad().categories().push_back("CheckOut1");
	test1_dbElement.payLoad().objstatus(0);
	test1_dbElement.payLoad().nmspc("NameSpaceCheckOut");
	vec_of_dbElements.push_back(test1_dbElement);	 //Checkout.cpp.1 in closed state.

	DbElement<PayLoad> test2_dbElement;
	test2_dbElement.name("Author_TC5");
	test2_dbElement.descrip("This file containes the code of CheckOut.h");
	test2_dbElement.dateTime(DateTime().now());
	test2_dbElement.payLoad().value("../CheckOut/CheckOut.h");
	test2_dbElement.payLoad().categories().push_back("CheckOut1");
	test2_dbElement.payLoad().objstatus(0);
	test2_dbElement.payLoad().nmspc("NameSpaceCheckOut");
	vec_of_dbElements.push_back(test2_dbElement);//Checkout.h.1 in closed state.

	c.checkIn(vec_of_dbElements); //vector of two file with their keys is sent to CodeRepo to checkIn
	c.showCodeRepoDb();
	crp.cr() = c;
	return true;
}

//This is the main function which is called by myexecutive package to run all test cases.
void Test::execute(void)
{
	Utilities::Title("Test Case start from here !!");
	putLine();
	CodeRepo<PayLoad> c;
	TestExecutive ex;

	TestExecutive::TestStr ts1{ testR1, "\nUse C++11" };
	TestExecutive::TestStr ts2{ testR2, "\nUse streams and new and delete" };
	TestExecutive::TestStr ts3{ TC3 , "\nReading XML for some open(1) state files and some close(0) ans come closing(2) state files" };
	TestExecutive::TestStr ts4{ TC4 , "\nBasic 5 check in Scenarios , default state open , open-open , close-close , close-open, open-close" };
	TestExecutive::TestStr ts5{ TC5 , "\n Check In multiple files together" };
	TestExecutive::TestStr ts6{ TC6 , "\n A check In can only be closed if its dependent packages are presnt with closed check ins" };
	TestExecutive::TestStr ts7{ TC7 , "\n CheckOut latest version , check out specific version , checkout with dependencies" };
	TestExecutive::TestStr ts8{ TC8 , "\n Browse By category and Browse by FileName" };
	TestExecutive::TestStr ts9{ TC9 , "\n Persisting Code Repo DB and Dependency XML" };
	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3);
	ex.registerTest(ts4);
	ex.registerTest(ts5);
	ex.registerTest(ts6);
	ex.registerTest(ts7);
	ex.registerTest(ts8);
	ex.registerTest(ts9);
	// run tests

	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n  all tests passed";
	else
		std::cout << "\n  at least one test failed";

	putLine(2);
	std::getchar();
}

#ifdef TEST_CODEREPO
int main()
{
	Utilities::Title("Test Case start from here !!");
	putLine();
	TestExecutive ex;
	CodeRepo<PayLoad> c;

	TestExecutive::TestStr ts1{ testR1, "\nUse C++11" };
	TestExecutive::TestStr ts2{ testR2, "\nUse streams and new and delete" };
	TestExecutive::TestStr ts3{ TC3 , "\nReading XML for some open(1) state files and some close(1) state files" };

	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3);
	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n  all tests passed";
	else
		std::cout << "\n  at least one test failed";

	putLine(2);
	getchar();
	return 0;
}
#endif
