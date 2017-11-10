#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
//class with properties of player
class player
{
private:
char mat[10][10];
int hits;
//store the total parts of each of the different ship destroyed
int count_ship[5];
//store whether all parts of particular ship is destroyed
bool ship_destroy[5];

public:
string name;
int hitmat[10][10];
player(string Name)
{
    name=Name;
    hits=0;
    for(int i=0;i<5;i++)
    {
        count_ship[i]=0;
        ship_destroy[i]=0;
    }
}
void initialise_player_matrix();
int set_ship_position(int);
void display_matrix();
void hit_display_matrix();
int hit(int,int);
int show_winner(int,player,player);
};
//function to display the players matrix
void player::display_matrix()
{

    cout<<"    "<<setw(4);
    for(int i=0;i<10;i++)
    {
        cout<<setw(4)<<i;
    }
    cout<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<setw(4)<<i;
        for(int j=0;j<10;j++)
            cout<<setw(4)<<this->mat[i][j];
        cout<<endl;
    }
    return;
}
//function to display the matrix of players after attack
void player::hit_display_matrix()
{
    cout<<"    "<<setw(4);
    for(int i=0;i<10;i++)
    {
        cout<<setw(4)<<i;
    }
    cout<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<setw(4)<<i;
        for(int j=0;j<10;j++)
        {
            if(this->hitmat[i][j])
            {
               if(this->mat[i][j]=='.')
                    cout<<setw(4)<<"#";
                else
                {
                    if(ship_destroy[mat[i][j]-'a']==1)
                        cout<<setw(4)<<this->mat[i][j];
                    else
                        cout<<setw(4)<<"x";
                }

            }
            else
                cout<<setw(4)<<'.';
        }
        cout<<endl;
    }
    return;
}
//positioning the ship by the player
int player::set_ship_position(int length)
{
    this->display_matrix();
    char align;
    int col,row;
    bool f=1;
    cin>>row>>col>>align;//row,column and alignment of ship
    align=toupper(align);
    if(row>=10||row<0||col>=10||col<0)
        return 2;
    if(align!='H'&&align!='V')
        return 2;
    if(align=='H')
        if(col+length>10)
            return 2;
    if(align=='V')
        if(row+length>10)
            return 2;
    if(align=='H')
        {
            for(int i=col;i<col+length;i++)
                {
                    if(this->mat[row][i]!='.')
                    {
                        f=0;
                        return 3;
                    }
                }
            if(f)
                {
                    for(int i=col;i<col+length;i++)
                        this->mat[row][i]='f'-length;
                    return 1;
                }
        }
    if(align=='V')
        {
            for(int i=row;i<row+length;i++)
                {
                    if(this->mat[i][col]!='.')
                    {
                        f=0;
                        return 3;
                    }
                }
            if(f)
                {
                    for(int i=row;i<row+length;i++)
                        this->mat[i][col]='f'-length;
                    return 1;
                }
        }
}
void player::initialise_player_matrix()
{
    //Initialize all values of matrix to '.' at start '.' denotes water
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            mat[i][j]='.';
            hitmat[i][j]=0;
        }

    int ship_length=5;

    int flag=1;
    //calling set_ship_position function to set ship's position for different length of ship
    for(int i=0;i<5;)
    {
        if(flag==1)
        {
            system("cls");
            cout<<this->name<<"'s turn to set its ship position"<<endl;
            cout<<"\n\n";
            cout<<"Enter the starting position of ship in the form row index column ,index and alignment in one line"<<endl;
            cout<<"Enter row index in range '0-9' , column index in range '0-9' and H for horizontal alignment and V for vertical allignment"<<endl;
            cout<<"Example: '3 5 H' for starting position in 3rd row,5th column and horizontal alignment"<<endl;
            cout<<"----------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Enter the starting position of ship of length "<<ship_length<<endl;
            flag=this->set_ship_position(ship_length);
            if(flag==1)
            {
                i++;
                ship_length--;
            }
            else
            {
                if(flag==2)
                cout<<"The position is out of bound! please enter the start position again"<<endl;
                if(flag==3)
                cout<<"The position is already occupied by other ship! Please enter the start position again"<<endl;
                flag=1;
                Sleep(3* 1000);

            }
        }
    }
    system("cls");
    cout<<this->name<<"'s matrix"<<endl;
    this->display_matrix();
    getchar();
    getchar();
}
//function for game play between players where players will get chances alternatively
int player::hit(int x,int y)
{
    if(mat[x][y]!='.')
        {
            hits++;
            count_ship[mat[x][y]-'a']++;
            if(count_ship[mat[x][y]-'a']>=('e'-mat[x][y]+1))
                ship_destroy[mat[x][y]-'a']=1;
        }
    hitmat[x][y]=1;
    if(hits==15)
        return 1;
    else if(mat[x][y]!='.')
        return 2;
    else
        return 0;
}
int player::show_winner(int w,player p1,player p2)
{
    system("cls");
      if(w==1)
      {
          cout<<"Congrats!! "<<p1.name<<" won by "<<abs(p1.hits-p2.hits)<<" points"<<endl;
      }
      if(w==2)
      {
          cout<<"Congrats!! "<<p2.name<<" won by "<<abs(p2.hits-p1.hits)<<" points"<<endl;
      }
      getchar();
      getchar();
}
void start_game()
{
    //Input name of both players
    string name1,name2;
    getchar();
    cout<<"Enter the name of player one: ";
    getline(cin,name1);
    cout<<"\nEnter the name of player two: ";
    getline(cin,name2);
    player p1(name1),p2(name2);
    //Initialize position of ships of both players
    p1.initialise_player_matrix();
    p2.initialise_player_matrix();
    //Game play
    int gameover=0,player_chance=1,winner;
    system("cls");
    //loop for to control player chances
    while(!gameover)
    {
        //loop to control player 1 game play
        while(player_chance==1&&!gameover)
        {   system("cls");
            cout<<"It's "<<p1.name<<"'s Chance to attack"<<endl;
            cout<<"\n\n";
            cout<<p2.name<<"'s current affected areas ('x' denotes correct hit ,'#' denotes miss hit)          "<<endl;
            p2.hit_display_matrix();
            cout<<"Enter the coordinates you want to attack : "<<endl;
            int x,y;
            cin>>x>>y;
            if(x<0||x>=10||y<0||y>=10)
                cout<<"Please enter the coordinates which are present in the matrix! "<<endl;
            else if(p2.hitmat[x][y])
                cout<<"This position is already targeted please enter some another position"<<endl;
            else
            {
                player_chance=2;
               int win=p2.hit(x,y);
               system("cls");
               p2.hit_display_matrix();
               if(win==2)
               {
                   cout<<"It's a hit!! You will get another chance!!"<<endl;
                   player_chance=1;
               }
               if(win==1)
               {
                   gameover=1;
                   winner=1;
                   player_chance=1;
               }
               if(!win)
               {
                   cout<<"It's a miss hit"<<endl;
               }
            }
            Sleep(2.5*1000);
        }

        //loop to control player 2 game play
        while(player_chance==2&&!gameover)
        {
            system("cls");
            cout<<"It's "<<p2.name<<"'s Chance to attack ('x' denotes correct hit ,'#' denotes miss hit)"<<endl;
            cout<<"\n\n";
            cout<<p1.name<<"'s current affected areas "<<endl;
            p1.hit_display_matrix();
            cout<<"Enter the coordinates you want to attack : "<<endl;
            int x,y;
            cin>>x>>y;
            if(x<0||x>=10||y<0||y>=10)
                cout<<"Please enter the coordinates which are present in the matrix! "<<endl;
            else if(p1.hitmat[x][y])
                cout<<"This position is already targeted please enter some another position"<<endl;
            else
            {
               player_chance=1;
               int win=p1.hit(x,y);
               system("cls");
               p1.hit_display_matrix();
               if(win==2)
               {
                   cout<<"It's a hit!! You will get another chance!!"<<endl;
                   player_chance=2;
               }
               if(win==1)
               {
                   gameover=1;
                   winner=2;
               }
               if(!win)
               {
                    cout<<"It's a miss hit"<<endl;
               }
            }
            Sleep(2.5*1000);
        }
    }
      p1.show_winner(winner,p1,p2);
}
int main()
{
    system("cls");
    //Main menu
    cout<<"\n\n\n\n\n";
    cout<<"\t\t\t\t\t*******************************************"<<endl;
    cout<<"\t\t\t\t\t\tMain Menu"<<endl;
    cout<<"\n";
    cout<<"\t\t\t\t\t\t1.Start a new game"<<endl;
    cout<<"\n";
    cout<<"\t\t\t\t\t\t2.Exit"<<endl;
    cout<<"\t\t\t\t\t*******************************************"<<endl;
    int choice;
    cin>>choice;
    if(choice==1)
        {
            start_game();
            main();
        }
    else if(choice==2)
    {
        system("cls");
        cout<<"\n\n\n\n\n";
        cout<<"\t\t\t\t********************************"<<endl;
        cout<<"\t\t\t\t\tThank You for Playing"<<endl;
        cout<<"\t\t\t\t********************************"<<endl;
        return 0;
    }
    else
    {
        cout<<"Wrong Choice!! Enter again"<<endl;
        main();
    }
}
