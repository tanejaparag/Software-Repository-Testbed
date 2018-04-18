#include "XmlMapPersistent.h"
#include "../NoSQLDB/PayLoad/PayLoad.h"

#ifdef TEST_XMLMAP
int main()
{
	std::map<std::string, std::vector<std::string>> temp_map;
	temp_map["Key1"].push_back("Dep1");
	temp_map["Key1"].push_back("Dep2");
	temp_map["Key2"].push_back("Dep3");
	temp_map["Key2"].push_back("Dep4");
	std::string temp_path = "../TEST_XMLMAP.xml";
	XMLMapPersistent<PayLoad>::saveMaptoXML(temp_map, temp_path);
	std::cout << "XML created with name TEST_XMLMAP";
	std::getchar();
	return 0;
}
#endif