#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#define infinity 999999999
int payment();
using namespace std;

struct store 
{
    long long int cost[20];
    int array[20];
} travel[15];

struct initialdata {
    long long int cost[20];
} ini[15];

class datamodule {
public:
    string city[15];

    datamodule():city{"Delhi", "Mumbai", "Chennai", "Kolkata", "Kerala", "Hyderabad", "Pune", "Goa", "Bangalore", "Amritsar", "Jaipur", "Patna", "Puducherry", "Srinagar", "Bhopal"} {}

    void costdeclaration() {
        int N, i, j;
        N = 15;

        ifstream file("prices.txt");  // Assuming the file contains prices of flights between cities

        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                file >> travel[i].cost[j];
                travel[i].array[j] = j;
                ini[i].cost[j] = travel[i].cost[j];
            }
        }

    
    
        file.close();
    }
};

class bellmanfordalgorithm:public datamodule{
	public:
	int N,i,j,k;
	bellmanfordalgorithm(){
		N=15;
	}
	void algorithmic_implementation(){
	
		//3 different loops are executed
	
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				for(k=0;k<N;k++){
					if(travel[i].cost[j]>travel[i].cost[k]+travel[k].cost[j])//if low fare is found for the same origin and destination, the minimum possible fare is changed.
					{
						travel[i].cost[j]=travel[i].cost[k]+travel[k].cost[j];
						travel[i].array[j]=k;
					}
				}
			}
		}
	}
};
class filehandlingmodule{
	public:
	
	void ticket(string firstname[],string lastname[],string sex[],int age[],string email[],string c_no[],string souce,string dist,int no){
		ofstream filewrite;
		filewrite.open("ticket.txt",ios::app);
		for(int i=0;i<no;i++){
			filewrite<<"firstname: "<<firstname[i]<<" "<<"lastname: "<<lastname[i]<<" "<<"sex: "<<sex[i]<<" "<<"age: "<<age[i]<<" "<<"email: "<<email[i]<<" "<<"contact_no: "<<c_no[i]<<" "<<"source: "<<souce<<" "<<"destination: "<<dist<<"\n";
		}
		filewrite.close();
	}
};


class inputmodule{
	public:
	string source,destination;
	void user_input(string userchoice[]){
		system("CLS");
		cout<<"\n\n                                                  WELCOME TO FLIGHT RESERVATION SYSTEM                              "<<endl;
		cout<<endl<<endl;
		cout<<"                    Enter Your City:";
		cin>>source;
		cout<<endl<<"                 Enter Your Destination:";
		cin>>destination;
		cout<<endl;
		userchoice[0]=source;
		userchoice[1]=destination;
	}
	
	
	int noofpassenger(){
		int no;
		cout<<endl<<"                 Enter the no of passengers:";
		cin>>no;
		return no;
	}
};

class outputmodule{
	public:
	string source,destination;
	void initial(){
		system("CLS");
		cout<<"\n\n                                           WELCOME TO FLIGHT RESERVATION SYSTEM                         "<<endl;
		cout<<"\n\n";
		cout<<endl;
		cout<<"                   Facilities Available:  "<<endl;
		cout<<endl;
		cout<<"\n\n";
		cout<<"                 ENTER                     "<<endl<<endl;
		
		cout<<"                   1. To Display List of Cities     "<<endl<<endl;
	
		cout<<"                   2. To Book Ticket                 "<<endl<<endl;
		
	
	}
	void list_cities(int N){
		datamodule o;
		cout<<endl;
		system("CLS");
		cout<<"\n\n                                                                 WELCOME TO FLIGHT RESERVATION SYSTEM                  "<<endl;
		cout<<"\n\n";
		cout<<"                 The listed cities are:"<<endl<<endl;
		for(int i=0;i<N;i++){
		cout<<"                          "<<o.city[i]<<"            "<<endl;
		cout<<endl;
		}
		cout<<endl;
	}
	
	void ticket(int total_price,int no,string source,string destination){
		system("CLS");
		cout<<"\n\n                                                   E-TICKET                       "<<endl;
		
		cout<<endl<<"                                     Source:"<<source<<endl;
		cout<<endl<<"                                     Destination:"<<destination<<endl;
		cout<<endl<<"                                     Total No of Passengers:"<<no<<endl;
		cout<<endl<<"                                     Total Cost:"<<total_price<<endl;
		cout<<"\n\n "<<endl;
	}
	
	void passengerdetailedticket(int no,string firstname[],string lastname[],string sex[],int age[],string email[], string c_no[]){
		for(int i=0;i<no;i++){
			cout<<"                                     Passenger "<<(i+1)<<" Details:"<<endl<<endl;
			cout<<"                                     First Name: "<<firstname[i]<<endl;
			cout<<"                                     Last Name: "<<lastname[i]<<endl;
			cout<<"                                     Sex: "<<sex[i]<<endl;
			cout<<"                                     Age: "<<age[i]<<endl;
			cout<<"                                     Email: "<<email[i]<<endl;
			cout<<"                                     Contact No: "<<c_no[i]<<endl;
			cout<<"\n\n"<<endl;
		}
		int ch;
		cout<<endl<<"                                     Enter 1 to continue:";
		cin>>ch;
		if(ch==1){
			initial();
		}
	}
	
	int display_price(string source,string destination,int N){
		source=source;
		destination=destination;
		datamodule o;
		inputmodule in;
		int i,j,choiceofpassenger;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				if(source==o.city[i] && destination==o.city[j]){
					cout<<endl;
					if(ini[i].cost[j]==infinity){
						cout<<"                 There is no direct flight from "<<source<<" to "<<destination<<". So, Travel via other cities is only possible."<<endl;
						cout<<"                 The Price is:"<<travel[i].cost[j]<<endl<<endl;
						cout<<"					The Route is:"<<source;
						int c1=i,c2=j;
						while(c1!=c2){
							cout<<"-->"<<o.city[travel[c1].array[j]];
							c1=travel[c1].array[j];
						}
						cout<<endl<<endl;
					}
					else if((ini[i].cost[j]!=infinity)&&(ini[i].cost[j]==travel[i].cost[j])){
						cout<<"                 There is direct flight available from "<<source<<" to "<<destination<<" . And,it is cheapest among all other paths..."<<endl;
						cout<<"                 The Price is:"<<travel[i].cost[j]<<endl;
					}
					else if((ini[i].cost[j]!=infinity)&&(ini[i].cost[j]>travel[i].cost[j])){
						cout<<"                 There is direct flight available from "<<source<<" to "<<destination<<" ."<<endl;
						cout<<"                 The Price is:"<<ini[i].cost[j]<<endl<<endl;
						cout<<"                 -----------------------------------------"<<endl<<endl;
						cout<<"                 You can go via other cities that will cost you less than direct flight."<<endl;
						cout<<"                 The Price is:"<<travel[i].cost[j]<<endl<<endl;
						cout<<"					The Route is:"<<source;
						int c1=i,c2=j;
						while(c1!=c2){
							cout<<"-->"<<o.city[travel[c1].array[j]];
							c1=travel[c1].array[j];
						}
						cout<<endl<<endl;
						cout<<"                 Press 1 to go by direct flight and Press 2 to go via other cities: ";
						cin>>choiceofpassenger;
					}
					char c;
					cout<<endl;
					cout<<"                 Do You want to Continue(Y/N)?";
					cin>>c;
					if(c=='Y'){
						int no=in.noofpassenger();
						string firstname[no],lastname[no],sex[no],email[no];
						int age[no];
						string c_no[20];
						for(int i=0;i<no;i++){
							cout<<endl;
							cout<<endl;
							cout<<"                                    Passenger "<<(i+1)<<":"<<endl<<endl;
							cout<<endl<<"                         First Name:";
							cin>>firstname[i];
							cout<<endl<<"                         Last Name:";
							cin>>lastname[i];
							cout<<endl<<"                         Sex(Male/Female/Other):";
							cin>>sex[i];
							cout<<endl<<"                         Age:";
							cin>>age[i];
							cout<<endl<<"                         Email Id:";
							cin>>email[i];
                          
                             cout<<endl<<"                        Contact no.(10 digits):";
                             cin>>c_no[i];
						}
						int total_price;
						if(choiceofpassenger==1){
							total_price=no*ini[i].cost[j];
						}
						else{
							total_price=no*travel[i].cost[j];
						}
						cout<<endl<<"                 The total Price is:"<<total_price<<endl;
						char y;
						cout<<"                 Do You want to confirm Your Ticket(Y/N)?";
						cin>>y;
						
						if(y=='Y'){
							filehandlingmodule f;
							payment();
							f.ticket(firstname,lastname,sex,age,email,c_no,source,destination,no);
							ticket(total_price,no,source,destination);
							passengerdetailedticket(no,firstname,lastname,sex,age,email,c_no);
						}
						else{
							cout<<endl<<"                 Thank You For choosing Us...";
							cout<<endl<<"                 Do You Want to Continue(Y/N)?";
							char ch;
							cin>>ch;
							if(ch=='Y'){
								initial();
							}
						return 0;
						}
					}
					else{
						cout<<endl<<"                 Thank You For choosing Us...";
						cout<<endl<<"                 Do You Want to Continue(Y/N)?";
						char ch;
						cin>>ch;
						if(ch=='Y'){
							initial();
						}
					}
					return 0;
				}
			}
		}
		cout<<"                 Sorry, There are no flights available connecting the cities..."<<endl;
		cout<<endl<<"                 Do You Want to Continue(Y/N)?";
		char ch;
		cin>>ch;
		if(ch=='Y'){
			initial();
		}
		return 0;
	}
};

int payment()//class for payment
{
  int choice1,bank,card,date,cvv,user_id;
    char password[10];
    
	showMenu:// for payment method
        cout << "\n\n\nHow would you like to pay?:\n";
        cout << "\nDebit Card(1) \nCredit Card(2) \nNet Banking(3)";
        cout << "\n\nEnter your choice";
        cin >> choice1;
        switch(choice1)//switch case
        {
        case 1://condition
            cout << "\nEnter card no.:";
            cin >> card;
            cout << "\nEnter expiry date:";
            cin >> date;
            cout << "\nEnter CVV no.:";
            cin >> cvv;
            cout << "\nTransaction Successful\n";
			getch();
            break;
        case 2://condition
            cout << "\nEnter card no.:";
            cin >> card;
            cout << "\nEnter expiry date:";
            cin >> date;
            cout << "\nEnter password:";
            cin >> password;
            cout << "\nTransaction Successful\n";
			getch();
            break;
        case 3://condition
            cout << "Banks Available: Indian Bank(1)  HDFC Bank(2) ICICI Bank(3)  UPI(4)";
            cout << "\nSelect your bank:";
            cin >> bank;
            cout << "\nYou have selected:" << bank;
            cout << "\nEnter user no:";
            cin >> user_id;
            cout << "\nEnter passw.....ord:";
            cin >> password;
            cout << "\nTransaction Successful\n";
			getch();
            break;
        default://condition
            cout << "\nWrong input entered.\nTry again\n\n";
			goto showMenu;
           
        }
    }

int main() {
    int N;
    N = 15;
    string first[10], last[10], se[10], emal[15];
    int ag[10], n;
    string c[20];

    datamodule obj;
    obj.costdeclaration();
	
	bellmanfordalgorithm ob;// object for bellmanfordalgorithm class
	ob.algorithmic_implementation();
	
	string userchoice[2];
	
	
	inputmodule obj1;//object for inputmodule class
	
	
	outputmodule object;// object for outputmodule
	
	object.initial();
		
	while(1){
		int choice;
		cout<<"\n                 Enter Your Choice:";
		cin>>choice;
		switch(choice){
			case 1:
				object.list_cities(N);
				cout<<"\n\n                 Press 1 to Continue...";
				int cont;
				cin>>cont;
				if(cont==1){
					object.initial();
				}
				break;
			case 2:
				obj1.user_input(userchoice);
				
				object.display_price(userchoice[0],userchoice[1],N);//passing user inputted source and destination to display_price function of outputmodule
				break;
			case 3:
			object.passengerdetailedticket(n,first,last,se,ag,emal,c);
			break;	     
		}
		int n,ag,c;
		string first,last,se,emal;
	}
return 0;
}



