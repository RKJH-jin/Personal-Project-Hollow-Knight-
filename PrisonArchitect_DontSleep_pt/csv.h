#pragma once
#include "gameNode.h"
#include <iostream> 
#include <fstream>
#include <string> //get�����Լ��� ���ؼ� �ʿ���

using namespace std;
/*
ifstream : ���� �б�
ofstream : ���� ���� <<�̰� �Ⱦ��� �б⸸�Ѵٸ�..
*/

class csv : public gameNode
{
public:
	void read()
	{
		//���� ���� �κ� ���������
		/*
		ofstream output("����.csv"); //�������� �̸��� Ȯ���ڸ� ����
		output << "Hello World!, �ȴ�" << endl; //���Ͽ� �� ���� �Է�
		output.close(); //���ϴݱ�*/

		string str_buf; //���� ���ڸ� ���� ����
		ifstream file; //�����д� �ڷ���. ������ �ڷ���

		file.open("objectFile.csv", ios::in);

		//fail()�Լ� : ���� ���°Ϳ� �����Ұ�츦 �˷��� 
		if (file.fail())cout << "������ ���� �� �����߽��ϴ�." << endl;

		while (!file.eof()) //eof: ������ ���̾ƴϸ� ��� �ݺ�. ������ ���������� ��� �� ������ �о��.
		{
			getline(file, str_buf, ','); //�����̴�� ���� / ���ڸ� ���� ���� / ������
			DATAMANAGER->_vStr_buf.push_back(str_buf);
		}

		file.close();

	}
};

