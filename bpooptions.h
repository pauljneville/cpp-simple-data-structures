#ifndef _BPO_OPTIONS_
#define _BPO_OPTIONS_

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "container.h"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace bpo = boost::program_options;

/** Encapsulated boost::program_options for easy use
 */
class BPOOptions
{
	const int cmd_argc_count = 9;
	
	bpo::options_description desc;
	bpo::variables_map vm;
public:
	BPOOptions() : desc("Enter in terminal / commandline:\n"\
						"./program_name -s datastructure -d dictionary"\
						" -t textfile -o outputfile\n")
	{
		desc.add_options()
			("datastructure,s", bpo::value<std::vector<std::string>>(), "all,"\
			 " list, vector, set, custom_list, or custom_tree")
			("dictionary,d", bpo::value<std::vector<std::string>>(), "fileName.txt\n"\
			 "The dictionary file to read in")
			("textfile,t", bpo::value<std::vector<std::string>>(), "fileName.txt\n"\
			 "The word document file to compare with dictionary words")
			("outputfile,o", bpo::value<std::vector<std::string>>(), "fileName.txt\n"\
			 "The output file for words found or,"\
			 " if not found, the word, followed by their closest"\
			 " edit-distance matches");
	}
	
	void printDesc() { std::cout << desc << std::endl; }
	
	bool checkCMDArgs(int argc) { return argc == cmd_argc_count; }
	bool storeCommands(int argc, char* argv[]);
	
	bool testAllSpecified() const;
	bool dataStructureSpecified() const { return vm.count("datastructure"); }
	bool dictionaryFileSpecified() const { return vm.count("dictionary"); }
	bool textDocFileSpecified() const { return vm.count("textfile"); }
	bool outputFileSpecified() const { return vm.count("outputfile"); }
	
	bool getDataStructure(std::unique_ptr<Container>& dictContainer, 
						  std::unique_ptr<Container>& docuContainer) const;
	std::string getDSName() const;
	void getDictionaryFileName(std::string& dictFileName) const;
	void getTextDocFileName(std::string& docuFileName) const;
	void getOutputFileName(std::string& outFileName) const;
};

#endif




















