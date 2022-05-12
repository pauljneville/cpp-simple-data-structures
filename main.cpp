#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <set>
#include <map>
#include <chrono>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include "utility.h"
#include "container.h"
#include "linkedlist.h"
#include "tree.h"
#include "stdlist.h"
#include "stdvector.h"
#include "stdmultiset.h"

#include "bpooptions.h"

using namespace std;

bool readLineFile(std::string fileName, Container& container);
bool tokenizeTextFile(std::string fileName, std::string wordCountFileName, Container& container);
bool writeFoundToFile(std::string fileName, Container& dictContainer, Container& docuContainer);
void timeAllStructures(std::string timingFileName, std::string dictFileName, std::string docuFileName, std::string outFileName, std::string wordCountFileName);
bool getDataStructure(std::string dataStructure, std::unique_ptr<Container>& dictContainer, std::unique_ptr<Container>& docuContainer);

/** Reads dictionary file into data structure
 * Reads and tokenizes text document file into data structure
 *   Writes to word count file
 * Writes to file the words found or word and closest edit distance matches
 */
int main(int argc, char* argv[])
{
	BPOOptions bpoOptions{};

	if ( !bpoOptions.checkCMDArgs(argc))
	{
		bpoOptions.printDesc();
		return 1;
	}

	if ( !bpoOptions.storeCommands(argc, argv))
	{
		std::cout << "error on bpo::store" << endl;
		return 1;
	}
	
	// read in and set the container to use and the name of files to open
	std::unique_ptr<Container> dictContainer = nullptr;
	std::unique_ptr<Container> docuContainer = nullptr;
	std::string dictFileName = "";
	std::string docuFileName = "";
	std::string outFileName = "";
	std::string wordCountFileName = "wordc";
	std::string timingFileName = "timings";
	bool testAll = false;
	
	bool missingArgs = false;

	// get datastructure to use
	if (bpoOptions.testAllSpecified())
		testAll = true;
	else if (bpoOptions.dataStructureSpecified())
	{
		if ( !bpoOptions.getDataStructure(dictContainer, docuContainer))
		{
			cout << "Unsupported datastructure" << endl;
			missingArgs = true;
		}
	}
	else
	{
		cout << "No datastructure specified" << endl;
		missingArgs = true;
	}	

	// get dictionary file name
	if (bpoOptions.dictionaryFileSpecified())
		bpoOptions.getDictionaryFileName(dictFileName);
	else
	{
		cout << "No dictionary specified" << endl;
		missingArgs = true;
	}
	
	// get text document file name
	if (bpoOptions.textDocFileSpecified())
		bpoOptions.getTextDocFileName(docuFileName);
	else
	{
		cout << "No text document file specified" << endl;
		missingArgs = true;
	}
	
	// get output file name
	if (bpoOptions.outputFileSpecified())
		bpoOptions.getOutputFileName(outFileName);
	else
	{
		cout << "No output file specified" << endl;
		missingArgs = true;
	}
	
	if (missingArgs)
	{
		bpoOptions.printDesc();
		return 1;
	}
	
	if (testAll)
	{
		timeAllStructures(timingFileName + ".csv", dictFileName, docuFileName, outFileName, wordCountFileName);
	}
	else
	{
		readLineFile(dictFileName, *dictContainer);
		tokenizeTextFile(docuFileName, outFileName + '_' + wordCountFileName + '_' + bpoOptions.getDSName() + ".csv", *docuContainer);
		writeFoundToFile(outFileName + '_' + bpoOptions.getDSName() + ".txt", *dictContainer, *docuContainer);
	}
	
	return 0;
}

/** Reads file, inserting each line into Container provided
 *
 * @param fileName, the file name to read from
 * @param container, the datastructure to store the lines read from fileName
 * @return true if successful, false if not
 */
bool readLineFile(std::string fileName, Container& container)
{
	string readLine;
	ifstream inFileStream;
	
	inFileStream.open(fileName);
	if (inFileStream.is_open())
	{
		while (getline(inFileStream, readLine))
		{
			boost::trim(readLine);
			container.insert(readLine);
		}
		inFileStream.close();
		cout << "> " << fileName << " read" << endl;
		return true;
	}
	return false;
}

/** Reads file, tokenizes each line into words, storing each word into Container provided
 * Counts words encountered, writing them to wordCountFileName file
 *
 * @param fileName, the file name to read from
 * @param wordCountFileName, the file name to write the cord counts to
 * @param container, the datastructure to store the lines read from fileName
 * @return true if successful, false if not
 */
bool tokenizeTextFile(std::string fileName, std::string wordCountFileName, Container& container)
{
	string readLine;
	ifstream ISTextDoc;
	std::map<std::string, int> wordCount;

	ISTextDoc.open(fileName);
	if (ISTextDoc.is_open())
	{
		while (std::getline(ISTextDoc, readLine))
		{
			boost::tokenizer<> tok(readLine);
			for (boost::tokenizer<>::iterator begin = tok.begin(); begin != tok.end(); ++ begin)
			{
				std::string inString = *begin;
				boost::algorithm::to_lower(inString);
				container.insert(inString);
				++wordCount[inString];
			}
		}
		
		ISTextDoc.close();
		cout << "> " << fileName << " read" << endl;
		
		ofstream OSWordCount;
		OSWordCount.open(wordCountFileName);
		if (OSWordCount.is_open())
		{
			for (const auto& pair : wordCount)
				OSWordCount << pair.first << "," << pair.second << endl;

			OSWordCount.close();
			cout << "> " << wordCountFileName << " created" << endl;
		}
		
		return true;
	}
	return false;
}

/** For each word stored in the docuContainer, dictContainer is searched for the words presence
 * If the word is found, the word is written to the file specified by fileName
 * If the word is not found, the edit distances of all dictContainer words are calculated in
 * comparison to the word not found, then all are written to the file specified by fileName
 *
 * @param fileName, the file name to write found/not found words + edit distance matches to
 * @param dictContainer, the datastructure holding the words from the dictionary calculate 
 *  edit distance against
 * @param docuContainer, the datastructure holding the words from the text document to compare
 * @return true if successful, false if not
 */
bool writeFoundToFile(std::string fileName, Container& dictContainer, Container& docuContainer)
{
	ofstream OSNotFound;
	
	OSNotFound.open(fileName);
	if (OSNotFound.is_open())
	{
		for (docuContainer.resetIter(); docuContainer.validIter(); docuContainer.incrIter())
		{
			if (dictContainer.search(docuContainer.getIterData()) == false)
			{
				int minEditDist = 0;
				std::vector<string> minEDStrings;
				// set minEditDist of first string in the dictionary
				dictContainer.resetIter();
				if (dictContainer.validIter())
				{
					minEditDist = editDistance(docuContainer.getIterData(), dictContainer.getIterData());
					minEDStrings.push_back(dictContainer.getIterData());
				}
				dictContainer.incrIter();
				
				// iterate through dictContainer, storing minEditDist
				for (; dictContainer.validIter(); dictContainer.incrIter())
				{
					int curEditDist = editDistance(docuContainer.getIterData(), dictContainer.getIterData());
					if (curEditDist < minEditDist)
					{
						minEDStrings.clear();
						minEditDist = curEditDist;
						minEDStrings.push_back(dictContainer.getIterData());
					}
					else if (curEditDist == minEditDist)
					{
						minEDStrings.push_back(dictContainer.getIterData());
					}
				}
				
				OSNotFound << "Not Found: " << docuContainer.getIterData() << ", " << minEditDist << ". Closest Matches: " << minEDStrings.back();
				minEDStrings.pop_back();
				while (minEDStrings.empty() == false)
				{
					OSNotFound << ", " << minEDStrings.back();
					minEDStrings.pop_back();
				}
				OSNotFound << endl;
			}
			else
			{
				OSNotFound << "Yes Found: " << docuContainer.getIterData() << endl;
			}
		}
		
		OSNotFound.close();
		cout << "> " << fileName << " created" << endl;
		return true;
	}
	return false;
	
}

void timeAllStructures(std::string timingFileName, std::string dictFileName, std::string docuFileName, std::string outFileName, std::string wordCountFileName)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
	std::unique_ptr<Container> dictContainer = nullptr;
	std::unique_ptr<Container> docuContainer = nullptr;
	std::vector<std::string> dataStructureNames = { "list", "vector", "set", "custom_list", "custom_tree" };
			
	ofstream OSTimingStream;
	OSTimingStream.open(timingFileName);
	if (OSTimingStream.is_open())
	{
		OSTimingStream << "data struct,read time,token time,write time" << endl;
		for (auto& dsname : dataStructureNames)
		{
			OSTimingStream << dsname;
			if (getDataStructure(dsname, dictContainer, docuContainer))
			{
				startTime = std::chrono::high_resolution_clock::now();
				readLineFile(dictFileName, *dictContainer);
				endTime = std::chrono::high_resolution_clock::now();
				OSTimingStream << "," << std::chrono::duration<double, std::milli>(endTime-startTime).count();
				
				startTime = std::chrono::high_resolution_clock::now();
				tokenizeTextFile(docuFileName, outFileName + '_' + wordCountFileName + '_' + dsname + ".csv", *docuContainer);
				endTime = std::chrono::high_resolution_clock::now();
				OSTimingStream << "," << std::chrono::duration<double, std::milli>(endTime-startTime).count();
				
				startTime = std::chrono::high_resolution_clock::now();
				writeFoundToFile(outFileName + '_' + dsname + ".txt", *dictContainer, *docuContainer);
				endTime = std::chrono::high_resolution_clock::now();
				OSTimingStream << "," << std::chrono::duration<double, std::milli>(endTime-startTime).count();
				OSTimingStream << endl;
			}
			else
				cout << "Data structure name not found: " << dsname << endl;
		}
		OSTimingStream.close();
		cout << "> " << timingFileName << " created" << endl;
	}
}

bool getDataStructure(std::string dataStructure, std::unique_ptr<Container>& dictContainer, std::unique_ptr<Container>& docuContainer)
{
	if (dataStructure.compare("list") == 0)
	{
		cout << "list created" << endl;
		dictContainer = std::make_unique<StdList>();
		docuContainer = std::make_unique<StdList>();
	}
	else if (dataStructure.compare("vector") == 0)
	{
		cout << "vector created" << endl;
		dictContainer = std::make_unique<StdVector>();
		docuContainer = std::make_unique<StdVector>();
	}
	else if (dataStructure.compare("set") == 0)
	{
		cout << "set created" << endl;
		dictContainer = std::make_unique<StdMultiset>();
		docuContainer = std::make_unique<StdMultiset>();
	}
	else if (dataStructure.compare("custom_list") == 0)
	{
		cout << "custom_list created" << endl;
		dictContainer = std::make_unique<LinkedList>();
		docuContainer = std::make_unique<LinkedList>();
	}
	else if (dataStructure.compare("custom_tree") == 0)
	{
		cout << "custom_tree created" << endl;
		dictContainer = std::make_unique<Tree>();
		docuContainer = std::make_unique<Tree>();
	}
	else 
		return false;
	
	return true;
}




















