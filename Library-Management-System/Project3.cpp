#include<iostream>
#include<cctype>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<time.h>
#include<conio.h>
using namespace std;
const int MAX_BOOK_ID=13;
const int DATE_SIZE= 11;
const int MAX_COPY_NUMBER= 17;
const int MAX_BOOKS= 200;
const int MAX_CATEGORIES= 30;
const int MAX_BOOK_NAME=  60;
const int MAX_CATEGORY_NAME= 20;
const int MAX_CATEGORY_NUMBER= 4;
const int MAX_STUDENTS=100;
const int MAX_STUDENT_NAME=60;
const int MAX_REGISTRATION_NUMBER=12;
enum Month
{
	January=1,Feburary,March,April,May,June,July,August,September,October,November,December
};
enum BookStatus
{
   Issued =0,Returned=1	
};
struct Date
{
    int Day;
	int Month;
	int Year;  
};
struct User
{
	char UserName[30];
	char Password[20];
};
struct BookIssue
{
	char regNo[MAX_REGISTRATION_NUMBER];
	char bookCopy[MAX_COPY_NUMBER];
	BookStatus status;
	Date IssueDate;
}; 
struct Student
{
	char RegistrationNo[MAX_REGISTRATION_NUMBER];
	char Name[MAX_STUDENT_NAME];
	int Session;
	Date AdmissionDate;
};
struct Category
{
	char Id[MAX_CATEGORY_NUMBER];
	char Name[MAX_CATEGORY_NAME];
};
struct Book
{
	char Id[MAX_BOOK_ID]; 
	char Name[MAX_BOOK_NAME]; 
	int Edition; 
};
struct BookCopy
{
	char Id[MAX_COPY_NUMBER]; 
	Date PurchaseDate; 
};
void loadUser(User arr[],int size)
{
	bool valid= true;
    ifstream file;
	file.open("users.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<10;i++)
    	{
    		file.getline(arr[i].UserName,',');
    		file.getline(arr[i].Password,'\n');
        }
	    file.close();
	} 	
}
bool findUser(User arr[],int size, User toFind)
{
	bool valid1= false,valid2=false;
	for(int i=0;i<10;i++)
	{
	  for(int j=0;j<30;j++)
	   {
	 	  if(arr[i].UserName[j]==toFind.UserName[j])
	 	  {
	 	  	 valid1 = true;
		  }
	   }
	   for(int j=0;j<20;j++)
	   {
	   	  if(arr[i].Password[j]==toFind.Password[j])
	   	  {
	   	  	valid2= true;
		  }
		}	
	}
	if(valid1==true && valid2==true)
	return true;
	else
	return false;
}
bool issueBook(BookIssue arr[], int size, BookIssue toIssue)
{
	bool valid= false; 
	time_t now = time(0);
	tm *ltm = localtime(&now);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<MAX_COPY_NUMBER-1;j++)
		{
		   arr[i].bookCopy[j]=toIssue.bookCopy[j];
		}
		for(int j=0;j<MAX_REGISTRATION_NUMBER;j++)
		{
			arr[i].regNo[j]=toIssue.regNo[j];
		}		
		arr[i].status = Issued;
		arr[i].IssueDate.Day=ltm->tm_mday;
		arr[i].IssueDate.Month=1+ltm->tm_mon;
		arr[i].IssueDate.Year=1900+ltm->tm_year;
		valid = true;
		if(valid== true)
		{
			break;
		}
	}
	if(valid== true)
	cout<<"The book has been  issued successfully ";
	else
	cout<<"The book has not been issued successsfully ";
}
int returnBook(BookIssue arr[], int size, char copyIdtoReturn[]) 
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int days;
   for(int i=0;i<MAX_BOOKS;i++)
   {
   	for(int j=0;j<MAX_COPY_NUMBER;j++)
   	{
   		if(arr[i].bookCopy[j]==copyIdtoReturn[j])
   		{
   			arr[i].status=Returned;
		}	
	}
	for(int j=0;j<MAX_REGISTRATION_NUMBER;j++)
	{
		arr[i].regNo[j]='\0';
	}
	days=ltm->tm_mday-arr[i].IssueDate.Day;
	arr[i].IssueDate.Day=0;
	arr[i].IssueDate.Month=0;
	arr[i].IssueDate.Year=0;
   }
   if(days>14)
   {
   	  days=(days-14)*10;
   	  cout<<"The  has returned the book with fine of PKR "<<days;
   }
   else
   {
   cout<<"The student has returned the book with zero fine ";
   }
}
void studentCurrentBook(BookIssue arr[], int size, char regNo[]) 
{
	for(int i=0;i<MAX_BOOKS;i++)
	{
		for(int j=0;j<MAX_COPY_NUMBER;j++)
		{
			if(arr[i].regNo[j]==regNo[j])
			{
				cout<<arr[i].bookCopy[j];
			}
		}
		cout<<"\t";
		cout<<arr[i].IssueDate.Day<<"-"<<arr[i].IssueDate.Month<<"-"<<arr[i].IssueDate.Year;
		cout<<endl;
	}
}
void checkBookStatus(BookIssue arr[],BookCopy Arr[], int issueSize, int bookCopySize, char copyId[]) 
{
	bool copystatus;
    for(int i= 0; i<MAX_BOOKS ;i++)
	{
		for(int j=0;j<MAX_COPY_NUMBER;j++)
		{
			if(arr[i].bookCopy[j]==copyId[j])
			{
				if(arr[i].status==Returned)
				{
					cout<<"The book is available ";
				}
				else
				{
					cout<<"The book is currently issued to Registration Number ";
					break;
				} 
			}
		}
	    for(int j=0;j<MAX_REGISTRATION_NUMBER;j++)
		{
			cout<<arr[i].regNo[j];
		}
		break;
	}	
}
void saveBookIssue(BookIssue arr[], int size) 
{
 	bool valid= true;
	ofstream file;
	file.open("bookhistory.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		
		for(int i=0;i<MAX_BOOKS;i++)
    	{
			file<<arr[i].bookCopy<<","<<arr[i].regNo<<","<<arr[i].status<<","<<arr[i].IssueDate.Day<<"-"<<arr[i].IssueDate.Month<<"-"<<arr[i].IssueDate.Year;       
	    }
	    file.close();
	}
}
void loadBookIssue(BookIssue arr[], int size) 
{
   bool valid= true;
    ifstream file;
    int a;
	file.open("bookhistory.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_BOOKS;i++)
    	{
			file.getline(arr[i].bookCopy ,',');
			file.getline(arr[i].regNo,',');
			file>>a;
			if(a==0)
			{
				arr[i].status=Issued;
			}
			else if(a==1)
			{
				arr[i].status=Returned;
			}
			
			file>>arr[i].IssueDate.Day>>arr[i].IssueDate.Month>>arr[i].IssueDate.Year;
		    valid=true;
	    }
	    file.close();
	}	
}
bool isValidRegistrationNo(char regNo[])
{
  int i=0;
  bool valid = false;
  while(regNo[i]!='\0')
  {
  	if(regNo[0]>=48 && regNo[0]<=57 && regNo[1]>=48 && regNo[1]<=57 && regNo[2]>=48 && regNo[2]<=57 && regNo[3]>=48 && regNo[3]<=57)
  	{
  		if(regNo[4]=='-')
  		{
  			if(isupper(regNo[5]) && isupper(regNo[6]) )
  			{
  				if(regNo[7]=='-')
  				{
  					if(isdigit(regNo[8]) && isdigit(regNo[9]) && isdigit(regNo[10]))
  					{
					   valid= true;
					}
					else 
					   valid= false;
				}
				else 
				  valid= false;  
			}
			else 
			  valid= false;
		}
		else 
		  valid= false;
	}
	else
	   valid= false;
	  i++;
  }
  return valid;
}
bool isValidDate(Date date)
{
	bool valid = false;
   if(date.Day>=1 && date.Day<=30 )
   {
   	if(date.Month>=1&& date.Month<=12)
   	{
   	   valid = true;	
    }
	else 
	  valid = false; 	
	}
	return valid;
}
bool isValidStudentName(char stdName[])
{
	int i=0;
	bool valid = false;
	while(stdName[i]=='\0')
	{
		if(stdName[i]>='A' && stdName[i]<='Z' && stdName[i]>='a' && stdName[i]<='z' || stdName[i]==' ')
		valid = true;
		else
		valid = false;
		i++;
	}
	return valid;
}
bool isValidBookId(char bookid[])
{
	bool valid;
	int i=0; 
     while(bookid[i]=='\0')
     {
     	if(bookid[0]<=0 && bookid[0]>=9 && bookid[1]<=9 && bookid[1]>=0 && bookid[2]<=9 && bookid[2]>=9)
     	{
     		if(bookid[3]=='-')
     		{
     			if(bookid[4]>='A'&& bookid[4]<='Z' && bookid[5]>='A'&& bookid[5]<='Z')
     			{
     				if(bookid[6]=='-')
     				{
     			       for(i=7;i<=13;i++)
						{
							if(bookid[i]>=0 && bookid[i]<=9)
							valid = true;
							else 
							valid = false;
						}	
				   }
				   else 
				   valid = false;					   	
				}
				else 
				valid = false;
			}
			else 
			valid = false;
			
		}
		else 
		valid = false;
		i++;
	}
	  return valid; 
}
bool isValidBookName(char bookName[])
{
	 int valid=0,i=0;
	while(bookName[i]=='\0')
	{
		if(bookName[i]>='A' && bookName[i]<='Z' || bookName[i]>='a' && bookName[i]<='z')
		{
          if(bookName[i]==',' || bookName[i]==':' || bookName[i]==' ')
		  {
		  	if(bookName[i]==' ' && bookName[i +1]==' ' || bookName[i]==',' && bookName[i+1]==',' || bookName[i]==':' && bookName[i+1]==':' )
		  	{
		  		valid = 0;
			}
			else 
			   valid = 1;
		  }
		  else 
		    valid = 0; 		
		} 
		else 
		   valid = 0;
		i++;
    }
    return valid;
}
   bool isValidCategoryName(char bookCategory[])
{      
    int i=0;
    bool valid =true;
	while(bookCategory[i]=='\0')
	{
		if( bookCategory[i]>='A' && bookCategory[i]<='Z'|| bookCategory[i]>='a' && bookCategory[i]<='z')
		{
			return true;
		}
		else 
		   return  false;
		i++;   
	}
	return valid;
}
bool isValidCategoryNumber(char bookCategory[])
{    
    int i=0;
	bool valid= true; 
   while(bookCategory[i]=='\0')
   {
   	    if(bookCategory[0]>='0' && bookCategory[0]<='9' || bookCategory[1]>='0' && bookCategory[1]<='9' || bookCategory[2]>='0' && bookCategory[2]<='9' )
   	    {
   	        valid = true;	
		}
	    else 
		    valid = false;	
   }
     return valid;  
}
void readInCategory(Category& category) 
{
	for(int i=0;i<MAX_CATEGORY_NUMBER;i++)
	{
		cin.get(category.Id[i]);
	}
	for(int i=0;i<MAX_CATEGORY_NAME;i++)
	{
		cin.get(category.Name[i]);
		if(cin.peek()=='\n')
		break;
	}
}
bool isExist(Category arr[], int arraySize, char catId[]) 
{
	bool valid = false;
      for(int i=0;i<MAX_CATEGORIES;i++)
      {
      	for(int j=0;j<MAX_CATEGORY_NUMBER;j++)
      	{
      		if(arr[i].Id[j]==catId[j])
      		{
      			valid = true;
			}
		}
	  }
	if(valid==true)
	 cout<<"The Category Id exist ";
	else
	 cout<<"The Category Id does not exist ";   
}
bool addCategory(Category arr[],int ArraySize,Category newCategory)
{
	bool valid1=false,valid2=false;	
	for(int i=0; i<MAX_CATEGORIES; i++)
	{
		for(int j=0;j<MAX_CATEGORY_NUMBER;j++)
		{
			if(	arr[i].Id[j]=='\0')
			{
				arr[i].Id[j]=newCategory.Id[j];
				valid1=true;
		    }
		}
		for(int j=0;j<MAX_CATEGORY_NAME;j++)
		{
			if(arr[i].Name[j]=='\0')
			{
				arr[i].Name[j]=newCategory.Name[j];
				valid2=true;  
			}
		}
		if(valid1==true && valid2==true)
		{
			break;	
		}
	}
	if(valid1==true && valid2==true)
	  cout<<"The Category has been added Successfully ";
	else 
	  cout<<"The Category has not been added Successfully ";  
}
bool editCategory(Category arr[], int arraySize, char catId[], Category newData) 
{
	bool valid1 = false,valid2=false;
	for(int i=0; i<MAX_CATEGORIES;i++)
	{
		for(int j=0;j<MAX_CATEGORY_NUMBER;j++)
		{
			if(arr[i].Id[j]==catId[j])
			{
				arr[i].Id[j]=newData.Id[j];
				valid1 = true;
		    }
		    for(int j=0;j<MAX_CATEGORY_NAME;j++)
		    {
		    	arr[i].Name[j]=newData.Name[j];
		    	valid2= true;
			}
			if(valid1==true && valid2==true)
			  break;
	    }
    }
	if(valid1==true && valid2==true)
	 cout<<"The Category has been editd successfully ";
	else
	 cout<<"The Category has not been edited successfully";  
}
bool deleteCategory(Category arr[], int arraySize, char catId[]) 
{
	bool valid = false;
	for(int i=0;i<MAX_CATEGORIES;i++)
	{
		for(int j=0;j<MAX_CATEGORY_NUMBER;j++)
		{
			if(arr[i].Id[j]==catId[j])
			{
				arr[i].Id[j]='\0';
				valid= true;
			}
		}
	for(int j=0;j<MAX_CATEGORY_NAME;j++)
		{
			arr[i].Name[j] ='\0';
			valid = true;
		}
    }
    if(valid= true)
    {
    	cout<<"Id has been deleted Successfully \n";
	}
	else 
	  cout<<"Id has not been deleted Successfully \n";
}
void printCategories(Category arr[], int arraySize) 
{
	bool valid = false;
    cout<<"Category Id \t Category Name ";
	for(int i=0;i<MAX_CATEGORIES;i++)
	{
		cout<<arr[i].Id<<"\t \t"<<arr[i].Name;   
    }
}
bool saveCategories(Category arr[], int arraySize)  
{
	bool valid= true;
	ofstream file;
	int ArraySize;
	file.open("Categories.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_CATEGORIES;i++)
    	{
		    file<<arr[i].Id<<","<<arr[i].Name;
	    } 
	    file.close();
	} 	
}
bool loadCategories(Category arr[], int arraySize) 
{
    bool valid= true;
    ifstream file;
	file.open("Categories.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_CATEGORIES;i++)
    	{
			file.getline(arr[i].Id , 4 );
			file.getline(arr[i].Name,'\n');
		    valid=true;
	    }
	    file.close();
	} 	
}
bool isExist(Book arr[], int arraySize, char bookId[]) 
{
	bool valid=false;
	for(int i=0;i<MAX_BOOKS;i++)
	{
		for(int j=0;j<MAX_BOOK_ID;j++)
		{
			if(arr[i].Id[j]==bookId[j])
			{
				valid= true;
			}
		}
	}
}
void readInBook(Book& book) 
{
	for(int i=0;i<MAX_BOOK_ID;i++)
	{
		cin.get(book.Id[i]);
		if(cin.peek()=='\n')
		break;
	}
	cin>>book.Edition; 
	for(int i=0;i<MAX_BOOK_NAME;i++)
	{
		cin.get(book.Name[i]);
		if(cin.peek()=='\n')
		  break;
	}
}
bool addBook(Book arr[], int arraySize, Book newBook) 
{    
    bool valid1=false,valid2=false;	
	for(int i=0; i<MAX_BOOKS; i++)
	{
		for(int j=0;j<MAX_BOOK_ID;j++)
		{
			if(	arr[i].Id[j]=='\0')
			{
				arr[i].Id[j]=newBook.Id[j];
				valid1=true;
		    }
		}
		arr[i].Edition=newBook.Edition;
		for(int j=0;j<MAX_BOOK_NAME;j++)
		{
			if(arr[i].Name[j]=='\0')
			{
				arr[i].Name[j]=newBook.Name[j];
				valid2=true;  
			}
		}
		if(valid1==true && valid2==true)
		{
			break;	
		}
	}
	if(valid1==true && valid2==true)
	  cout<<"The Book has been added Successfully ";
	else 
	  cout<<"The Book has not been added Successfully ";  
}
bool editBook(Book arr[], int arraySize, char bookId[], Book newData)  
{
	bool valid = false;
	for(int i=0; i<MAX_BOOKS;i++)
	{
		for(int j=0;j<MAX_BOOK_ID;j++)
		{
			if(arr[i].Id[j]==bookId[j])
			{
				arr[i].Id[j]=newData.Id[j];
				valid = true;
		    }
	    }
		for(int j=0;j<MAX_BOOK_NAME;j++)
		{
			arr[i].Name[j]=newData.Name[j];
			valid = true;
		}
	}
}
bool deleteBook (Book arr[], int arraySize, char bookId[])
{
	bool valid = true;
	for(int i=0;i<MAX_BOOKS;i++)
	{
		for(int j=0;j<MAX_BOOK_ID;j++)
		{
			if(arr[i].Id[j]==bookId[j])
			{
				arr[i].Id[j]='\0';
				valid= true;
		    }
		}
	for(int j=0;j<MAX_BOOK_NAME;j++)
		{
			arr[i].Name[j]='\0';
			valid = true;
		}
    }
}
void printBooks(Book arr[], int arraySize)
{
	bool valid = false;
	for(int i=0;i<MAX_CATEGORIES;i++)
	{
			cout<<arr[i].Id<<"\t"<<arr[i].Name<<"\t"<<arr[i].Edition;
			valid= true;   
    }
}
bool saveBooks(Book arr[], int arraySize)
{
	bool valid= true;
	ofstream file;
	file.open("Books.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_BOOKS;i++)
    	{
			    file<<arr[i].Id<<","<<arr[i].Name<<","<<arr[i].Edition;
		        
	    }
	    file.close();
	}
	return valid;
}
bool loadBooks(Book arr[], int arraySize)
{
	bool valid= true;
    ifstream file;
	file.open("Categories.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_BOOKS;i++)
    	{
			file.getline(arr[i].Id ,',');
			file.getline(arr[i].Name,',');
			file>>arr[i].Edition;
		    valid=true;
	    }
	    file.close();
	}
}
bool isExist(BookCopy arr[], int arraySize, char copyId[])
{
	bool valid = false;
 	for(int i=0;i<MAX_BOOKS;i++)
 	{
 		for(int j=0;j<MAX_COPY_NUMBER;j++)
 		{
 			if(arr[i].Id[j]==copyId[j])
 			{
 				valid = true;
			}
		}
	}
 	
} 
void readInBookCopy(BookCopy  &bookCopy) 
{
	char hold[0];
	for(int i=0;i<MAX_COPY_NUMBER;i++)
	{
		cin.get(bookCopy.Id[i]);
	}
	cin>>bookCopy.PurchaseDate.Day>>hold[0]>>bookCopy.PurchaseDate.Month>>hold[1]>>bookCopy.PurchaseDate.Year;
}
bool addBookCopy(BookCopy arr[], int arraySize, BookCopy newBookCopy) 
{
	bool valid1= false,valid2=false;
	for(int i= 0; i<MAX_BOOKS;i++)
	{
		for(int j=0;j<MAX_COPY_NUMBER;j++)
		{
			if(arr[i].Id[j]=='\0')
			{
				arr[i].Id[j]=newBookCopy.Id[j];
				valid1= true;
			}
		}
				arr[i].PurchaseDate=newBookCopy.PurchaseDate;
				valid2= true;
		if(valid1==true && valid2==true)
		{
			break;	
		}
    }
		if(valid1==true && valid2==true)
		cout<<"Book Copy has been added successfully ";
		else
		cout<<"Book Copy not been added successfully ";
}
bool editBookCopy(BookCopy arr[], int arraySize, char bookCopyId[], BookCopy newData) 
{
	bool valid = false;
	for(int i=0; i<MAX_BOOKS;i++)
	{
		for(int j=0;j<MAX_COPY_NUMBER;j++)
		{
			if(arr[i].Id[j]==bookCopyId[j])
			{
				arr[i].Id[j]=newData.Id[j];
				valid = true;
			}
		}
			arr[i].PurchaseDate.Day=newData.PurchaseDate.Day;
			arr[i].PurchaseDate.Month=newData.PurchaseDate.Month;
			arr[i].PurchaseDate.Year=newData.PurchaseDate.Year;
			valid = true;
	}
	return valid;
}
bool deleteBookCopy(BookCopy arr[], int arraySize, char bookCopyId[])
{
	bool valid = true;
	for(int i=0;i<MAX_BOOKS;i++)
	{
		for(int j=0;j<MAX_COPY_NUMBER;j++)
		{
			if(arr[i].Id[j]== bookCopyId[j])
			{
				arr[i].Id[j]='\0';
				valid= true;
			}
	    }
			arr[i].PurchaseDate.Day=0;
			arr[i].PurchaseDate.Month=0;
			arr[i].PurchaseDate.Year=0;
			valid = true;
    }
    return valid;
}
void printBookCopies(BookCopy arr[], int arraySize, char bookId[]) 
{
   cout<<"\tBooks Id \t PurchasedDate\t ";	
  for(int i=0;i<MAX_BOOKS;i++)
  {
  	if(arr[i].Id[4]!=0)
  	{
  		cout<<"\t"<<arr[i].Id;
  		cout<<"\t"<<arr[i].PurchaseDate.Day<<"-"<<arr[i].PurchaseDate.Month<<"-"<<arr[i].PurchaseDate.Year;
  		cout<<endl;
	}
  }
                      	
}
bool saveBookCopies(BookCopy arr[], int arraySize)
{
	bool valid= true;
	ofstream file;
	int ArraySize;
	file.open("BookCopies.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_BOOKS;i++)
    	{
		    file<<arr[i].Id<<","<<arr[i].PurchaseDate.Day<<"-"<<arr[i].PurchaseDate.Month<<"-"<<arr[i].PurchaseDate.Year;
	    } 
	    file.close();
	} 
}
bool loadBookCopies(BookCopy arr[], int arraySize) 
{
	bool valid= true;
    ifstream file;
	file.open("Categories.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_BOOKS;i++)
    	{
    		for(int j=0;j<MAX_COPY_NUMBER-1;j++)
    		{
    			if(file.peek()==',')
    			{
    			 	break;
				} 
			file>>arr[i].Id;
		    valid=true;
	        }
	        for(int j=0;j<DATE_SIZE;j++)
	        {
	        	
			}
	    }
	    file.close();
	} 	
}
bool isExist(Student arr[], int arraySize, char regNo[]) 
{
	bool valid = false;
	for(int i=0;i<MAX_STUDENTS;i++)
	{
		for(int j=0;j<MAX_REGISTRATION_NUMBER;j++)
		{
			if(arr[i].RegistrationNo[j]==regNo[j])
			{
			    valid = true;
			}
		}
	}
}
bool addStudent(Student arr[], int arraySize, Student newStudent)
{
	bool valid1=false,valid2=false;	
	for(int i=0; i<MAX_STUDENTS; i++)
	{
		for(int j=0;j<MAX_REGISTRATION_NUMBER;j++)
		{
			if(	arr[i].RegistrationNo[j]=='\0')
			{
				arr[i].RegistrationNo[j]=newStudent.RegistrationNo[j];
				valid1=true;
		    }
		    arr[i].Session=newStudent.Session;
		    arr[i].AdmissionDate.Day=newStudent.AdmissionDate.Day;
		    arr[i].AdmissionDate.Month=newStudent.AdmissionDate.Month;
		    arr[i].AdmissionDate.Year=newStudent.AdmissionDate.Year;
		}
		for(int j=0;j<MAX_STUDENT_NAME;j++)
		{
			if(arr[i].Name[j]=='\0')
			{
				arr[i].Name[j]=newStudent.Name[j];
				valid2=true;  
			}
			arr[i].Session=newStudent.Session;
		}
		if(valid1==true && valid2==true)
		{
			break;	
		}
	}
	if(valid1==true && valid2==true)
	  cout<<"The Student has been added Successfully ";
	else 
	  cout<<"The Student has not been added Successfully ";
} 
bool editStudent(Student arr[], int arraySize, char regNo[], Student newData)
{
	bool valid = false;
	for(int i=0; i<MAX_STUDENTS;i++)
	{
		for(int j=0;j<MAX_REGISTRATION_NUMBER;j++)
		{
			if(arr[i].RegistrationNo[j]==regNo[j])
			{
				arr[i].RegistrationNo[j]=newData.RegistrationNo[j];
				valid = true;
		    }
		    for(int j=0;j<MAX_STUDENT_NAME;j++)
		    {
		    	arr[i].Name[j]=newData.Name[j];
			}
	    }
	    arr[i].Session=newData.Session;
	    arr[i].AdmissionDate.Day=newData.AdmissionDate.Day;
		arr[i].AdmissionDate.Month=newData.AdmissionDate.Month;
		arr[i].AdmissionDate.Year=newData.AdmissionDate.Year;
    }
	if(valid==true)
	cout<<"The Student  has been editd successfully ";
	else
	cout<<"The Student has not been edited successfully";
}
bool deleteStudent (Student arr[], int arraySize, char regNo[])
{
	bool valid = false;
	for(int i=0;i<MAX_STUDENTS;i++)
	{
		for(int j=0;j<MAX_REGISTRATION_NUMBER;j++)
		{
			if(arr[i].RegistrationNo[j]==regNo[j])
			{
				arr[i].RegistrationNo[j]='\0';
				valid= true;
			}
		}
	for(int j=0;j<MAX_STUDENT_NAME;j++)
		{
			arr[i].Name[j] ='\0';
			valid = true;
		}
		arr[i].Session=0;
		arr[i].AdmissionDate.Day=0;
		arr[i].AdmissionDate.Month=0;
		arr[i].AdmissionDate.Year=0;
    }
    if(valid==true)
    cout<<"The Student has deleted Successfully ";
    else
    cout<<"The Student has not been deleted Successfully ";
}
void printStudents(Student arr[], int arraySize)
{
	bool valid = false;
	for(int i=0;i<MAX_STUDENTS;i++)
	{
		cout<<arr[i].RegistrationNo<<"\t"<<arr[i].Session<<"\t"<<arr[i].AdmissionDate.Day<<"-"<<arr[i].AdmissionDate.Month<<"-"<<arr[i].AdmissionDate.Year<<"\t"<<arr[i].Name;
		valid= true;   
    } 
}
bool saveStudents(Student arr[], int arraySize)
{
	bool valid= true;
	ofstream file;
	int ArraySize;
	file.open("Students.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_STUDENTS;i++)
    	{
		    file<<arr[i].RegistrationNo<<","<<arr[i].Session<<","<<arr[i].AdmissionDate.Day<<"-"<<arr[i].AdmissionDate.Month<<"-"<<arr[i].AdmissionDate.Year<<","<<arr[i].Name;
	    } 
	    file.close();
	} 	
}
bool loadStudents(Student arr[], int arraySize) 
{
	bool valid= true;
    ifstream file;
	file.open("Students.csv");
	if(file.fail())
	{
		cout<<"	File NOT Open"<<endl;
		valid=false;
	}
	else
	{
		for(int i=0;i<MAX_STUDENTS;i++)
    	{
			file.getline(arr[i].RegistrationNo,',');
			file>>arr[i].Session;
			file>>arr[i].AdmissionDate.Day;
			file>>arr[i].AdmissionDate.Month;
			file>>arr[i].AdmissionDate.Year;
			file.getline(arr[i].Name,'\n');
		    valid=true;
	    }
	    file.close();
	}
}
 void readInStudent(Student& student) 
 {
 	char hold[2]; 
  	for(int i=0;i<MAX_REGISTRATION_NUMBER;i++)
 	{
 	    cin.get(student.RegistrationNo[i]);
		 if(cin.peek()=='\n')
		 break;	
	}
	cin>>student.Session;
	cin>>student.AdmissionDate.Day>>hold[0]>>student.AdmissionDate.Month>>hold[1]>>student.AdmissionDate.Year;
	for(int j=0;j<MAX_STUDENT_NAME;j++)
	{
		cin.get(student.Name[j]);
		if(cin.peek()=='\n')
		break;
	}
}
void printMenu() 
{
cout<<"\nChoose the following option \n"; 
cout<<"1 Category Management(A,E,L,D)\n"; 
cout<<"2 Books Management(A,E,L,D)\n";
cout<<"3 Book Copies Management(A,E,L,D)\n"; 
cout<<"4 Student Management(A,E,L,D)\n";
cout<<"5 Book Issue Management(I,R,S,B)\n"; 
cout<<"9 Logout(9L) \n";
cout<<"0  Exit Program(0E)\n";  
}
void TakeMenuInput(int& mainOption, char& subOption)
{
	cout<<"\n Choose the Option: ";
	cin>>mainOption;
	cout<<"Choose the SubOption: ";
	cin>>subOption;
	
}
int main()
{
	
	int mainOption;
    char subOption;
    int ArraySize;
    int size;
    int issueSize;
    int bookCopySize;
    User find;
    bool choice;
    char ch[2];
    char copyId[MAX_COPY_NUMBER]={};
    char copyIdtoReturn[MAX_COPY_NUMBER];
    BookIssue toIssue;
    char regNo[MAX_REGISTRATION_NUMBER];
    Student Drr[MAX_STUDENTS]={};
    BookCopy Crr[MAX_BOOKS]={};
    Book Arr[MAX_BOOKS]={};
    BookIssue Err[3]={};
    User Frr[10]={};
    char catId[MAX_CATEGORY_NUMBER]={'\0'};
	Category category;
	Category arr[MAX_CATEGORIES]={};
	Category newData;
	loadUser(Frr,size);
a:	cout<<"** Welcome to University Library Management System ** \n";
	cout<<"Kindly enter the credentials to access the system features";
	cout<<"\nUserName : ";
	for(int i=0;i<30;i++)
	{
		cin.get(find.UserName[i]);
		if(cin.peek()=='\n')
		break;
    }
	cout<<"\nPassword: ";
	find.Password[0]=getch();
	for(int j=1;j<20;j++)
	{
		cout<<'*';
		find.Password[j]=getch();	
		if(find.Password[j]==13)
		{
		    break;
	    }
    }
    cin.ignore();
	if(findUser(Frr,size,find))
	{
	 printMenu();
  c: TakeMenuInput(mainOption,subOption);
     switch(mainOption)
	{
		case 1:
			if(subOption=='A')
			{ 
                Category newCategory;
                do
				{
				cout<<"Enter the Details of the Category (Id Name): ";			
			    readInCategory(newCategory);
			    }
			    while(!(isValidCategoryName(newCategory.Name)) &&  !(isValidCategoryNumber(newCategory.Id)));
			    addCategory(arr,ArraySize,newCategory);
			    goto c;
			}
			else if(subOption=='E')
			{   
			   cout<<"Enter the Category Id you want to edit ";
			   for(int i=0;i<MAX_CATEGORY_NUMBER;i++)
			   {
			   	   cin.get(catId[i]);
			   	   if(cin.peek()=='\n')
			   	   break;
			   }
			   cout<<"Enter the details of the new Category( Id Name ): ";
			    readInCategory(newData); 
				editCategory(arr,ArraySize,catId,newData); 
				goto c;				
			}
			else if(subOption=='L')
			{
			  int ArraySize;
			  printCategories(arr,ArraySize); 
			  goto c;
			}
			else if(subOption=='D')
			{ 
			    cout<<"Enter the Id you want to delete ";
				for(int i=0;i<MAX_CATEGORY_NUMBER;i++)
			   {
			   	   cin.get(catId[i]);
			   	   if(cin.peek()=='\n')
			   	   break;
			   }
				deleteCategory(arr,ArraySize,catId);
			    goto c;
			}
			break;
		case 2:
			if(subOption=='A')
			{
				Book newBook;
				cout<<"Enter the details of the book (Id Edition Name ): ";
				readInBook(newBook);  
				addBook(Arr,ArraySize,newBook);
				goto c;
			}
			else if(subOption=='E')
			{
				Book newData;
				char bookId[MAX_BOOK_ID];
				cout<<"Enter the Book Id you want to edit ";
				for(int i=0;i<MAX_BOOK_ID;i++)
				{
					cin.get(bookId[i]);
					if(cin.peek()=='\n')
					break;
				}
				cout<<"Enter the details of the new Book (Id Edition Name): ";
				readInBook(newData);
			    editBook(Arr,ArraySize,bookId,newData);
               	goto c;
			}
			else if(subOption=='L')
			{
			    int ArraySize;
				printBooks(Arr,ArraySize);
				goto c; 
			}
			else if(subOption=='D')
			{
				char bookId[MAX_BOOK_ID];
				cout<<"Enter the Book Id you want to delete ";
				for(int i=0;i<MAX_CATEGORY_NUMBER;i++)
				{
				     cin.get(bookId[i]);
					 if(cin.peek()=='\n')
					 break;	
				}
				deleteBook(Arr,ArraySize,bookId);
				goto c; 
			}
			break;
		case 3:
			if(subOption=='A')
			{
				BookCopy newBookCopy;
				cout<<"Enter the details of the sample (Copy Id  Date of Purchase): ";
				readInBookCopy(newBookCopy);
				addBookCopy(Crr,ArraySize,newBookCopy);
				goto c; 
			}
			else if(subOption=='E')
			{
				BookCopy newData;
				char bookCopyId[MAX_COPY_NUMBER];
				cout<<"Enter the Book Copy you want to edit ";
				for(int i=0;i<MAX_COPY_NUMBER;i++)
				{
					cin.get(bookCopyId[i]);
					if(cin.peek()=='\n')
					break;
				}
				cout<<"Enter the details of the Copy( Id  Date of Purchase): ";
				readInBookCopy(newData);
				editBookCopy(Crr,ArraySize,bookCopyId,newData);
				goto c;
			}
			else if(subOption=='D')
			{
				char AddedCopyId[MAX_COPY_NUMBER];
				cout<<"Enter the Book Copy you want to delete ";
				for(int i=0;i<MAX_COPY_NUMBER;i++)
				{
					cin.get(AddedCopyId[i]);
					if(cin.peek()=='\n')
					break;
				}
				deleteBookCopy(Crr,ArraySize,AddedCopyId);
				goto c; 
			}
			else if(subOption=='L')
			{
				char bookId[MAX_BOOK_ID];
				cout<<"Enter the Book Id you wanrt to see copies ";
				for(int i=0;i<MAX_BOOK_ID;i++)
				{
					cin.get(bookId[MAX_BOOK_ID]);
					if(cin.peek()=='\n')
					break;
				}
				printBookCopies(Crr,ArraySize,bookId);
			}
			break;
		case 4:
		     if(subOption=='A')
			 {
			 	Student newStudent;
			 	do
				{
			 	cout<<"Enter the details of the student (RegNo Session AdmissionDate Name ): ";
			 	readInStudent(newStudent);
			    }
			    while(!(isValidStudentName(newStudent.Name)) && !(isValidRegistrationNo(newStudent.RegistrationNo)) && !(isValidDate(newStudent.AdmissionDate)));
			 	addStudent(Drr,ArraySize,newStudent);
			 	goto c;
		     }
			 else if(subOption=='E')
			 {
			 	Student newData;
			 	char regNo[MAX_REGISTRATION_NUMBER];
			 	cout<<"Enter the Student's Registration No to edit: ";
			 	for(int i=0;i<MAX_REGISTRATION_NUMBER;i++)
			 	{
			 		cin.get(regNo[i]);
			 		if(cin.peek()=='\n')
			 		break;
				 }
				cout<<"Enter the deatils of the Student (RegNo Session AdmissionDate Name): "; 
				readInStudent(newData); 
			 	editStudent(Drr,ArraySize,regNo,newData);
			 	goto c;
		     }
			 else if(subOption=='L')
			 {
			 	int ArraySize;
			 	printStudents(Drr,ArraySize);
			 	goto c;
		     }
			 else if(subOption=='D')
			 {
			 	char regNo[MAX_REGISTRATION_NUMBER];
			 	cout<<"Enter the Student Registration No you want to delete: ";
			 	for(int i=0;i<MAX_REGISTRATION_NUMBER;i++)
			 	{
			 		cin.get(regNo[i]);
			 		if(cin.peek()=='\n')
			 		break;
				}
			 	deleteStudent (Drr,ArraySize,regNo);
			 	goto c;
			 }
			break;
		case 5:
		if(subOption=='I')	
		{
			cin.ignore();
            cout<<"\nEnter the BookCopy you want to issue: ";
            cin.getline(toIssue.bookCopy,17);
            cout<<"\n Enter the Registration Number to which you want to Issue Book: ";
	        cin.getline(toIssue.regNo,12);
	        issueBook(Err,size,toIssue);
	        goto c;
		}
		else if(subOption=='R')
		{
			cout<<"\nEnter the Copy Id you want to return: ";
	        for(int i=0;i<MAX_COPY_NUMBER;i++)
	        {
		    cin.get(copyIdtoReturn[i]);
		    if(cin.peek()=='\n')
		    break;
	        }
	        returnBook(Err,size,copyIdtoReturn);
	        goto c;
		}
		else if(subOption=='S')
		{
			cout<<"\nEnter the Student Registration Number whose status you want to know: ";
	        cin.getline(regNo,12);
	        studentCurrentBook(Err,size,regNo);
	        goto c;
		}
		else if(subOption=='B')
		{
			cout<<"Enter the Copy Id whose status you want to check: ";
	        cin.getline(copyId,17);
	        checkBookStatus(Err,Crr,issueSize,bookCopySize,copyId);
	        goto c;
		}
		break;
		case 9:
		if(subOption=='L')	
		{
		  saveBookIssue(Err,size); 
		  goto a;
		}
		break;	
		case 0:
			if(subOption=='E')
			{
				int ArraySize;
				saveCategories(arr,ArraySize);
				saveBooks(Arr,ArraySize);
				saveBookCopies(Crr,ArraySize);
				saveStudents(Drr,ArraySize);
		    }
			break;
        }
     }
     else 
     {
     cout<<"The Username or Password is Incorrect ";
     goto a;
     }
}




