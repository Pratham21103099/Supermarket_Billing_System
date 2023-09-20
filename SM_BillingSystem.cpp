#include<iostream>
#include<fstream>
using namespace std;

class shopping{
    private:
    int ProductID;
    float ProductPrice;
    float Discount;
    string ProductName;
    public:
    void menu();
    void admin();
    void buyer();
    void add();
    void edit();
    void del();
    void list();
    void receipt();
};

void shopping::menu(){
    main_menu:
    int choice;
    string email;
    string pswd;
    cout<<"\n\n\t\t-----------------------------\n";
    cout<<"\t\t    SuperMarket Main Menu    \n";
    cout<<"\t\t-----------------------------\n";
    cout<<"\t\t                             \n";
    cout<<"\t\t|   1) Administrator     |\n";
    cout<<"\t\t|   2) Buyer             |\n";
    cout<<"\t\t|   3) Exit              |\n";
    cout<<"\n\t\t  Select Your Choice!  ";
    cin>>choice;
    // Might be wrong here
    switch(choice){
        case 1:
            cout<<"\t\t Please Login \n";
            cout<<"\t\t Enter Email: ";
            cin>>email;
            cout<<"\t\t Enter Password: ";
            cin>>pswd;
            if(email=="pbansal2025@gmail.com" && pswd=="admin@123"){
                admin();
            }
            else{
                cout<<"\n\t\tInvalid email/password !!\n";
            }
            break;
        case 2:
            buyer();
        case 3:
            exit(0);
        default:
            cout<<"\n\tInvalid Choice! Please select from the given options\n\n";
            break;
    }
    goto main_menu;
}

void shopping::admin(){
    m:
    int choice;
    cout<<"\t\t-------------------------------------\n";
    cout<<"\t\t    Welcome to Administrator Menu    \n";
    cout<<"\t\t-------------------------------------\n\n";
    cout<<"\t\t|___1) Add Product________|\n";
    cout<<"\t\t|___2) Modify Product_____|\n";
    cout<<"\t\t|___3) Delete Product_____|\n";
    cout<<"\t\t|___4) Back to Main Menu__|\n";
    cout<<"\n\t\t Enter Your Choice: ";
    cin>>choice;
    switch(choice){
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            del();
            break;
        case 4:
            menu();
            break;
        default:
            cout<<"Invalid Choice!";
    }
    goto m;
}

void shopping::buyer(){
    m:
    int choice;
    cout<<"\n\n\t\t-------------------------------------\n";
    cout<<"\t\t        Welcome to Buyer Menu    \n";
    cout<<"\t\t-------------------------------------\n\n";
    cout<<"\t\t|___1) Buy Product________|\n";
    cout<<"\t\t|___2) Go Back____________|\n";
    cout<<"\n\t\t Enter Your Choice: ";
    cin>>choice;
    switch(choice){
        case 1:
            receipt();
            break;
        case 2:
            menu();
        default:
            cout<<"\n\t\tInvalid Choice! Please select from the given choices";
    }
    goto m;
}

void shopping::add(){
    m:
    fstream data;
    int code, token=0;
    float price;
    float discount;
    string name;
    cout<<"\n\n\t\t Add New Product ";
    cout<<"\n\n\t ProductID of the Product: ";
    cin>>ProductID;
    cout<<"\n\t Name of the Product: ";
    cin>>ProductName;
    cout<<"\n\t Price of the Product: ";
    cin>>ProductPrice;
    cout<<"\n\t Discount on the Product: ";
    cin>>Discount;
    data.open("database.txt",ios::in);
    if(!data){
        data.open("database.txt",ios::app|ios::out);
        data<<" "<<ProductID<<" "<<ProductName<<" "<<ProductPrice<<" "<<Discount<<"\n";
        data.close();
    }
    else{
        data>>code>>name>>price>>discount;
        while(!data.eof()){
            if(code==ProductID){
                token++;
                break;
            }
            data>>code>>name>>price>>discount;
        }
        data.close();
        if(token==1){
            cout<<"\n\t Product ID Not Available\n";
            goto m;
        }
        else{
            data.open("database.txt",ios::app|ios::out);
            data<<" "<<ProductID<<" "<<ProductName<<" "<<ProductPrice<<" "<<Discount<<"\n";
            data.close();
        }
    }
    cout<<"\n\t\t   Product Record Added!\n";
}

void shopping::edit(){
    fstream data,data1;
    int Productkey;
    int token=0;
    int Id;
    float price,discount;
    string name;
    cout<<"\n\t\t   Modify Product Record   ";
    cout<<"\n\t\t   Product Code: ";
    cin>>Productkey;
    data.open("database.txt",ios::in);
    if(!data)   cout<<"\nFile Does Not Exist";
    else{
        data1.open("database1.txt",ios::app|ios::out);
        data>>ProductID>>ProductName>>ProductPrice>>Discount;
        while(!data.eof()){
            if(Productkey==ProductID){
                cout<<"\n\t\t Enter New Product ID: ";
                cin>>Id;
                cout<<"\n\t\t Name of the Product: ";
                cin>>name;
                cout<<"\n\t\t Price of the Product: ";
                cin>>price;
                cout<<"\n\t\t Discount on the Product: ";
                cin>>discount;
                data1<<" "<<Id<<" "<<name<<" "<<price<<" "<<discount<<"\n";
                cout<<"\n\n\t\t Record Edited";
                token++; 
            }
            else{
                data1<<" "<<ProductID<<" "<<ProductName<<" "<<ProductPrice<<" "<<Discount<<"\n";
            }
            data>>ProductID>>ProductName>>ProductPrice>>Discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt","database.txt");
        if(token==0){
            cout<<"\n\n No Record Found with the provided Product ID";
        }
    }
}

void shopping::del(){
    fstream data,data1;
    int pkey;
    int token=0;
    cout<<"\n\n\t\t Delete Product";
    cout<<"\n\t\t Product Code: ";
    cin>>pkey;
    data.open("database.txt",ios::in);
    if(!data)   cout<<"\n\n\t\t File Doesn't Exist!";
    else{
        data1.open("database1.txt",ios::app|ios::out);
        data>>ProductID>>ProductName>>ProductPrice>>Discount;
        while(!data.eof()){
            if(pkey==ProductID){
                cout<<"\n\n\t\t Product Deleted Successfully!\n";
                token++;
            }
            else{
                data1<<" "<<ProductID<<" "<<ProductName<<" "<<ProductPrice<<" "<<Discount<<"\n";
            }
            data>>ProductID>>ProductName>>ProductPrice>>Discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt","database.txt");
        if(token==0){
            cout<<"\n\n No Record Found with the provided Product ID";
        }
    }
}

void shopping::list(){
    fstream data;
    data.open("database.txt",ios::in);
    cout<<"\n\n|-------------------------------------------------------|\n";
    // cout<<"\n                                                    \n";
    cout<<"\n     ProductId   ProductName   ProductPrice   Discount \n";
    // cout<<"\n                                                    \n";
    cout<<"\n|-------------------------------------------------------|\n";
    data>>ProductID>>ProductName>>ProductPrice>>Discount;
    while(!data.eof()){
        cout<<"\t"<<ProductID<<"\t "<<ProductName<<"\t\t "<<ProductPrice<<"\t\t"<<Discount<<"\n";
        data>>ProductID>>ProductName>>ProductPrice>>Discount;   
    }
    data.close();
}

void shopping::receipt(){
    fstream data;
    int arr_ID[100];
    int arr_quantity[100];
    char choice;
    int c=0;
    float amount=0;
    float total=0;
    cout<<"\n\n\t\t RECEIPT ";
    data.open("database.txt",ios::in);
    if(!data)   cout<<"\n\n\t   Empty Database  ";
    else{
        data.close();
        list();
        cout<<"\n------------------------------\n";
        cout<<"\n       Place Your Order       \n";
        cout<<"\n------------------------------\n";
        do{
            m:
            cout<<"\n   Enter Product Code: ";
            cin>>arr_ID[c];
            cout<<"\n   Enter Product Quantity: ";
            cin>>arr_quantity[c];
            for(int i=0;i<c;i++){
                if(arr_ID[c]==arr_ID[i]){
                    cout<<"\n\n Duplicate product code. Please Try Again";
                    goto m;
                }
            }
            c++;
            cout<<"\n\n Do you want to buy another Product? Press 'y' for yes or 'n' for no: ";
            cin>>choice;
        }
        while(choice=='y');

        cout<<"\n\nC: "<<c<<"\n\n";
        for(int i=0;i<c;i++){
            cout<<"ID: "<<arr_ID[i]<<" ,";
        }
        cout<<"\n\n";


        cout<<"\n\n\t\t____________RECEIPT____________\n";
        cout<<"\nProduct No.\t   Product Name\t   Product Quantity\tPrice\tAmount\tAmount after Discount\n";
        for(int i=0;i<c;i++){
            data.open("database.txt",ios::in);
            data>> ProductID>>ProductName>>ProductPrice>>Discount;
            while(!data.eof()){
                if(ProductID==arr_ID[i]){
                    amount=ProductPrice*arr_quantity[i];
                    Discount=amount-(amount*Discount)/100;
                    total=total+Discount;
                    cout<<"\n\t"<<ProductID<<"\t\t"<<ProductName<<"\t\t"<<arr_quantity[i]<<"\t\t"<<ProductPrice<<"\t"<<amount<<"\t\t"<<Discount;
                }
                data>>ProductID>>ProductName>>ProductPrice>>Discount;
            }
            data.close();
        }
        // data.close();
        cout<<"\n\n---------------------------------------------";
        cout<<"\n Total Amount: "<<total;
        cout<<"\n";
    }
}

int main(){
    shopping shop;
    shop.menu();
}