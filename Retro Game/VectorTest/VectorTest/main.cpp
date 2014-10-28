#include <iostream>
#include <vector>

class DummyAssClass
{
public:
	bool IsAlive;
	int numberOfPotatos;

	void Tittays()
	{
		std::cout << "My butts have " << numberOfPotatos << " potatos.\n";
	}
};

using std::vector;

vector<DummyAssClass> dumVector;	// declare the vector!!!

void main()
{
	DummyAssClass CaptainPonPon;
	CaptainPonPon.numberOfPotatos = 99;

	dumVector.push_back(CaptainPonPon);

	DummyAssClass Brandon;
	Brandon.numberOfPotatos = 1;

	dumVector.push_back(Brandon);

	for (int i = 0; i < dumVector.size(); i++)
	{
		dumVector[i].Tittays();
		dumVector[i].numberOfPotatos += 1;
	}
	
}