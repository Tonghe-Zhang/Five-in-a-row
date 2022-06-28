#pragma once
#pragma once
#include "general.h"

class fileManager
{
public:
	fileManager(char c);

	char play_rounds[2];

	ofstream fileWriter;

	ifstream fileReader;

	void recordGameboard();

	void readInGameboardData();

	void closeFiles();

	bool checkAndChooseFilename();//1 normal. 0: use an empty gameboard.

	inline void checkSafe();//to secure safety for file recording.

	inline void renew_filename(char* temp);

	inline int renew_filename_in(string);//to get a gameboard.the user will design filename, and this function returns whether this file has been safely established.//-1 invalid input. 1, redo_rename_process, 0 default(use empty gameboard) 2,valid.

	inline int renew_filename_out(char*);//to record a gameboard.

	void getFileNames(string path, vector<string>& files);
	void showFilenameUnderFolder(string path, vector<string>& files);
	void makeFolder(string folderPath);
	void renew();
	string getDesktopPath();
	void createFolder_and_Files();
	void checkFilenames_under_folder();


};
extern fileManager fileKeeper;

