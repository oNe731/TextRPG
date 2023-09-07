#include "pch.h"
#include "Inventory.h"

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
}

void CInventory::Initialize()
{
	// �̸� ���� Ȯ�� ����.
}

void CInventory::Update()
{
	int iInput(0), i_Input(0);
	bool bSame(false);

	while (true)
	{
		system("cls");
		Inven_Output();
		cout << "1) ������ ����. 2) ������ ���� ����. 3) ������ �Ǹ�. 4) ����ȭ�� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			cout << "������ ������ ��ȣ�� �Է��Ͻÿ�. : ";
			cin >> i_Input;
			if (i_Input > m_Item_Have.size())
				continue;

			iter = m_Item_Have.begin();
			iter += (i_Input - 1);

			for (iter2 = m_Item_Equip.begin(); iter2 != m_Item_Equip.end(); ++iter2){
				if ((*iter2)->ItemInfo_Get().iNum == (*iter)->ItemInfo_Get().iNum){
					bSame = true;
					cout << "�̹� ������ ���Ⱑ �����մϴ�." << endl;
				}
			}
			if (!bSame) {
				m_Item_Equip.push_back(*iter);
				iter = m_Item_Have.erase(iter);
			}
			system("pause");
			break;
		case 2:
			cout << "������ ������ ��ȣ�� �Է��Ͻÿ�. : ";
			cin >> i_Input;
			if (i_Input > m_Item_Equip.size())
				continue;

			iter = m_Item_Equip.begin();
			iter += (i_Input - 1);

			m_Item_Have.push_back(*iter);
			iter = m_Item_Equip.erase(iter);
			system("pause");
			break;
		case 3:
			cout << "�Ǹ��� ������ ��ȣ�� �Է��Ͻÿ�. : ";
			cin >> i_Input;
			if (i_Input > m_Item_Have.size())
				continue;

			iter = m_Item_Have.begin();
			iter += (i_Input - 1);

			dynamic_cast<CPlayer*>(m_Copy_Player)->Set_PlayerCoin((*iter)->ItemCoin_Get()/2);
			iter = m_Item_Have.erase(iter);
			system("pause");
			break;
		case 4:
			return;
		default:
			break;
		}
		system("cls");
	}
	system("pause");
}

void CInventory::Release()
{
	for (iter = m_Item_Have.begin(); iter != m_Item_Have.end(); ++iter) {
		DELETE_MEMORY(*iter);
	}

	for (iter = m_Item_Equip.begin(); iter != m_Item_Equip.end(); ++iter) {
		DELETE_MEMORY(*iter);
	}
}

void CInventory::Inven_Output()
{
	cout << "=============================================" << endl;
	cout << "[������ ������]" << endl;
	cout << "---------------------------------------------" << endl;
	for (iter = m_Item_Equip.begin(); iter != m_Item_Equip.end(); ++iter)
	{
		(*iter)->Item_Output();
	}
	cout << "=============================================" << endl;
	cout << "[�������� ������]" << endl;
	cout << "---------------------------------------------" << endl;
	for (iter = m_Item_Have.begin(); iter != m_Item_Have.end(); ++iter)
	{
		(*iter)->Item_Output();
	}
	cout << "-------------------------------------" << endl;
	cout << "�������� : " << dynamic_cast<CPlayer*>(m_Copy_Player)->Get_PlayerCoin() << endl;
	cout << "=====================================" << endl;
}