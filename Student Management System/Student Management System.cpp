#include<iostream>
#include<fstream>
#include<string> 
#include<string.h>
using namespace std;

//This is the structure of the Node of the linked list 
struct node{
	node* prev;
	string firstname,lastname,fname,email,address,degree,phone_no;
	int age,id,fee,semester;
	float cgpa,attendance;
	node* next;
};

//This is the implementation of the class 
class LinkedList{
	    string Username,Password;
	    node* head;
	public:
		//Null Constructors
		LinkedList()
		{
			head=NULL;
		}
		//This function returns the head of the linked list
		node* get_head()
		{
			return head;
		}
		
		//This function reads the user credetinlas from the file
		void ReadUser()
		{
			fstream file;
			file.open("User.txt",ios::in);
			if(file.fail())
			{
				cout<<"\nFile Not Open \n";
			}
			else
			{
				file>>this->Username;
				file>>this->Password;
			}
			file.close();
		}
		
		//This function checks whether the user exits in the file or not
		bool CheckUser()
		{
			string n,p;
			int res1,res2;
			cout<<"\nEnter the Username: ";
			cin>>n;
			cout<<"\nEnter the Password: ";
			cin>>p;
			res1 = n.compare(Username);
			res2 = p.compare(Password);
			if(res1 == 0 && res2 == 0)
			{
				return true;
			}
			else if(res1 != 0)
			{
				cout<<"\nUser Not Found \n";
				return false;
			}
			else if(res2 != 0)
			{
				cout<<"\nIncorrect Password \n";
				return false;
			}
			else
			{
				cout<<"\nIncorrect Username or Password \n";
			}
		}
	    
	    //This function takes input untill "Yes" is entered by the user
		void add() 
		{
			char choice;
			do{
				node* temp = set_data();
			    add_node(temp);
			    cout<<"\nDo you want to Add more record (y/n): ";
			    cin>>choice;
			    cin.ignore();
			    cout<<endl;
			}while(choice=='y');
		}
		
		//This function takes the input from the user
		node* set_data()
		{
			node* temp=new node();
			cout<<"Enter the Student's Information: \n";
			cout<<"Enter First Name: ";
			getline(cin,temp->firstname);
			cout<<"Enter Last Name: ";
			getline(cin,temp->lastname);
			cout<<"Enter ID: ";
			cin>>temp->id;
			cin.ignore();
			cout<<"Enter Father Name: ";
			getline(cin,temp->fname);
			cout<<"Enter Age: ";
			cin>>temp->age;
			cin.ignore();
			cout<<"Enter Email: ";
			getline(cin,temp->email);
			cout<<"Enter Phone No.: ";
			getline(cin,temp->phone_no);
			cout<<"Enter House Address: ";
			getline(cin,temp->address);
			cout<<"Enter Degree/Program: ";
			getline(cin,temp->degree);
			cout<<"Enter Semester: ";
			cin>>temp->semester;
			cout<<"Enter CPGA: ";
			cin>>temp->cgpa;
			cout<<"Enter Attendance: ";
			cin>>temp->attendance;
			cout<<"Enter Fee: ";
			cin>>temp->fee;
			cin.ignore();
			return temp;
			
		}
		
		//This function adds the node in the linked list 
		void add_node(node* temp)
		{
			node* tail = new node;
			temp->next=NULL;
			if(head==NULL)
			{
				temp->prev=NULL;
				head=temp;
			}
			else
			{
				tail=head;
				while(tail->next!=NULL)
				{
					tail=tail->next;
				}
				tail->next=temp;
				temp->prev=tail;
			}
		}
		
		//This function writes the data into the file
		void write(node* temp)
		{
			fstream file;
			file.open("Database.txt",ios::app);
			if(file.fail())
			{
				cout<<"\nFile NOT Open\n";
			}
			else
			{
				while(temp!=NULL)
				{
					
					file<<temp->firstname<<" "<<temp->lastname<<" "<<temp->id<<" "<<temp->fname<<" , "<<temp->age<<" "<<temp->email<<" " <<temp->phone_no<<" ";
					file<<temp->address<<" , "<<temp->degree<<" "<<temp->semester<<" "<<temp->cgpa<<" "<<temp->attendance<<" "<<temp->fee<<endl;
					temp=temp->next;
				}
			}
			file.close(); 
    	}
    	
    	//This function rewrites the data if a record is modified aur record is added aur removed from the system
    	void rewrite(node* temp)
    	{
    		fstream file;
			file.open("Database.txt",ios::out);
			if(file.fail())
			{
				cout<<"\nFile NOT Open\n";
			}
			else
			{
				while(temp!=NULL)
				{
					
					file<<temp->firstname<<" "<<temp->lastname<<" "<<temp->id<<" "<<temp->fname<<" , "<<temp->age<<" "<<temp->email<<" "<<temp->phone_no<<" ";
					file<<temp->address<<" , "<<temp->degree<<" "<<temp->semester<<" "<<temp->cgpa<<" "<<temp->attendance<<" "<<temp->fee<<endl;
					temp=temp->next;
				}
			}
			file.close(); 
		}
		
		//This function reads the data from the file into linked list
    	void read()
    	{		
			fstream file;
			file.open("Database.txt",ios::in);
			if(file.fail())
			{
				cout<<"\nFile NOT Open\n";
			}
			else
			{	
			    string firstname;
			    while(file>>firstname)
				{
					node* temp=new node;
					temp->firstname=firstname;
					file>>temp->lastname;
					file>>temp->id;
					getline(file,temp->fname,',');
					file.ignore();
					file>>temp->age;
					file>>temp->email;
					file>>temp->phone_no;
					getline(file,temp->address,',');
					file.ignore();
					file>>temp->degree;
					file>>temp->semester;
					file>>temp->cgpa;
					file>>temp->attendance;
					file>>temp->fee;
					add_node(temp);		
				}
			}
			file.close();
		}   
		
		//This function ask the whether to search record by name aur by Id
	    node* search()
		{
			node* temp=new node;
			int choice;
			do{
			    cout<<"\nPress 0: Search by ID\n";
			    cout<<"Press 1: Search by Name\n";
			    cout<<"\nEnter Choice: ";
			    cin>>choice;
			    switch(choice)
			    {
			    	case 0:
			    		temp = search_by_ID();
			    		break;
			    	case 1:
			    		cin.ignore();
			    		temp=search_by_Name();
			    		break;
			    	default:
			    		cout<<"\nInvalid Input\n";
				}
			}while(choice!=0 && choice!=1);
			return temp;
		}
		
		//This function Searchs the record by Id
		node* search_by_ID()
		{
			node* temp = head;
		    int id;
		    bool flag=0;
		    cout<<"Enter ID: ";
		    cin>>id;
		    while(temp!=NULL)
		    {
		    	if(temp->id==id)
		    	{
		    		flag=1;
		    		break;
				}
				temp=temp->next;
			}
			if(flag==1)
			{
				cout<<"\nID is Available\n\n";
				display(temp);
			}
			else
			{
				cout<<"\nID is NOT Available\n";
			}
			return temp;		    
		}
		
		//This function searches the Record by name
		node* search_by_Name()
		{
			node* temp=head;
		    string fname,lname;
		    bool flag=0;
		    cout<<"Enter First Name: ";
		    getline(cin,fname);
		    cout<<"Enter Last Name: ";
		    getline(cin,lname);
		    while(temp!=NULL)
		    {
		    	if(temp->firstname==fname && temp->lastname==lname)
		    	{
		    		flag=1;
		    		break;
				}
				temp=temp->next;
			}
			if(flag==1)
			{
				cout<<"\nName is Found\n\n";
				display(temp);
			}
			else
			{
				cout<<"\nName NOT Found\n";
			}
			return temp;		    
		}
		
		//This function delete the record from the linked list
    	void Delete(node* temp)
		{
			if(temp==head)
			{
				head=head->next;
				head->prev=NULL;
				delete temp;
			}
			else if(temp->next==NULL)
			{
				temp->prev->next=NULL;
				delete temp;
			}
			else
			{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
				delete temp;
			}
		}
		
		//This function delete the entire linked list 
		void Delete_LinkedList()
    	{
    		while(head!=NULL)
    		{	
    		    node* temp=head;
    		    if(head->next!=NULL)
    		    {
			        delete temp;
			        head=NULL;
				}
				else
				{
			        head=head->next;
			        delete temp;
			    }
			}  		
		}
		
		//This function modifys the record in the system
		void modify(node* temp)
		{
			int choice;
			do{
			    cout<<"\nPress 0: First Name";
			    cout<<"\nPress 1: Last Name";
			    cout<<"\nPress 2: Student ID";
			    cout<<"\nPress 3: Father Name";
			    cout<<"\nPress 4: Age";
			    cout<<"\nPress 5: Email";
			    cout<<"\nPress 6: Phone No.";
			    cout<<"\nPress 7: Address";
			    cout<<"\nPress 8: Exit";
			    cout<<"\n\nEnter Choice: ";
			    cin>>choice;
			    switch(choice)
			    {
			    	case 0:
			    		cin.ignore();
			    		cout<<"Enter First Name: ";
			    		cin>>temp->firstname;
			    		break;
			    	case 1:
			    		cin.ignore();
			    		cout<<"Enter Last Name: ";
			    		cin>>temp->lastname;
			    		break;
			    	case 2:
			    		cout<<"\nStudent ID can NOT be changed\n";
			    		cout<<"It is Assigned by University\n";
			    		break;
			    	case 3:
			    		cin.ignore();
			    		cout<<"\nEnter Father Name: ";
			    		cin>>temp->fname;
			    		break;
			    	case 4:
			    		cout<<"\nEnter Age: ";
			    		cin>>temp->age;
			    		break;
			    	case 5:
			    		cin.ignore();
			    		cout<<"\nEnter Email: ";
			    		cin>>temp->email;
			    		break;
			    	case 6:
			    		cout<<"\nEnter Phone No.: ";
			    		cin>>temp->phone_no;
			    		break;
			    	case 7:
			    		cin.ignore();
			    		cout<<"\nEnter Adress: ";
			    		cin>>temp->address;
			    		break;
			    	case 8:
			    		cout<<"\nChanges are Saved\n";
			    		break;
			    	default:
			    		cout<<"\nInvalid Input\n";
				}
			}while(choice!=8);
		}
		
		//This function disply the a selective record
		void display(node* temp)
		{
			cout<<"\nFirst Name: "<<temp->firstname;
			cout<<"\nLast Name: "<<temp->lastname;
			cout<<"\nID: "<<temp->id;
			cout<<"\nFather Name: "<<temp->fname;
			cout<<"\nAge: "<<temp->age;
			cout<<"\nEmail: "<<temp->email;
			cout<<"\nPhone no: "<<temp->phone_no;
			cout<<"\nAddress "<<temp->address;
			cout<<"\nDegree: "<<temp->degree;
			cout<<"\nSemester: "<<temp->semester;
			cout<<"\nCGPA: "<<temp->cgpa;
			cout<<"\nAttendance: "<<temp->attendance;
			cout<<"\nFee: "<<temp->fee<<endl;
		}
		
		//This function displays the records present in the system
		void display_all()
		{
			node* temp;
			temp=head;
			while(temp!=NULL)
			{
			    cout<<"\nFirst Name: "<<temp->firstname;
		    	cout<<"\nLast Name: "<<temp->lastname;
				cout<<"\nID: "<<temp->id;
				cout<<"\nFather Name: "<<temp->fname;
				cout<<"\nAge: "<<temp->age;
				cout<<"\nEmail: "<<temp->email;
				cout<<"\nPhone no: "<<temp->phone_no;
				cout<<"\nAddress "<<temp->address;
			    cout<<"\nDegree: "<<temp->degree;
				cout<<"\nSemester: "<<temp->semester;
				cout<<"\nCGPA: "<<temp->cgpa;
				cout<<"\nAttendance: "<<temp->attendance;
				cout<<"\nFee: "<<temp->fee<<endl;			
			    temp=temp->next;
			}
		}
};

int main()
{
	LinkedList list;
	node* Node = new node;
	int choice;
	bool result;
c:  cout<<"\n\n********************************************************************************";
	cout<<"\n                               Student Management System                          ";
	cout<<"\n\n********************************************************************************";
	list.ReadUser();
	cout<<"\nEnter your Credentials to acces the System \n";
	do
	{
		result = list.CheckUser();
	}
	while(!(result));
	if(result)
	{
		cout<<"\n*******************************************************************************";
		cout<<"\n                               Welcome to the System                           ";
		cout<<"\n*******************************************************************************";
		do{
		cout<<"\nPress 0: Add Record";
	    cout<<"\nPress 1: Search Record";
	    cout<<"\nPress 2: Modify Record";
	    cout<<"\nPress 3: Delete Record";
	    cout<<"\nPress 4: Display Record";
	    cout<<"\nPress 5: Log Out";
	    cout<<"\nPress 6: Exit";
		cout<<"\n\n*******************************************************************************";
		cout<<"\nEnter Choice: ";
	    cin>>choice;
	    cout<<"*******************************************************************************";
		cout<<endl;
	    switch(choice)
	    {
	    	case 0:
	    		cin.ignore();
	    		list.add();
	    		list.write(list.get_head());
	    		list.Delete_LinkedList();
	    		cout<<"\n********************************************************************************";
	    		break;
	    	case 1:
	    		list.read();
	    		list.search();
	    		list.rewrite(list.get_head());
	    		list.Delete_LinkedList();
	    		cout<<"\n********************************************************************************";
	    		break;
	    	case 2:
	    		list.read();
	    		Node=list.search();
	    	    list.display(Node);
	    		list.modify(Node);
	    		list.display(Node);
	    		list.rewrite(list.get_head());
	    		list.Delete_LinkedList();
	    		cout<<"\n********************************************************************************";
	    		break;
	    	case 3:
	    		list.read();
	    		Node=list.search();
	    	    list.display(Node);
	    		list.Delete(Node);
	    		list.rewrite(list.get_head());
	    		list.Delete_LinkedList();
	    		cout<<"\n********************************************************************************";
	    		break;
	    	case 4:
	    		list.read();
	    		list.display_all();
	    		cout<<"\n********************************************************************************";
	    		break;
	    	case 5:
	    		goto c;
	    		break;
	    	case 6:
	    		cout<<"\nExit \n";
	    		break;
	    	default:
	    		cout<<"\nInvalid Input\n";
		}
     }while(choice!=6);
	}
}
