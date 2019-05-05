#include<iostream>
#include <stdlib.h>

using namespace std;

template<typename DT>
class Nod;

template<typename DT>
class ListaC;

template<typename DT>
ostream& operator <<  (ostream& os, const ListaC<DT>& lst)
{
	Nod<DT> *tmp;
	os << "{ ";
	if (lst.inc->urm)
	{
		tmp = lst.inc->urm;
		while (tmp != lst.sf)
		{
			os << tmp->info << " ";
			tmp = tmp->urm;
		}
		os << lst.sf->info << " ";
	}
	os << "}";
	return os;
}

template<typename DT>
class Nod
{
	DT info;
	Nod *urm;
public:
	friend class ListaC<DT>;

	Nod()
	{
		urm = NULL;
	}

	Nod(DT x)
	{
		info = x;
		urm = NULL;
	}

	~Nod()
	{
		if (urm != NULL)
		{
			DT d = urm->info;
			delete urm;
			cout << "S-a sters elementul cu info= " << d << endl;
		}
	}

	friend ostream& operator<< <DT>(ostream&, const ListaC<DT>&);
};

template<typename DT>
class ListaC {
protected:
	Nod<DT> *inc, *crt, *sf;
public:
	ListaC() {
		inc = sf = crt = new Nod<DT>;
	}
	~ListaC();
	int addElemSf(DT);
	int addElemInc(DT);
	int operator++();
	int getCrtData(DT&);
	int setCrtData(DT);
	int insertElemDupaCrt(DT);
	int insertElemCrt(DT);
	int deleteCrt(DT&);
	int lungime();

	bool lista_goala()
	{
		return !(inc->urm);
	}

	DT& operator[](int);
	DT& operator()();
	DT& operator()(int);

	int lookup(DT);

	friend ostream& operator<< <DT>(ostream&, const ListaC<DT>&);
};

template <typename DT>
int ListaC<DT>::addElemSf(DT d)
{
	Nod<DT> *tmp = new Nod<DT>(d);
	if (!tmp)
		return 1;
	if (inc->urm == NULL) {
		inc->urm = tmp;
		sf = tmp;
		crt = sf;
		sf->urm = tmp;
		return 0;
	}
	tmp->urm = inc->urm;
	sf->urm = tmp;
	sf = sf->urm;
	return 0;
}

template<typename DT>
int ListaC<DT>::addElemInc(DT d) {
	Nod<DT>* tmp = new Nod<DT>(d);
	if (!tmp)
		return 1;
	if (inc->urm == NULL) {
		inc->urm = tmp;
		sf = tmp;
		sf->urm = tmp;
		crt = sf;
		return 0;
	}
	tmp->urm = inc->urm;
	inc->urm = tmp;
	sf->urm = tmp;
	return 0;
}

template<typename DT>
int ListaC<DT>::operator++()
{
	if (crt = crt->urm)
		return 0;
	else return 1;
}

template<typename DT>
DT& ListaC<DT>::operator()(int p)
{
	if (inc->urm)
	{
		crt = inc->urm;
		p--;
		while (p != 0) {
			p--;
			crt = crt->urm;
		}
		return crt->info;
	}
}

template<typename DT>
int ListaC<DT>::setCrtData(DT d)
{
	if (!crt)
		return 1;
	crt->info = d;
	return 0;
}

template<typename DT>
int ListaC<DT>::getCrtData(DT& d)
{
	if (!crt)
		return 1;
	d = crt->info;
	return 0;
}

template<typename DT>
int ListaC<DT>::insertElemDupaCrt(DT d)
{
	Nod<DT>* tmp = new Nod<DT>(d);
	if (!tmp)
		return 1;
	if (inc->urm == NULL) {
		inc->urm = tmp;
		sf = tmp;
		sf->urm = tmp;
		crt = sf;
		return 0;
	}
	tmp->urm = crt->urm;
	crt->urm = tmp;
	if (crt == sf)
		sf = sf->urm;
	return 0;
}

template<typename DT>
int ListaC<DT>::insertElemCrt(DT d)
{
	if (inc->urm == NULL)
	{
		if (!(crt->urm = new Nod<DT>(d)))
			return 1;
		crt = crt->urm;
		crt->urm = crt;
		sf = crt;
		inc->urm = crt;
		return 0;
	}

	Nod<DT>* tmp = new Nod<DT>(crt->info);

	if (!tmp)
		return 1;

	crt->info = d;
	tmp->urm = crt->urm;
	crt->urm = tmp;
	if (crt == sf)
		sf = sf->urm;
	return 0;
}

template<typename DT>
int ListaC<DT>::deleteCrt(DT& d) {
	Nod<DT> *tmp;
	if (!crt)
		return 1;

	if (crt == sf)
	{
		crt = inc;
		while (crt->urm != sf)
			crt = crt->urm;
		d = crt->urm->info;
		tmp = crt->urm;
		crt->urm = inc;
		sf = crt;
		tmp->urm = NULL;
		delete tmp;
		return 0;
	}
	else
	{
		d = crt->info;
		crt->info = crt->urm->info;
		tmp = crt->urm;
		crt->urm = tmp->urm;
		tmp->urm = NULL;
		delete tmp;
		return 0;
	}
}

template<typename DT>
DT& ListaC<DT>::operator[](int p)
{
	operator()(p);
	return crt->info;
}

template<typename DT>
DT& ListaC<DT>::operator()()
{
	return crt->info;
}

template<typename DT>
ListaC<DT>::~ListaC()
{
	sf->urm = NULL;
	if (inc->urm)
		delete inc;
}

template<typename DT>
int ListaC<DT>::lungime()
{
	int lung = 1;
	if (inc->urm)
	{
		crt = inc->urm;
		while (crt != sf)
		{
			crt = crt->urm;
			lung++;
		}
		return lung;
	}
	else return 0;
}

template<typename DT>
int ListaC<DT>::lookup(DT d)
{
	if (inc->urm)
	{
		crt = inc->urm;
		while (crt != sf)
		{
			if (crt->info == d)
				return 1;
			crt = crt->urm;
		}
		if (sf->info == d) {
			crt = sf;
			return 1;
		}
	}
	return 0;
}

class DATA
{
	int a;
	float b;

public:
	friend class ListaC<DATA>;
	DATA()
	{
		a = b = 0;
	}
	DATA(int a1, float b1)
	{
		a = a1;
		b = b1;
	}
	DATA(const DATA & x2)
	{
		a = x2.a;
		b = x2.b;
	}
	void operator=(const DATA & x2)
	{
		this->a = x2.a;
		this->b = x2.b;
	}

	bool operator==(DATA x2)
	{
		return (a == x2.a && b == x2.b);
	}
	friend ostream& operator<<(ostream&, DATA);
};

ostream& operator<<(ostream& os, DATA d) {
	os << "( " << d.a << " , " << d.b << " )";
	return os;
}
int main() {
	ListaC<DATA> lst;
	DATA data;

	cout << "Lista iniliala:" << endl << lst << endl;

	cout << endl << "Adaug succesiv 2 elemente la sfarsitul listei" << endl;
	if (lst.addElemSf(DATA(1, 2.5)) == EXIT_FAILURE)
		exit(1);
	cout << lst << endl;

	if (lst.addElemSf(DATA(4, 2.9)) == EXIT_FAILURE)
		exit(1);
	cout << lst << endl;

	lst.insertElemCrt(DATA(112, 333.999));
	cout << endl << "Lista dupa inserare pe pozitia 1 " << lst << endl;

	lst.insertElemCrt(DATA(666, 999.1));
	cout << endl << "Lista dupa inserare pe pozitia 1 " << lst << endl;

	cout << endl << "Modificare valoare pe pozitia crt (primul element)" << endl;
	if (lst.setCrtData(DATA(3, 5.7)))
		exit(1);
	cout << lst << endl;

	lst.getCrtData(data);
	cout << endl << "Citire element crt: " << data << endl;

	cout << endl << "Modificare valoare pe pozitia crt (primul element), Metoda 2 = operator" << endl;
	lst() = DATA(27, 10.3);
	cout << lst << endl;

	cout << endl << "Citire element crt, Metoda 2 = operator: " << endl;
	cout << lst() << endl;

	cout << endl << "Avansare in lista" << endl;
	++lst;

	cout << endl << "Inserare element nou pe pozitia crt (al doilea)" << endl;
	if (lst.insertElemCrt(DATA(9, 3.7)))
		exit(1);
	cout << lst << endl;

	cout << endl << "Avansare in lista" << endl;
	++lst;

	cout << endl << "Eliminare element de pe pozitia crt (al treilea)" << endl;
	if (lst.deleteCrt(data))
		exit(1);

	cout << lst << endl;

	cout << endl << "Afisare element sters:" << endl;
	cout << data << endl;

	cout << endl << "Citire element de pe o anumita pozitie (ex.: 2) folosind op indexare" << endl;
	cout << lst[2] << endl;

	cout << endl << "Modificare element de pe o anumita pozitie (ex.: 2), folosind op indexare" << endl;
	lst[2] = DATA(17, 6.7);
	cout << lst << endl;

	data = DATA(17, 6.7);
	cout << endl << "Se cauta elementul " << data << " in lista" << endl;
	if (lst.lookup(data))
		cout << endl << "   Elementul " << data << " a fost gasit in lista" << endl;

	else
		cout << endl << "   Elementul " << data << " nu a fost gasit in lista" << endl;

	data = DATA(4, 9.1);
	cout << endl << "Se cauta elementul " << data << " in lista" << endl;
	if (lst.lookup(data))
		cout << endl << "   Elementul " << data << " a fost gasit in lista" << endl;

	else
		cout << endl << "   Elementul " << data << " nu a fost gasit in lista" << endl;
	cout <<endl<< " Mutare cursor pe ultima pozitie" << endl;
	lst(lst.lungime());
	cout << endl << " incrementare cursor" << endl;
	++lst;
	cout << endl << " citire element de pe pozitia curenta : " << endl;
	lst.getCrtData(data);
	cout << endl;
	cout << data << endl;
	cout<<endl<<"CARE ESTE PRIMUL ELEMENT, DECI LISTA ESTE CIRCULARA ! " << endl;
	cout << endl;
	system("pause");
	return 0;
}
	
