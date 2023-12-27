#include <iostream>
#include <string>
#include <conio.h>
#include <mysql.h> //libmysql
#include <ctime>
#include <iomanip>
using namespace std;


void giveStar();
void Register();
void LoginChef();
void LoginAdmin();
void UserMenu();
void ViewCategory();
void ViewRecipeAdmin();
void AdminMenu();
void Approve();
void ViewRecipe();
void GiveRate();
void ViewRecipeFed();
//void ViewCar();
void Search();
void InsertRecipe();
void InsertCategory();
void ViewFeedback();
void EditRecipe();
void ViewDetail();
void ViewDetailFed();
void GetFeedback();
void ViewRating();
void Feedback();
void ListUser();
void Rank();
//void EditCar();
//void DeleteCar();
//void SearchCar();

int qstate,vstate,astate;
//int qstate1;
MYSQL* conn;
//MYSQL* conn1;
MYSQL_ROW row;
MYSQL_ROW row1;
MYSQL_RES* res;
MYSQL_RES* res1;

string UserID, CarID;

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
            //    cout << "Database Connected" << endl;
            cout << "\t\t************************************************" << endl;
        else
            cout << "Failed To Connect!" << endl;

        conn = mysql_real_connect(conn, "localhost", "root", "", "workshop", 3306, NULL, 0);
        if (conn)
           // cout << "Database Connected To MySql" << endl;
            cout << "\t\t************************************************" << endl;
        else
            cout << "Failed To Connect!" << endl;
    }
};



int main() {
   
  
    system("cls");
    system("title My Project");
    db_response::ConnectionFunction();

    int choice;
    int choice1;
    cout << "\t\t\tCOOKING RECIPE MANAGEMENT" << endl;
    cout << "\t\t\t1. Login" << endl;
    cout << "\t\t\t2. Register(User)" << endl;
    cout << "\t\t\t3. Exit" << endl;
   
    cout << "\t\t\tChoose: ";
    cin >> choice;

    if (choice == 1)
    {
        //Login();
        cout << endl;
        cout << "\t\t\t*******LOGIN SECTION*********" << endl;
        cout << "\t\t\t1.Admin" << endl;
        cout << "\t\t\t2.User" << endl;
        cout << "\t\t\tChoose: ";
        cin >> choice1;
        if (choice1 == 1)
        {
            LoginAdmin();
        }
        else if(choice1 == 2)
        {
            LoginChef();
        }
        else
        {
            cout << "Invalid..";
           // main();
        }
  
    }
    else if (choice == 2)
    {
        Register();
    }
    else if (choice == 3)
    {
        cout << "Program Exiting..." << endl;
        exit(0);
    }
    else
    {
        cout << "Invalid.Please try again..";
        
        system("cls");
       // main();
    }
    return 0;
}


void Register()
{
    system("cls");
    string name, username, password;
    cout << "--- User Register ---" << endl;
    cout << "Enter Username: ";
    cin.ignore(1, '\n');
    getline(cin, username);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Password: ";
    getline(cin, password);

    string checkUser_query = "select * from Chef where Username = '" + username + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            cout << "Username is already exist. Press Enter to Try Again...";
            (void)_getch();
            Register();
        }
        else
        {
            string insertCustomer_query = "insert into Chef (Username, name, password) values ('" + username + "', '" + name + "', '" + password + "')";
            const char* q = insertCustomer_query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate)
            {
                cout << endl << "You have been registered. Press Enter to Continue...";
                (void)_getch();
                main();
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}


void LoginChef()
{
    system("cls");
    string password;
    string username;

    cout << "--- Login Page User---" << endl;
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        password += ch;
        cout << '*';
    }

    string checkUser_query = "select username from chef where username = '" + username + "' and password = '" + password + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
                UserID = row[0];
           // AdminMenu();
            cout << "\nWelcome to the system." << endl;
            UserMenu();

        }
        else
        {
            char c;
            cout << "\nInvalid username or password. Want to try again? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                LoginChef();
            else
                main();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}


void LoginAdmin()
{
    system("cls");
    string password;
    string adminID;

    cout << "--- Login Page Admin---" << endl;
    cout << "Admin ID : ";
    cin >> adminID;
    cout << "Password : ";
    char ch;
    while ((ch = _getch()) != 13)
    {
        password += ch;
        cout << '*';
    }

    string checkUser_query = "select AdminID from admin where AdminID = '" + adminID + "' and password = '" + password + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        if (res->row_count == 1)
        {
            while (row = mysql_fetch_row(res))
                UserID = row[0];
            // AdminMenu();
            cout << "\nWelcome to the system Admin." << endl;
            AdminMenu();
           
        }
        else
        {
            char c;
            cout << "\nInvalid AdminID or password. Want to try again? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y')
                LoginAdmin();
            else
                main();
        }
    }
    else
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

void Feedback()
{
    ViewRecipe();
}


void Rank()
{
    int choice;
    system("cls");
    cout << "-----Rank Option------" << endl;
    cout << "1. Top Recipe(Rating)" << endl;
    cout << "2. Latest recipe" << endl;
    cout << "3. Back" << endl;
    cout << "Choose menu: ";

    cin >> choice;

    if (choice == 1)
    {
        qstate = mysql_query(conn, "SELECT RecipeID,Title,AvgRating FROM recipe WHERE AvgRating IS NOT NULL ORDER BY AvgRating DESC;");

        if (!qstate)
        {
            cout << setw(11) << "RecipeID" << setw(17) << "Title" << setw(17) << "AvgRating"  << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << setw(11) << row[0] << setw(17) << row[1] <<setw(17)<<row[2]<< endl;
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        system("pause");
        system("cls");
        Rank();
       
    }
    else if (choice == 2)
    {
        qstate = mysql_query(conn, "SELECT RecipeID,Title,Date FROM recipe ORDER BY Date DESC;");

        if (!qstate)
        {
            cout << setw(11) << "RecipeID" << setw(17) << "Title" << setw(17) << "Date" << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << setw(11) << row[0] << setw(17) << row[1] << setw(17) << row[2] << endl;
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        system("pause");
        system("cls");
        Rank();
    }
    else if (choice == 3)
    {
        UserMenu();
    }
    else
    {
        cout << "Invalid.Please choose between 1 - 2. Press Enter To Continue...";
    }
}

void UserMenu()
{
    int menu,i=1;

    system("cls");
    cout << "-----User Page------" << endl;

    cout << "1. View Recipe" << endl;
    cout << "2. Add Recipe" << endl;
    cout << "3. Search Recipe" << endl;
    cout << "4. Edit Recipe" << endl;
    cout << "5. Rank" << endl;
    cout << "6. Report" << endl;
    cout << "7. Logout" << endl;
    cout << "Choose menu: ";

    cin >> menu;

 
        if (menu == 1)
        {
            ViewRecipe();
        }
        else if (menu == 2)
        {
            InsertRecipe();
        }
        else if (menu == 3)
        {      
    
            Search();
        }
        else if (menu == 4)
        {
        
            EditRecipe();
        }
        else if (menu == 5)
        {
            Rank();
        }
        else if (menu == 6)
        {
            
            system("cls");
            cout << "--Frequency for category--" << endl;
            qstate = mysql_query(conn, "SELECT category.cid,category.category, COUNT(recipe.cid)AS Frequency FROM recipe inner join category on recipe.cid = category.cid WHERE recipe.status=1 GROUP BY category ORDER BY COUNT(recipe.cid) DESC;;");

            if (!qstate)
            {

                
                cout << setw(11) << "CategoryID" << setw(17) << "Category" << setw(17) << "Frequency" << endl;

                res = mysql_store_result(conn);
               
                while (row = mysql_fetch_row(res))
                {
                 //   int sales[5];
                  //  int sale = 0;

                 
                     //   cout << "Store #" << c + 1;

                       
                    
                    string a = row[0];
                    string b = row[2];
                    cout << setw(11) << row[0] << setw(17) << row[1] << setw(17)<<"("<<row[2]<<")";
                    for (int f = 0; f < stoi(row[2]); f++)
                    {
                        cout << " *";
                    }
                    cout <<endl;
                  //  cout << setw(11) << row[0] << setw(17) << row[1] << endl;
                    string update_query = "UPDATE category SET CountCat = '" + b + "' WHERE cid='" + a + "' ";
                    const char* q = update_query.c_str();
                    astate = mysql_query(conn, q);
                }

                
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }
            system("pause");
            UserMenu();
        }
        else if (menu == 7)
        {
            main();
        }

        else {
            cout << "Please choose between 1 - 7. Press Enter To Continue...";
            // void(_getch());
          
        
            
        }

    

}



void EditRecipe()
{
    system("cls");

    string recipeID,input;
    int choose,pilih;
    char option;
    cout << "-----Edit Recipe-----" << endl;
    cin.ignore(1, '\n');
   // qstate = mysql_query(conn, ""+UserID+"'");
   // getline(cin, data);
    string search_query = "Select recipe.recipeID,category.category,recipe.title,recipe.ingredient,recipe.description from recipe inner join category on recipe.cid=category.cid where username='" + UserID + "' and status = 1";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);


    if (!qstate)
    {
        cout << setw(11) << "RecipeID" << setw(17) << "Category"<<setw(20) << "Title" << setw(20) << "Ingredient" << setw(50) << "Description" <<  endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3]  << setw(50)<<row[4]<<endl;
        }

        cout << "Choose ID: ";
        cin >> recipeID;

        cout << endl << "-----Category-----" << endl;
        cout << "1. Title" << endl;
        cout << "2. Category" << endl;
        cout << "3. Description" << endl;
        cout << "4. Ingredient" << endl;
        cout << "Choose 1-4: ";
        cin >> choose;

        cin.ignore(1, '\n');
        if (choose == 1)
        {
            cout << "New Title: ";
            getline(cin, input);
            string update_query = "update recipe set title = '" +input  + "' where recipeID = '" + recipeID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }
        else if (choose == 2)
        {
          /*  cout << "New Category: ";
            getline(cin, input);
            //UPDATE recipe INNER JOIN category ON recipe.cid = category.cid SET category = 'lunch' WHERE recipeid = 11;
            string update_query = "update recipe set category = '" + input + "' where recipeID = '" + recipeID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);*/
            ViewCategory();
            cout << "New Category(choose new category number.): ";
            cin >> pilih;
            switch (pilih)
            {
            case 1:
            {
                //  UPDATE recipe INNER JOIN category ON recipe.cid = category.cid SET category = 'lunch' WHERE recipeid = 11;
                string update_query = "update recipe set cid = 1 where recipeID = '" + recipeID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                UserMenu();
                break;
            }
            case 2:
            {
            
                string update_query = "update recipe set cid = 2 where recipeID = '" + recipeID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q); 
                UserMenu();
                break;
            }
            case 3:
            {
                string update_query = "update recipe set cid = 3 where recipeID = '" + recipeID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                UserMenu();
                break;
            }
            case 4:
            {
                string update_query = "update recipe set cid = 4 where recipeID = '" + recipeID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                UserMenu();
                break;
            }
            case 5:
            {
                string update_query = "update recipe set cid = 5 where recipeID = '" + recipeID + "'";
                const char* q = update_query.c_str();
                qstate = mysql_query(conn, q);
                UserMenu();
                break;
            }
            default:
                cout << "Please choose between 1 - 5. Press Enter To Continue...";
                // void(_getch());
                system("cls");
                EditRecipe();
                break;
            }

        }
        else if (choose == 3)
        {
            cout << "New Description: ";
            getline(cin, input);
            string update_query = "update recipe set description = '" + input + "' where recipeID = '" + recipeID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }
        else if (choose == 4)
        {
            cout << "New Ingredient: ";
            getline(cin, input);
            string update_query = "update recipe set ingredient = '" + input + "' where recipeID = '" + recipeID + "'";
            const char* q = update_query.c_str();
            qstate = mysql_query(conn, q);
        }

        cout << "Do you want to edit other detail? (y/n): ";
        cin >> option;

        if (option == 'y' || option == 'Y')
            EditRecipe();
        else
            UserMenu();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

}


void giveStar()
{
    int sales[5];
    int sale = 0;

    for (int i = 0; i < 5; i++)
    {
        cout << "Please enter sales for store #" << i + 1 << endl;
        cin >> sale;
        sales[i] = sale / 100;
    }

    for (int c = 0; c < 5; c++)
    {
        cout << "Store #" << c + 1;
        for (int f = 0; f < sales[c]; f++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

void InsertRecipe()
{
   
   
    
    //cout << "Current Day, Date and Time is : " << asctime(ti) << endl;
    system("cls");
    //int category;
   // time_t tt;
   // struct tm* ti;
    //time(&tt);
   // ti = localtime(&tt);
    string  category,desc, title,ingredient;
    /*auto t = time(nullptr);
    auto tm = *localtime(&t);
    auto date = put_time(&tm, "%d/%m/%Y");
    cout << date << endl;*/
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y/%m/%d", timeinfo);
    string date(buffer);
    ViewCategory();
    char menu;
    char choose;
    cout << "-----Insert New Recipe(This process need time for admin to accept!!)-----" << endl;
    cout << "Do you want to proceed?(y/n)" ;
    cin >> menu;
    //cout << date;

   // ViewCategory();


    if (menu == 'Y' || menu == 'y')
    {
        
        cin.ignore(1, '\n');//'" + date + "',

        cout << "Category ID(Refer to category): ";
        getline(cin, category);
        cout << "Title Recipe: ";
        getline(cin, title);
        cout << "Ingredient: ";
        getline(cin, ingredient);
        cout << "Description(Step by step): " << endl;
        getline(cin, desc);
        string insert_query = "insert into Recipe (Username, CID,Title, Date,Ingredient, Description, Status) values ('" + UserID + "', '" + category + "','" + title + "' ,'" + date + "',  '" + ingredient + "','" + desc + "', '" + "0" + "')";
        const char* q = insert_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Recipe has been deposited." << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        do
        {
            cout << "Do you want add another recipe? (y/n): ";
            cin >> choose;
            if (choose == 'y' || choose == 'Y')
            {
                InsertRecipe();
            }
            else if (choose == 'n' || choose == 'N')
            {
                UserMenu();
            }
        } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');

    }
    else if(menu=='N'||menu=='n')
    {
        UserMenu();
    }
    else
    {
        cout << "Invalid input" << endl;
    }
       
  
   
  

   
}
void ViewFeedback()
{
   // system("cls");
    char choose;
    cout << "--- List of Feedback ---" << endl;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "select FeedID,Feedback,username,recipeid from feedback");

    if (!qstate)
    {
        cout << setw(11) << "FeedID" << setw(17) << "Feedback" << setw(17) << "Username"<< setw(17) << "RecipeID"<<endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << setw(17) << row[2] << setw(17) << row[3] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    //cout << "Press Enter To Back...";
    //_getch();
    //UserMenu();

}
void ViewCategory()
{
    system("cls");
    char choose;
    cout << "--- List of Category ---" << endl;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "select CID, Category from Category");

    if (!qstate)
    {
        cout << setw(11) << "CID" << setw(17) << "Category" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    //cout << "Press Enter To Back...";
    //_getch();
    //UserMenu();


}

void Search()
{
    
        system("cls");
        char choose;
        string title;
        cin.ignore(1, '\n');
        cout << "Search recipe by title: ";
        getline(cin, title);

        cout << "--- List of Searched Recipe ---" << endl;

        string search_query = "select recipe.recipeID, recipe.title,category.category from recipe join category on recipe.cid=category.cid where title like '%" + title + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << setw(11) << "Recipe ID" << setw(17) << "Recipe Ttile" << setw(20) << "Category"  << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2]  << endl;
            }

            cout << endl << "Do you want to search other recipe?(y/n): ";
            cin >> choose;

            if (choose == 'y' || choose == 'Y')
                Search();
            else if (choose == 'n' || choose == 'N')
                UserMenu();
        }
        else
        {
            cout << "Not found!" << mysql_errno(conn) << endl;
        }
    

}

void ViewRecipeFed()
{
    system("cls");
    char choose;
    cout << "--- List of Recipe ---" << endl;
    int i = 1;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "Select recipe.username,recipe.recipeID,recipe.title,category.category,recipe.date,IFNULL(recipe.avgrating,0) from recipe join category on recipe.cid=category.cid where status=1;");

    if (!qstate)
    {
        cout << setw(11) << "Username" << setw(17) << "RecipeID" << setw(17) << "Title" << setw(17) << "Category" << setw(17) << "Date" << setw(17) << "Rating" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << setw(17) << row[2] << setw(17) << row[3] << setw(17) << row[4] << setw(17) << row[5] << endl;
        }


    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ViewFeedback();
    ViewDetailFed();


    cout << "Press Enter To Back...";
    _getch();
    ViewRecipe();
}

void GiveRate()
{
    string  recipeid;
    int rating;
 
    char menu;
    char choose;
    cout << "-----Rate Recipe-----" << endl;
    cout << "Do you want to proceed?(y/n)";
    cin >> menu;
    //cout << date;

   // ViewCategory();


    if (menu == 'Y' || menu == 'y')
    {

       

        cout << "Select Recipe ID to rate: ";
        cin>>recipeid ;
        cout << "Rating for Recipe ID "<<recipeid<<": "<<endl;
        cin >> rating;
       
        string insert_query = "insert into rate (rating,recipeid,chef) values('"+to_string(rating)+"','" + recipeid + "','" + UserID + "')";
        const char* q = insert_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Rating recipe has been insert." << endl;
            string update_query = "UPDATE recipe SET AvgRating = (SELECT avg(rating) from rate where recipeID = '" + recipeid + "') WHERE recipeID = '" + recipeid + "'";
            const char* q = update_query.c_str();
            vstate = mysql_query(conn, q);
        }
        else
        {
            cout << "Invalid!"  << endl;
        }

        do
        {
            cout << "Do you want rate another recipe? (y/n): ";
            cin >> choose;
            if (choose == 'y' || choose == 'Y')
            {
                GiveRate();
            }
            else if (choose == 'n' || choose == 'N')
            {
                UserMenu();
            }
        } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');

    }
    else if (menu == 'N' || menu == 'n')
    {
        ViewRecipe();
    }
    else
    {
        cout << "Invalid input.Press enter" << endl;
        _getch();
        GiveRate();
    }

}



void ViewRecipe()
{
   
    system("cls");
    int choose;
    cout << "--- List of Recipe ---" << endl;
    int i = 1;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "Select recipe.username,recipe.recipeID,recipe.title,category.category,recipe.date,IFNULL(recipe.avgrating,0) from recipe join category on recipe.cid=category.cid where status=1;");

    if (!qstate)
    {
        cout << setw(11) << "Username" << setw(17) << "RecipeID" << setw(17) << "Title" <<setw(17)<< "Category" <<setw(17) << "Date"<< setw(17) << "Rating"<<endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] <<  setw(17) << row[2] << setw(17) << row[3] << setw(17) << row[4] << setw(17)<< row[5]<< endl;
        }
      
       
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "\nChoose option\n";
    cout << "1.View more recipe"<<endl;
    cout << "2.Rate recipe"<<endl;
    cout << "3.Back" << endl;
   
    cin >> choose;
    switch (choose)
    {
    case 1:
    {
        //  UPDATE recipe INNER JOIN category ON recipe.cid = category.cid SET category = 'lunch' WHERE recipeid = 11;
        ViewDetail();
        break;
    }
    case 2:
    {
        system("cls");
        // ViewRecipeFed();
        cout << "--- List of Recipe ---" << endl;
       
        string search_query = "Select recipe.username,recipe.recipeID,recipe.title,category.category,recipe.date,IFNULL(recipe.avgrating,0)as averageRating from recipe join category on recipe.cid=category.cid where status=1 and username !='"+UserID+"';";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);
        //date_format() used to convert the format of date.
       

        if (!qstate)
        {
            cout << setw(11) << "Username" << setw(17) << "RecipeID" << setw(17) << "Title" << setw(17) << "Category" << setw(17) << "Date" << setw(17) << "Rating" << endl;

            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << setw(11) << row[0] << setw(17) << row[1] << setw(17) << row[2] << setw(17) << row[3] << setw(17) << row[4] << setw(17) << row[5] << endl;
            }


        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        GiveRate();
        break;
    }
    case 3:
    {
        UserMenu();
    }
    
    default:
        cout << "Please choose between 1 - 5. Press Enter To Continue...";
        // void(_getch());
        system("cls");
        ViewRecipe();
        break;
    }
   
  

    cout << "Press Enter To Back...";
    _getch();
    UserMenu();
}

void ViewRating()
{

    system("cls");
    char choose;
    cout << "--- Recipe ---" << endl;
    int i = 1;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "Select recipe.username,recipe.recipeID,recipe.title,category.category,recipe.date,IFNULL(rateID,0) as RateID from recipe join category on recipe.cid=category.cid where status=1;");

    if (!qstate)
    {
        cout << setw(11) << "Username" << setw(17) << "RecipeID" << setw(17) << "Title" << setw(17) << "Category" << setw(17) << "Date" << setw(17) << "Rate ID" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << setw(17) << row[2] << setw(17) << row[3] << setw(17) << row[4] << setw(17) << row[5] << endl;
        }


    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    ViewDetail();


    cout << "Press Enter To Back...";
    _getch();
    UserMenu();
}

void GetFeedback()
{
    string Feedback,RecipeID;
    char choose;
    cin.ignore(1, '\n');
    cout << "Insert RecipeID you want to give a feedback:";
    getline(cin, RecipeID);
    cout << "Insert Feedback:";
    getline(cin, Feedback);
    string search_query = "insert into feedback (feedback,username,recipeid) values('"+Feedback+"','"+UserID+"','"+RecipeID+"')";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);
}

void ViewDetailFed()
{
    //system("cls");
    string Recipe;
    char choose;
    cin.ignore(1, '\n');
    cout << "Insert RecipeID you want to see more:";
    getline(cin, Recipe);
    string search_query = "Select title,ingredient,description from recipe where RecipeID='" + Recipe + "'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << setw(11) << "Title" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << endl;
            cout << endl;
            cout << setw(11) << "Ingredient" << endl;
            cout << setw(11) << row[1] << endl;
            cout << endl;
            cout << setw(11) << "Description" << endl;
            cout << setw(11) << row[2] << endl;

        }
        
        GetFeedback();
        cout << endl << "Do you want to see other recipe?(y/n): ";
        cin >> choose;

        if (choose == 'y' || choose == 'Y')
            ViewDetail();
        else if (choose == 'n' || choose == 'N')
            UserMenu();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}
void ViewDetail()
{
    //system("cls");
    string Recipe;
    char choose;
    cin.ignore(1, '\n');
    cout << "Insert RecipeID you want to see more:";
    getline(cin, Recipe);
    string search_query = "Select title,ingredient,description from recipe where RecipeID='"+Recipe+"'";
    const char* q = search_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << setw(11) << "Title" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << endl;
            cout << endl;
            cout << setw(11) << "Ingredient" << endl;
            cout << setw(11) << row[1] << endl;
            cout << endl;
            cout << setw(11) << "Description" << endl;
            cout << setw(11) << row[2] << endl;
           
        }

        cout << endl << "Do you want to see other recipe?(y/n): ";
        cin >> choose;

        if (choose == 'y' || choose == 'Y')
            ViewDetail();
        else if (choose == 'n' || choose == 'N')
            ViewRecipe();
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}



void ViewRecipeAdmin()
{
    system("cls");
    char choose;
    cout << "--- List of Recipe ---" << endl;
  //  int i = 1;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "Select recipe.username,recipe.recipeID,recipe.title,category.category,recipe.date from recipe inner join category on recipe.cid=category.cid where status=1");

    if (!qstate)
    {
        cout << setw(11) << "Username" << setw(17) << "RecipeID" << setw(17) << "Title" << setw(17) << "Category" << setw(17) << "Date" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << setw(17) << row[2] << setw(17) << row[3] << setw(17) << row[4] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "Press Enter To Back...";
    _getch();
    AdminMenu();
}

void ListUser()
{
    system("cls");
    char choose;
    cout << "--- List of User ---" << endl;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "SELECT Username,Name FROM chef");

    if (!qstate)
    {
        cout << setw(11) << "Username" << setw(17) << "Name" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "Press Enter To Back...";
    _getch();
    AdminMenu();
   

}
void AdminMenu()
{
    int menu; 
    system("cls");
    cout << "-----Admin Page------" << endl;
    
    cout << "1.Approve recipe." << endl;
    cout << "2.View recipe(approved)." << endl;
    cout << "3.Add category." << endl;
    cout << "4.List of user." << endl;
    cout << "5.Log out." << endl;
    cout << "Choose:";

    cin >> menu;

    switch (menu)
    {
    case 1:
        Approve();
        break;
    case 2:
        ViewRecipeAdmin();
        break;
    case 3:
        //Approve();
        InsertCategory();
        break;
    case 4:
        ListUser();
     
        break;
    case 5:
        main();
        break;
    default:
        cout << "Please choose between 1 - 2. Press Enter To Continue...";
        // void(_getch());
        system("cls");
        AdminMenu();
        break;
    }
}

void InsertCategory()
{
    string  category;
   
    ViewCategory();
    char menu;
    char choose;
    cout << "-----Insert New Category------" << endl;
    cout << "Do you want to proceed?(y/n)";
    cin >> menu;
    //cout << date;

   // ViewCategory();


    if (menu == 'Y' || menu == 'y')
    {

        cin.ignore(1, '\n');

        cout << "Category name: ";
        getline(cin, category);
        string insert_query = "insert into category (category) values ( '" + category + "')";
        const char* q = insert_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Category has been add successfully." << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        do
        {
            cout << "Do you want add another category? (y/n): ";
            cin >> choose;
            if (choose == 'y' || choose == 'Y')
            {
                InsertCategory();
            }
            else if (choose == 'n' || choose == 'N')
            {
                AdminMenu();
            }
        } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');

    }
    else if (menu == 'N' || menu == 'n')
    {
        AdminMenu();
    }
    else
    {
        cout << "Invalid input" << endl;
    }






}

void Approve()
{
    system("cls");
    char choose;
    string  choice;
    cin.ignore(1, '\n');

   
    cout << "--- List of Recipe that have not been approve ---" << endl;

    //date_format() used to convert the format of date.
    qstate = mysql_query(conn, "SELECT Username,RecipeID,Title FROM recipe where status = 0");

    if (!qstate)
    {
        cout << setw(11) << "Username" << setw(17) << "RecipeID" << setw(17)<<"Title"<< endl;
        cout << "------------------------------------------------------" << endl;

        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << setw(11) << row[0] << setw(17) << row[1] <<setw(17)<<row[2]<< endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    cout << "Choose Recipe ID you want to approve: ";
    getline(cin, choice);

    string insert_query = "UPDATE recipe SET status = 1,adminID='"+UserID+"' WHERE RecipeID = '"+choice+"'";
    const char* q = insert_query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << endl << "Recipe has been approve." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    do
    {
        cout << "Do you want approve another recipe? (y/n): ";
        cin >> choose;
        if (choose == 'y' || choose == 'Y')
        {
            Approve();
        }
        else if (choose == 'n' || choose == 'N')
        {
            AdminMenu();
        }
    } while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');

    cout << "Press Enter To Back...";
    _getch();
    
}