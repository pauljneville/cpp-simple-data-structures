#include "bpooptions.h"
#include "container.h"
#include "linkedlist.h"
#include "tree.h"
#include "stdlist.h"
#include "stdvector.h"
#include "stdmultiset.h"

/** Stores command line arguments passed into main
 *
 * @param argc, number of arguments inc. program name entered in cmd line
 * @param argv, array of strings arguments entered in cmd line
 * @return true if successful, false bpo::error thrown
 */
bool BPOOptions::storeCommands(int argc, char* argv[])
{
	try{
		bpo::store(bpo::command_line_parser(argc, argv).options(desc).run(), vm);
		notify(vm);
	}
	catch (const bpo::error& ex)
	{
		//cout << "error on bpo::store" << endl;
		return false;
	}
	return true;
}

/** Checks if datastructure argument specifies test all
 *
 * @return true if datastructure arg. is "all"
 */
bool BPOOptions::testAllSpecified() const
{
	if (vm.count("datastructure"))
	{
		vector<string> dst = vm["datastructure"].as<vector<string>>();
		//std::cout << "-s " << dst[0] << endl;
		return dst[0].compare("all") == 0;
	}
	return false;
}

/** Assigns correct data structure to Containers used throughout the program
 *
 * @param dictContainer, the dictionary Container
 * @param docuContainer, the document file Container
 * @return true if datastructure arg. is supported
 */
bool BPOOptions::getDataStructure(std::unique_ptr<Container>& dictContainer, std::unique_ptr<Container>& docuContainer) const
{
	// get datastructure to use
	if (vm.count("datastructure"))
	{
		vector<string> dst = vm["datastructure"].as<vector<string>>();
		//std::cout << "-s " << dst[0] << endl;
		if (dst[0].compare("list") == 0)
		{
			dictContainer = std::make_unique<StdList>();
			docuContainer = std::make_unique<StdList>();
		}
		else if (dst[0].compare("vector") == 0)
		{
			dictContainer = std::make_unique<StdVector>();
			docuContainer = std::make_unique<StdVector>();
			
		}
		else if (dst[0].compare("set") == 0)
		{
			dictContainer = std::make_unique<StdMultiset>();
			docuContainer = std::make_unique<StdMultiset>();
			
		}
		else if (dst[0].compare("custom_list") == 0)
		{
			dictContainer = std::make_unique<LinkedList>();
			docuContainer = std::make_unique<LinkedList>();
		}
		else if (dst[0].compare("custom_tree") == 0)
		{
			dictContainer = std::make_unique<Tree>();
			docuContainer = std::make_unique<Tree>();
		}
		else
		{
			return false;
			//cout << "Unsupported datastructure: " << dst[0] << endl;
			//cout << desc << endl;
			//missingArgs = true;
		}
	}
	else 
		return false;
	
	return true;
}

std::string BPOOptions::getDSName() const
{
	vector<string> dst = vm["datastructure"].as<vector<string>>();
	return dst[0];
}

void BPOOptions::getDictionaryFileName(std::string& dictFileName) const
{
	vector<string> dic = vm["dictionary"].as<vector<string>>();
	dictFileName = dic[0];
}

void BPOOptions::getTextDocFileName(std::string& docuFileName) const
{
	vector<string> doc = vm["textfile"].as<vector<string>>();
	docuFileName = doc[0];
}

void BPOOptions::getOutputFileName(std::string& outFileName) const
{
	vector<string> out = vm["outputfile"].as<vector<string>>();
	outFileName = out[0];
}

