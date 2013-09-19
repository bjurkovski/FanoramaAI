#include "posicao.h"
using namespace std;

Posicao::~Posicao()
{
}

string Posicao::toString() const
{
	stringstream ret;
	ret << "Posicao(" << (int)x << ", " << (int)y <<")";
	return ret.str();
}

const Posicao operator*(const Posicao& pos, const int mult) {
	return Posicao(pos.getX()*mult, pos.getY()*mult);
}

const Posicao operator*(const int mult, const Posicao& pos) {
	return pos*mult;
}