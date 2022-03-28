#include <vector>
#include <fstream>

using namespace std;
ifstream f("citire.txt");
ofstream g("afisare.txt");

int  k, nrcuv, x, y, nrf, initial, N, M, starifinale[10000001];
vector < pair<int,char> >v[10000001];                   // facem pereche de tip ( nod 2 , litera ) pentru a verifica mai usor starea curenta
vector <int> backup;                        // vector dinamic facut pentru trace route
char l;
string cuvant;


int DFA(int starifinale[], string cuvinte, int stare, int nrF)              // bfs modificat
{
    int poz=0;                                      // poz reprezinta pozitia literei din cuvant in momentul executiei

    while(poz<cuvinte.size())
    {
        char litera = cuvinte[poz];                  // retinem litera pe care ne aflam
        bool ok = 0;                     //ok verifica daca avem litera respectiva pe muchie (daca putem sa avansam cu verificarea cuv.)
        for(int i=0; i<v[stare].size(); i++)
        {
            if(v[stare][i].second == litera)
            {
                ok = 1;                                      //ok = 1 daca litera este aceeasi
                stare = v[stare][i].first;                  //retinem starea (pe first avem y)

                backup.push_back(stare);           // adaugam pentru fiecare litera, numarul nodului pe care aceasta a parcurs-o
                break;
            }
        }

        if(ok == 0)
            {
                backup.clear();         // curatam vectorul de trace route
                return 0;
            }
        poz = poz + 1;                  // crestem poz pentru a verifica urmatoarea litera
    }

    for(int i=0; i<nrf; i++)
        if(stare == starifinale[i])          // verificam daca starea initiala = starea finala
            return 1;

    backup.clear();                         // curatam vectorul de trace route la terminarea functiei
    return 0;                               // daca nu, returnam 0


}

int main()
{
    f>>N;                           //citire numar de stari
    f>>M;                               //M este nr de tranzitii

    for(int i=0; i<M; i++)
    {
        f>>x>>y>>l;              //citim nodul x, nodul y si litera de pe muchie prin care facem tranzitia
        v[x].push_back(make_pair(y,l));                        //construim perechile de tipul (y,litera)
    }

    f>>initial;
    f>>nrf;
    for(int i=0; i<nrf; i++)
        f>>starifinale[i];

    f>>nrcuv;
    for(int i=0; i<nrcuv; i++)
    {
        f>>cuvant;
        backup.push_back(0);
        if(DFA(starifinale,cuvant,initial,nrf)!=0)                   // apelam functia de bfs pentru a verifica cuv
            {
                g<<"DA"<<endl;                    //daca cuv este acceptat de dfa atunci afisam mesajul corespunzator si afisam si traseul pe care a trebuit sa il parcurga cuvantul respectiv pana in starea finala
                for (auto i= backup.begin();i!=backup.end();i++)
                    g<<*i<<" ";
                g<<endl;
                backup.clear();
            }
        else
            g<<"NU"<<endl;                    //daca cuv nu este acceptat de dfa atunci afisam mesajul corespunzator
    }

    return 0;
}
