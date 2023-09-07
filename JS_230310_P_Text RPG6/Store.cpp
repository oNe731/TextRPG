#include "pch.h"
#include "Store.h"

CStore::CStore()
{

}

CStore::~CStore()
{
	Release();
}

void CStore::Initialize()
{
	m_Item[TYPE_Sword][GRADE_Beginner]     = new CItem((char*)"�ʱ� ��", (char*)"���ݷ�", 10, 100, 1, 0);
	m_Item[TYPE_Sword][GRADE_Intermediate] = new CItem((char*)"�߱� ��", (char*)"���ݷ�", 30, 300, 1, 0);
	m_Item[TYPE_Sword][GRADE_Advanced]     = new CItem((char*)"��� ��", (char*)"���ݷ�", 50, 500, 1, 0);

	m_Item[TYPE_Shield][GRADE_Beginner]     = new CItem((char*)"�ʱ� ����", (char*)"����", 20, 100, 2, 0);
	m_Item[TYPE_Shield][GRADE_Intermediate] = new CItem((char*)"�߱� ����", (char*)"����", 40, 300, 2, 0);
	m_Item[TYPE_Shield][GRADE_Advanced]     = new CItem((char*)"��� ����", (char*)"����", 60, 500, 2, 0);
}

void CStore::Update()
{
	int iInput(0);

	while (true)
	{
		system("cls");
		cout << "=====================================" << endl;
		cout << "[���� ����]" << endl;
		cout << "-------------------------------------" << endl;
		cout << "1) �ʱ� ����. 2) �߱� ����. 3) ��� ����. 4) ����ȭ��: ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			MiniStore(GRADE_Beginner);
			break;
		case 2:
			MiniStore(GRADE_Intermediate);
			break;
		case 3:
			MiniStore(GRADE_Advanced);
			break;
		case 4:
			return;
		default:
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
			break;
		}
	}
}

void CStore::MiniStore(ITEM_GRADE _int)
{
	int iInput(0), i_Input(0);

	while (true)
	{
		system("cls");
		cout << "=====================================" << endl;
		cout << "[���� ����]" << endl;
		cout << "-------------------------------------" << endl;
		m_Item[TYPE_Sword][_int]->Item_Output();
		m_Item[TYPE_Shield][_int]->Item_Output();
		cout << "-------------------------------------" << endl;
		cout << "�������� : " << dynamic_cast<CPlayer*>(m_Copy_Player)->Get_PlayerCoin() << endl;
		cout << "=====================================" << endl;
		cout << "1. ������ ���� / 2. ���� ȭ�� : ";
		cin >> iInput;

		if (iInput == 1)
		{
			cout << "�����Ͻ� ������ ��ġ�� ���ڸ� �Է����ּ��� : ";
			cin >> i_Input; 
			
			if (i_Input == 1){
				if (m_Copy_Player->Get_PlayerCoin() >= m_Item[TYPE_Sword][_int]->ItemCoin_Get() && m_Copy_PlayerInven->ItemVec_HaveGet().size() < 5)
				{
					m_Copy_PlayerInven->ItemVec_HaveGet().push_back(m_Item[TYPE_Sword][_int]);
					m_Copy_Player->Set_PlayerCoin_(m_Item[TYPE_Sword][_int]->ItemCoin_Get());
					cout << "���� ����!" << endl;
					system("pause");
				}
				else
				{
					cout << "���� ����!" << endl;
					system("pause");
				}
				
			}
			else if (i_Input == 2){

				if (m_Copy_Player->Get_PlayerCoin() >= m_Item[TYPE_Shield][_int]->ItemCoin_Get() && m_Copy_PlayerInven->ItemVec_HaveGet().size() < 5)
				{
					m_Copy_PlayerInven->ItemVec_HaveGet().push_back(m_Item[TYPE_Shield][_int]);
					m_Copy_Player->Set_PlayerCoin_(m_Item[TYPE_Shield][_int]->ItemCoin_Get());
					cout << "���� ����!" << endl;
					system("pause");
				}
				else
				{
					cout << "���� ����!" << endl;
					system("pause");
				}
			}
		}
		else if (iInput == 2)
		{
			return;
		}
	}
	
}

void CStore::Release()
{
	for (int i = 0; i < TYPE_End; ++ i){
		for (int j = 0; j < GRADE_End; ++ j){
			DELETE_MEMORY(m_Item[i][j]);
		}
	}
}