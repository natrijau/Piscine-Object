#include	"../includes/Vector2.hpp"
#include	<vector>

Vector2::Vector2(float x, float y) : _x(x), _y(y){
	//std::cout << "Vector2 created" << std::endl;
};

Vector2::~Vector2(){
	//std::cout << "Vector2 deleted" << std::endl;
};

float Vector2::getX() const{
	return _x;
};

float Vector2::getY() const{
	return _y;
};

bool Vector2::operator>(const Vector2& other) const {
	if (getY() > other.getY())
		return true;
	else if (getY() == other.getY() && getX() > other.getX())
		return true;
	return false;
};
