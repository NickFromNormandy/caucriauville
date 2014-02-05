#include "NickThread.hh"

class FileParser : public NickThread
{
    typedef  std::vector<std::string> myArray_t;
    typedef  std::unordered_map <std::string, int> mymap; 
    typedef  std::unordered_map <int, myArray_t> myMapOccurenceToWord_t;

public:
    
    FileParser() {}   
    void ReadAndParseTheFile(void);
    void PrintMapWordToOccurence(void);
    void PrintMapOccurenceToWords(void);
    void tokenize(const std::string& str, myArray_t& tokens);
    void CreateOccurenceToWord(void);
    void CreateThreads(void);

private:

    static const int threadCounter =10;
    mymap  MapWordToOccurence;
    mymap::const_iterator myMapIter;
    myMapOccurenceToWord_t MapOccurenceToWord;
    NickThread myThread[threadCounter];   

};

//const int FileParser::threadCounter = 10;

void FileParser::CreateThreads(void)
{
    
    unsigned int *pIndexThread;
    Counter myCounter(0);

    for(int i =0;i<threadCounter;i++)
    {
        myThread[i].SetCounter(&myCounter);
        myThread[i].Start(i);
    }

    for(int i =0;i<threadCounter;i++)
    {
        pthread_t mythread;
        pthread_join(myThread[i].GetID(), (void **) &pIndexThread);
        std::cout << "pThread Index: " << *pIndexThread << "\n";
    }

    std::cout << "This is done\n";

}

void FileParser::CreateOccurenceToWord(void)
{
    for(mymap::const_iterator myIter = MapWordToOccurence.begin(); myIter != MapWordToOccurence.end(); myIter++)
    {    
        std::cout << "value:" << myIter->first << ":" << myIter->second << ":\n";
        myMapOccurenceToWord_t::const_iterator myOccurenceIter = MapOccurenceToWord.find(myIter->second);
        MapOccurenceToWord[myIter->second].push_back(myIter->first);
    }
}

void FileParser::PrintMapWordToOccurence(void)
{
    std::cout << "Print Map: Word To Occurence---------------------------------------------------------\n";
    
    for(mymap::const_iterator myIter = MapWordToOccurence.begin();myIter != MapWordToOccurence.end(); myIter++)
    {    
        std::cout << "value:" << myIter->first << ":" << myIter->second << ":\n";
     
    }
    std::cout << "Map Word To Occurence has been printed----------------------------------------------\n";
}

void FileParser::PrintMapOccurenceToWords(void)
{
    for(myMapOccurenceToWord_t::const_iterator myIter = MapOccurenceToWord.begin();myIter != MapOccurenceToWord.end(); myIter++)
    {
        std::cout << myIter->first << "->";
        
        for(std::vector<std::string>::const_iterator it =  myIter->second.begin();it!= myIter->second.end();++it)
        {
            std::cout << *it << ",";
        }
        std::cout << "\n";
    }
}

void FileParser::tokenize(const std::string& str, myArray_t& tokens)
{
    std::string::const_iterator myIterator = str.begin();
    std::string::const_iterator begin_pos = myIterator;
    bool inAword = false;

    while( myIterator!=str.end())
    {
        std::string::value_type c=*myIterator;

        if  ((c >= 'A' && c <= 'Z') || (c >= 'a' & c <= 'z'))
        {
            if (inAword == false) {begin_pos = myIterator;inAword = true;}
        }
        else
        {                 
            if (inAword && ( myIterator-begin_pos)>0)
            {                
                tokens.push_back(std::string(begin_pos, myIterator));
                inAword = false;
            }
        }       
        myIterator++;
    }

    if (inAword && ( myIterator-begin_pos)>0)
    {                
        tokens.push_back(std::string(begin_pos, myIterator));
        inAword = false;
    }
};


void FileParser::ReadAndParseTheFile(void)
{

    std::ifstream myFile;    

    myFile.open("toto.txt");

    if (myFile.is_open() == false)
    {
        std::cerr << "The file toto.txt does not exist\n";
        exit(-1);
    }
  
    for(std::string myString;std::getline(myFile, myString); )
    {
        myArray_t myVectorOfTokens;
        tokenize(myString, myVectorOfTokens);
     
        for(std::vector<std::string>::iterator it =  myVectorOfTokens.begin();it!= myVectorOfTokens.end();++it)
        {
            MapWordToOccurence.find(*it);
           
            if (myMapIter == MapWordToOccurence.end())
            {
                MapWordToOccurence[*it] = 1;
            }
            else
            {
                MapWordToOccurence[*it]+=1;
            }
        }
    }

    CreateOccurenceToWord();
    PrintMapWordToOccurence();
    PrintMapOccurenceToWords();
    exit(-1);
    
}

