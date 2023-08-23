#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;


struct User{
    string username;
    string password;
    int amount;
};

User readData(ifstream &read){ 
    //This fuction reads data from a file and returns a struct 
    User r1;
    read>> r1.username >> r1.password >> r1.amount;

    return r1;
}

void spaces(){
    cout<<"\t";
}

bool CheckPassword(const string &username, const string &password, string file)
{
    // Function that checks the users password and username
    bool status = false;

    ifstream fin(file);

    if (!fin){
        cout << "Unable to open file!\n";
    }else{
        for (string u, p, a; !status && (fin >> u >> p >> a);)
            status = username == u && password == p;}

             //this returns a true value if the username and password match.

    fin.close();
    return status;
}

void RegisterUser()
{

    // function that registers a new user

    //prompts the admin to enter the users username, password and amount
    ofstream write("usersDB.txt", ios::app);
    User s1;
    cout<<"\n\t Enter username : ";
    cin >>s1.username;
    cout<<"\n\t Enter password : ";
    cin >> s1.password;
    cout<<"\n\t Enter initial amount : ";
    cin >> s1.amount;

    //writes the username, password and amount to the text file "usersDB.txt"

    write << s1.username<<endl<< s1.password<< endl<< s1.amount<<endl;

    cout << "\n\t[+] Registration successful" << endl;

    write.close();
    sleep(3);
    system("cls");
}

void deposit(string username, int deposit ,ifstream &read){
    ofstream write("temp.txt");
    User d;
    d = readData(read);
    //update data
   
        while (!read.eof())
        {
            if(d.username == username){
                int newbal;
                newbal = d.amount+ deposit;

                //appends the new balance after deposit
                write<< d.username << endl << d.password << endl << newbal << endl;
                cout<<"\n\t[+] Deposit successful";
                cout<<"\n\n\t[+] " <<username<<"'s new balance is "<<newbal;
                }
            else{
        write<< d.username << endl << d.password << endl << d.amount << endl;
        }
         d = readData(read);
        }
        write.close();
        read.close();
        remove("usersDB.txt");
        //renames temp.txt
        rename("temp.txt", "usersDB.txt");

        sleep(3);
        system("cls");
        
       
    

}

void ResetPassword(string username, string password ,ifstream &read){
        ofstream write("temp2.txt");

         //declaring the struct Users as c
        User c;

        c = readData(read);

        while(!read.eof()){
            //update data
            
            if(c.username == username){
                write<<c.username<<endl<<password<<endl<<c.amount<<endl;
                cout<<"\n\t[+] Password changed";
            }
            else{
                 write<<c.username<<endl<<c.password<<endl<<c.amount<<endl;
            }
            c = readData(read);
        }
        write.close();
        read.close();
        remove("admin.txt");
        rename("temp2.txt", "admin.txt");

        sleep(3);
        system("cls");

       
}

void ResetPassword2(string username, string password ,ifstream &read){
        ofstream write("temp4.txt");
        User g;
        g = readData(read);

        while (!read.eof())
        {
            
            if(g.username==username){
                write<<g.username<<endl<<password<<endl<<g.amount<<endl;
                cout<<"\n\t[+] Password changed";
            }
        else{
            write<<g.username<<endl<<g.password<<endl<<g.amount<<endl;
        }
        g = readData(read);
        }
        write.close();
        read.close();
        remove("usersDB.txt");
        rename("temp4.txt", "usersDB.txt");

        sleep(3);
        system("cls");
}

void CheckBalance(string username){
    ifstream read("usersDB.txt");

    User bal;
   
    while (!read.eof())
    {
         bal = readData(read);
         if (bal.username == username)
         {
            cout<<"\n\t[+] Your balance is "<<bal.amount;
         }
         
    }
    read.close();
    
}

void withdrawal(string username, int amount ,ifstream &read){
        ofstream write("temp3.txt");
        User w;

        w = readData(read);

        while(!read.eof()){
            //update data
           
                 if (w.username==username)
                {
                    if (w.amount>=amount)
                    {
                        int nbalance;
                        nbalance = w.amount - amount;
                        write<<w.username<<endl<<w.password<<endl<<nbalance<<endl;
                        cout<<"\n\t[+] You have successfully withdrawn "<< amount;
                        cout<<"\n\t[+] Your new balance is "<<nbalance<<endl;
                    }
                    else
                    {
                        cout<<"\n\t[+] You have insufficient funds\n\t[+] Your balance is "<<w.amount<<endl;
                    }
                
                }
                else
                {
                write<<w.username<<endl<<w.password<<endl<<w.amount<<endl;
                }
                w = readData(read);
            
            
            
           
            
        }
        write.close();
        read.close();
        remove("usersDB.txt");
        rename("temp3.txt", "usersDB.txt");

}

string PasswordPrompt(){
    string password;
    string password2;
     cout<<"\n\tEnter your new password: " ;
    cin>>password;
    cout<<"\n\tConfirm your new password: ";
    cin>>password2;

    if(password2==password){
        return password;
    }else{
        cout<<"\n\t[-] Passwords do not match, try again"<<endl;
        return 0;
    }
}

void AdminPage(){
     // this is the admin page
           char selection2;
           
            cout << "\n\t****----Welcome admin----****" << endl;
            cout << "\n\t1. Deposit money for client\n\n\t2. Register new client\n\n\t3. Reset your password\n\n\t4. Exit program\n\n\tEnter option to proceed: ";
            cin >> selection2;
            switch (selection2){
            case '1':
            {
                system("cls");
                ifstream read("usersDB.txt");
                string username;
                int amount;
                cout<<"\n\t[+] Enter the client's username : ";
                cin>>username;
                cout<<"\n\t[+] Enter the amount you wish to deposit : ";
                cin >> amount;
                deposit(username, amount, read);
                read.close();
                AdminPage();
                break;}

            case '2':
            {
                system("cls");
                RegisterUser();
                AdminPage();
                break;}
            
            case '3':
            {
                system("cls");
                ifstream read("admin.txt");
                string uname, newpass, newpass2;
                cout<<"\n\t[+] Enter your username : ";
                cin>>uname;
                cout<<"\n\t[+] Enter your new password : ";
                cin>>newpass;
                cout<<"\n\t[+] Confirm your new password : ";
                cin>>newpass2;
                if (newpass==newpass2)
                {
                    ResetPassword(uname, newpass2, read);
                }
                else
                {
                    cout<<"\n\t[-] Passwords do not match";
                }
                read.close();
                AdminPage();
                break;}

            case '4':

                cout << "\n\t****----Thank you for using Fintech----****" << endl;
                sleep(2);
                exit(0);
                break;
            
            default:
                cout<<"\n\t[-] Invalid entry"<<endl;
                break;
}
        
}

void UserPage(string username){
        char selection3;
       

        
        cout<<"\n\t1. Withdraw cash\n\n\t2. Check balance\n\n\t3. Reset your password\n\n\t4. Exit program\n\n\tEnter option to proceed : ";
        cin>>selection3;
        switch (selection3)
            {
            case '1':{
            
            ifstream read("usersDB.txt");
            int withdraw;
            string uname;
            cout<<"\n\t[+] Enter the amount you want to withdraw : ";
            cin>>withdraw;
            system("cls");

            withdrawal(username, withdraw, read);

            read.close();
            UserPage(username);
                
            break;}

             case '2':{
                CheckBalance(username);
                sleep(3);
                system("cls");
                UserPage(username);
                break;}

             case '3':{
                system("cls");
                ifstream read("usersDB.txt");
                string pass2;
                pass2 = PasswordPrompt();
               ResetPassword2(username, pass2,  read);
               read.close();       
               UserPage(username);
            
                break;}

            case '4':{
                cout << "\n\t****----Thank you for using Fintech----****" << endl;
                sleep(2);
                exit(0);
                break;}
            default:
            cout<<"\n\t[-] Invalid entry"<<endl;
                break;
            }
            
           
            }


int main(){
     // initial variables
     system("cls");
    int selection;

    string username, password;
    

    // Choosing the type of user
    cout << "\n\t***** WELCOME TO FINTECH CASH SERVICES *****\n\n\t[+] Enter 1 for User Login.\n\n\t[+] Enter 2 for Administrator Login.\n\n\t[+] Enter 3 to exit program" << endl;
    cout<<"\n\tEnter option to proceed: ";
    cin >> selection;

    switch (selection)
    {
    case 1:{
       
        system("cls");
        cout << "\n\t***----Welcome to the user page----***\n\t[+] Enter your username: ";
        cin >> username;
        cout << "\n\t[+] Enter your password: ";
        cin >> password;

        if (CheckPassword(username, password, "usersDB.txt") == true)
        {
            cout << "\n\t[+] Login succesful" << endl;
            cout << "--------------------------------------------------------\n";
            sleep(2);
            system("cls");
            cout<<"\n\t[+] Welcome "<<username<<endl;
            UserPage(username);
           
            }

             else
        {
            cout << "\n\t[-] Login failed" << endl;
        }
    
        
        
        break;}
    
    
    case 2:
                // Admin enters uername and password
        system("cls");
         cout << "\n\t*******----Welcome to the Registration and Deposit page----*******\n\n\t[+] Enter your username: ";
        cin >> username;
        cout << "\n\t[+] Enter your password: ";
        cin >> password;

        if (CheckPassword(username, password, "admin.txt") == true)
        {
            cout << "\n\t[+] Login succesful" << endl;
            cout << "\t***-------------------------------------------------***\n";
            sleep(2);
            system("cls");

            AdminPage();
           
            }

             else
        {
            cout << "\n\t[-] Login failed" << endl;
        }
        break;

     case 3:
                cout << "\n\t****----Thank you for using Fintech----****" << endl;
                sleep(2);
                exit(0);
                break;
    default:
         cout<<"\n\t[-] Invalid entry"<<endl;
        break;
    }

}