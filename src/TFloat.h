#ifndef __TFLOAT_H__
#define __TFLOAT_H__

#include <iostream>
#include <bitset>

using namespace std;

class TFloat
{
  public:
	/**
	 * Constructores y destructor
	 * El parámetro t en cada constructor indica la cantidad
	 * de bits de mantisa que se desean usar en el TFloat
	 */
    TFloat();
	TFloat(size_t t);
	TFloat(double f, size_t t);
	TFloat(float f, size_t t);
	TFloat(int i, size_t t);
	~TFloat(){}

	/**
	 * Los siguientes sirven para setear y obtener la precisión
	 * utilizada por el TFloat
	 */
	size_t precision() { return _t; } const
	void set_precision(const size_t t) { _t = (t <= 52? t : 52); }

	// Operadores de asignacion y comparacion
	void operator=(const TFloat& );
	void operator=(const double& );
	bool operator==(const TFloat& ) const;

	// Operadores aritméticos
	TFloat operator+(const TFloat&) const;
	TFloat operator-(const TFloat&) const;
	TFloat operator*(const TFloat&) const;
	TFloat operator/(const TFloat&) const;

	// Operadores aritméticos (que reciben un tipo primitivo)
	TFloat operator+(const double&) const;
	TFloat operator-(const double&) const;
	TFloat operator*(const double&) const;
	TFloat operator/(const double&) const;

	/**
	 * La siguiente función calcula el valor del número e
	 * elevado al valor del TFloat
	 */
	TFloat exponencial() const;

	/**
	 * La siguiente función devuelve el valor del TFloat en un
	 * double. Esta función sirve por ejemplo para imprimir por
	 * pantalla el valor del TFloat.
	 */
	double dbl() const;

private:
	size_t _t;
	double _valor;
	void recortar();
};

#endif //__TFLOAT_H__
