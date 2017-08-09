#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <Windows.h>
#include<fstream>

using namespace std;

//ファイル名のディレクトリを取得
class Dir
{
public:
	// コンストラクタ
	Dir(void){}
	// デストラクタ
	virtual ~Dir(void){}

	// ファイル一覧取得
	// folder : フォルダの絶対パスを入力とする 
	// 例 : "D:\\Users\\Pictures\\"
	static vector<string> read(string folder){
		// 宣言
		vector<string> fileList;
		HANDLE hFind;
		WIN32_FIND_DATA fd;

		// ファイル名検索のためにワイルドカード追加
		// 例 : "D:\\Users\\Pictures\\*.*"
		stringstream ss;
		ss << folder;
		string::iterator itr = folder.end();
		itr--;
		if(*itr != '\\') ss << '\\';
		ss << "*.*";

		// ファイル探索
		// FindFirstFile(ファイル名, &fd);
		hFind = FindFirstFile(ss.str().c_str(), &fd);

		// 検索失敗
		if(hFind == INVALID_HANDLE_VALUE){
			std::cout << "ファイル一覧を取得できませんでした" << std::endl;
			exit(1); // エラー終了
		}

		// ファイル名をリストに格納するためのループ
		do{
			// フォルダは除く
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			  && !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				//ファイル名をリストに格納
				char *file = fd.cFileName;
				string str = file;
				fileList.push_back(str);
			}
		}while(FindNextFile(hFind, &fd)); //次のファイルを探索
		
		// hFindのクローズ
		FindClose(hFind); 

		return fileList;
	}
};


int main(int argc, char *argv[])
{

	// ファイル入力
	std::vector<std::string> backfilelist = Dir::read("..\\inputfiles\\");		//変更前ファイルのディレクトリ 1/2
	//propertyファイルの読み込み指定
	std::ifstream propety_dire("..\\property.txt");		
//	std::ifstream propety_dire("..\\property2.txt");	//間違えて名前を付けてしまった場合はこちらで一度リセットする
	
	char oldname[256];
	char newname[256];
	char chengename[256];	//変更前のディレクトリ．上の関数で読み取ったもの
	char chegename2[256];	//property.txtから読み取った文字
	char propety[255];		//property.txtから読み取った生の文字	
	int i=0;

	

	//プロパティtxtファイルの読み込み
    if (propety_dire.fail())
    {
        printf("propertyテキストを読み取ることができません\n");
        return -1;
    }

	

	while (propety_dire.getline(propety, 256 - 1))
    {
		sprintf(chegename2,propety);
		sprintf(newname,"..\\inputfiles\\%s.pdf",chegename2);		//変更後ファイルのディレクトリ
		//sprintf(newname,"..\\inputfiles\\%s",chegename2);		//変更後ファイルのディレクトリ
		//printf("%s",newname);
 

		sprintf(chengename,"%s",backfilelist[i].c_str());			//charに形式を変換
		sprintf(oldname,"..\\inputfiles\\%s",chengename);			//変更前ファイルのディレクトリ 2/2
		//printf("%s\n",oldname);


	//ファイル名を変換
	if (rename(oldname, newname) == 0)
		printf("%s -> %s\n", oldname, newname);
	else
		perror("rename error");
		
	++i;
	}	

	return 0;
}