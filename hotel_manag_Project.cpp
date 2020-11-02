#include<iostream>
#include <iomanip>
using namespace std;
//#################################    Structures   #################################
struct list
{
	string dish_type, dish_name;
	int price,cost;
	list* next;
};
struct list2
{
	string dish_name;
	int price,cost;
	list2* next;
};
list2* insertBill(list2 *root, string name, int value, int c_val)
{
	if(root == NULL)
	{
		root = new list2;
		root->dish_name = name;
		root->price = value;
		root->cost = c_val;
		root->next = NULL;
	}
	else
	{
		root->next = insertBill(root->next,name,value,c_val);
	}
	return root;
}
list* insert(list *Root, string type, string name, int value, int c_val)
{
	if(Root == NULL)
	{
		Root = new list;
		Root->dish_type = type;
		Root->dish_name = name;
		Root->price = value;
		Root->cost = c_val;
		Root->next = NULL;
	}
	else
	{
		Root->next = insert(Root->next,type,name,value, c_val);
	}
	return Root;
}
//#################################    AVL Functions   #################################
struct node{
	int value, cnic;
	list2* bills;
	node *right, *left;
	int height;
};
void pre_order(node *temp)
{
	if(temp == NULL)
		cout<<"NO data found!!\n";
	else
	{
		cout << temp->value <<"   "<<endl;
		if(temp->left != NULL)
		{
			pre_order(temp->left);
		}
		if(temp->right != NULL)
		{
			pre_order(temp->right);
		}
	}
	
}

int max(int a, int b)
{
	if(a > b)
	{
		return a;
	}
	else
	{
		return b;
	}	
}
int height(node *temp)
{
	if(temp == NULL)
	{
		return 0;
	}
		
	int lh = height(temp->left);
	int rh = height(temp->right);
		
	if(lh > rh)
	{
		return lh+1;
	}
	else
	{
		return rh+1;
	}
}
	
node *left_rotation(node *temp2)
{
	node *temp1;
	temp1 = temp2->right;
	temp2->right = temp1->left;
	temp1->left = temp2;
		
	temp2->height = max(height(temp2->left), height(temp2->right)) + 1;
	temp1->height = max(height(temp1->left), height(temp1->right)) + 1;
	
	return temp1;
}
	
node *right_rotation(node *temp2)
{
	node *temp1;
	temp1 = temp2->left;
	temp2->left = temp1->right;	
	temp1->right = temp2;
		
	temp2->height = max(height(temp2->left), height(temp2->right)) +1;
	temp1->height = max(height(temp1->left), height(temp1->right)) +1;
		
	return temp1;
}
	
node *right_left_rotation(node *temp3)
{
	temp3->right = right_rotation(temp3->right);
	return left_rotation(temp3);
}
	
node *left_right_rotation(node *temp3)
{
	temp3->left = left_rotation(temp3->left);
	return right_rotation(temp3);
}


node *insertAVL(node *temp, int x, list2* point, int u_cnic)
{
	if(temp == NULL)
	{
		temp = new node();
		temp->cnic = u_cnic;
		temp->value = x;
		temp->bills = point;
		temp->left = temp->right = NULL;
		temp->height = 0;
	}
	if(x < temp->value)
	{
		temp->left = insertAVL(temp->left, x, point,u_cnic);
			
		if(height(temp->left) - height(temp->right) == 2)
		{
			if(x < temp->left->value)
			{
				temp = right_rotation(temp);
			}
			else
			{
				temp = left_right_rotation(temp);
			}
		}
	}
	if(x > temp->value)		
	{  
		temp->right = insertAVL(temp->right, x, point,u_cnic);
			
		if(height(temp->right) - height(temp->left) == 2)
		{
			if(x > temp->right->value)
			{
				temp = left_rotation(temp);
			}
			else
			{
				temp = right_left_rotation(temp);
			}
		}
	}
	temp->height = max(height(temp->left), height(temp->right)) +1 ;
	return temp;
}
node *min(node *temp)
{
	if(temp == NULL)
	{
		return 0;	
	}	
	if(temp->left == NULL)
	{
		return temp;
	}
	else
	{
		min(temp->left);
	}
		
}	
node *balance(node *temp)
{
	if( height(temp->left)-height(temp->right) > 1)
	{
		if(height(temp->left->left) >= height(temp->left->right))
		{ 
			temp =right_rotation(temp);
		}
		else
		{
			temp =left_right_rotation(temp);
		}
	}
	else if( height(temp->right)-height(temp->left) > 1)
	{
		
		if(height(temp->right->right) >= height(temp->right->left))
		{
			temp =left_rotation(temp);
		}
		else
		{
			temp =right_left_rotation(temp);
		}
	}
	temp->height = max(height(temp->left), height(temp->right)) + 1;
	return temp;
}
	
 node *deletion(node *temp, int x)
{
	node *tempcell ;
	if(x < temp->value)
	{  
		temp->left = deletion(temp->left, x);
	}
	else if(x > temp->value)
	{
		temp->right = deletion(temp->right, x);
	}
	else if(temp->left && temp->right)
	{
		tempcell = min(temp->right);
		temp->value = tempcell->value;
		temp->right = deletion(temp->right, temp->value);
	}
	else
	{
		tempcell = temp;
		if(temp->left == NULL)
		{ 
			temp = temp->right;
		}
		else if(temp->right == NULL)
		{
			temp = temp->left;
		}
		delete tempcell;
	}
	if(temp != NULL)
	{
		temp = balance(temp);
	}
		return temp;
}


//#################################    Functions Prototypes   #################################
void main_menu(list* menu_list, node* avl);
void admin_main(list* menu_list, node* avl);
void drinks(list* menu_list, list2* Bill, node* avl);
void order(list* menu_list, list2* Bill, node* avl);
void Paki_food(list* menu_list, list2* Bill, node* avl);
void Chinese_food(list* menu_list, list2* Bill, node* avl);
void bill_fun(list*menu_list, list2* Bill, node* avl);
void table(list2* Bill, node* avl, list*menu_list);
void room(list2* Bill, node* avl, list*menu_list);
void add_food(list* menu_list,node* avl);
void delete_item(list* menu_list, node* avl);
void search_bill(list*menu_list, node* avl);
void profit(list* menu_list, node* avl);
void bill_delete(list* menu_list, node* avl);
//#################################    Display Functions    #################################
void dash(int x, char a)
{
	for (int i = 1; i <= x; i++)
	{
		cout << a;
	}
	cout << endl;
}
void title()
{
	string space_2 = "       ";
	cout << space_2 << " =========================================================================================================================================================   " << endl;
	cout << space_2 << "|    ***    ***   ********   ***********  **********  ***           ********   *********    ********     ********  **********   *********  ***********    |  " << endl;
	cout << space_2 << "|    ***    ***  **********  ***********  **********  ***           *********  **********  **********    ********  **********  **********  ***********    |  " << endl;
	cout << space_2 << "|    ***    ***  ***    ***      ***      ***         ***           ***    **  ***    ***  ***    ***       **     ***         ***             ***        |  " << endl;
	cout << space_2 << "|    **********  ***    ***      ***      ********    ***           ***    **  ***    ***  ***    ***       **     ********    ***             ***        |  " << endl;
	cout << space_2 << "|    **********  ***    ***      ***      ********    ***           ********   *********   ***    ***       **     ********    ***             ***        |  " << endl;
	cout << space_2 << "|    ***    ***  ***    ***      ***      ***         ***           ***        *** **      ***    ***       **     ***         ***             ***        |  " << endl;
	cout << space_2 << "|    ***    ***  **********      ***      **********  ********      ***        ***   **    **********  * *  **     **********  **********      ***        |  " << endl;
	cout << space_2 << "|    ***    ***   ********       ***      **********  ********      ***        ***     **   ********   ******      **********   *********      ***        |  " << endl;
	cout << space_2 << " =========================================================================================================================================================   " << endl;
	cout << endl << endl;
}
void dely_fun()
{
	for(int i = 0; i<1000000; i++)
	{
		for(int j = 0 ; j< 600; j++)
		{}
	}
}
void valid_option()
{
	string space_1 = "                                                                   ";
	cout <<endl<< space_1;
	dash(36, '-');
	cout <<space_1;
	cout<<"|  Please select a valid option!!  |\n";
	cout << space_1;
	dash(36, '-');
}
void option_give(string a, int b)
{
	string space = "                                                                   ";
	cout << space << "|  "<< setw(13) << a <<" |  "<< setw(7) <<"Press "<< b <<"  |" << endl;
	cout << space;
	
}
void D_give(int c, string a, int b, int p)
{
	string space = "                                                                   ";
	cout << space;
	dash(c, '-');
	cout << space << "|  "<< setw(13) << a <<" |  "<<setw(7)<< p <<"  RS |  " <<setw(7) <<"Press "<< b <<"  |" << endl;
	
}
void B_give(int c, string a,  int p)
{
	string space = "                                                                   ";
	cout << space;
	dash(c, '-');
	cout << space << "|  "<< setw(13) << a <<" |  "<<setw(7)<< p <<"     |"<<endl;
	
}
void give_option(int c, string a, string b, int a1, int b1)
{
	string space = "                                                                   ";
	
	cout << space << "|  "<< setw(13) << a <<" |  "<< setw(7) <<"Press "<< a1 <<"  |" << endl;
	cout << space;
	dash(c, '-');
	cout << space << "|  "<< setw(13) << b <<" |  "<< setw(7) <<"Press "<<b1<<"  |" << endl;
	cout << space;
	dash(c, '-');
}

//#################################    Admin Display Functions    #################################
void login(list* menu_list, node* avl)
{
	
	
	string name, password;
	system("cls");
	title();
	string space = "                                                                   ";
	cout << space<< "-------------------    " << endl;
	cout << space<< "|    Email        |    " << endl;
	cout << space<< "-------------------    ";
	cin >> name;

	cout << space<< "------------------    " << endl;
	cout << space<< "|    Password    |" << endl;
	cout << space<< "------------------    ";
	cin >> password;

	if (name == "fahad" && password == "123")
	{
		admin_main(menu_list, avl);
	}
	else
	{
		cout <<endl<< space;dash(40, '-');
		cout <<space;cout<<"|  Please enter a valid Credentials!!  |\n";
		cout << space;dash(40, '-');
		dely_fun();
		main_menu(menu_list, avl);
	}

	
}
int bill_id = 0;
void admin_main(list* menu_list, node* avl)
{
	system("cls");
	title();
	
	string space = "                                                                   ";
	cout << space;
	dash(31, '-');
	give_option(31,"Add Item", "Delete Item",1,2);
	give_option(31,"Search Bill ", "Check Profit",3,4);
	cout << space << "|  "<< setw(12) << "Delete Bill" <<"  |  "<< setw(7) <<"Press "<< "5" <<"  |" << endl;
	cout<<space;dash(31, '-');
	cout << space << "|  "<< setw(12) << "Go Back" <<"  |  "<< setw(7) <<"Press "<< "0" <<"  |" << endl;
	cout << space;
	dash(31, '-');
	
	int admin_option = 0;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> admin_option;
	
	if(admin_option == 1)
		add_food(menu_list, avl);
	else if(admin_option == 2)
		delete_item(menu_list, avl);
	else if(admin_option == 3)
		search_bill(menu_list,avl);
	else if(admin_option == 4)
		profit(menu_list, avl);
	else if(admin_option == 5)
		bill_delete(menu_list, avl);
	else if(admin_option == 0)
		main_menu(menu_list, avl);
	else
	{
		valid_option();
		dely_fun();
		admin_main(menu_list, avl);
	}
}
//#################################    del    #################################
void bill_delete(list* menu_list, node* avl)
{
	system("cls");
	title();
	string space = "                                                                   ";
	int id_bill = -1;
	cout << space<< "---------------------" << endl;
	cout << space<< "|  Enter Bill ID    |    " << endl;
	cout << space<< "---------------------   ";
	cin >> id_bill;
	if(avl == NULL)
	{
		cout << space<< "-----------------------" << endl;
		cout << space<< "|  No Record Found    |    " << endl;
		cout << space<< "-----------------------   ";
		
	}
	else 
	{
		avl = deletion(avl, id_bill);
	
		cout << space<< "----------------------" << endl;
		cout << space<< "|  Record Deleted    |    " << endl;
		cout << space<< "----------------------   ";	
	}
	
	dely_fun();
	admin_main(menu_list, avl);
}
//#################################    Search bill    #################################
int search_id(node* avl, int key)
{
	system("cls");
	title();
	string space = "                                                                   ";
	if(avl == NULL)
	{
		system("cls");
		title();
		string space = "                                                                   ";
		cout << space<< "-----------------------" << endl;
		cout << space<< "|  No Record Found    |    " << endl;
		cout << space<< "-----------------------   ";
		return 1;
	}
	else
	{
		
		if (avl->value == key) 
    	{
    		list2* temp = avl->bills;
    		int total = 0;
    		cout<<space;dash(33, '-');
			cout << space << "|  "<< setw(12) << "Bill id" <<"  |  "<< setw(7)<< avl->value <<"     |" << endl;
			cout<<space;dash(33, '-');
			cout << space << "|  "<< setw(12) << "CNIC" <<"  |  "<< setw(7)<< avl->cnic <<"     |" << endl;
			for(temp; temp != NULL; temp = temp->next)
			{	
				B_give(33, temp->dish_name, temp->price);
				total = total + temp->price;
			}	
			cout<<space;dash(33, '-');
			temp = avl->bills;
			if(temp->dish_name == "Room No")
			{
				cout << space << "|  "<< setw(12) << "Total" <<"  |  "<< setw(7)<< temp->cost <<"  RS |" << endl;
				cout<<space;dash(33,'-');
			}
				
			else if(temp->dish_name == "Table No")
			{}
			else
			{
				cout << space << "|  "<< setw(12) << "Total" <<"  |  "<< setw(7)<< total <<"  RS |" << endl;
				cout<<space;dash(33,'-');
			}
			
			temp = NULL;delete temp;
			return 0;
		}
     
    	else if (avl->value < key) 
	    	return search_id(avl->right, key); 
  		else if(avl->value > key)
    		return search_id(avl->left, key); 
    	else 
    		return 2;
	}
}

void search_bill(list*menu_list, node* avl)
{
	system("cls");
	title();
	string space = "                                                                   ";
	int id_bill = -1;
	cout << space<< "---------------------" << endl;
	cout << space<< "|  Enter Bill ID    |    " << endl;
	cout << space<< "---------------------   ";
	cin >> id_bill;
	int a = search_id(avl, id_bill);
		cout <<endl<<endl<< space << "Press any num key to leave... ";
		cin >> id_bill;
		admin_main(menu_list, avl);	
	
	
	
}
//#################################    Add Food    #################################

void add_food(list* menu_list,node* avl)
{
	system("cls");
	title();
	string space = "                                                                   ";
	
	cout << space;dash(31, '-');
	give_option(31,"Pakistani", "Chinese",1,2);
	give_option(31,"Drinks", "Go Back",3,0);
	int select = -1;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> select;
	if(select == 0)
		admin_main(menu_list, avl);
	else if(select == 1)
	{
		system("cls");
		title();
		cout << space;dash(31, '-');
		give_option(31,"Mutton", "Korma",1,2);
		cout <<endl<<endl<< space << "Please select any option... ";
		select = -1;
		cin >> select;
		if (select == 1)
		{
			menu_list = insert(menu_list, "Pakistani", "Mutton", 890, 700);
			cout << space<< "--------------------------" << endl;
			cout << space<< "|  Added in Menu List    |    " << endl;
			cout << space<< "--------------------------";
			dely_fun();
			admin_main(menu_list, avl);
		}
		else if (select == 2)
		{
			menu_list = insert(menu_list, "Pakistani", "Korma", 450, 300);
			cout << space<< "--------------------------" << endl;
			cout << space<< "|  Added in Menu List    |    " << endl;
			cout << space<< "--------------------------";
			dely_fun();
			admin_main(menu_list, avl);
		}
		else
		{
			valid_option();
			dely_fun();
			add_food(menu_list, avl);
		}
	}
	else if(select == 2)
	{
		system("cls");
		title();
		cout << space;dash(31, '-');
		give_option(31,"Chkn chilli", "Veg Rice",1,2);
		cout <<endl<<endl<< space << "Please select any option... ";
		select = -1;
		cin >> select;
		if (select == 1)
		{
			menu_list = insert(menu_list, "Chinese", "Chkn chilli", 420, 300);
			cout << space<< "--------------------------" << endl;
			cout << space<< "|  Added in Menu List    |    " << endl;
			cout << space<< "--------------------------";
			dely_fun();
			admin_main(menu_list, avl);
		}
		else if (select == 2)
		{
			menu_list = insert(menu_list, "Chinese", "Veg Rice", 450, 300);
			cout << space<< "--------------------------" << endl;
			cout << space<< "|  Added in Menu List    |    " << endl;
			cout << space<< "--------------------------";
			dely_fun();
			admin_main(menu_list, avl);
		}
		else
		{
			valid_option();
			dely_fun();
			add_food(menu_list, avl);
		}
	}
	else if(select == 3)
	{
		system("cls");
		title();
		cout << space;dash(31, '-');
		give_option(31,"Fanta", "Sting",1,2);
		cout <<endl<<endl<< space << "Please select any option... ";
		select = -1;
		cin >> select;
		if (select == 1)
		{
			menu_list = insert(menu_list, "Drinks", "Fanta", 40, 30);
			cout << space<< "--------------------------" << endl;
			cout << space<< "|  Added in Menu List    |    " << endl;
			cout << space<< "--------------------------";
			dely_fun();
			admin_main(menu_list, avl);
		}
		else if (select == 2)
		{
			menu_list = insert(menu_list, "Drinks", "String", 450, 30);
			cout << space<< "--------------------------" << endl;
			cout << space<< "|  Added in Menu List    |    " << endl;
			cout << space<< "--------------------------";
			dely_fun();
			admin_main(menu_list, avl);
		}
		else
		{
			valid_option();
			dely_fun();
			add_food(menu_list, avl);
		}
	}
	
}
//#################################    delete  Food item    #################################
void delete_item(list* menu_list, node* avl)
{
	system("cls");
	title();
	
	string space = "                                                                   ";
	list* temp = menu_list;
	int count = 1;
	for(temp; temp!= NULL; temp = temp->next)
	{
		D_give(46, temp->dish_name, count, temp->price);
		count++;
	}
	int amount =0;
	cout<<space;dash(46, '-');
	cout << space << "|  "<< setw(12) << "Go Back" <<" |  "<< setw(7) <<"Press "<< 0 <<"  |" << endl;
	cout <<space;dash(30, '-');
	cout <<endl<<endl<< space << "Please select any option... ";
	cin>> count;
	
	if(count == 0)
		admin_main(menu_list, avl);
	else if((amount+1) == count)
	{
		list* temp1 = menu_list;
		menu_list = menu_list->next;
		temp1 = NULL;
		delete temp1;
		cout << space<< "--------------------" << endl;
		cout << space<< "|  Item Deleted    |    " << endl;
		cout << space<< "--------------------";
		dely_fun();
		admin_main(menu_list, avl);
		
	}
	else
	{
		temp = menu_list;
		for(temp; temp!= NULL; temp = temp->next)
		{
			amount++;
			if((amount+1) == count)
			{
				list* temp1 = temp->next;
				temp->next = temp1->next;
				temp1 = NULL;
				delete temp1;
				cout << space<< "--------------------" << endl;
				cout << space<< "|  Item Deleted    |    " << endl;
				cout << space<< "--------------------";
				dely_fun();
			}		
		}		
		admin_main(menu_list, avl);
	}
	
}

int food_cost = 0, food_sell = 0, room_rent = 0, total_cost = 0, total_income = 0;
//#################################    Profit Function    #################################
void count_order(list* menu_list, node *temp)
{
	string space = "                                            ";
	if(temp == NULL)
	{
		cout << space<< "---------------------" << endl;
		cout << space<< "|  No Data Found    |    " << endl;
		cout << space<< "---------------------";
		dely_fun();
		admin_main(menu_list, temp);
		
	}
	else
	{
		list2* temp1 = temp->bills;
		for(temp1; temp1 != NULL; temp1 = temp1->next)
		{
			if(temp1->dish_name == "Room No")
			{
				room_rent = room_rent + temp1->cost;
			}
			else
			{
				food_cost = food_cost + temp1->cost;
				food_sell = food_sell + temp1->price;
			}
		}
		
		total_cost = food_cost;
		total_income = food_sell + room_rent;
		
		if(temp->left != NULL)
		{
			count_order(menu_list,temp->left);
		}
		if(temp->right != NULL)
		{
			count_order(menu_list,temp->right);
		}
	}
	
}
void profit(list* menu_list, node* avl)
{
	system("cls");
	title();
	string space = "                                                     ";
	count_order(menu_list,avl);
	cout<<space;dash(56, '-');
	cout << space << "|  "<< setw(12) << "Products" <<" |  "<< setw(7) <<"Total sales"<<"  |"<< setw(7) <<"Total Cost"<<"  |"<< setw(7)<<"Profit" <<"  |"<<endl;
	cout<<space;dash(56, '-');
	cout << space << "|  "<< setw(12) << "Food items" <<" |  "<< setw(7) <<food_sell<<"      |"<< setw(7) <<food_cost<<"     |"<< setw(7)<<(food_sell - food_cost) <<"  |"<<endl;
	cout<<space;dash(56, '-');
	cout << space << "|  "<< setw(12) << "Rooms" <<" |  "<< setw(7) <<0<<"      |"<< setw(7) <<room_rent<<"     |"<< setw(7)<<room_rent<<"  |"<<endl;
	cout<<space;dash(56, '-');
	cout << space << "|  "<< setw(12) << "Total" <<" |  "<< setw(7) <<total_income<<"      |"<< setw(7) <<total_cost<<"     |"<< setw(7)<<(total_income - total_cost )<<"  |"<<endl;
	cout<<space;dash(56, '-');
	cout <<endl<<endl<< space << "Please select any option... ";
	int count =0;
	cin>> count;
	if(count == 0)
		admin_main(menu_list, avl);
	else 
		admin_main(menu_list, avl);
	
}
//#################################    Customer Display Functions    #################################
void customer_main(list* menu_list, list2* Bill, node* avl)
{
	system("cls");
	title();
	
	string space = "                                                                   ";
	cout << space;dash(31, '-');
	give_option(31,"Order Food", "Book Table",1,2);
	give_option(31,"Book Room", "Go Back",3,4);
	
	
	int customer_option = 0;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> customer_option;
	
	if(customer_option == 1)
		order(menu_list, Bill, avl);
	else if(customer_option == 2)
		table(Bill, avl,menu_list);
	else if(customer_option == 3)
		room(Bill,avl, menu_list);
	else if(customer_option == 4)
		main_menu(menu_list, avl);
	else
	{
		valid_option();
		dely_fun();
		customer_main(menu_list, Bill, avl);
	}
}
//#################################    book Table    #################################
int table_id = 10;
int room_id = 20;
void room(list2* Bill, node* avl, list*menu_list)
{
	system("cls");
	title();
	string space = "                                                                   ";
	list2* temp = new list2;

	temp->dish_name = "Room No";
	temp->cost = 15000;
	temp->price = room_id;
	int cnic;

	
	cout << space<< "-------------------    " << endl;
	cout << space<< "|  Enter  CNIC    |    " << endl;
	cout << space<< "-------------------    ";
	cin >> cnic;
	if(room_id<=40)
	{
		system("cls");
		title();
	
		Bill = insertBill(Bill, temp->dish_name, temp->price, temp->cost);
		B_give(33, "Bill ID", bill_id);
		B_give(33, "CNIC", cnic);
		B_give(33, temp->dish_name, temp->price);
		B_give(33, "Rent", 15000);
		cout<<space;dash(33,'-');
	
		avl = insertAVL(avl, bill_id, Bill, cnic);
	//	pre_order(avl);
		bill_id++;
		room_id++;
		
		cout <<endl<<endl<< space << "Press any num key to leave... ";
		int leave = 0;
		cin >> leave;
		if (leave == 1)
			main_menu(menu_list, avl);
		else 
			main_menu(menu_list, avl);
	}
	else
	{
		system("cls");
		title();
		cout << space<< "-------------------------" << endl;
		cout << space<< "|  All Room reserved  |" << endl;
		cout << space<< "-------------------------";
		dely_fun();
		main_menu(menu_list, avl);
	}
	

}
void table(list2* Bill, node* avl, list*menu_list)
{
	system("cls");
	title();
	string space = "                                                                   ";
	list2* temp = new list2;

	temp->dish_name = "Table No";
	temp->cost = 0;
	temp->price = table_id;
	int cnic;

	
	cout << space<< "-------------------    " << endl;
	cout << space<< "|  Enter  CNIC    |    " << endl;
	cout << space<< "-------------------    ";
	cin >> cnic;
	if(table_id<=20)
	{
		system("cls");
		title();
	
		Bill = insertBill(Bill, temp->dish_name, temp->price, temp->cost);
		B_give(33, "Bill ID", bill_id);
		B_give(33, "CNIC", cnic);
		B_give(33, temp->dish_name, temp->price);
		cout<<space;dash(33,'-');
	
		avl = insertAVL(avl, bill_id, Bill, cnic);
	//	pre_order(avl);
		bill_id++;
		table_id++;
		
		cout <<endl<<endl<< space << "Press any num key to leave... ";
		int leave = 0;
		cin >> leave;
		if (leave == 1)
			main_menu(menu_list, avl);
		else 
			main_menu(menu_list, avl);
	}
	else
	{
		system("cls");
		title();
		cout << space<< "-------------------------" << endl;
		cout << space<< "|  All Tables reserved  |" << endl;
		cout << space<< "-------------------------";
		dely_fun();
		main_menu(menu_list, avl);
	}
	

}
//#################################    get order    #################################
void order(list* menu_list, list2* Bill, node* avl)
{
	system("cls");
	title();
	
	string space = "                                                                   ";
	cout << space;
	dash(31, '-');
	give_option(31,"Pakisani Food", "Chinese Food",1,2);
	option_give("Drinks", 3);
	dash(31, '-');
	option_give("Go Back", 4);
	dash(31, '-');
	
	
	int order_type = 0;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> order_type;
	
	if(order_type == 1)
		Paki_food(menu_list, Bill,avl);
	else if(order_type == 2)
		Chinese_food(menu_list, Bill,avl);
	else if(order_type == 3)
		drinks(menu_list, Bill,avl);
	else if(order_type == 4)
		customer_main(menu_list, Bill, avl);	
	else
	{
		valid_option();
		dely_fun();
		order(menu_list, Bill, avl);
	}
}


void Paki_food(list* menu_list, list2* Bill, node* avl)
{
	string space = "                                                                   ";
	list* temp = menu_list;
	system("cls");
	title();
	int count = 1, check = 0, amount = 0;
	for(temp; temp != NULL; temp = temp->next)
	{
		if(temp->dish_type == "Pakistani")
		{
			D_give(46, temp->dish_name, count, temp->price);
			count++;
			check++;
		}
	}
	if(check == 0)
	{
		string space_1 = "                                                                   ";
		cout <<endl<< space_1;
		dash(20, '-');
		cout <<space_1;
		cout<<"|   No Item Found  |\n";
		cout << space_1;
		dash(20, '-');
		dely_fun();
		order(menu_list, Bill, avl);
	}
	else
	{
		cout<<space;dash(46, '-');
		cout << space << "|  "<< setw(12) << "Go Back" <<" |  "<< setw(7) <<"Press "<< 0 <<"  |" << endl;
		cout<<space;dash(30, '-');
	}
	int enter = -1;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> enter;
	
	temp = menu_list;
	if(enter == 0)
	{
		order(menu_list, Bill, avl);
	}
	else
	{
		for(temp; temp != NULL; temp = temp->next)
		{
			if(temp->dish_type == "Pakistani")
			{
				amount++;
				if(amount == enter)
				{
					Bill = insertBill(Bill, temp->dish_name, temp->price, temp->cost);
				}
			}
		}
	}
	system("cls");
	title();
	cout<<space;dash(32,'-');
	give_option(31,"Menu", "Bill",1,2);
	enter = 0;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> enter;
	
	if(enter == 1)
	{
		order(menu_list, Bill, avl);
	}
	else
		bill_fun(menu_list,Bill, avl);
	
}

void Chinese_food(list* menu_list, list2* Bill, node* avl)
{
	string space = "                                                                   ";
	list* temp = menu_list;
	system("cls");
	title();
	int count = 1, check = 0,amount = 0;
	for(temp; temp != NULL; temp = temp->next)
	{
		if(temp->dish_type == "Chinese")
		{
			D_give(46, temp->dish_name, count, temp->price);
			count++;
			check++;
		}
	}
	if(check == 0)
	{
		string space_1 = "                                                                   ";
		cout <<endl<< space_1;
		dash(20, '-');
		cout <<space_1;
		cout<<"|   No Item Found  |\n";
		cout << space_1;
		dash(20, '-');
		dely_fun();
		order(menu_list, Bill,avl);
	}
	else
	{
		cout<<space;dash(46, '-');
		cout << space << "|  "<< setw(12) << "Go Back" <<" |  "<< setw(7) <<"Press "<< 0 <<"  |" << endl;
		cout<<space;dash(30, '-');
	}
	
	int enter = -1;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> enter;
	
	temp = menu_list;
	if(enter == 0)
	{
		order(menu_list, Bill, avl);
	}
	else
	{
		for(temp; temp != NULL; temp = temp->next)
		{
			if(temp->dish_type == "Chinese")
			{
				amount++;
				if(amount == enter)
				{
					Bill = insertBill(Bill, temp->dish_name, temp->price, temp->cost);
				}
			}
		}
	}
	system("cls");
	title();
	cout<<space;dash(32,'-');
	give_option(31,"Menu", "Bill",1,2);
	enter = 0;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> enter;
	
	if(enter == 1)
	{
		order(menu_list, Bill,avl);
	}
	else
		bill_fun(menu_list,Bill, avl);

}
void drinks(list* menu_list, list2* Bill, node* avl)
{
	string space = "                                                                   ";
	list* temp = menu_list;
	system("cls");
	title();
	int count = 1, check = 0,amount = 0;
	for(temp; temp != NULL; temp = temp->next)
	{
		if(temp->dish_type == "Drinks")
		{
			D_give(46, temp->dish_name, count, temp->price);
			count++;
			check++;
		}
	}
	if(check == 0)
	{
		string space_1 = "                                                                   ";
		cout <<endl<< space_1;
		dash(20, '-');
		cout <<space_1;
		cout<<"|   No Item Found  |\n";
		cout << space_1;
		dash(20, '-');
		dely_fun();
		order(menu_list, Bill, avl);
	}
	else
	{
		cout<<space;dash(46, '-');
		cout << space << "|  "<< setw(12) << "Go Back" <<" |  "<< setw(7) <<"Press "<< 0 <<"  |" << endl;
		cout<<space;dash(30, '-');
	}
	int enter = -1;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> enter;
	
	temp = menu_list;
	if(enter == 0)
	{
		order(menu_list, Bill, avl);
	}
	else
	{
		for(temp; temp != NULL; temp = temp->next)
		{
			if(temp->dish_type == "Drinks")
			{
				amount++;
				if(amount == enter)
				{
					Bill = insertBill(Bill,temp->dish_name, temp->price, temp->cost);
				}
			}
		}
	}
	system("cls");
	title();
	cout<<space;dash(32,'-');
	give_option(31,"Menu", "Bill",1,2);
	enter = 0;
	cout <<endl<<endl<< space << "Please select any option... ";
	cin >> enter;
	
	if(enter == 1)
	{
		order(menu_list, Bill, avl);
	}
	else
		bill_fun(menu_list,Bill, avl);

}
//#################################   Bill Function    #################################
void bill_fun(list*menu_list, list2* Bill, node* avl)
{
	string space = "                                                                   ";
	system("cls");title();
	list2* temp = Bill;
	int total = 0;
	if(temp == NULL)
	{
		cout<<"No data";
	}
	else
	{
		cout<<space;dash(33, '-');
		cout << space << "|  "<< setw(12) << "Bill id" <<"  |  "<< setw(7)<< bill_id <<"     |" << endl;
		for(temp; temp != NULL; temp = temp->next)
		{	
			B_give(33, temp->dish_name, temp->price);
			total = total + temp->price;
		}	
	}
	cout<<space;dash(33, '-');
	cout << space << "|  "<< setw(12) << "Total" <<"  |  "<< setw(7)<< total <<"  RS |" << endl;
	cout<<space;dash(33,'-');

	avl = insertAVL(avl, bill_id, Bill, 0);
	temp = Bill = NULL;
	cout <<endl<<endl<< space << "Press any num key to leave... ";
	int leave = 0;
	cin >> leave;
	bill_id ++;
	if (leave == 1)
		main_menu(menu_list, avl);
	else 
		main_menu(menu_list, avl);
}
//#################################   First display Function    #################################
void main_menu(list* menu_list, node* avl)
{
	system("cls");
	title();
	string space = "                                                                   ";
	
//	pre_order(avl);
	
	list2* Bill = NULL;
	
	cout << space;
	dash(31, '-');
	give_option(31,"Admin", "Customer",1,2);
	cout <<endl<<endl<< space << "Please select any option... ";
	int login_option = 0;
	cin >> login_option;
	
	if(login_option == 1)
	{
		login(menu_list, avl);
	}
	else if(login_option == 2)
	{
		customer_main(menu_list, Bill, avl);
	}
	else
	{
		valid_option();
		dely_fun();
		main_menu(menu_list, avl);
	}
		
}

//#################################   Main Function    #################################
int main()
{
	list *menu_list = NULL;
	node *avl = NULL;
	menu_list = insert(menu_list, "Pakistani", "Briyani", 320, 200);
	menu_list = insert(menu_list, "Pakistani", "Chickn Karahi", 590, 350);
	menu_list = insert(menu_list, "Pakistani", "Sekh Kabab", 400, 300);
	menu_list = insert(menu_list, "Chinese", "Chowmein", 380, 300);
	menu_list = insert(menu_list, "Chinese", "Fried Rise", 350, 300);
	menu_list = insert(menu_list, "Chinese", "Manchorian", 410, 350);
	menu_list = insert(menu_list, "Drinks", "Pepsi", 40, 30);
	menu_list = insert(menu_list, "Drinks", "Coke", 45, 35);
	menu_list = insert(menu_list, "Drinks", "Dew", 30, 25);
	main_menu(menu_list, avl);
	return 0;
}
