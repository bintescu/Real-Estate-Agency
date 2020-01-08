#include <iostream>
#include <vector>
#include <typeinfo>
#include <set>
#include <iterator>
#include <cstring>
#include <stdio.h>
#include <windows.h>
using namespace std;


class locuinta
{
protected:
    char id_client[30];
    float suprafata_utila;
    double discount;
    float chirie;
    float pret;
public:
    float get_chirie()
    {
        return this->chirie;
    }
     // functia get_suprafata este implementata pentru creearea setului
     // la verificarea unicitatii necesita operatorul< ce trebuie rescris
    float get_suprafata() const
    {
        return this->suprafata_utila;
    }
    template <class tip> friend void calculChirie(tip&);
    locuinta(char* s ="nedefinit",float supr=0,double disc=0)
    {
        strcpy(id_client,s);
        this->suprafata_utila=supr;
        this->discount=disc;
        this->chirie=0;
        this->pret=0;
    }

    locuinta(const locuinta &ob)
    {
        strcpy(this->id_client,ob.id_client);
        this->suprafata_utila=ob.suprafata_utila;
        this->discount=ob.discount;
        this->chirie=ob.chirie;
        this->pret=ob.pret;
    }
    friend istream& operator>>(istream &in,locuinta &ob)
    {
        int ok;
        cout<<"\n Introduceti id_client :";
        in>>ob.id_client;
        cout<<"\n  Introduceti suprafata utila:";
        do
        {
            ok=1;
            try
            {
                in>>ob.suprafata_utila;
                if(ob.suprafata_utila<0)
                    throw(2);

            }
            catch(int n)
            {
                cout<<"\n  !trebuie sa introduceti o suprafata pozitiva !";
                cout<<"\n  Introduceti din nou suprafata utila:";
                ok=0;
            }

        }
        while(!ok);
        cout<<"\n Introduceti discount :";
        do
        {
            ok=1;
            try
            {
                in>>ob.discount;
                if(ob.discount<0 || ob.discount>10)
                    throw(2);
            }
            catch(int n)
            {
                cout<<"\n  !discount-ul trebuie sa fie intre 0 si 10!";
                cout<<"\n  Introduceti din nou discount:";
                ok=0;
            }

        }
        while(!ok);
        cout<<"\n Introduceti pretul :";
        in>>ob.pret;
        return  in;
    }
    friend ostream& operator<<(ostream &out,locuinta &ob)
    {
        out<<"\n Locuinta cu clientul :";
        out<<ob.id_client;
        out<<" are suprafata utila :";
        out<<ob.suprafata_utila;
        out<<" cu discount :";
        out<<ob.discount<<"%";
        return out;
    }
    virtual void afisare() const
    {
        cout<<"\n Locuinta cu clientul :";
        cout<<id_client;
        cout<<" are suprafata utila :";
        cout<<suprafata_utila;
        cout<<" cu discount :";
        cout<<discount;
        cout<<" si chiria ";
        cout<<chirie;
    }
    virtual ~locuinta()
    {
        strcpy(id_client,"null");
        suprafata_utila = 0;
        discount=0;
        pret=0;

    }

};


class apartament:public locuinta
{
private:
    char strada_numar[100];
    int nr_etaj;
public:
    template <class tip> friend void calculChirie(tip&);
    void afisare() const
    {
        cout<<"\n Locuinta clientului :";
        cout<<this->id_client;
        cout<<" de pe strada, numarul : ";
        cout<<this->strada_numar;
        cout<<" la etajul : ";
        cout<<this->nr_etaj;
        cout<<" suprafata utila : ";
        cout<<this->suprafata_utila;
        cout<<" are si discount-ul :";
        cout<<this->discount;
        cout<<" chiria :";
        cout<<this->chirie;
    }
    apartament(char *strada="strada null",int nr=-2,char* s ="nedefinit",float supr=0,double disc=0): locuinta(s,supr,disc)
    {
        strcpy(this->strada_numar,strada);
        nr_etaj = nr;
    }
    friend istream& operator>>(istream &in, apartament &ob)
    {   int ok=0;
        in>>dynamic_cast<locuinta &>(ob);
        cout<<"\n Strada si numarul :";
        fflush(stdin);
        in.getline(ob.strada_numar,100);
        cout<<" etaj: ";
        do
        {
            ok=1;
            try
            {
                in>>ob.nr_etaj;
                if(ob.nr_etaj<0 || ob.nr_etaj>1000)
                    throw(2);
            }
            catch(int n)
            {
                cout<<"\n  ! Etajul introdus in mod eronat !";
                cout<<"\n  Introduceti din nou etajul:";
                ok=0;
            }

        }
        while(!ok);
    }
    ~apartament()
    {
        strcpy(strada_numar,"null");
        nr_etaj=0;
    }
};

class casa:public locuinta
{
private:
    char strada_numar[100];
    float suprafata_curte;
    int numar_etaje;
    float supr_pe_etaj[30];
    float pret_curte;
public:
    int get_numar()
    {
        return numar_etaje;
    }
    template <class tip> friend void calculChirie(tip&);
    friend void calculChirie(casa &);
    casa(char *id_client="null", float suprafata_utila=0, float discount=0, char *strada="nedefinit",float suprafata_curte=0,int nr_etaje=0):locuinta(id_client,suprafata_utila,discount)
    {
        this->suprafata_curte=suprafata_curte;
        this->numar_etaje=nr_etaje;
        strcpy(this->strada_numar,strada);
        for(int i=0; i<=numar_etaje; i++)
        {
            supr_pe_etaj[i]=0;
        }

    }
    casa(const casa& ob)
    {
        this->chirie=ob.chirie;
        this->discount=ob.discount;
        strcpy(this->id_client,ob.id_client);
        this->pret=ob.pret;
        this->suprafata_utila=ob.suprafata_utila;
        strcpy(this->strada_numar,ob.strada_numar);
        this->suprafata_curte=ob.suprafata_curte;
        this->numar_etaje=ob.numar_etaje;
        this->pret_curte=ob.pret_curte;
        for(int i=0; i<=numar_etaje; i++)
            this->supr_pe_etaj[i]=ob.supr_pe_etaj[i];
    }
    void afisare() const
    {
        cout<<"\n locuinta clientului :";
        cout<<this->id_client;
        cout<<" de pe strada,numarul : ";
        cout<<this->strada_numar;
        cout<<" cu pret pe m2 suprafata utila :";
        cout<<this->pret;
        cout<<" suprafata utila:";
        cout<<this->suprafata_utila;
        cout<<" suprafata curte : ";
        cout<<this->suprafata_curte;
        cout<<" cu numar de etaje :";
        cout<<this->numar_etaje;
        cout<<" are si discount-ul :";
        cout<<this->discount;
        cout<<" cu chiria :";
        cout<<this->chirie;
        if(numar_etaje >=0)
        {
            cout<<"\n pe fiecare etaj are urmatoarele suprafete:";
            for(int i=0; i<=numar_etaje; i++)
            {
                cout<<"\n pe etajul "<<i<<" :";
                cout<<supr_pe_etaj[i];
            }
        }
    }
    friend istream& operator>>(istream &in,casa &ob)
    {
        in>>dynamic_cast<locuinta &>(ob);
        cout<<"\n Introduceti strada,numar : ";
        fflush(stdin);
        in.getline(ob.strada_numar,100);
        cout<<"\n Introduceti suprafata curtii :";
        int ok;
        do
        {
            ok=1;
            try
            {
                in>>ob.suprafata_curte;
                if(ob.suprafata_curte<0)
                    throw(2);
            }
            catch(int n)
            {
                cout<<"\n  ^!trebuie sa introduceti o suprafata pozitiva !^";
                cout<<"\n  Introduceti din nou suprafata curtii:";
                ok=0;
            }

        }
        while(!ok);
        cout<<"\n Introduceti pretul pe m2 al curtii :";
        in>>ob.pret_curte;
        cout<<"\n Introduceti numarul de etaje :";
        do
        {
            ok=1;
            try
            {
                in>>ob.numar_etaje;
                if(ob.numar_etaje <0)
                    throw(2);

            }
            catch(int n)
            {
                cout<<"\n   ^! numarul de etaje trebuie sa fie >0 !^";
                cout<<"\n Introduceti din nou numarul de etaje:";
                ok=0;
            }
        }
        while(!ok);

        for(int i=0; i<=ob.numar_etaje; i++)
        {
            if(i==0)
                cout<<"\n Introduceti suprafata parterului :";
            else
                cout<<"\n Introduceti suprafata etajului "<<i<<" :";
            in>>ob.supr_pe_etaj[i];

        }
        return in;
    }
    ~casa()
    {
        strcpy(strada_numar,"null");
        suprafata_curte=0;
        for(int i=0; i<=numar_etaje; i++)
        {
            supr_pe_etaj[i]=0;
        }
        numar_etaje=0;
    }


};


bool operator<(const locuinta &ob,const locuinta &ob2)
{
    return ob.get_suprafata()>ob2.get_suprafata();
}

template<class tip> void calculChirie(tip &X)
{
    float total=X.pret*X.suprafata_utila;
    total=total-(X.discount*(total/100));
    X.chirie=total;
}

void calculChirie(casa &X)
{
    float total=X.pret*X.suprafata_utila;
    total=total-(X.discount*(total/100));
    total=total+X.pret_curte*X.suprafata_curte;

    X.chirie=total;
}

template<class Type>
class Gestiune
{
    static vector<Type> a;
    static int index;
    static int total;
    casa casele_din_gestiune[100];
    float Castig_total;
public:
    void CastigAgentie(casa&);
    template<typename T>
    void adauga(T &ob)
    {

        locuinta *p = &ob;
        a.push_back(*p);
        index++;
    }

    void adaugaC(casa &ob)
    {
        CastigAgentie(ob);
        locuinta *p = &ob;
        a.push_back(*p);
        index++;
    }

    void afisare()
    {
        typename vector<Type>::iterator it;

        int i=0;
        cout<<"\n\n\ N="<<index;
        for(it=a.begin(); it!=a.end(); it++)
        {
            it->afisare();
            i++;
        }


    }
    void afisareCase()
    {
        cout<<"\n Agentia de pe urma caselor castiga :";
        cout<<Castig_total;
        cout<<"\n avem in gestiune "<<total<<" case \n";
        for(int i=0; i<total; i++)
            casele_din_gestiune[i].afisare();
    }

    Gestiune()
    {
        Castig_total=0;
    }
};
template<class Type>
vector<Type> Gestiune<Type>::a;

template<class Type>
int Gestiune<Type>::index=0;

template<class Type>
int Gestiune<Type>::total=0;

template<class Type>
void Gestiune<Type>::CastigAgentie(casa &ob2)
{
    this->casele_din_gestiune[total] = ob2;
    total++;
    Castig_total += ob2.get_chirie();
}


int main()
{

    Gestiune<locuinta> gest;
    set<pair<int,locuinta> > l1;
    set<pair<int,apartament> > a2;
    set<pair<int,casa> > c3;
    locuinta *l;
    apartament *a;
    casa *c;
    int X=0;
    int i=0;
    cout<<"\n ------- Buna ziua si bine v-am gasit la agentia imobiliara FMI POO srl  ------";
    cout<<"\n ------- Pentru a opri introducerea caselor apasati tasta 0 . ----";
    do
    {
        cout<<"\n Mai introduceti imobile ? (0-NU , 1-Da)\n";
        cin>>X;
        system("cls");
        if(X==1)
        {
            int tipul;
            cout<<"\n     Ce tip de imobil doriti ? (1 - apartament , 2 - casa , default locuinta) \n";
            cin>>tipul;
            switch(tipul)
            {
            case 1:
            {
                a = new apartament;
                cin>>*a;
                calculChirie(*a);
                gest.adauga(*a);
                pair<int,apartament> p1 = make_pair(i,*a);
                a2.insert(p1);
                i++;
                break;
            }
            case 2:
            {
                c = new casa;
                cin>>*c;
                calculChirie(*c);
                gest.adaugaC(*c);
                pair<int,casa> p1 = make_pair(i,*c);
                c3.insert(p1);
                i++;
                break;

            }
            default:
            {
                l = new locuinta;
                cin>>*l;
                calculChirie(*l);
                gest.adauga(*l);
                pair<int,locuinta> p1 = make_pair(i,*l);
                l1.insert(p1);
                i++;
                break;
            }
            }

        }

    }
    while(X);
    system("cls");
    cout<<"\n\n Multumim pentru increderea acordata ! \n\n";


    cout<<"\n\n Toate casele introduse :\n ";
    set<pair<int,casa> >::iterator it;
    for (it=c3.begin(); it != c3.end(); ++it)
    {
        cout<< it->first<<" ";
        it->second.afisare();
        cout<<"\n";
    }

    cout<<"\n\n Toate apartamentele introduse :\n";
    set<pair<int,apartament> >::iterator it2;
    for (it2=a2.begin(); it2 != a2.end(); ++it2)
    {
        cout<< it2->first<<" ";
        it2->second.afisare();
        cout<<"\n";
    }

    cout<<"\n\n Toate locuintele default introduse :\n";

    set<pair<int,locuinta> >::iterator it3;
    for (it3=l1.begin(); it3 != l1.end(); ++it3)
    {
        cout<< it3->first<<" ";
        it3->second.afisare();
        cout<<"\n";
    }
    cout<<"\n\n";
    gest.afisare();
    gest.afisareCase();



    return 0;
}


