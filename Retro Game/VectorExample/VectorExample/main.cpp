#include <vector>

class Justin
{
public:
	int HP;
	int Butts;

	void Draw()
	{

	}
};

std::vector<Justin> MyJustins;

void main()
{
	// Make something to put in the array
	Justin JustinClone;
	JustinClone.HP = 100;
	JustinClone.Butts = 5;

	Justin DeadJustinClone;
	DeadJustinClone.HP = 0;

	// Put things in the array
	MyJustins.push_back(JustinClone);
	MyJustins.push_back(DeadJustinClone);

	// Loop over the array
	for (int i = 0; i < MyJustins.size(); i++)
	{
		if (MyJustins[i].HP > 0)
		{
			MyJustins[i].Draw();
		}
	}
}