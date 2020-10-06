
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
# include <fstream> 		// open, is_open, close, ignore

# define NOT !
# define AND &&
# define OR ||


using namespace std;


typedef struct pageT {
	char pageNum;
	string pageContent;
	bool hasPageFault;
} pageType ;


typedef struct infoT {
	int count;
	int timeStamp;
} infoType ;


bool Compare_LFU( infoType & info1, infoType & info2 );
bool Compare_MFU( infoType & info1, infoType & info2 );
bool Compare_Count( infoType & info1, infoType & info2 );


bool Compare_LFU( infoType & info1, infoType & info2 ){

	if ( info1.count == info2.count ) {
		return info1.timeStamp < info2.timeStamp;
	} // if
	else {
		return info1.count < info2.count;
	} // else
	
} // Compare_LFU()

bool Compare_MFU( infoType & info1, infoType & info2 ){

	if ( info1.count == info2.count ) {
		return info1.timeStamp > info2.timeStamp;
	} // if
	else {
		return info1.count < info2.count;
	} // else
	
} // Compare_MFU()

bool Compare_Count( infoType & info1, infoType & info2 ){

	return info1.count < info2.count;

} // Compare_Count()




class PageReplacement {

public:
	
	void Init();
	void DoMethod();
	bool ReadFile();
	void OutputFile();
	
private:
	string fileName;
	int pageFrame;
	string inputPage;

	vector<pageType> FIFO_result;
	vector<pageType> LRU_result;
	vector<pageType> ARB_result;
	vector<pageType> SC_result;
	vector<pageType> LFU_result;
	vector<pageType> MFU_result;

	void FIFO();
	void LRU();
	void ARB();
	void SC();
	void LFU();
	void MFU();
	void LFU_FIFO();
	void MFU_LIFO();
	void Sort_timeStamp( string & pageContent, vector<infoType> & infoList ) ;
	
} ; // class PageReplacement


void PageReplacement::Init() {
	fileName = "";
	pageFrame = 0;
	inputPage = "";
	FIFO_result.clear();
	LRU_result.clear();
	ARB_result.clear();
	SC_result.clear();
	LFU_result.clear();
	MFU_result.clear();
} // Scheduling::Init()

bool PageReplacement::ReadFile() {
	
	fstream fp;
	
	char ch = '\0';
	string temp = ""; 
	fileName = ""; 
	
	
	while ( 1 ) {
		cout << "\nPlease enter file name(quit : 0) : ";
		cin >> fileName;
		if ( fileName == "0" )  return false;
		fp.open((fileName + ".txt").c_str(), fstream::in);
		if ( fp.is_open() ) {
			fp >> pageFrame >> inputPage;
			fp.close();
			break;
		} // if
		else {
			cout << "Please enter file name again !\n";
		} // else
	} // while
	
	return true;
	
} // Scheduling::ReadFile()

void PageReplacement::OutputFile() {

	fstream fp;
	int pageFault = 0;
	fp.open((fileName + "_output.txt").c_str(), fstream::out);
	
	if ( !fp.is_open() ) return;
	
	fp << "--------------FIFO-----------------------\n" ;
	
	pageFault = 0;
	for ( int i = 0 ; i < FIFO_result.size() ; i++ ) {
		fp << FIFO_result[i].pageNum << "\t"; 
		fp << FIFO_result[i].pageContent << "\t"; 
		
		if ( FIFO_result[i].hasPageFault ) {
		  fp << "F";
		  pageFault++;
	    } // if
		
		fp << "\n";
	} // for
	
	fp << "Page Fault = " << pageFault << "  " << "Page Replaces = " << pageFault-pageFrame << "  " <<  
	      "Page Frames = " << pageFrame << "\n\n";
	      
	fp << "--------------LRU--------------------------\n" ;
	
	pageFault = 0;
	for ( int i = 0; i < LRU_result.size() ; i++ ) {
		fp << LRU_result[i].pageNum << "\t"; 
		fp << LRU_result[i].pageContent << "\t"; 
		
		if ( LRU_result[i].hasPageFault ) {
		  fp << "F";
		  pageFault++;
	    } // if
		
		fp << "\n";
	} // for
	
	fp << "Page Fault = " << pageFault << "  " << "Page Replaces = " << pageFault-pageFrame << "  " <<  
	      "Page Frames = " << pageFrame << "\n\n";
	      
	      
	fp << "--------------Additional Reference Bits-------------------\n" ;
	
	pageFault = 0;
	for ( int i = 0 ; i < ARB_result.size() ; i++ ) {
		fp << ARB_result[i].pageNum << "\t"; 
		fp << ARB_result[i].pageContent << "\t"; 
		
		if ( ARB_result[i].hasPageFault ) {
		  fp << "F";
		  pageFault++;
	    } // if
		
		fp << "\n";
	} // for
	
	fp << "Page Fault = " << pageFault << "  " << "Page Replaces = " << pageFault-pageFrame << "  " <<  
	      "Page Frames = " << pageFrame << "\n\n";
		  
		  
	fp << "--------------Second chance Page-------------------------\n" ;
	pageFault = 0;
	for ( int i = 0 ; i < SC_result.size() ; i++ ) {
		fp << SC_result[i].pageNum << "\t"; 
		fp << SC_result[i].pageContent << "\t"; 
		
		if ( SC_result[i].hasPageFault ) {
		  fp << "F";
		  pageFault++;
	    } // if
		
		fp << "\n";
	} // for
	
	fp << "Page Fault = " << pageFault << "  " << "Page Replaces = " << pageFault-pageFrame << "  " <<  
	      "Page Frames = " << pageFrame << "\n\n";
	
	
	fp << "--------------Least Frequently Used Page Replacement --------------------\n" ;	  
	
	pageFault = 0;
	for ( int i = 0 ; i < LFU_result.size() ; i++ ) {
		fp << LFU_result[i].pageNum << "\t"; 
		fp << LFU_result[i].pageContent << "\t"; 
		
		if ( LFU_result[i].hasPageFault ) {
		  fp << "F";
		  pageFault++;
	    } // if
		
		fp << "\n";
	} // for
	
	fp << "Page Fault = " << pageFault << "  " << "Page Replaces = " << pageFault-pageFrame << "  " <<  
	      "Page Frames = " << pageFrame << "\n\n";
	
	
	fp << "--------------Most Frequently Used Page Replacement ------------------------\n" ;
	
	pageFault = 0;
	for ( int i = 0 ; i < MFU_result.size() ; i++ ) {
		fp << MFU_result[i].pageNum << "\t"; 
		fp << MFU_result[i].pageContent << "\t"; 
		
		if ( MFU_result[i].hasPageFault ) {
		  fp << "F";
		  pageFault++;
	    } // if
		
		fp << "\n";
	} // for
	
	fp << "Page Fault = " << pageFault << "  " << "Page Replaces = " << pageFault-pageFrame << "  " <<  
	      "Page Frames = " << pageFrame << "\n\n";      
	
	cout << "Successfully write result to " <<  fileName  <<  "_output.txt\n";
	
	fp.close();

} // Scheduling::OutputFile()


void PageReplacement::DoMethod() {
	
	FIFO();
	LRU();
	ARB();
	SC();
	//LFU();
	//MFU();
	LFU_FIFO();
	MFU_LIFO();
	
} // Scheduling::DoMethod()

void PageReplacement::FIFO() {
    
    pageType curPage;
    string pageContent = "";

	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace
			pageContent.pop_back();  // ��̫�@�ӧR�� 
			pageContent = curPage.pageNum + pageContent;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		pageContent = curPage.pageNum + pageContent;
	  	} // else
	  	
	  } // if
	  
	  curPage.pageContent = pageContent;
	  
	  FIFO_result.push_back( curPage );
	} // for
	
} // PageReplacement::FIFO()

void PageReplacement::LRU() {
	
    pageType curPage;
    string pageContent = "";
    int loc = 0;
    
	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace
			pageContent.pop_back();  // ��̫�@�ӧR�� 
			pageContent = curPage.pageNum + pageContent;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		pageContent = curPage.pageNum + pageContent;
	  	} // else
	  	
	  } // if
	  else {  // �ثepage��curNum
	  	 loc = pageContent.find( curPage.pageNum );
	  	 pageContent.erase(pageContent.begin()+loc);
	  	 pageContent = curPage.pageNum + pageContent;
	  } // else
	  
	  curPage.pageContent = pageContent;
	  LRU_result.push_back( curPage );
	} // for
	
	
} // PageReplacement::LRU()
	
void PageReplacement::ARB() {
	pageType curPage;
    string pageContent = "";
    int loc = 0;

    int replace_index = 0;
    vector<string> reg;
    
    
	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace

			replace_index = distance( reg.begin(), min_element( reg.rbegin(), reg.rend() ).base() - 1 );
			// �]��max_element�^�ǲĤ@�ӳ̤j������(�]�t�۵������p)
			// �ҥH�ΤϦV���N��
			// ��base��^���V���N
			// �ഫ���̷|�t1, �ҥH�n��1 
			
			reg.erase( reg.begin() + replace_index );
			pageContent.erase( pageContent.begin() + replace_index );
			reg.insert( reg.begin(), "00000000" );
			pageContent = curPage.pageNum + pageContent;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		reg.insert( reg.begin(), "00000000" );
	  		pageContent = curPage.pageNum + pageContent;
	  	} // else
	  	
	  } // if

	  loc = pageContent.find( curPage.pageNum );
	  
	  for ( int k = 0 ; k < reg.size() ; k++ ) {
	  	reg[k].erase( reg[k].begin()+reg[k].size()-1 );
	  	if ( k == loc ) {
	  		reg[k].insert( reg[k].begin(), '1' );
	  	} // if
	  	else {
	  		reg[k].insert( reg[k].begin(), '0' );
	  	} // else
	  } // for
	  
	  
	  curPage.pageContent = pageContent;
	  ARB_result.push_back( curPage );
	} // for

} // PageReplacement::ARB()

void PageReplacement::SC() {

	pageType curPage;
    string pageContent = "";
    int loc = 0;
    int replace_index = 0;
    bool isFindReplace = false;
    vector<infoType> infoList;
    
    infoType info;
    
	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  isFindReplace = false;
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace
	  		
	  		
	  		// �Υ��i���X��������� 
	  		for ( int k = infoList.size()-1 ; k >= 0 AND NOT isFindReplace ; k-- ) {
				if ( infoList[k].count == 0 ) {
					replace_index = k;
					isFindReplace = true;
				} // if
				else {  
				    // �p�G���1, �N���L�ĤG�����| 
				    // �]��0�åB��s�ɶ� 
					infoList[k].count = 0;
					infoList[k].timeStamp = i;
				} // else
			} // for
			

			
			if ( NOT isFindReplace ) {
				replace_index = infoList.size()-1;
			} // if
			
			
			info.count = 1;
			info.timeStamp = i;
			
			infoList.erase( infoList.begin() + replace_index );
			pageContent.erase( pageContent.begin() + replace_index );
			Sort_timeStamp( pageContent, infoList ) ;  // �b�s���i�h���e, ���̷Ӯɶ��Ƨ�
			// �]���i�঳�ɶ���s�����p 
			infoList.insert( infoList.begin(), info );
			pageContent = curPage.pageNum + pageContent;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		info.count = 1;
			info.timeStamp = i;
			
	  		infoList.insert( infoList.begin(), info );
	  		pageContent = curPage.pageNum + pageContent;
	  	} // else
	  	
	  } // if
	  else {  // �ثepage��curNum
	    // �Qreference�� 
		loc = pageContent.find( curPage.pageNum );
		if ( infoList[loc].count == 0 ) { 
		  infoList[loc].count = 1;
	    } // if
	  } // else
	  
	  
	  curPage.pageContent = pageContent;
	  SC_result.push_back( curPage );
	} // for
	
} // PageReplacement::SC()

void PageReplacement::LFU() {

	pageType curPage;
    string pageContent = "";
    int loc = 0;

    int min_index = 0;
    vector<infoType> infoList;
    infoType info;
    
	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace
	  		
			min_index = distance( begin(infoList), min_element( infoList.rbegin(), infoList.rend(), Compare_LFU ).base() - 1 );
			// �]��max_element�^�ǲĤ@�ӳ̤j������(�]�t�۵������p)
			// �ҥH�ΤϦV���N��
			// ��base��^���V���N
			// �ഫ���̷|�t1, �ҥH�n��1 
			
			info.count = 1;
			info.timeStamp = i;

			infoList.erase( infoList.begin() + min_index );
			pageContent.erase( pageContent.begin() + min_index );
			infoList.insert( infoList.begin(), info );
			pageContent = curPage.pageNum + pageContent;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		info.count = 1;
			info.timeStamp = i;
	  		infoList.insert( infoList.begin(), info );
	  		pageContent = curPage.pageNum + pageContent;
	  	} // else
	  	
	  } // if
	  else {  // �ثepage��curNum
	  	 loc = pageContent.find( curPage.pageNum );
	  	 infoList[loc].count++;
	  	 infoList[loc].timeStamp = i;
	  } // else
	  
	  
	  curPage.pageContent = pageContent;
	  LFU_result.push_back( curPage );
	} // for
	
} // PageReplacement::LFU()

void PageReplacement::MFU() {

	pageType curPage;
    string pageContent = "";
    int loc = 0;

    int max_index = 0;
    vector<infoType> infoList;
    infoType info;
    
	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace
	  		
			max_index = distance( begin(infoList), max_element( infoList.rbegin(), infoList.rend(), Compare_MFU ).base() - 1 );
			// �]��max_element�^�ǲĤ@�ӳ̤j������(�]�t�۵������p)
			// �ҥH�ΤϦV���N��
			// ��base��^���V���N
			// �ഫ���̷|�t1, �ҥH�n��1 
			
			info.count = 1;
			info.timeStamp = i;

			infoList.erase( infoList.begin() + max_index );
			pageContent.erase( pageContent.begin() + max_index );
			infoList.insert( infoList.begin(), info );
			pageContent = curPage.pageNum + pageContent;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		info.count = 1;
			info.timeStamp = i;
	  		infoList.insert( infoList.begin(), info );
	  		pageContent = curPage.pageNum + pageContent;
	  	} // else
	  	
	  } // if
	  else {  // �ثepage��curNum
	  	 loc = pageContent.find( curPage.pageNum );
	  	 infoList[loc].count++;
	  	 infoList[loc].timeStamp = i;
	  } // else
	  
	  
	  curPage.pageContent = pageContent;
	  MFU_result.push_back( curPage );
	} // for
	
} // PageReplacement::MFU()


void PageReplacement::LFU_FIFO() {

	pageType curPage;
    string pageContent = "";
    int loc = 0;

    int min_index = 0;
    vector<infoType> infoList;
    infoType info;
    
	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace
	  		
			min_index = distance( begin(infoList), min_element( infoList.rbegin(), infoList.rend(), Compare_Count ).base() - 1 );
			// �]��max_element�^�ǲĤ@�ӳ̤j������(�]�t�۵������p)
			// �ҥH�ΤϦV���N��
			// ��base��^���V���N
			// �ഫ���̷|�t1, �ҥH�n��1 
			
			info.count = 1;
			info.timeStamp = i;

			infoList.erase( infoList.begin() + min_index );
			pageContent.erase( pageContent.begin() + min_index );
			infoList.insert( infoList.begin(), info );
			pageContent = curPage.pageNum + pageContent;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		info.count = 1;
			info.timeStamp = i;
	  		infoList.insert( infoList.begin(), info );
	  		pageContent = curPage.pageNum + pageContent;
	  	} // else
	  	
	  } // if
	  else {  // �ثepage��curNum
	  	 loc = pageContent.find( curPage.pageNum );
	  	 infoList[loc].count++;
	  	 infoList[loc].timeStamp = i;
	  } // else
	  
	  
	  curPage.pageContent = pageContent;
	  LFU_result.push_back( curPage );
	} // for
	
} // PageReplacement::LFU_FIFO()

void PageReplacement::MFU_LIFO() {

	pageType curPage;
    string pageContent = "";
    int loc = 0;

    int max_index = 0;
    vector<infoType> infoList;
    infoType info;
    
	for ( int i = 0 ; i < inputPage.size() ; i++ ) {
      curPage.pageContent = "";
      curPage.hasPageFault = false;
	  curPage.pageNum = inputPage[i];
	  
	  // ���ˬdcurPageNum���S���bPage�� 
	  if ( pageContent.find( curPage.pageNum ) == string::npos ) {
	  	// �Y curPageContent ���S�� curPageNum 
	  	curPage.hasPageFault = true;
		
	  	if ( pageContent.size() == pageFrame ) {
		    // page�w�g���F 
	  		// �o��pageFault & pageReplace
	  		
			max_index = distance( begin(infoList), max_element( infoList.rbegin(), infoList.rend(), Compare_Count ).base() - 1 );
			// �]��max_element�^�ǲĤ@�ӳ̤j������(�]�t�۵������p)
			// �ҥH�ΤϦV���N��
			// ��base��^���V���N
			// �ഫ���̷|�t1, �ҥH�n��1 
			
			info.count = 1;
			info.timeStamp = i;

			infoList.erase( infoList.begin() + max_index );
			pageContent.erase( pageContent.begin() + max_index );
			infoList.insert( infoList.end(), info );
			pageContent = pageContent + curPage.pageNum ;
	  	} // if
	  	else {
	  		// �٦��Ŷ��i�H�� 
	  		info.count = 1;
			info.timeStamp = i;
	  		infoList.insert( infoList.end(), info );
			pageContent = pageContent + curPage.pageNum ;
	  	} // else
	  	
	  } // if
	  else {  // �ثepage��curNum
	  	 loc = pageContent.find( curPage.pageNum );
	  	 infoList[loc].count++;
	  	 infoList[loc].timeStamp = i;
	  } // else
	  
	  
	  curPage.pageContent = pageContent;
	  MFU_result.push_back( curPage );
	} // for
	
} // PageReplacement::MFU_LIFO()



void PageReplacement::Sort_timeStamp( string & pageContent, vector<infoType> & infoList ) {
	
	for ( int i = 0 ; i < infoList.size() ; i++ ) {
		for ( int k = i+1 ; k < infoList.size() ; k++ ) {
			if ( infoList[i].timeStamp < infoList[k].timeStamp ) {
				swap( infoList[i], infoList[k] );
				swap( pageContent[i], pageContent[k] );
			} // if
		} // for
	} // for 
	
} // PageReplacement::Sort_timeStamp()

int main() {
	
	PageReplacement page;
	page.Init();
	
	while ( page.ReadFile() ) {
		page.DoMethod();
		page.OutputFile();
		page.Init();
	} // while
	
} // main
