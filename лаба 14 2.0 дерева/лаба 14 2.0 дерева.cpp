// лаба 14 дерева.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <string.h>
#include <Windows.h>

using namespace std;

struct Ware
{
	string name_tovar;
	int weight;
	int cost_tovar;
	string color;
	Ware* left = NULL;
	Ware* right = NULL;
	Ware* parent = NULL;
}; Ware* koren = nullptr;

struct Color
{
	string name_tovar;
	int weight;
	int cost_tovar;
	string color;
	Color* left1 = NULL;
	Color* right1 = NULL;
	Color* parent1 = NULL;
}; Color* koren1 = nullptr;

void Header();
void Menu();
void Input_one_value(Ware* a0);
void display_all(Ware* koren);
void display_level(Ware* koren_d, int& i, int level);
void LEVEL(Ware* koren_d, int& i, int& max_level);
//void removeNullWare(Ware* root);
//void removeWareWithSameValue(Ware* root, string value);
//void removeWare(Ware* root, string value);
void postorderTraversal(Ware* root);
void Output_color_tree(Color* temp_val_color);
void dfs(Ware* koren);
void deleteTree_base(Ware* koren);
void deleteTree(Color* koren);
void removeDuplicates(Ware*& ware);
bool isDuplicate(Ware* koren, string name, int P);
void input_Ware(Ware* koren);
void Add_new_Ware(Ware* koren, Ware* new_code);
void insert_Color(Color*& root, string name_tovar, int weight, int cost_tovar, string color);
void Create_Tree_with_color(Ware* root, string cur_color);

int main()
{
	setlocale(LC_ALL, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int k;

	Ware* a0 = new Ware;
	Input_one_value(a0);
	bool t = true;
	while (t)
	{
		Menu();
		cout << "Виберiть режим роботи: " << endl;
		k = 0;
		cin >> k;
		cin.ignore();
		switch (k)
		{
		case 1:
		{
			Ware* a1 = new Ware; 
			input_Ware(koren);  
			Add_new_Ware(koren, a0);
			cout << endl;
			break;
		}
		case 2:
		{
			cout << "Обхід графа знизу: " << endl;
			Header();
			postorderTraversal(koren);
			cout << endl;
			//display_all(koren); break;
			break;
		}
		case 3:
		{
			string cur_color;
			cout << "Ведіть колір, який хочете додати: ";
			cin >> cur_color;
			Create_Tree_with_color(koren, cur_color);
			/*Color* koren1 = NULL;
			search(koren, cur_color);
			cout << "Дерево було сформовано:" << endl;
			Output_color_tree(koren1);
			deleteTree(koren1);
			cout << "Дерево з кольорами було видалено" << endl;*/
			break;
		}
		case 4:
		{
			display_all(koren); break;
		}
		case 5:
		{
			removeDuplicates(koren);
			cout << "Дублікати були видалені" << endl;
			break;
			/*
			int key;
			cout << "Введіть ключ" << endl;
			cin >> key;
			key--;
			cut(k);  break;*/
		}
		case 6:
		{
			t = 0;
			break;
		}
		}
	}
	deleteTree_base(koren);
	cout << "Дерево було видалено" << endl;
}
void Create_Tree_with_color(Ware* root, string cur_color)
{
	int i = 0;
	string name_tovar, color;
	int weight, cost_tovar;
	if (root == NULL)
	{
		return;
	}
	if (root->color == cur_color)
	{
		Color* new_el = new Color;
		name_tovar = root->name_tovar;
		weight = root->weight;
		cost_tovar = root->cost_tovar;
		color = root->color;
		insert_Color(new_el, name_tovar, weight, cost_tovar, color);
	}
	Create_Tree_with_color(root->left, cur_color);
	Create_Tree_with_color(root->right, cur_color);

}
void insert_Color(Color*& root, string name_tovar, int weight, int cost_tovar, string color)
{
	if (root == nullptr)
	{
		root = new Color{ name_tovar, weight, cost_tovar, color };
		return;
	}
	if (name_tovar < root->name_tovar)
	{
		if (root->left1 == nullptr) 
		{
			root->left1 = new Color{ name_tovar, weight, cost_tovar, color };
			root->left1->parent1 = root;
		}
		else 
		{
			insert_Color(root->left1, name_tovar, weight, cost_tovar, color);
		}
	}
	else 
	{
		if (root->right1 == nullptr) 
		{
			root->right1 = new Color{ name_tovar, weight, cost_tovar, color };
			root->right1->parent1 = root;
		}
		else 
		{
			insert_Color(root->right1, name_tovar, weight, cost_tovar, color);
		}
	}
}
void Add_new_Ware(Ware* koren, Ware* new_code)
{
	if (koren->cost_tovar > new_code->cost_tovar && koren->left != NULL)
		Add_new_Ware(koren->left, new_code);
	if (koren->cost_tovar < new_code->cost_tovar && koren->right != NULL)
		Add_new_Ware(koren->right, new_code);

	if (koren->cost_tovar > new_code->cost_tovar && koren->left == NULL)
		koren->left = new_code;
	if (koren->cost_tovar < new_code->cost_tovar && koren->right == NULL)
		koren->right = new_code;

}

void input_Ware(Ware* koren)
{
	Ware* a1 = new Ware;
	cout << "Введіть назву товару: ";
	cin >> a1->name_tovar;
	cout << "Введіть вагу товару: ";
	cin >> a1->weight;
	cout << "Введіть вартість товару: ";
	cin >> a1->cost_tovar;
	cout << "Введіть колір товару: ";
	cin >> a1->color;
	if (koren == NULL) { koren = a1; }
	Add_new_Ware(koren, a1);
}

bool isDuplicate(Ware* koren, string name, int P)
{
	//if (root == NULL)
	//{
	//	return false;
	//}
	//if (root->name_tovar == name)
	//{
	//	P++;
	//	if (P > 1)
	//	{
	//		return true;
	//	}
	//}
	//isDuplicate(root->left, name, 0);
	//isDuplicate(root->right, name, 0);
	//return false;
	if (koren == nullptr)
	{
		return false;
	}

	if (koren->name_tovar == name)
	{
		P++;
		if (P > 1)
		{
			return true;
		}
	}

	if (isDuplicate(koren->left, name, P))
	{
		P++;
		if (P > 1)
		{
			return true;
		}
	}
	if (isDuplicate(koren->right, name, P))
	{
		P++;
		if (P > 1)
		{
			return true;
		}
	}


}

void removeDuplicates(Ware*& ware)
{
	if (ware == nullptr)
	{
		return;
	}

	if (isDuplicate(koren, ware->name_tovar, 0))
	{
		cout << "Ware " << ware->name_tovar << " is a duplicate. Delete? (y/n) ";
		char answer;
		cin >> answer;

		if (answer == 'y')
		{
			ware = nullptr;
			delete ware;
		}
	}
	removeDuplicates(ware->left);
	removeDuplicates(ware->right);
}

void deleteTree(Color* koren)
{
	if (koren == nullptr) {
		return;
	}
	deleteTree(koren->left1);
	deleteTree(koren->right1);
	delete koren;
}

void deleteTree_base(Ware* koren)
{
	if (koren == nullptr) {
		return;
	}
	deleteTree_base(koren->left);
	deleteTree_base(koren->right);
	delete koren;
}

void dfs(Ware* koren)
{
	if (koren == NULL)
	{
		return;
	}
	dfs(koren->left);
	dfs(koren->right);
}

void Output_color_tree(Color* temp_val_color)
{
	if (temp_val_color == NULL) {
		cout << "У дерево нічого не записано" << endl;
		return;
	}
	cout << temp_val_color->name_tovar << setw(8) << temp_val_color->weight << setw(8) << temp_val_color->cost_tovar << setw(8) << temp_val_color->color << endl;

	Output_color_tree(temp_val_color->left1);
	Output_color_tree(temp_val_color->right1);
}

void postorderTraversal(Ware* root)
{
	if (root == NULL)
		return;

	cout << root->name_tovar << setw(8) << root->weight << setw(8) << root->cost_tovar << setw(8) << root->color << endl;
	postorderTraversal(root->left);
	postorderTraversal(root->right);
}

void LEVEL(Ware* koren_d, int& i, int& max_level)
{
	if (koren_d->left != NULL)
	{
		i++;
		if (max_level < i)
			max_level = i;
		LEVEL(koren_d->left, i, max_level);
		i--;
	}
	if (koren_d->right != NULL)
	{
		i++;
		if (max_level < i)
			max_level = i;
		LEVEL(koren_d->right, i, max_level);
		i--;
	}
}

void display_level(Ware* koren_d, int& i, int level)
{
	if (i == level)
	{
		cout << "           ";
		cout << koren_d->name_tovar << setw(10) << koren_d->weight << setw(10) << koren_d->cost_tovar << setw(10) << koren_d->color << endl;
	}
	if (koren_d->left != NULL)
	{
		i++;
		display_level(koren_d->left, i, level);
		i--;
	}
	if (koren_d->right != NULL)
	{
		i++;
		display_level(koren_d->right, i, level);
		i--;
	}
}

void display_all(Ware* koren)
{
	int i = 0;
	int max_level = 0;
	LEVEL(koren, i, max_level);
	cout << "max рівень = " << max_level << endl;
	cout << "           "; Header();
	for (int level = 0; level <= max_level; level++)
	{
		if (level == 0)
			cout << "0 рівень:  " << endl;
		else
		{
			cout << "(" << level << " рівень): " << endl;
		}

		display_level(koren, i, level);
	}
	cout << endl;
}


void Input_one_value(Ware* a0)
{
	cout << "Введіть назву товару: ";
	cin >> a0->name_tovar;
	cout << "Введіть вагу товару: ";
	cin >> a0->weight;
	cout << "Введіть вартість товару: ";
	cin >> a0->cost_tovar;
	cout << "Введіть колір товару: ";
	cin >> a0->color;
	koren = a0;
}


void Menu()
{
	cout << "1 - додавання нового елементу в дерево у діалоговому режимі;" << endl;
	cout << "2 - обхід знизу;" << endl;
	cout << "3 - побудова окремих дерев для різних кольорів;" << endl;
	cout << "4 - роздрукування дерева;" << endl;
	cout << "5 - видалення із дерева усіх вузлів, що повторюються (в діалоговому режимі з підтвердженням)" << endl;
	cout << "6 - вихiд;" << endl;
	cout << endl;
}
void Header()
{
	cout << "Назва товару" << setw(10) << "Вагa" << setw(10) << "Вартість" << setw(10) << "Колір" << endl;
}

void removeWare(Ware* root, string value)
//{
//	removeWareWithSameValue(root, value);
//	removeNullWare(root);
//}
//
//void removeWareWithSameValue(Ware* root, string value)
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	//if (root == koren)
//	//{
//	//	removeWareWithSameValue(root->left, value);
//	//}
//	if (root->name_tovar == value)
//	{
//		root = NULL;
//		return;
//	}
//	removeWareWithSameValue(root->left, value);
//	removeWareWithSameValue(root->right, value);
//}
//
//void removeNullWare(Ware* root)
//{
//	if (root == NULL)
//	{
//		return;
//	}
//	if (root->left != NULL && root->left->name_tovar == "")
//	{
//		root->left = NULL;
//	}
//	if (root->right != NULL && root->right->name_tovar == "")
//	{
//		root->right = NULL;
//	}
//	removeNullWare(root->left);
//	removeNullWare(root->right);
//}
//
//void Add_new_Color(Color* root1, Color* new_code)
//{
//	if (root1->cost_tovar > new_code->cost_tovar && root1->left1 != NULL)
//	{
//		Add_new_Color(root1->left1, new_code);
//	}
//	if (root1->cost_tovar < new_code->cost_tovar && root1->right1 != NULL)
//	{
//		Add_new_Color(root1->right1, new_code);
//	}
//	if (root1->cost_tovar > new_code->cost_tovar && root1->left1 == NULL)
//	{
//		root1->left1 = new_code;
//	}
//	if (root1->cost_tovar < new_code->cost_tovar && root1->right1 == NULL)
//	{
//		root1->right1 = new_code;
//	}
//
//}


//void input_Color(Color* root1, string cur_name, int weight, int cost_tovar, string color)
//{
//	Color* a1 = new Color;
//	a1->name_tovar = cur_name;
//	a1->weight = weight;
//	a1->cost_tovar = cost_tovar;
//	a1->color = color;
//	if (koren1 == NULL) { koren1 = a1; }
//	Add_new_Color(root1, a1);
//}

//void search(Ware* root, string cur_color)
//{
//	int i = 0;
//	string cur_name1, cur_color1;
//	int cur_cost, cur_weight;
//	Color* a0 = new Color;
//	if (koren == NULL)
//	{
//		return;
//	}
//	if (root->color == cur_color)
//	{
//		if (i == 0)
//		{
//			a0->name_tovar = root->name_tovar;
//			a0->weight = root->weight;
//			a0->cost_tovar = root->cost_tovar;
//			a0->color = root->color;
//			koren1 = a0;
//		}
//		Color* a1 = new Color;
//		cout << "Пройшло умову" << endl;
//		cur_name1 = root->name_tovar;
//		cur_weight = root->weight;
//		cur_cost = root->cost_tovar;
//		cur_color1 = root->color;
//		input_Color(koren1, cur_name1, cur_weight, cur_cost, cur_color1);
//		
//		Add_new_Color(koren1, a0);
//		i++;
//	}
//	search(root->left, cur_color);
//	search(root->right, cur_color);

//}
//cout << "Немає в дереві елемента з таким ключом\n";
//string cur_name1, cur_color1;
//int cur_cost, cur_weight;
//Ware* a1 = koren;
//if (koren == nullptr)
//{
//	cout << "Дерево пусте\n";
//}
//int i = 0;
//while (a1 != nullptr)
//{
//	if (a1->color == cur_color) {

//		cout << "Пройшло умову" << endl;
//		cur_name1 = root->name_tovar;
//		cur_weight = root->weight;
//		cur_cost = root->cost_tovar;
//		cur_color1 = root->color;

//		insert(koren1, cur_name1, cur_weight, cur_cost, cur_color1);
//		search(root->left, cur_color);
//		search(root->right, cur_color);
//		return;
//	}
//	if (a1->cost_tovar < a1->right->cost_tovar) {
//		a1 = a1->left;
//	}
//	else {
//		a1 = a1->right;
//	}
//	i++;
//}
//bool isDuplicate(Ware* root, string name, int P)
//{
//	if (root == NULL)
//	{
//		return false;
//	}
//	if (root->name_tovar == name)
//	{
//		P++;
//		if (P > 1)
//		{
//			return true;
//		}
//	}
//	isDuplicate(root->left, name, 0);
//	isDuplicate(root->right, name, 0);
//	return false;
//	//if (koren == nullptr)
//	//{
//	//	return false;
//	//}
//
//	//if (koren->name_tovar == name)
//	//{
//	//	return true;
//	//}
//
//	//if (isDuplicate(koren->left, name))
//	//{
//	//	return true;
//	//}
//	//if (isDuplicate(koren->right, name))
//	//{
//	//	return true;
//	//}
//
//
//}
//
//void removeDuplicates(Ware*& ware)
//{
//	if (ware == nullptr)
//	{
//		return;
//	}
//
//	if (isDuplicate(koren, ware->name_tovar, 0))
//	{
//		cout << "Ware " << ware->name_tovar << " is a duplicate. Delete? (y/n) ";
//		char answer;
//		cin >> answer;
//
//		if (answer == 'y')
//		{
//			ware = nullptr;
//			delete ware;
//		}
//	}
//	removeDuplicates(ware->left);
//	removeDuplicates(ware->right);
//}
//void search(int cost_for_find)
//{
//	Ware* a1 = koren;
//	if (koren == nullptr)
//		cout << "Дерево пусте\n";
//	while (a1 != nullptr)
//	{
//		if (a1->cost_tovar == cost_for_find) {
//			cout << a1->name_tovar << setw(10) << a1->weight << setw(10) << a1->cost_tovar << setw(10) << a1->color << endl;
//			return;
//		}
//		if (cost_for_find < a1->cost_tovar) {
//			a1 = a1->left;
//		}
//		else {
//			a1 = a1->right;
//		}
//	}
//	cout << "Немає в дереві елемента з таким ключом\n";
//}


//
//void insert(Color*& root, string cur_name, int weight, int cost_tovar, string color)
//{
//	cout << "Потрапило на додавання" << endl;
//	if (root == nullptr)
//	{
//		root = new Color;
//		root->name_tovar = cur_name;
//		root->weight = weight;
//		root->cost_tovar = cost_tovar;
//		root->color = color;
//		root->left1 = nullptr;
//		root->right1 = nullptr;
//		return;
//	}
//	else
//	{
//		root = new Color;
//		root->name_tovar = cur_name;
//		root->weight = weight;
//		root->cost_tovar = cost_tovar;
//		root->color = color;
//		root->left1 = nullptr;
//		root->right1 = nullptr;
//		return;
//	}
//	if (cost_tovar < root->cost_tovar) {
//		insert(root->left1, cur_name, weight, cost_tovar, color);
//	}
//	else {
//		insert(root->right1, cur_name, weight, cost_tovar, color);
//	}
//}


//void Great_tree_with_color(Ware* ware, string cur_color)
//{
//	int k = 0;
//	if (ware == NULL) {
//		return;
//	}
//	if (cur_color == ware->color)
//	{
//		Color* new_color = new Color;
//		//new_color->color = cur_color;
//		new_color->name_tovar = ware->name_tovar;
//		new_color->weight = ware->weight;
//		new_color->cost_tovar = ware->cost_tovar;
//		new_color->color = ware->color;
//		if (koren1 == NULL)
//		{
//			k++;
//			koren1 = new_color;
//		}
//		cout << "Потрапило на додавання" << endl;
//		if (k > 0)
//		{
//			Add_color_for_new_tree(koren1, new_color);
//		}
//	}
//	cout << ware->color << " " << endl;
//	Great_tree_with_color(ware->left, cur_color);
//	Great_tree_with_color(ware->right, cur_color);
//}
//
//void Add_color_for_new_tree(Color* koren, Color* new_code)
//{
//	if (koren->cost_tovar > new_code->cost_tovar && koren->left1 != NULL)
//		Add_color_for_new_tree(koren->left1, new_code);
//	if (koren->cost_tovar < new_code->cost_tovar && koren->right1 != NULL)
//		Add_color_for_new_tree(koren->right1, new_code);
//
//	if (koren->color > new_code->color && koren->left1 == NULL)
//		koren->left1 = new_code;
//	if (koren->color < new_code->color && koren->right1 == NULL)
//		koren->right1 = new_code;
//}

//void cut(int key)
//{
//	Ware* a1 = koren;
//	if (koren == nullptr)
//		cout << "Дерево пусте\n";
//	while (a1 != nullptr)
//	{
//		if (a1->cost_tovar == key) {
//			Ware* Ware_for_delete = a1;
//			if (Ware_for_delete != nullptr)
//			{
//				if (Ware_for_delete->left == nullptr && Ware_for_delete->right == nullptr)
//				{
//					if (Ware_for_delete->parent == nullptr)
//					{
//						delete Ware_for_delete;
//					}
//					else
//					{
//						if (Ware_for_delete->parent->left == Ware_for_delete)
//						{
//							Ware_for_delete->parent->left = nullptr;
//							delete Ware_for_delete;
//						}
//						else
//						{
//							Ware_for_delete->parent->right = nullptr;
//							delete Ware_for_delete;
//						}
//					}
//
//				}
//				else if (Ware_for_delete->left != nullptr && Ware_for_delete->right == nullptr)
//				{
//					if (Ware_for_delete->parent == nullptr)
//					{
//						koren = Ware_for_delete->left;
//						delete Ware_for_delete;
//					}
//					else
//					{
//						if (Ware_for_delete->parent->left == Ware_for_delete)
//						{
//							Ware_for_delete->parent->left = Ware_for_delete->left;
//							delete Ware_for_delete;
//						}
//						else
//						{
//							Ware_for_delete->parent->right = Ware_for_delete->right;
//							delete Ware_for_delete;
//						}
//					}
//				}
//				else if (Ware_for_delete->left == nullptr && Ware_for_delete->right != nullptr)
//				{
//					if (Ware_for_delete->parent == nullptr)
//					{
//						koren = Ware_for_delete->right;
//						delete Ware_for_delete;
//					}
//					else
//					{
//						if (Ware_for_delete->parent->right == Ware_for_delete)
//						{
//							Ware_for_delete->parent->right = Ware_for_delete->right;
//							delete Ware_for_delete;
//						}
//						else
//						{
//							Ware_for_delete->parent->left = Ware_for_delete->right;
//							delete Ware_for_delete;
//						}
//					}
//				}
//				else
//				{
//					Ware* tmp = Ware_for_delete->right;
//					while (tmp->left != nullptr)
//					{
//						tmp = tmp->left;
//					}
//
//
//					tmp->left = Ware_for_delete->left;
//					Ware_for_delete->left->parent = tmp->left;
//
//					if (Ware_for_delete->parent != nullptr)
//					{
//						if (Ware_for_delete->parent->left == Ware_for_delete)
//						{
//							Ware_for_delete->parent->left = tmp;
//							delete Ware_for_delete;
//						}
//						else
//						{
//							Ware_for_delete->parent->right = tmp;
//							delete Ware_for_delete;
//						}
//					}
//					else
//					{
//						koren = tmp;
//						delete Ware_for_delete;
//					}
//				}
//			}
//
//			return;
//
//		}
//		if (key < a1->cost_tovar) {// >
//			a1 = a1->left;
//		}
//		else {
//			a1 = a1->right;
//		}
//	}
//	cout << "Немає в дереві елемента з таким ключом\n";
//}
// 
// //
//Color* insertWare(Color* koren, string cur_color, int weight, int cost_tovar, string color)
//{
//	cout << "Потрапило на додаванння" << endl;
//	if (koren == nullptr) 
//	{
//
//		koren = new Color;
//		koren->name_tovar = cur_color;
//		koren->weight = weight;
//		koren->cost_tovar = cost_tovar;
//		koren->color = color;
//		koren->left1 = nullptr;
//		koren->right1 = nullptr;
//		return;
//	}
//	if (cur_color < koren->color) {
//		koren->left1 = insertWare(koren->left1, cur_color, weight, cost_tovar, color);
//	}
//	else if (cur_color > koren->color) {
//
//		koren->right1 = insertWare(koren->right1, cur_color, weight, cost_tovar, color);
//	}
//	return koren;
//}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


