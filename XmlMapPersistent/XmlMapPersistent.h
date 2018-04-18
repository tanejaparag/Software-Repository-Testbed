#pragma once
////////////////////////////////////////////////////////////////////////////
// XmlMapPersistent.h - Has design of class XmlMapPersistent to read -write Depedency Map and DB to XML and vice versa//
// ver 1.0                                                                //
// Language:    C++, Visual Studio 2017                                  //
// Parag Taneja, CSE687 - Object Oriented Design, Spring 2018          //
///////////////////////////////////////////////////////////////////////////


/*
Package Operations:
* -------------------
* This package provides 1 class:
*
- XmlMapPersistent : Has design of class XmlMapPersistent to read -write Depedency Map and DB to XML and vice versa.

Public Functions :
static void saveDB(DbCore<T>& db,std::string& path) - save DB to XML
static void writeDB(DbCore<T>& db , std::string& path) - writes XML to DB
static void saveMaptoXML(std::map<std::string, std::vector<std::string>>& map,std::string& path) - saves Map to XML
static void readMapfromXML(std::map<std::string, std::vector<std::string>>& map,std::string& path) - Read XML and write to Map.
* Required Files:
* ---------------
* Executive.h, XmlDocument.h
* XmlParser.h
*
*
* Maintenance History:
* --------------------
* ver 1.0 : 2nd Mar 2018

*/




#include <iostream>
#include<string>
#include <map>
#include <vector>

#include "../NoSQLDB/Executive/Executive.h"
#include "../NoSQLDB/XmlDocument/XmlDocument/XmlDocument.h"
#include "../NoSQLDB/XmlDocument/XmlParser/XmlParser.h"

using namespace NoSqlDb;

template<typename T>
class XMLMapPersistent
{
	public:
		static void saveDB(DbCore<T>& db,std::string& path);
		static void writeDB(DbCore<T>& db , std::string& path);
		static void saveMaptoXML(std::map<std::string, std::vector<std::string>>& map,std::string& path);
		static void readMapfromXML(std::map<std::string, std::vector<std::string>>& map,std::string& path);
};

template<typename T>
//save DB to XML
inline void XMLMapPersistent<T>::saveDB(DbCore<T>& db,std::string& path)
{
	Persist<T> persist(db);
	Xml xml = persist.toXml();
	std::string xml_head = "< ? xml version = \"1.0\" encoding = \"utf-8\" ? >\n";
	xml_head = xml_head + xml; // added header to XML
	std::string filename = path;
	std::ofstream outfile(filename); // writing into a file 
	outfile << xml_head << std::endl;
	outfile.close();
	//std::cout << "Please check file at ../DB.xml whihc is inside Project 2";
}

template<typename T>
//reads XML adn write into DB
inline void XMLMapPersistent<T>::writeDB(DbCore<T>& db,std::string& path)
{
	std::string filename = path;
	Persist<PayLoad> persist(db);

	std::ifstream ifs(filename);
	std::string xml((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())); //reading whole File.
	persist.fromXml(xml); //using persist class
}

template<typename T>
//saving Map to XML.
inline void XMLMapPersistent<T>::saveMaptoXML(std::map<std::string, std::vector<std::string>>& map,std::string& path)
{
	using sptr = std::shared_ptr<AbstractXmlElement>;
	sptr root = makeTaggedElement("Dependency");
	for (auto x : map)
	{
		//creating tag element and making children of each other.
		sptr row = makeTaggedElement("row");
		root->addChild(row);
		sptr key = makeTaggedElement("key", x.first);
		row->addChild(key);
		sptr vec = makeTaggedElement("VectorValues");
		row->addChild(vec);
		for (auto y : x.second)
		{
			sptr vecvalue = makeTaggedElement("Value", y);
			vec->addChild(vecvalue);
		}
	}
	sptr docEl = makeDocElement(root);
	std::string xml_head = "< ? xml version = \"1.0\" encoding = \"utf-8\" ? >\n";
	xml_head = xml_head + docEl->toString();
	std::string filename = path;
	std::ofstream outfile(filename);
	outfile << xml_head << std::endl;
	outfile.close();
	//std::cout << "Please check file at ../Dependency_Map.xml which is inside Project 2";
}

template<typename T>
//reading XML and writing to Dependency Map.
inline void XMLMapPersistent<T>::readMapfromXML(std::map<std::string, std::vector<std::string>>& map,std::string& path)
{

	XmlParser parser(path);
	XmlDocument* pDoc = parser.buildDocument();
	using sptr = std::shared_ptr<AbstractXmlElement>;

	//Select the root element and return all the childrens below root
	std::vector<sptr> vec = pDoc->elements("Dependency").select();
	for (auto x : vec) {
		std::string key;
		for (auto y : x->children()) {
			if (y->tag() == "key")
			{
				key = y->children()[0]->value();
			}
			else
			{
				for (auto z : y->children())
				{
					map[key].push_back(z->children()[0]->value());
				}
			}
		}
	}
}