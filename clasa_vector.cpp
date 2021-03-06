#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
using namespace  std;
template <typename T>
class Vector {
	int lungime;
	T*vector;
public:
	Vector() //constructor implicit
	{
		lungime = 0;
		vector = nullptr;
	}
	Vector(int lung) //constructor cu parametrii
	{
		lungime = lung;
		vector = new T[lungime];
		if (!vector)
			throw "Nu s-a alocat";
	}
	Vector(const Vector& sursa) //constructor de copiere
	{
		this->lungime = sursa.lungime;
		vector = new T[lungime];
		if (!vector)
			throw "Nu s-a alocat";
		for (int i = 0; i < lungime; i++)
		{
			vector[i] = sursa.vector[i];
		}
	}
	~Vector() //destructor
	{
		if (vector)
			delete[]vector;
	}
	Vector & operator =(const Vector & sursa) //operator de atribuire
	{
		if (vector != sursa.vector) {
			delete[]vector;
			this->lungime = sursa.lungime;
			vector = new T[lungime];
			if (!vector)
				throw "Nu s-a alocat";
			for (int i = 0; i < lungime; i++)
			{
				vector[i] = sursa.vector[i];
			}
		}
		return *this;
	}
	T & operator[](int index) //operator de indexare
	{
		return vector[index];
	}
	T&operator [] (int index)const
	{
		return vector[index];
	}
	int lungime_vector()const //aflare lungime
	{
		return lungime;
	}
	bool vector_gol() //verificare daca e vector gol
	{
		if (lungime > 0)
			return false;
		else return true;
	}
	T & push_back(const T & element) //adauga un element la finalul vectorului
	{
		T*aux = new T[lungime + 1];
		if (vector)
		{
			for (int i = 0; i < lungime; i++)
			{
				aux[i] = vector[i];
			}
		}
		aux[lungime] = element;
		if (vector)
			delete[]vector;
		lungime++;
		vector = new T[lungime];
		vector = aux;
		return vector[lungime];
	}
	T & pop_back() // stergere element de la finalul vectorului si returnarea acestuia
	{
		if (vector)
		{
			T*aux = new T[lungime - 1];
			T elem = vector[lungime-1];
			for (int i = 0; i < lungime - 1; i++)
			{
				aux[i] = vector[i];
			}
			delete[] vector;
			lungime--;
			vector = new T[lungime];
			vector = aux;
			return elem;
		}
		else throw "vector gol";
	}

	void del(int index)//stergere element de pe pozitia index
	{
		if (vector && (index < (lungime - 1)))
		{
			T*aux = new T[lungime - 1];
			for (int i = 0; i < index; i++)
			{
				aux[i] = vector[i];
			}
			for (int i = index + 1; i < lungime - 1; i++)
			{
				aux[i - 1] = vector[i];
			}
			lungime--;
			delete[]vector;
			vector = new T[lungime];
			vector = aux;
		}
		else if (index == lungime - 1)
			this->pop_back();
		else throw "nu se poate sterge elementul";
	} 
	void add_elem(int index, const T& elem)// adaugare element pe pozitia index
	{
		if (vector && (index < (lungime)))
		{
			T*aux = new T[lungime + 1];
			for (int i = 0; i < index; i++)
				aux[i] = vector[i];
			aux[index] = elem;
			for (int i = index + 1; i <= lungime; i++)
				aux[i] = vector[i - 1];
			lungime++;
			delete[]vector;
			vector = new T[lungime];
			vector = aux;
		}
		else if (index == lungime)
			this->push_back(elem);
		else throw"nu se poate adauga elementul";
	}
	template <typename T>
	friend ostream& operator <<(ostream&, const Vector&);
};
template <typename T>
ostream & operator<<(ostream&os, const Vector<T> & vec) //operator de ostream
{
	for (int i = 0; i < vec.lungime_vector(); i++)
	{
		os << vec[i] << " ";
	}
	return os;
}
#endif

