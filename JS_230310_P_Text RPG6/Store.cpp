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
	m_Item[TYPE_Sword][GRADE_Beginner]     = new CItem((char*)"초급 검", (char*)"공격력", 10, 100, 1, 0);
	m_Item[TYPE_Sword][GRADE_Intermediate] = new CItem((char*)"중급 검", (char*)"공격력", 30, 300, 1, 0);
	m_Item[TYPE_Sword][GRADE_Advanced]     = new CItem((char*)"고급 검", (char*)"공격력", 50, 500, 1, 0);

	m_Item[TYPE_Shield][GRADE_Beginner]     = new CItem((char*)"초급 방패", (char*)"방어력", 20, 100, 2, 0);
	m_Item[TYPE_Shield][GRADE_Intermediate] = new CItem((char*)"중급 방패", (char*)"방어력", 40, 300, 2, 0);
	m_Item[TYPE_Shield][GRADE_Advanced]     = new CItem((char*)"고급 방패", (char*)"방어력", 60, 500, 2, 0);
}

void CStore::Update()
{
	int iInput(0);

	while (true)
	{
		system("cls");
		cout << "=====================================" << endl;
		cout << "[무기 상점]" << endl;
		cout << "-------------------------------------" << endl;
		cout << "1) 초급 상점. 2) 중급 상점. 3) 고급 상점. 4) 메인화면: ";
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
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
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
		cout << "[무기 상점]" << endl;
		cout << "-------------------------------------" << endl;
		m_Item[TYPE_Sword][_int]->Item_Output();
		m_Item[TYPE_Shield][_int]->Item_Output();
		cout << "-------------------------------------" << endl;
		cout << "보유코인 : " << dynamic_cast<CPlayer*>(m_Copy_Player)->Get_PlayerCoin() << endl;
		cout << "=====================================" << endl;
		cout << "1. 아이템 구매 / 2. 메인 화면 : ";
		cin >> iInput;

		if (iInput == 1)
		{
			cout << "구매하실 아이템 위치의 숫자를 입력해주세요 : ";
			cin >> i_Input; 
			
			if (i_Input == 1){
				if (m_Copy_Player->Get_PlayerCoin() >= m_Item[TYPE_Sword][_int]->ItemCoin_Get() && m_Copy_PlayerInven->ItemVec_HaveGet().size() < 5)
				{
					m_Copy_PlayerInven->ItemVec_HaveGet().push_back(m_Item[TYPE_Sword][_int]);
					m_Copy_Player->Set_PlayerCoin_(m_Item[TYPE_Sword][_int]->ItemCoin_Get());
					cout << "구매 성공!" << endl;
					system("pause");
				}
				else
				{
					cout << "구매 실패!" << endl;
					system("pause");
				}
				
			}
			else if (i_Input == 2){

				if (m_Copy_Player->Get_PlayerCoin() >= m_Item[TYPE_Shield][_int]->ItemCoin_Get() && m_Copy_PlayerInven->ItemVec_HaveGet().size() < 5)
				{
					m_Copy_PlayerInven->ItemVec_HaveGet().push_back(m_Item[TYPE_Shield][_int]);
					m_Copy_Player->Set_PlayerCoin_(m_Item[TYPE_Shield][_int]->ItemCoin_Get());
					cout << "구매 성공!" << endl;
					system("pause");
				}
				else
				{
					cout << "구매 실패!" << endl;
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