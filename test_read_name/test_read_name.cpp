#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <Windows.h>
#include<fstream>

using namespace std;

//�t�@�C�����̃f�B���N�g�����擾
class Dir
{
public:
	// �R���X�g���N�^
	Dir(void){}
	// �f�X�g���N�^
	virtual ~Dir(void){}

	// �t�@�C���ꗗ�擾
	// folder : �t�H���_�̐�΃p�X����͂Ƃ��� 
	// �� : "D:\\Users\\Pictures\\"
	static vector<string> read(string folder){
		// �錾
		vector<string> fileList;
		HANDLE hFind;
		WIN32_FIND_DATA fd;

		// �t�@�C���������̂��߂Ƀ��C���h�J�[�h�ǉ�
		// �� : "D:\\Users\\Pictures\\*.*"
		stringstream ss;
		ss << folder;
		string::iterator itr = folder.end();
		itr--;
		if(*itr != '\\') ss << '\\';
		ss << "*.*";

		// �t�@�C���T��
		// FindFirstFile(�t�@�C����, &fd);
		hFind = FindFirstFile(ss.str().c_str(), &fd);

		// �������s
		if(hFind == INVALID_HANDLE_VALUE){
			std::cout << "�t�@�C���ꗗ���擾�ł��܂���ł���" << std::endl;
			exit(1); // �G���[�I��
		}

		// �t�@�C���������X�g�Ɋi�[���邽�߂̃��[�v
		do{
			// �t�H���_�͏���
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			  && !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				//�t�@�C���������X�g�Ɋi�[
				char *file = fd.cFileName;
				string str = file;
				fileList.push_back(str);
			}
		}while(FindNextFile(hFind, &fd)); //���̃t�@�C����T��
		
		// hFind�̃N���[�Y
		FindClose(hFind); 

		return fileList;
	}
};


int main(int argc, char *argv[])
{

	// �t�@�C������
	std::vector<std::string> backfilelist = Dir::read("..\\inputfiles\\");		//�ύX�O�t�@�C���̃f�B���N�g�� 1/2
	//property�t�@�C���̓ǂݍ��ݎw��
	std::ifstream propety_dire("..\\property.txt");		
//	std::ifstream propety_dire("..\\property2.txt");	//�ԈႦ�Ė��O��t���Ă��܂����ꍇ�͂�����ň�x���Z�b�g����
	
	char oldname[256];
	char newname[256];
	char chengename[256];	//�ύX�O�̃f�B���N�g���D��̊֐��œǂݎ��������
	char chegename2[256];	//property.txt����ǂݎ��������
	char propety[255];		//property.txt����ǂݎ�������̕���	
	int i=0;

	

	//�v���p�e�Btxt�t�@�C���̓ǂݍ���
    if (propety_dire.fail())
    {
        printf("property�e�L�X�g��ǂݎ�邱�Ƃ��ł��܂���\n");
        return -1;
    }

	

	while (propety_dire.getline(propety, 256 - 1))
    {
		sprintf(chegename2,propety);
		sprintf(newname,"..\\inputfiles\\%s.pdf",chegename2);		//�ύX��t�@�C���̃f�B���N�g��
		//sprintf(newname,"..\\inputfiles\\%s",chegename2);		//�ύX��t�@�C���̃f�B���N�g��
		//printf("%s",newname);
 

		sprintf(chengename,"%s",backfilelist[i].c_str());			//char�Ɍ`����ϊ�
		sprintf(oldname,"..\\inputfiles\\%s",chengename);			//�ύX�O�t�@�C���̃f�B���N�g�� 2/2
		//printf("%s\n",oldname);


	//�t�@�C������ϊ�
	if (rename(oldname, newname) == 0)
		printf("%s -> %s\n", oldname, newname);
	else
		perror("rename error");
		
	++i;
	}	

	return 0;
}