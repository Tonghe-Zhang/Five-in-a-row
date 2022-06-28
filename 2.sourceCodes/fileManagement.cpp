#include "general.h"
#include "fileManagement.h"
#include "chessboard.h"
#include "globalFunctionDeclaration.h"
#include <graphics.h>
#include "globalVariableDeclaration.h"
#include "Gui_inputControl.h"
#include "GUI_outputControl.h"
//For class fileManager

//constructor.
fileManager::fileManager(char c)
{
	play_rounds[0] = c;
	play_rounds[1] = c;
}

void fileManager::closeFiles()
{
	fileWriter.close();
	fileReader.close();
}

void fileManager::recordGameboard()
{
	string  path = "D:";
	path.append("\\Albert's_Gomoku\\gameboard\\");
	path.append(filename);
	string text = "Your gameboard will be stored at:  ";
	text.append(path);
	cleardevice();
	YNInput(text.c_str(), "OK", 1);
	quickOutput(text);
	if (directive[0] == 'O')
	{
		fileWriter.close();
		fileWriter.open(path, ios::ate | ios::out | ios::in);

		if (fileWriter.fail())
		{
			printf("write in error!");
			exit(-1);
		}

		for (int i = 1; i < 16; i++)
		{
			for (int j = 1; j < 15; j++)
			{
				char temp[3];
				sprintf(temp, "%d", gameboard.sequence[i][j]);
				fileWriter << temp;
				fileWriter << " ";
			}
			char temp[3];
			sprintf(temp, "%d", gameboard.sequence[i][15]);
			fileWriter << temp;
			fileWriter << " ";
		}

		fileWriter << '#' << endl;
		time_t now = time(NULL);
		tm* timeNow = localtime(&now);
		fileWriter << name1 << " ●\n V.S." << name2 << " ○\n at ";
		fileWriter << asctime(timeNow);
		fileWriter << endl;

		fileWriter.close();
	}
	
}

void fileManager::readInGameboardData()
{
	int i = 0;//one-dimensional number of the positions.
	fileReader.close();

	fileReader.open(filename, ios_base::in);

	if (!fileReader.is_open())
	{
		cerr << filename << "read in error!" << endl;

		exit(-1);
	}

	char temp[10] = { "aaaaaaaaa" };
	int numbers;//a temporary variable used to receive atoi(temp)
	int PlayerTurn = 0;//to record player's turn in this gameboard， where black==odd numbers, white==even numbers.
	while (true)
	{
		fileReader >> temp;
		if (temp[0] == '#' || i == 255)
			break;

		numbers = atoi(temp);
		if (numbers && numbers > PlayerTurn)
			PlayerTurn = numbers;

		i++;

		gameboard.sequence[(i % 15 == 0 ? i / 15 : 1 + i / 15)][(i % 15 == 0 ? 15 : i % 15)] = numbers;

	}
	gameboard.player_s_turn = PlayerTurn % 2 + 1;

	fileReader.close();

	gameboardPainter painter(15);
	string text;

	for (int i = 1; i < 16; i++)
	{
		for (int j = 1; j < 16; j++)
		{
			if (gameboard.sequence[i][j] == 0)
				gameboard.board[i][j] = chessColor::empty;
			else if (gameboard.sequence[i][j] % 2 == 1)
				gameboard.board[i][j] = chessColor::black;
			else gameboard.board[i][j] = chessColor::white;
		}
	}
	cleardevice();
}

//Return :False==use empty gameboard. True==use specified gameboard.
bool fileManager::checkAndChooseFilename()
{
	if (directive[0] == 'Y' || directive[0] == 'y')
	{
		char NewName[40];
		int result = 100;
		string temp;

		do
		{
			cleardevice();
			quickOutput("These are history gameboards on your device. Please select one from below.", "absoluteLine", 0);
			fileKeeper.checkFilenames_under_folder();
			::GUI_mode = playing;
			
			quickOutput("Please type in the name of your selected gameboard.", middleLineX-(strlen("Please type in the name of your selected gameboard.")/2)*10,bottomBoarderY-40);
			InputText(&temp,6);
			result = fileKeeper.renew_filename_in(temp);

		} while (result == 1);//return 1 means we need to specify a valid filename again.

		::GUI_mode = start;

		if (result == 0)//start with empty board.
			return false;
		return true;
	}
}

void fileManager::renew_filename(char* temp)
{

	if (strlen(temp) > 40)
	{
		quickOutput("<ERROR>filnemae exceeds lenght limit(no more than 40 words).");
		exit(-1);
	}
	filename = temp;
	filename.append(".txt");
}

// return : 1  select name again.   0  use empty gameboard. 
//          2  opened specified document successfully,use that gameboard.
int fileManager::renew_filename_in(string NewName)
{
	string temp = "NewName==";
	temp.append(NewName);


	string  path = "D:";//getDesktopPath();
	path.append("\\Albert's_Gomoku\\gameboard\\").append(NewName).append(".txt");
	cleardevice();

	filename = path;

	//fileWriter.open(path, ios::ate | ios::out | ios::in);
	fileReader.open(path, ios::in);

	if (!fileReader.is_open())
	{
		cleardevice();
		quickOutput("There's no such a file under current directory.");
		Sleep(2000);
		cleardevice();
		YNInput("Now You can SELECT gameboard again or start with EMPTY board.", "SELECT AGAIN", "EMPTY");
		if (directive[0] == 'S')
			return 1;     //
		return 0;        //Empty:default
		fileWriter.close();
		fileReader.close();
	}
	return 2;
}

int fileManager::renew_filename_out(char* NewName)
{
	renew_filename(NewName);

}

void fileManager::checkSafe()
{
	if (play_times > 99)
	{
		quickOutput("too many filenames");
		exit(-1);
	}
}


//===================================================================================================================================================================================================================================


void fileManager::makeFolder(string folderPath)
{

	string command;
	command = "mkdir -p " + folderPath;
	system(command.c_str());
}


//自动更新文件名
void fileManager::renew()
{
	play_rounds[1] = '0' + play_times % 10;//个位
	play_rounds[0] = '0' + play_times / 10;//十位
	filename[9] = play_rounds[0];
	filename[10] = play_rounds[1];
}

//获取目录下文件地址名
void fileManager::getFileNames(string path, vector<string>& files)
{
	//文件句柄
	//注意：我发现有些文章代码此处是long类型，实测运行中会报错访问异常
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,递归查找
			//如果不是,把文件绝对路径存入vector中
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);



			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));



			}

		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


void fileManager::showFilenameUnderFolder(string path, vector<string>& files)
{
	int i = 1;
	string filenameForDisplay = "";

	//文件句柄
	//
	intptr_t hFile = 0;
	//
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//If it's the directory, search file recursively.
			//Else,store the absolute path into vector.
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					showFilenameUnderFolder(p.assign(path).append("\\").append(fileinfo.name), files);


				filenameForDisplay = fileinfo.name;
				filenameForDisplay = filenameForDisplay.substr(0, filenameForDisplay.length()-4);
				if(i>2)//Skip first two meaningless files.
				quickOutput(filenameForDisplay, "absoluteLine", i);
				
				i++;

			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));


				filenameForDisplay = fileinfo.name;
				filenameForDisplay = filenameForDisplay.substr(0, filenameForDisplay.length() - 4);
				if (i > 2)//Skip first two meaningless files.
					quickOutput(filenameForDisplay, "absoluteLine", i);
				i++;
				

			}

		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

}

//getAbsolutePath of the user's desktop.
string  fileManager::getDesktopPath()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[200];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
			// 如果成功返回true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}

	return string(szDir);
}
//create a folder in disk D and name it as "Albert's_Gomuku\\gameboard\\";
void fileManager::createFolder_and_Files()
{

	//If we have already created this folder and it can be read or written,then don't create again.
	if (_access("D:\\Albert's_Gomuku\\gameboard",06)==0)
		return;

	cleardevice();
	quickOutput("Please type in your filename.");
	string temp;
	InputText(&temp);
	if (temp.length() > 40)
	{
		quickOutput("<ERROR>filnemae exceeds lenght limit(no more than 40 words).");
		exit(-1);
	}
	temp += ".txt";
	filename = temp;
	string  path = "D:";//getDesktopPath();
	path.append("\\Albert's_Gomoku\\gameboard\\");
	makeFolder(path);
	path += filename;
	fstream fout(path, ios::out);
	cleardevice();
	play_times++;
}

void fileManager::checkFilenames_under_folder()
{
	
	vector<string> fileNames;
	string  path = "D:";
	path.append("\\Albert's_Gomoku\\gameboard\\");
	showFilenameUnderFolder(path, fileNames);
	for (const auto& ph : fileNames)
	{
		;
	}
}



