#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>

using namespace std;

int        Create();
int        Check(string);
int        LogIn(string);

int        main(void)
{
int    a;
    while (true)
    {
        cout<<"Enter\n1>Create An Account\n2>Log In\n3>Exit\n:";
                cin>>a;
        switch (a)
        {
        case 1:
            cin.ignore(1);
                if (Create())
                    cout<<"Account Is Created";
                else
                    cout<<"Account Is Not Created";
                break;
        case 2:
            char        Email[100];
                cout<<"Enter Email  :     ";        cin>>Email;
                if (Check(Email))
                    {
                        cout<<"Logged In";
                        LogIn(Email);
                    }
                else
                    cout<<"Incorrect Email Or Password";
                break;
        case 3:
                return  0;
        }
    getch();
    system("cls");
    }
}

int        LogIn(string    Email)
{
    MYSQL         *conn;
    MYSQL_RES     *res,*res1;
    MYSQL_ROW      row,row1;
    string         Query,Name,Number,email;
    string         Temp;
    int            b;
    char           name[100];
    const char     *Q;

conn = mysql_init(0);
conn = mysql_real_connect(conn,"localhost","root","","TrueCaller",0,NULL,0);

if (!conn)
{
    mysql_close(conn);
    return  0;
}

    while (true)
    {
        getch();
        system("cls");
        cout<<"Enter\n1>Add Contact\n2>See Contact\n3>Search Number\n4>Exit\n:";
                cin>>b;
        switch (b)
        {
            case 1:
                cin.ignore(1);
                    cout<<"Enter Name    :      ";      gets(name);
                        Name = name;
                    cout<<"Enter Number  :      ";      cin>>Number;
                    Query = "Select * From Account Where Phone = '"+Number+"'";
                        Q = Query.c_str();

                    if (!mysql_query(conn,Q))
                    {
                        res = mysql_store_result(conn);
                        if (!res->row_count)
                        {
                            cout<<"Incorrect Number";
                            break;
                        }
                        row = mysql_fetch_row(res);
                        email = row[2];
                    }
                    else
                        cout<<mysql_error(conn);

                    Query = "Insert Into "+Email+" values('"+Number+"','"+Name+"','"+email+"')";
                        Q = Query.c_str();

                    if (!mysql_query(conn,Q))
                        cout<<"Contact Saved"<<endl;
                    else
                        cout<<mysql_error(conn)<<endl;

                    break;
            case 2:
                    Query = "Select * from "+Email+"";
                        Q = Query.c_str();
                    if (!mysql_query(conn,Q))
                    {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                        {
                            cout<<"Name      :     "<<row[1]<<endl;
                            cout<<"Number    :     "<<row[0]<<endl;
                            cout<<"Email     :     "<<row[2]<<endl<<endl;
                        }
                    }
                    else
                        cout<<mysql_error(conn)<<endl;
                    break;
            case 3:
                    cout<<"Enter  Number   :     ";     cin>>Number;
                    Query = "Select * From "+Email+"";
                        Q = Query.c_str();
                    if (!mysql_query(conn,Q))
                    {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                        {
                            Temp = row[2];
                                Query = "Select * From "+Temp+" Where Phone = '"+Number+"'";
                                    Q = Query.c_str();
                                if (!mysql_query(conn,Q))
                                {
                                    res1 = mysql_store_result(conn);
                                    if (res1->row_count)
                                    {
                                        row1 = mysql_fetch_row(res1);
                                        cout<<"Name      :       "<<row1[0]<<endl;
                                        cout<<"Number    :       "<<row1[1]<<endl;
                                        cout<<"Email     :       "<<row1[2]<<endl;
                                        break;
                                    }
                                }
                                else
                                    cout<<mysql_error(conn)<<endl;
                            }
                        }
                    else
                        cout<<mysql_error(conn)<<endl;
                    break;
            case 4:
                    mysql_free_result(res);
                    mysql_close(conn);
                    return  0;
        }
    }
}

int        Check(string    Email)
{
    string        Password,Query;
    const char    *Q;
    MYSQL         *conn;
    MYSQL_RES     *res;

conn = mysql_init(0);
conn = mysql_real_connect(conn,"localhost","root","","TrueCaller",0,NULL,0);

if (!conn)
{
    mysql_close(conn);
    return  0;
}

    cout<<"Enter  Password      :      ";       cin>>Password;

    Query = "Select * from Account where Email = '"+Email+"' and Password = '"+Password+"'";
        Q = Query.c_str();
    if (!mysql_query(conn,Q))
    {
        res = mysql_store_result(conn);
        if (res->row_count)
        {
            mysql_close(conn);
            return  1;
        }
    }
    else
        cout<<mysql_error(conn)<<endl;

mysql_free_result(res);
mysql_close(conn);
return  0;
}

int        Create()
{
    char          name[100];
    MYSQL         *conn;
    string        Name,Password,Email,Query,Phone;
    const char    *Q;

conn = mysql_init(0);
conn = mysql_real_connect(conn,"localhost","root","","TrueCaller",0,NULL,0);

if (!conn)
{
    mysql_close(conn);
    return  0;
}

    cout<<"Enter Name          :     ";     gets(name);
        Name = name;
    cout<<"Enter Email         :     ";     cin>>Email;
    cout<<"Enter Password      :     ";     cin>>Password;
    cout<<"Enter Phone Number  :     ";     cin>>Phone;

    Query = "Insert Into Account Values ('"+Name+"','"+Phone+"','"+Email+"','"+Password+"')";
        Q = Query.c_str();

    if (!mysql_query(conn,Q))
    {
        Query = "Create Table "+Email+" (Phone long,Name text,Email char(100))";
            Q = Query.c_str();

        if (!mysql_query(conn,Q))
        {
            mysql_close(conn);
            return  1;
        }

        cout<<mysql_error(conn);
        cout<<"Contact Table not Created";
    }
    else
        cout<<mysql_error(conn);

mysql_close(conn);
return  0;
}
