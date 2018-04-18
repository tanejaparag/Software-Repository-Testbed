#ifndef PAYLOAD_H
#define PAYLOAD_H
///////////////////////////////////////////////////////////////////////
// PayLoad.h - application defined payload                           //
// ver 1.1                                                           //
// Author - Parag Taneja , CSE 687 , OOD 
// Source - Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018         //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides a single class, PayLoad:
*  - holds a payload string and vector of categories
*  - provides means to set and access those values
*  - provides methods used by Persist<PayLoad>:
*    - Sptr toXmlElement();
*    - static PayLoad fromXmlElement(Sptr elem);
*  - provides a show function to display PayLoad specific information
*  - PayLoad processing is very simple, so this package contains only
*    a header file, making it easy to use in other packages, e.g.,
*    just include the PayLoad.h header.
*
*  Required Files:
*  ---------------
*    PayLoad.h, PayLoad.cpp - application defined package
*    DbCore.h, DbCore.cpp
*
*  Maintenance History:
*  --------------------
*  ver 1.1 : 19 Feb 2018
*  - added inheritance from IPayLoad interface
*  Ver 1.0 : 10 Feb 2018
*  - first release
*
*/

#include <string>
#include <vector>
#include <iostream>
#include "../../NoSQLDB/Executive/NoSqlDb.h"
#include "IPayLoad.h"

///////////////////////////////////////////////////////////////////////
// PayLoad class provides:
// - a std::string value which, in Project #2, will hold a file path
// - a vector of string categories, which for Project #2, will be 
//   Repository categories
// - methods used by Persist<PayLoad>:
//   - Sptr toXmlElement();
//   - static PayLoad fromXmlElement(Sptr elem);
// - get setter method for object status and namespace fields.


namespace NoSqlDb
{
  class PayLoad : public IPayLoad<PayLoad>
  {
  public:

	  PayLoad() : object_status(status::open) {}
	
    PayLoad(const std::string& val) : value_(val), object_status(status::closed) {}
    static void identify(std::ostream& out = std::cout);
    PayLoad& operator=(const std::string& val)
    {
      value_ = val;
      return *this;
    }
    operator std::string() { return value_; }
	enum status
	{
		closed,
		open,
		closing
	};

    std::string value() const { return value_; }
    std::string& value() { return value_; }
    void value(const std::string& value) { value_ = value; }

	std::string nmspc() const { return nmspc_; }
	std::string& nmspc() { return nmspc_; }
	void nmspc(const std::string& param_nmspc) { nmspc_ = param_nmspc; }

	status objstatus() const { return object_status; }
	status& objstatus() { return object_status; }
	void objstatus(status param_status) { object_status = param_status; }
	void objstatus(int param_status) { object_status = static_cast<status>(param_status); }

    std::vector<std::string>& categories() { return categories_; }
    std::vector<std::string> categories() const { return categories_; }

    bool hasCategory(const std::string& cat)
    {
      return std::find(categories().begin(), categories().end(), cat) != categories().end();
    }

    Sptr toXmlElement();
    static PayLoad fromXmlElement(Sptr elem);

    static void showPayLoadHeaders(std::ostream& out = std::cout);
    static void showElementPayLoad(NoSqlDb::DbElement<PayLoad>& elem, std::ostream& out = std::cout);
    static void showDb(NoSqlDb::DbCore<PayLoad>& db, std::ostream& out = std::cout);
  private:
    std::string value_;
	std::string nmspc_;
    std::vector<std::string> categories_;
	status object_status;

  };

  //----< show file name >---------------------------------------------

  inline void PayLoad::identify(std::ostream& out)
  {
    out << "\n  \"" << __FILE__ << "\"";
  }
  //----< create XmlElement that represents PayLoad instance >---------
  /*
  * - Required by Persist<PayLoad>
  */
  inline Sptr PayLoad::toXmlElement()
  {
    Sptr sPtr = XmlProcessing::makeTaggedElement("payload");
    XmlProcessing::XmlDocument doc(makeDocElement(sPtr));
    Sptr sPtrVal = XmlProcessing::makeTaggedElement("value",value_);
    sPtr->addChild(sPtrVal);
	Sptr sPtrNmSpc = XmlProcessing::makeTaggedElement("namespace", nmspc_);
	sPtr->addChild(sPtrNmSpc);

	std::string temp_status;
	if (object_status == status::closed)
		temp_status = "closed";
	else if (object_status == status::open)
		temp_status = "open";
	else
		temp_status = "closing";

	Sptr sPtrObjectStatus = XmlProcessing::makeTaggedElement("Status", temp_status);
	sPtr->addChild(sPtrObjectStatus);
    Sptr sPtrCats = XmlProcessing::makeTaggedElement("categories");
    sPtr->addChild(sPtrCats);
    for (auto cat : categories_)
    {
      Sptr sPtrCat = XmlProcessing::makeTaggedElement("category", cat);
      sPtrCats->addChild(sPtrCat);
    }
    return sPtr;
  }
  //----< create PayLoad instance from XmlElement >--------------------
  /*
  * - Required by Persist<PayLoad>
  */
  inline PayLoad PayLoad::fromXmlElement(Sptr pElem)
  {
    PayLoad pl;
    for (auto pChild : pElem->children())
    {
      std::string tag = pChild->tag();
      std::string val = pChild->children()[0]->value();
      if (tag == "value")
      {
        pl.value(val);
      }
	  if (tag == "namespace")
	  {
		  pl.nmspc(val);
	  }
	  if (tag == "Status")
	  {
		  if (val == "closed")
			  pl.objstatus(status::closed);
		  else if (val == "open")
			  pl.objstatus(status::open);
		  else
			  pl.objstatus(status::closing);
	  }
      if (tag == "categories")
      {
        std::vector<Sptr> pCategories = pChild->children();
        for (auto pCat : pCategories)
        {
          pl.categories().push_back(pCat->children()[0]->value());
        }
      }
    }
    return pl;
  }
  /////////////////////////////////////////////////////////////////////
  // PayLoad display functions

  inline void PayLoad::showPayLoadHeaders(std::ostream& out)
  {
    out << "\n  ";
    out << std::setw(10) << std::left << "Name";
    out << std::setw(45) << std::left << "Payload Value";
	out << std::setw(25) << std::left << "PayloadStatus";
	out << std::setw(25) << std::left << "Categories";
	
    out << "\n  ";
    out << std::setw(10) << std::left << "--------";
    out << std::setw(40) << std::left << "--------------------------------------";
    out << std::setw(25) << std::left << "-----------------------";
	out << std::setw(25) << std::left << "-----------------------";
  }


  inline void PayLoad::showElementPayLoad(NoSqlDb::DbElement<PayLoad>& elem, std::ostream& out)
  {
    out << "\n  ";
    out << std::setw(10) << std::left << elem.name().substr(0, 8);
    out << std::setw(40) << std::left << elem.payLoad().value().substr(0, 38);
	out << std::setw(25) << std::left << elem.payLoad().objstatus();
    for (auto cat : elem.payLoad().categories())
    {
      out << cat << " ";
    }
	
  }

  inline void PayLoad::showDb(NoSqlDb::DbCore<PayLoad>& db, std::ostream& out)
  {
    showPayLoadHeaders(out);
    for (auto item : db)
    {
      NoSqlDb::DbElement<PayLoad> temp = item.second;
      PayLoad::showElementPayLoad(temp, out);
    }
  }
}
#endif
