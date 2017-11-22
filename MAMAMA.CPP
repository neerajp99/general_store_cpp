#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<iomanip.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>

void greet();
void plines();
void employee();
void customer();
int SearchByIno(char fname[80], int iNo, int k, int quantity);
int MatchPriceByIno(char fname[80], int iNo);
char* MatchNameByIno(char fname[80], int iNo);


char filName[50] = "wakawaka.dat";
char cart[50] = "cart.dat";

int validateName(char temp[80])
{
   if(!(isalpha(temp[0])))
       return 0;
   for(int i = 1; i < strlen(temp); i++)
   {
      if(!(isdigit(temp[i]) || isalpha(temp[i]) || (temp[i] == ' ')))
	  return 0;
   }
   return 1;
}
int validateNum(char temp[80])
{
   for(int i = 0; i < strlen(temp); i++)
   {
      if(isdigit(temp[i]))
	 	continue;
      else
      {
	 	return 0;
      }
   }
   return 1;
}
int atoi(char temp[80])
{
	int num = 0, cnt = strlen(temp)-1;
	for(int i = 0; i < strlen(temp) ; i++)
	{
		num += pow(10, cnt) * (temp[i]-'0');
		cnt--;
	}
	return num;
}
void clrstr(char temp[80])
{
	int len = strlen(temp);
	for(int i = 0; i < len; i++)
	{
		temp[i] = '\0';
	}
}
class ITEM
{
   int number, quantity, price;
   char name[50];
   public:
      ITEM()
      {
		  number = 0;
		  strcpy(name, "Default");
		  price = 0;
		  quantity = 0;
      }
      void getPrice()
      {
		 cout << "Enter Price of the item: ";
		 char tmp[80];
		 gets(tmp);
		 if(validateNum(tmp) == 0)
		 {
			cout << "Wrong Input! Please enter again" << endl;
			clrstr(tmp);
			getPrice();
			return;
		 }
		 price = atoi(tmp);
      }
      void getName()
      {
		 cout << "Enter name of the item: ";
		 gets(name);
		 if(validateName(name) == 0)
		 {
		      cout << "Wrong Input! Please enter again" << endl;
		      clrstr(name);
		      getName();
		      return;
		 }
      }
      void getNumber()
      {
		 cout << "Enter item number: ";
		 char tmp[80];
		 gets(tmp);
		 if(validateNum(tmp) == 0)
		 {
			cout << "Wrong Input! Please enter again" << endl;
			clrstr(tmp);
			getNumber();
			return;
		 }
		 number = atoi(tmp);
      }
      void getQuantity()
      {
		 cout << "Enter the quantity: ";
		 char tmp[80];
		 gets(tmp);
		 if(validateNum(tmp) == 0)
		 {
			cout << "Wrong Input! Please enter again" << endl;
			clrstr(tmp);
			getQuantity();
			return;
		 }
		 quantity = atoi(tmp);
      }
      void getITEM()
      {
		getNumber();
		getName();
		getPrice();
		getQuantity();
      }
      void getITEMCust()
      {
      	getNumber();
      	int val = SearchByIno(filName, number, -1);
      	while(val == 0)
      	{
      		cout << "No such item exists! Please try again." << endl;
      		getNumber();
      		val = SearchByIno(filName, number, -1);
      	}
      	getQuantity();
      	while(quantity == 0)
      	{
      		cout << "Quantity cannot be zero! Enter again." << endl;
      		getQuantity();
      	}
      	val = SearchByIno(filName, number, 3, quantity);
      	while(val == 0)
      	{
      		cout << "Not enough items available! Please enter a quantity below the available amount." << endl;
      		getQuantity();
      		val = SearchByIno(filName, number, 3, quantity);
      	}
      	strcpy(name, MatchNameByIno(filName, number));
      	price = MatchPriceByIno(filName, number);

      }
      void displayITEM()
      {
		 cout << "ITEM NO: " << number << endl;
		 cout << "ITEM NAME: " << name << endl;
		 cout << "ITEM PRICE: " << price << endl;
		 cout << "ITEM QUANTITY: " << quantity << endl;
      }
      float retPrice()
      {
	 	return price;
      }
      char* retName()
      {
	 	return name;
      }
      int retNumber()
      {
	 	return number;
      }
      int retQuantity()
      {
	 	return quantity;
      }
      void modifyPrice(int p)
      {
	 	price = p;
      }
      void modifyQuantity(int q)
      {
	 	quantity = q;
      }
};

void display(char fname[50])
{
   fstream fil;
   fil.open(fname, ios::in|ios::binary);
   ITEM item;
   while(fil.read((char*)&item, sizeof(item)))
   {
     item.displayITEM();
     cout << endl;
   }
   fil.close();
}

void clrfil(char fname[80])
{
   fstream fil;
   fil.open(fname, ios::out|ios::binary);
   fil.close();
}
void create()
{
   fstream fil;
   fil.open("wakawaka.dat", ios::app|ios::binary);
   ITEM item;
   char ch;
   do
   {
      clrscr();
      item.getITEM();
      fil.write((char*)&item, sizeof(item));
      cout << "Do you want to enter new items? (Y/N)" << endl;
      cin >> ch;
   } while(ch == 'Y');
   fil.close();
}

void createCart()
{
   fstream fil;
   fil.open("cart.dat", ios::app | ios::binary);
   ITEM item;
   char ch;
   int number, quantity;
   do
   {
		clrscr();
		item.getITEMCust();
		fil.write((char*)&item, sizeof(item));
		cout << "Do you want to enter new items? (Y/N)" << endl;
		cin >> ch;
   } while(ch == 'Y');
   fil.close();
}

void transfer(char f1[50], char f2[50])
{
   fstream fil, lif;
   fil.open(f1, ios::out | ios::binary);
   lif.open(f2, ios::in | ios::binary);
   ITEM item;
   while(lif.read((char*)&item, sizeof(item)))
   {
       fil.write((char*)&item, sizeof(item));
   }
   fil.close();
   lif.close();
}

void sortByPrice(char c)
{
   char fname[50];
   if(c == 'a')
       strcpy(fname, "sortedAsc.dat");
   else if(c == 'd')
       strcpy(fname, "sortedDesc.dat");
   else
       return;
   transfer(fname, "wakawaka.dat");
   fstream fil;
   fil.open(fname, ios::binary | ios::in | ios::out);
   ITEM item1, item2;
   fil.seekg(0, ios::end);
   int n = fil.tellg()/sizeof(item1);
   for(int i = 0; i < n-1; i++)
   {
       for(int j = 0; j < n-i-1; j++)
       {
		   fil.seekg(j*sizeof(item1));
		   fil.read((char*)&item1, sizeof(item1));
		   fil.read((char*)&item2, sizeof(item2));
		   if(c == 'a')
		   {
		     if(item1.retPrice() > item2.retPrice())
		     {
				fil.seekp(j*sizeof(item1));
				fil.write((char*)&item2, sizeof(item2));
				fil.write((char*)&item1, sizeof(item1));
		     }
		   }
		   else if(c == 'd')
		   {
		       if(item1.retPrice() < item2.retPrice())
		       {
				  fil.seekp(j*sizeof(item1));
				  fil.write((char*)&item2, sizeof(item2));
				  fil.write((char*)&item1, sizeof(item1));
		       }
		   }
       }
   }
   display(fname);
   fil.close();
}

void SearchByName(char iName[])
{
   fstream fil;
   int fnd = 0;
   fil.open("wakawaka.dat", ios::in | ios::binary);
   ITEM item;
   while(!fil.eof() && !fnd)
   {
      fil.read((char*)&item, sizeof(item));
      if(strcmpi(item.retName(), iName) == 0)
      {
		 item.displayITEM();
		 fnd = 1;
      }
   }
   if(!fnd)
      cout << "ITEM not found!" << endl;
   fil.close();
}

int SearchByIno(char fname[80], int iNo, int k, int quantity = 0)
{
   fstream fil;
   int fnd = 0;
   fil.open(fname, ios::in | ios::out | ios::binary);
   ITEM item;
   while(!fil.eof() && !fnd)
   {
      fil.read((char*)&item, sizeof(item));
      if(item.retNumber() == iNo)
      {
		 if(k == 0)
		 {
		    item.displayITEM();
		 }
		 else if(k == 1)
		 {
		    int nPrice;
		    cout << "Enter new price of " << item.retName() << " : ";
		    cin >> nPrice;
		    item.modifyPrice(nPrice);
		    int pos = fil.tellg();
		    fil.seekp(pos - sizeof(item));
		    fil.write((char*)&item, sizeof(item));
		 }
		 else if(k == 2)
		 {
		    int nQuantity;
		    cout << "Enter new quantity of " << item.retName() << " : ";
		    cin >> nQuantity;
		    item.modifyQuantity(nQuantity);
		    int pos = fil.tellg();
		    fil.seekp(pos - sizeof(item));
		    fil.write((char*)&item, sizeof(item));
		 }
		 else if(k == 3)
		 {
		 	if(quantity > item.retQuantity())
		 		return 0;
		 	else
		 		return 1;
		 }
		 else if(k == 4)
		 {
		 	item.modifyQuantity(item.retQuantity() - quantity);
		 	int pos = fil.tellg();
		    fil.seekp(pos - sizeof(item));
		    fil.write((char*)&item, sizeof(item));
		 }
		 fnd = 1;
      }
   }
   if(!fnd)
      cout << "Record not found!" << endl;
   fil.close();
   return fnd;
}

char* MatchNameByIno(char fname[80], int iNo)
{
   fstream fil;
   int fnd = 0;
   fil.open(fname, ios::in | ios::binary);
   ITEM item;
   while(!fil.eof() && !fnd)
   {
      fil.read((char*)&item, sizeof(item));
      if(item.retNumber() == iNo)
      {
      	 fil.close();
		 return item.retName();
      }
   }
   return "Default";
}

int MatchPriceByIno(char fname[80], int iNo)
{
   fstream fil;
   int fnd = 0;
   fil.open(fname, ios::in | ios::binary);
   ITEM item;
   while(!fil.eof() && !fnd)
   {
      fil.read((char*)&item, sizeof(item));
      if(item.retNumber() == iNo)
      {
      	 fil.close();
		 return item.retPrice();
      }
   }
   return 0;
}

void del(char fname[80], int iNo)
{
   fstream fil1, fil2;
   int fnd = 0;
   fil1.open(fname, ios::in | ios::binary);
   fil2.open("modified.dat", ios::out | ios::binary);
   ITEM item;
   while(fil1.read((char*)&item, sizeof(item)))
   {
      if(item.retNumber() != iNo)
      {
		fil2.write((char*)&item, sizeof(item));
      }
      else
	 fnd = 1;
   }
   fil1.close();
   fil2.close();
   if(!fnd)
      cout << "Record not found!" << endl;
   else
   {
       transfer(fname, "modified.dat");
       cout << "Record deleted!" << endl;
   }
}
int isEmpty(char fname[80])
{
	fstream fil;
	fil.open(fname, ios::in | ios::binary);
	int cnt = 0;
	ITEM item;
	while(fil.read((char*)&item, sizeof(item)))
		cnt++;
	if(cnt == 0)
		return 1;
	else
		return 0;
}

void deduct()
{
	fstream fil;
	fil.open(cart, ios::in | ios::binary);
	ITEM item;
	while(fil.read((char*)&item, sizeof(item)))
	{
		SearchByIno(filName, item.retNumber(), 4, item.retQuantity());
	}
	fil.close();
}
int generateBill()
{
	int billAmount = 0;
	fstream fil;
	fil.open(cart, ios::in | ios::binary);
	ITEM item;
	while(fil.read((char*)&item, sizeof(item)))
	{
		billAmount += item.retQuantity() * item.retPrice();
	}
	return billAmount;
}
void options()
{
	char x, c;
   	int iNo;
  	do
  	{
		cout << "Display inventory (D)\nAdd items (A)\nDelete an item(B)\nSort by Price (X)\nSearch by Name (N)\nSearch by Item No (I)\nModify Price by Item No (M)\nModify quantity by Item No (Q)\nClear Contents (C)" << endl;
	 	cin >> c;
	 	c = toupper(c);
		switch(c)
		{
			case 'D':
				if(isEmpty(filName))
					cout << "The inventory is empty! Please add some items." << endl;
				else
					display(filName);
				break;
			case 'A':
				create();
				break;
			case 'B':
				display(filName);
				cout << "Enter the item number to be deleted: ";
				cin >> iNo;
				del(filName, iNo);
				display(filName);
				break;
			case 'X':
				clrscr();
				char Sc;
				int done = 1;
				do 
				{
				clrscr();
				if(done == 0)
				  cout << "Invalid Input! Please enter again!" << endl;
				clrscr();
				done = 1;
				cout << "Choose:\n  Ascending (A)\n  Descending (D)" << endl;
				cin >> Sc;
				Sc = toupper(Sc);
				if(Sc == 'A')
				   sortByPrice('a');
				else if(Sc == 'D')
				   sortByPrice('d');
				else
				   done = 0;
				} while(done == 0);
				break;
			case 'N':
				char iName[50];
				int Nc = 0;
				do
				{
				if(Nc == 1)
				{
					cout << "Wrong Input! Please enter again" << endl;
					clrstr(iName);
				}
				clrscr();
				cout << "Enter the item name to search for: ";
				gets(iName);
				Nc = 1;
				} while(validateName(iName) == 0);
				SearchByName(iName);
				break;
			case 'I':
				char tmpI[80];
				int Ic = 0;
				do
				{
				if(Ic == 1)
				{
					cout << "Wrong Input! Please enter again" << endl;
					clrstr(tmpI);
				}
				clrscr();
				cout << "Enter the item number to search for: ";
				gets(tmpI);
				Ic = 1;
				} while(validateNum(tmpI) == 0);
				iNo = atoi(tmpI);
				SearchByIno(filName, iNo, 0);
				break;
			case 'M':
				char tmpM[80];
				int Mc = 0;
				do
				{
				if(Mc == 1)
				{
					cout << "Wrong Input! Please enter again" << endl;
					clrstr(tmpM);
				}
				clrscr();
				cout << "Enter the item number to modify price of: ";
				gets(tmpM);
				Mc = 1;
				} while(validateNum(tmpM) == 0);
				iNo = atoi(tmpM);
				SearchByIno(filName, iNo, 1);
				break;
			case 'Q':
				char tmpQ[80];
				int Qc = 0;
				do
				{
				if(Qc == 1)
				{
					cout << "Wrong Input! Please enter again" << endl;
					clrstr(tmpQ);
				}
				clrscr();
				cout << "Enter the item number to modify quantity of: ";
				gets(tmpQ);
				Qc = 1;
				} while(validateNum(tmpQ) == 0);
				iNo = atoi(tmpQ);
				SearchByIno(filName, iNo, 2);
				break;
			case 'C':
				clrfil(filName);
				break;
			default:
				 cout << "Invalid choice! Please try again." << endl;
		}
		cout << "Do you want to continue? (Y/N)" << endl;
		cin >> x;
		x = toupper(x);
		clrscr();
	} while(x == 'Y');
}

void wakawaka()
{
	char c;
	greet();
	int done = 1;
	do
	{
		if(done == 0)
			cout << "Wrong Input! Please enter again" << endl;
		done = 1;
		cout << "Are you a:\n  Customer (C)\n  Employee (E)\n";
		cin >> c;
		c = toupper(c);
		if(c == 'C')
			customer();
		else if(c == 'E')
			employee();
		else
			done = 0;
	} while(done == 0);
}
void main()
{
   clrscr();
   wakawaka();
   getch();
}

void mainmenu()
{
	int done = 1;
	char c;
	do
	{
		if(done == 0)
		{
			cout << "Wrong Input! Please enter again" << endl;
		}
		done = 1;
		cout << "Would you like to go back to the main menu? (Y/N)" << endl;
		cin >> c;
		c = toupper(c);
		if(c == 'Y')
			main();
		else if(c == 'N')
			exit(0);
		else
			done = 0;
	} while(done == 0);
}
void employee()
{
	char pass[80];
	cout << "Enter the employee password: "; 
	gets(pass);
	if(strcmp(pass, "wakawakastore") == 0)
	{
		options();
		mainmenu();
	}
	else
	{
		cout << "Wrong Password! Access Denied" << endl;
		getch();
		main();
	}
}

void customer()
{
	clrscr();
	fstream fil;
	fil.open(cart, ios::out | ios::binary);
	greet();
	char c, x;
	do
	{
		int iNo;
		cout << "Display available items (D)\nShow cart (S)\nAdd items to cart (A)\nDelete items from cart (B)\nModify quantity by Item No (Q)\nClear Cart (C)\nGenerate Bill (G)" << endl;
		cin >> c;
		switch(c)
		{
			case 'D':
				display(filName);
				break;
			case 'S':
				if(isEmpty(cart))
					cout << "Your cart is empty! Please add some items." << endl;
				else
					display(cart);
				break;
			case 'A':
				createCart();
				break;
			case 'B':
				display(cart);
				cout << "Enter the item number to be deleted: ";
				cin >> iNo;
				del(cart, iNo);
				display(cart);
				break;
			case 'Q':
				char tmpQ[80];
				int Qc = 0;
				do
				{
				if(Qc == 1)
				{
					cout << "Wrong Input! Please enter again" << endl;
					clrstr(tmpQ);
				}
				clrscr();
				cout << "Enter the item number to modify quantity of: ";
				gets(tmpQ);
				Qc = 1;
				} while(validateNum(tmpQ) == 0);
				iNo = atoi(tmpQ);
				SearchByIno(cart, iNo, 2);
				break;
			case 'C':
				clrfil(cart);
				break;
			case 'G':
				if(isEmpty(cart))
					cout << "Your cart is empty! Please add some items." << endl;
				else
				{
					int billAmount = generateBill();
					cout << "Your total bill amount is: " << billAmount << ". Do you wish to check out? (Y/N)" << endl;
					cin >> c;
					if(c == 'Y')
					{
						cout << "Thank you for shopping!" << endl;
						deduct();
						clrfil(cart);
						getch();
						main();
						return;
					}
				}
				break;
			default:
				 cout << "Invalid choice! Please try again." << endl;
		}
		cout << "Do you want to continue? (Y/N)" << endl;
		cin >> x;
		x = toupper(x);
		clrscr();
	} while(x == 'Y');
	mainmenu();
}
void plines(int n)
{
   for(int i = 0; i < n; i++)
   {
       cout << "_";
   }
   cout << endl;
}
void greet()
{
   plines(80);
   cout << setw(50) << "WELCOME TO WAKA WAKA STORE!" << endl;
   plines(80);
}