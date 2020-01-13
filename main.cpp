#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct
{
    float x, y;
}punct;

int test_orientare(punct A, punct B, punct C)
{
    float z = B.x * C.y + A.x * B.y + C.x * A.y - B.x * A.y - C.x * B.y - A.x * C.y;
    if(z == 0)
        return 1;///punctele sunt coliniare
    else if(z < 0)
        return 2;///C este situat la dreapta [AB]
    else return 3;///C este situat la stanga [AB]

}
int sortare(punct a, punct b)
{
    if(a.x == b.x)
    {
        if(a.y > b.y)
            return 1;
        return 0;
    }
    else
    {
        if(a.x > b.x)
            return 1;
        return 0;
    }
}

int punct_interior_tri(punct A,punct B, punct C, punct D)
{
     // verific daca D se afla in interiorul triunghiului ABC
     // la testul de orientare D trebuie sa fie de aceeasi parte a fiecarei laturi
     int t1, t2, t3;
     t1 = test_orientare(A, B, D);
     t2 = test_orientare(B, C, D);
     t3 = test_orientare(C, A, D);
     if(t1 == t2 && t2 == t3)
        return 1;
     return 0;
}


int main()
{
    int i;
    vector <punct> A(4);
    ifstream fin("date.in");
    for(i = 0; i < 4; i++)
        fin >> A[i].x >> A[i].y;

    if(test_orientare(A[0], A[1], A[2]) == 1 && test_orientare(A[0], A[1], A[3]) == 1 ) //segement A B C
    {
        cout << "Punctele sunt coliniare\n";
        sort(A.begin(), A.end(), sortare);
        cout << "I={ (" << A[0].x << "," << A[0].y << "),(" << A[3].x << "," << A[3].y << ")} \n ";
        cout <<< " J=(" << A[1].x << "," << A[1].y << "),(" << A[2].x << "," << A[2].y <<")}";
    }

    else if((test_orientare(A[0], A[1], A[2]) == 2 && test_orientare(A[0], A[1], A[3]) == 3) || //seg de o parte sau de alta
            (test_orientare(A[0], A[1], A[2]) == 3 && test_orientare(A[0], A[1], A[3]) == 2))
       {
           if(test_orientare(A[2], A[3], A[0]) != test_orientare(A[2], A[3], A[1]))  // Daca A si B sunt de parti diferite fata de [CD] atunci e patrulater
           {
               cout << "S-a format un patrulater!\n";
               cout << "I={ (" << A[0].x << "," << A[0].y << "),(" << A[1].x << "," << A[1].y << ")} \n ";
               cout << " J=(" << A[2].x << "," << A[2].y << "),(" << A[3].x << "," << A[3].y << ")}";
           }
           else // altfel e triunghi si verificam care din A sau B sunt in intrerior
           {
               int t1, ok = 0;
               t1 = punct_interior_tri(A[1], A[2], A[3], A[0]);
               if(t1 == 1) // A e in int lui BCD;
               {
                   cout << "S-a format un triunghi!\n";
                   ok = 1;
                   cout << "I={ (" << A[1].x << "," << A[1].y << "),(" << A[2].x << "," << A[2].y << "),(" << A[3].x << " ," << A[3].y << ")} \n ";
                   cout << " J=(" << A[0].x << "," << A[0].y << ")}";
               }
               else   // Verificam daca B e in int lui ACD;
               {
                   t1 = punct_interior_tri(A[0], A[2], A[3], A[1]);
                   if(t1 == 1) // B e in int lui ACD;
                   {
                        cout << "S-a format un triunghi!\n";
                        ok = 1;
                        cout << "I={ (" << A[0].x << "," << A[0].y << "),(" << A[2].x << "," << A[2].y << "),(" << A[3].x << " ," << A[3].y << ")} \n ";
                        cout << " J=(" << A[1].x << "," << A[1].y << ")}";
                   }
               }
           }
       }
       // A[2] si A[3] sunt de aceeasi parte fata de A0A1
       // verificam daca e triungi sau patrulater acoperirea convexa

    else
    {
        int t1, ok = 0;
        t1 = punct_interior_tri(A[0], A[1], A[2], A[3]);
        if(t1 == 1) // D e in int lui ABC;
        {
            cout << "S-a format un triunghi!\n";
            ok = 1;
            cout << "I={ (" << A[0].x << "," << A[0].y << "),(" << A[1].x << "," << A[1].y << "),(" << A[2].x << " ," << A[2].y << ")} \n ";
            cout << " J=(" << A[3].x << "," << A[3].y << ")}";
        }
        else   // Verificam daca C e in int lui ABD
        {
            t1 = punct_interior_tri(A[0], A[1], A[3], A[2]);
            if(t1 == 1) // C e in int lui ABD;
            {
                cout << "S-a format un triunghi!\n";
                ok = 1;
                cout << "I={ (" << A[0].x << "," << A[0].y << "),(" << A[1].x << "," << A[1].y << "),(" << A[3].x << " ," << A[3].y << ")} \n ";
                cout << " J=(" << A[2].x << "," << A[2].y << ")}";
            }
        }

        if(ok == 0) // Acoperirea convexa este un patrulater
        {
            cout << "S-a format un patrulater!\n";
            // facem test de orientare dupa segmentul AC
            int t1, t2;
            t1 = test_orientare(A[0], A[2], A[1]); // B fata de AC
            t2 = test_orientare(A[0], A[2], A[3]); // D fata de AC
            if(t1 == t2) // inseamna ca AC nu e diagonala
            {
                cout << "I={ (" << A[0].x << "," << A[0].y << "),(" << A[3].x << "," << A[3].y << ")} \n ";
                cout << " J=(" << A[2].x << "," << A[2].y << "),(" << A[1].x << "," << A[1].y << ")}";
            }
            else
            {
                cout << "I={ (" << A[0].x << "," << A[0].y << "),(" << A[2].x << "," << A[2].y << ")} \n ";
                cout <<< " J=(" << A[1].x << "," << A[1].y << "),(" << A[3].x << "," << A[3].y << ")}";
            }
        }
    }
    return 0;
}
