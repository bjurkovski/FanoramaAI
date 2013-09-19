#ifndef _POSICAO_H_
#define _POSICAO_H_

#include <sstream>
#include <string>

#include "definicoes.h"

#define POS_INDEFINIDA -1

class Posicao {
	private:
		small_int x;
		small_int y;
	public:
		Posicao(const small_int x=POS_INDEFINIDA, const small_int y=POS_INDEFINIDA) { this->x=x; this->y=y; }
		Posicao(const Posicao& pos) { x=pos.x; y=pos.y; }
		~Posicao();

		inline int getX() const { return x; }
		inline int getY() const { return y; }
		inline bool isIndefinida() { return (x==POS_INDEFINIDA || y==POS_INDEFINIDA); }

		inline void setX(const small_int x) { this->x = x; }
		inline void setY(const small_int y) { this->y = y; }
		inline void setIndefinida() { x=POS_INDEFINIDA; y=POS_INDEFINIDA; }

		inline Posicao& operator=(const Posicao& pos) { setX(pos.getX()); setY(pos.getY()); return *this; }
		inline bool operator==(const Posicao& pos) const { return (x==pos.getX() && y==pos.getY()); }
		inline const Posicao operator+(const Posicao& pos) const { return Posicao(x+pos.x, y+pos.y); }
		inline const Posicao operator-(const Posicao& pos) const { return Posicao(x-pos.x, y-pos.y); }
		std::string toString() const;
};

const Posicao operator*(const Posicao& pos, const int mult);
const Posicao operator*(const int mult, const Posicao& pos);

#endif
