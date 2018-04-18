#pragma once

////////////////////////////////////////////////////////////////////////////
// CodeRepo.h - Has design of CodeRepo class which helps in check in , check out and vesion of a file  //
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////


/*
Package Operations:
* -------------------
* This package provides 1 class:
*
- CodeRepo : Template Class ,  used to checkIn , CheckOut and Version,brwosing a File

Public Functions :
void checkIn(const DbElement<T> & db) - This function calls the static check In method of CheckIn Class with input as DBElement.
void checkIn(const std::vector<DbElement<T>> & vec_of_dbElemes) - This function calls the static check In method of CheckIn Class with input as vector of DBElement if user wants to check In Files in bulk.
std::vector<std::string> checkOut(const std::string &chekout_key , int version = 0) - This functions call the static checkOut function of CheckOut class which copies the files to stage folder depending upon the version specified by user.
void saveDB() - This function calls the saveDB method of XMLMapPersistant class which write the Code Repo DB to XML File
void writeDB() - This functions call the write DB method of XMLMapPersistant class which reads the XML and stores the DB into DB of code Repo.
void saveMaptoXML() - This function calls the saveMaptoXML method of XMLMapPersistant class which write the Code Repo Dependency Map to XML File 
void readMapfromXML() - This functions call the readMapfromXML method of XMLMapPersistant class which writes the Dependency Map of code Repo to XML File.
DbCore<T> BrowseByCategory(std::vector<std::string>& category_name) - This function calls browsebycategory function of browse call and returns a DBCore with keys and its metadata.
void browseSpecificFile(const std::string &chekout_key, int version = 0) - This function browse a file name into code repo and opens it in notepad.
int handlerForChildren(const std::string& child_key,DbElement<T> db, const std::string& temp_key) - This is function to hadnle a scenario where a element has depednecies which needs to be added into dependency map.
void showCodeRepoDb() - This function prints the current DB of code Repo.
void showDependencyMap() - This function prints the dependency Map.

Private Functions :
std::string getDestionation(const std::string& var_source, const std::string & var_namespace) - IT returns the destination path basis on parametre proivided ina  function
std::vector<std::string> getKeysWhichCanNowBeClosed(std::vector<std::string> &vec,std::map<std::string, std::vector<std::string>>& param_dep_map, std::string key_Search_In_Vactor_Value) - When a particualr file goes to closed state , what other files can also be cloased are figured out in this function becuase it could be dependent to other file.
void check_In_Keys_Which_can_be_closed(DbCore<T> &param_db, std::vector<std::string>& param_keys) - Further dependencies are find out this function to a particualr file.
std::vector<std::string> getDependencyOfKey(std::vector<std::string> key_and_their_parents_seq) - IT creates a vector of depedencies from top to bottom of a particular key.



* Required Files:
* ---------------
* Executive.h, CheckIn.cpp
* CehckOut.h, XmlMapPersistent.h
* Browse.h, Version.h

*
*
* Maintenance History:
* --------------------
* ver 1.0 : 2nd Mar 2018

*/

#include "../NoSQLDB/Executive/Executive.h"
#include "../CheckIn/CheckIn.h"
#include "../CheckOut/CheckOut.h"
#include "../XmlMapPersistent/XmlMapPersistent.h"
#include "../Browse/Browse.h"
#include "../Version/Version.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<fstream>

using namespace NoSqlDb;


template<typename T>
class CodeRepo {

private:
	static std::string root_path;
	static std::string persist_xml_path_name_input;
	static std::string persist_xml_path_name_output;
	static std::string persist_dependency_map_path_name_input;
	static std::string persist_dependency_map_path_name_output;
	static std::string checkout_rootpath;
	int versiongivenbyuser;
	DbCore<PayLoad> main_db;
	std::map<std::string,std::vector<std::string>> dependency_map;

	//private functions of Code Repo
	std::string getDestionation(const std::string& var_source, const std::string & var_namespace);
	std::vector<std::string> getKeysWhichCanNowBeClosed(std::vector<std::string> &vec,std::map<std::string, std::vector<std::string>>& param_dep_map, std::string key_Search_In_Vactor_Value);
	void check_In_Keys_Which_can_be_closed(DbCore<T> &param_db, std::vector<std::string>& param_keys);
	std::vector<std::string> getDependencyOfKey(std::vector<std::string> key_and_their_parents_seq);

	//public functions of code repo.
public :
	void checkIn(const DbElement<T> & db);
	void checkIn(const std::vector<DbElement<T>> & vec_of_dbElemes);
	std::vector<std::string> checkOut(const std::string &chekout_key , int version = 0);
	void saveDB();
	void writeDB();
	void saveMaptoXML();
	void readMapfromXML();
	DbCore<T> BrowseByCategory(std::vector<std::string>& category_name);
	void browseSpecificFile(const std::string &chekout_key, int version = 0);
	int handlerForChildren(const std::string& child_key,DbElement<T> db, const std::string& temp_key);
	void showCodeRepoDb();
	void showDependencyMap();
};

template<typename T>
std::string CodeRepo<T>::root_path = "../root";
template<typename T>
std::string CodeRepo<T>::persist_xml_path_name_input = "../DB_Input.xml";
template<typename T>
std::string CodeRepo<T>::persist_xml_path_name_output = "../DB_Output.xml";
template<typename T>
std::string CodeRepo<T>::persist_dependency_map_path_name_input = "../Dependency_Map_Input.xml";
template<typename T>
std::string CodeRepo<T>::persist_dependency_map_path_name_output = "../Dependency_Map_Output.xml";
template<typename T>
std::string CodeRepo<T>::checkout_rootpath = "../stage";


template<typename T>
//This fucntions check in the all DBelemnts present in a vector.
inline void CodeRepo<T>::checkIn(const std::vector<DbElement<T>>& vec_of_dbElemes)
{
	for (auto x : vec_of_dbElemes)
	{
		checkIn(x); //calling chekIn method of same class for paticular DBElement.
	}
}

template<typename T>
//This function checks in particular DBElement.
inline void CodeRepo<T>::checkIn(const DbElement<T> &db)
{
	T var_t = db.payLoad();
	std::string var_source = var_t.value();
	std::string var_namespace = var_t.nmspc();
	std::string var_destinarion = getDestionation(var_source, var_namespace);
	std::string var_current_key_RegEx = var_namespace + "::" + var_source.substr(var_source.rfind("/") + 1, var_source.size());
	int version_number = Version<T>::getVersion(this->main_db , var_source , var_namespace,db);
	int last_Version_Status = -1;
	Version<T>::getLatestVersionOfChildren(this->main_db, var_current_key_RegEx, last_Version_Status); //this function will retunr the latestversion for specific key by query database on basis of namespace and File PAth.
	if (last_Version_Status == 0) //checking if last version is closed then increase the version number by 1.
		version_number = version_number + 1;
	if (version_number != 1){
		std::string temp_key = var_namespace + "::" + var_source.substr(var_source.rfind("/") + 1, var_source.size()) + "." + std::to_string(version_number);
		if ((var_t.objstatus() == 0 && last_Version_Status == 0) || (var_t.objstatus() == 0 && last_Version_Status == 1)){ //Conditions where user sttaus of file is closed against server status of open and close.
			std::string child_key = var_namespace + "::" + var_source.substr(var_source.rfind("/") + 1, var_source.size())+ "." + std::to_string(version_number);
			std::vector<std::string> vec;
			int flag_has_dependency_which_is_open = 0;
			if (db.children().size() >= 1){ //checking if a file sent has a dependency
				flag_has_dependency_which_is_open = handlerForChildren(child_key,db,temp_key);} //hadling children if found.
			if (flag_has_dependency_which_is_open == 0){
				if (last_Version_Status = 1){ //update the DBElemnt of existing key if server state is opened state.
					main_db[temp_key].name() = db.name();
					main_db[temp_key].descrip() = db.descrip();
					main_db[temp_key].dateTime() = db.dateTime();
					main_db[temp_key].children() = db.children();
					main_db[temp_key].payLoad() = db.payLoad();}
				else
					main_db[temp_key] = db;
			CheckIn<T>::copyFile(var_source, var_destinarion + "." + std::to_string(version_number), var_namespace, CodeRepo<T>::root_path);}
			if (flag_has_dependency_which_is_open == 0){ //in case dependeny found in the file that needs to be checked in.
				std::vector<std::string> vec_keys_which_can_be_closed;
				getKeysWhichCanNowBeClosed(vec_keys_which_can_be_closed, this->dependency_map, var_namespace + "::" + var_source.substr(var_source.rfind("/") + 1, var_source.size()) + "." + std::to_string(version_number));
				check_In_Keys_Which_can_be_closed(this->main_db, vec_keys_which_can_be_closed);}}
		else if (var_t.objstatus() == 1 && last_Version_Status == 0){ //scenario where user sends close stattus and server status is also closed.
			main_db[temp_key] = db;
			CheckIn<T>::copyFile(var_source, var_destinarion + "." + std::to_string(version_number), var_namespace, CodeRepo<T>::root_path);}
		else if (var_t.objstatus() == 1 && last_Version_Status == 1){
			main_db[temp_key].name() = db.name();
			main_db[temp_key].descrip() = db.descrip();
			main_db[temp_key].dateTime() = db.dateTime();
			main_db[temp_key].children() = db.children();
			main_db[temp_key].payLoad() = db.payLoad();
			CheckIn<T>::copyFile(var_source, var_destinarion + "." + std::to_string(version_number), var_namespace, CodeRepo<T>::root_path);}}
	else{ //if file is checked in for the first time.
		std::string temp_key = var_namespace + "::" + var_source.substr(var_source.rfind("/") + 1, var_source.size()) + "." + std::to_string(version_number);
		main_db[temp_key] = db;
		CheckIn<T>::copyFile(var_source, var_destinarion + "." + std::to_string(version_number), var_namespace, CodeRepo<T>::root_path);}}


template<typename T>
//This functions handles a situation if checked in file is supposed to be cloased and has childrens which are open.
inline int CodeRepo<T>::handlerForChildren(const std::string & child_key, DbElement<T> db,const std::string& temp_key)
{
	//Checking whether the file sent for cloase has children or not.
	int flag_has_dependency_which_is_open = 0;
	for (auto x : db.children())
	{
		int latestversionstatus, latestversion;
		latestversion = Version<T>::getLatestVersionOfChildren(this->main_db, x, latestversionstatus);
		if (latestversionstatus == 1)
		{
			this->dependency_map[child_key].push_back(x); //depedency matters only if theor status is open , if its closed it should not create difference for checkin of file.
			flag_has_dependency_which_is_open = 1;
		}
	}

	if (flag_has_dependency_which_is_open == 1) // if depedency found and is in open state.
	{
		this->main_db[temp_key] = db;
		this->main_db[temp_key].payLoad().objstatus(2); //state will change to closing state.
	}

	return flag_has_dependency_which_is_open;
}

template<typename T>
//This functions shows the CodeRepo DB.
inline void CodeRepo<T>::showCodeRepoDb()
{
	showDb(this->main_db); //Printing DB of CodeRepo.
}

template<typename T>
//This functions shows the CodeRepo DB.
inline void CodeRepo<T>::showDependencyMap()
{
	for (auto x : this->dependency_map)//Printing Dependency Map
	{
		std::cout << x.first << "---Dependent On-->";
		for (auto y : x.second)
		{
			std::cout << y + ",";
		}
	}
}


template<typename T>
//This function finds the series of parent a particular key has.
inline std::vector<std::string> CodeRepo<T>::getDependencyOfKey(std::vector<std::string> key_and_their_parents_seq)
{
	//Here depedency tree is stored in vector of particular key. Keep on fetching partents until you reached the last parent.
	std::string temp_key;
	for (size_t i = 0; i < key_and_their_parents_seq.size(); i++)
	{
		for (auto y : this->main_db[key_and_their_parents_seq[i]].children())
		{
			auto temp_it = find(key_and_their_parents_seq.begin(), key_and_their_parents_seq.end(), y);
			if (temp_it == key_and_their_parents_seq.end())
			{
				key_and_their_parents_seq.push_back(y);
			}
		}

	}
	return key_and_their_parents_seq;
}

template<typename T>
//This function helps in checking out a file which means giving the copy of file in a stage folder depedning on the version specified by user.
inline std::vector<std::string> CodeRepo<T>::checkOut(const std::string& chekout_key, int version)
{
	int specifiedVersion;
	std::vector<std::string> key_and_their_parents_seq;
	int latestverion = -1;
	specifiedVersion = Version<T>::getLatestVersionOfChildren(this->main_db, chekout_key, latestverion);
	if (version != 0) //checke wether version asked by user does not exist in CodeRepo DB.
	{
		if (version > specifiedVersion)
			return key_and_their_parents_seq;
		specifiedVersion = version;
	}
	key_and_their_parents_seq.push_back(chekout_key + "." + std::to_string(specifiedVersion));
	//Copy file to stage folder to give it to user.
	CheckOut::copyFile(getDependencyOfKey(key_and_their_parents_seq),CodeRepo<T>::root_path,CodeRepo<T>::checkout_rootpath);
	return key_and_their_parents_seq;
}

template<typename T>
//This function will iterate over dependency map and check whick key is value free.
inline std::vector<std::string> CodeRepo<T>::getKeysWhichCanNowBeClosed(std::vector<std::string> &keys_Which_Can_Be_Closed,std::map<std::string, std::vector<std::string>>& param_dep_map ,std::string key_Search_In_Vactor_Value)
{
	int itr = param_dep_map.size();
	for (auto itr_map = param_dep_map.begin() ; itr_map != param_dep_map.end() ; ++itr_map )
	{
		itr--;
		std::vector<std::string> map_vector_value = param_dep_map[itr_map->first];
		int length = map_vector_value.size();
		int count = 0;
		for (auto y : map_vector_value)
		{
			if (y == key_Search_In_Vactor_Value) //if key matches the value present in vector remove it from vector.
			{
				length--;
				param_dep_map[itr_map->first].erase(param_dep_map[itr_map->first].begin() + count);
			}
			count++;
		}
		if (length == 0) //if vector becomes null delte that key from map.
		{
			keys_Which_Can_Be_Closed.push_back(itr_map->first);
		}
	}
	for (auto x : keys_Which_Can_Be_Closed)
		param_dep_map.erase(x);

	return keys_Which_Can_Be_Closed;
}

template<typename T>
//This functions actually work on the key which is returned by getKeysWhichCanNowBeClosed because that key-file can be closed now due to which other files can also be closed.
 inline void CodeRepo<T>::check_In_Keys_Which_can_be_closed(DbCore<T> &param_db,std::vector<std::string>& param_keys)
{
	if (param_keys.size() > 0)
	{
		int count = 0;
		for (auto x : param_keys)
		{
			int currentversionstatus = -1;
			//get latest version which should be in closing state.
			int current_version = Version<T>::getLatestVersionOfChildren(param_db, x, currentversionstatus);

			//copy the file with increase version to its directory structure
			std::string old_key_last_Version = x; //+ "." + std::to_string(current_version);
			T t = param_db[old_key_last_Version].payLoad();
			std::string var_destination = getDestionation(t.value() , t.nmspc());
			CheckIn<T>::copyFile(t.value(), var_destination + "." + std::to_string(current_version), t.nmspc(), CodeRepo<T>::root_path);
			
			//Enter it into DB after a successfull copy.
			//std::string new_key = x + "." + std::to_string(current_version + 1);
			//param_db[new_key] = param_db[old_key_last_Version];
			param_db[old_key_last_Version].payLoad().objstatus(0);

			param_keys.erase(param_keys.begin() + count);
			count++;
			//Remove if its there in anyone dependency map's (*Recursion*)
			param_keys = getKeysWhichCanNowBeClosed(param_keys, this->dependency_map, x);
			check_In_Keys_Which_can_be_closed(param_db,param_keys);
			if(param_keys.size() == 0)
				break;
		}
	}
}

template<typename T>
//This function creates the destination path
inline std::string CodeRepo<T>::getDestionation(const std::string& var_source , const std::string & var_namespace)
{
	size_t start_of_slash = var_source.rfind("/");
	std::string var_destinarion = this->root_path + "/" + var_namespace + "/" + var_source.substr(start_of_slash + 1, var_source.size());
	return var_destinarion;
}



template<typename T>
//This function calls the XMLMapPersistent saveMAptoXMl function which save Map to XML
inline void CodeRepo<T>::saveMaptoXML()
{
	XMLMapPersistent<T>::saveMaptoXML(this->dependency_map, CodeRepo<T>::persist_dependency_map_path_name_output);
}

template<typename T>
//This function calls the XMLMapPersistent readMAptoXMl function which read  XML adn write to Dependency Map
inline void CodeRepo<T>::readMapfromXML()
{
	XMLMapPersistent<T>::readMapfromXML(this->dependency_map, CodeRepo<T>::persist_dependency_map_path_name_input);
}

template<typename T>
//This function calss Browse by catoegory of browe class.
inline DbCore<T> CodeRepo<T>::BrowseByCategory(std::vector<std::string> & category_name)
{
	DbCore<T> temp_db;
	if (category_name.size() > 0)
	{
		for (auto y : category_name)
		{
			std::vector<std::string> keys;
			Browse<T>::browseByCategory(this->main_db, y, keys); //Querying DB on the basis of category.
			if (keys.size() > 0)
			{
				for (auto x : keys)
				{
					temp_db[x] = this->main_db[x];
				}
			}
		}
	}
	return temp_db; //return the DB to user who asked for all files files belong to a particualr category.
}

template<typename T>
//This functions opens the specific file in notepad.
inline void CodeRepo<T>::browseSpecificFile(const std::string &browse_key, int version)
{
	int specifiedVersion;
	int latestverion = -1;
	std::string browse_file_path;
	specifiedVersion = Version<T>::getLatestVersionOfChildren(this->main_db, browse_key, latestverion);

	//checking the version specified by user could be latest or specific version.
	if (version == 0)
	{
		browse_file_path = Browse<T>::browseBySpecificName(browse_key + "." + std::to_string(specifiedVersion), CodeRepo<T>::root_path, CodeRepo<T>::checkout_rootpath);
		Browse<T>::viewContentinNotepad(browse_file_path);
	}
	else if (version <= specifiedVersion)
	{
		browse_file_path = Browse<T>::browseBySpecificName(browse_key + "." + std::to_string(version), CodeRepo<T>::root_path, CodeRepo<T>::checkout_rootpath);
		Browse<T>::viewContentinNotepad(browse_file_path);
	}
	else
		std::cout << "You are trying to browse a file version which does not exist";
	
}




template<typename T>
//This function writes XML to DB to 
inline void CodeRepo<T>::writeDB()
{
	XMLMapPersistent<T>::writeDB(this->main_db, CodeRepo<T>::persist_xml_path_name_input);
}

template<typename T>
//This functin saves DB to XML
inline void CodeRepo<T>::saveDB()
{
	XMLMapPersistent<T>::saveDB(this->main_db, CodeRepo<T>::persist_xml_path_name_output);
}