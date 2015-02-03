class Dice
{
public:
 Dice() {};
 Dice( int numSides);
 virtual int rollDice() const;

protected:
 int numSides;
};

class LoadedDice : public Dice {
public:
	LoadedDice() {};
	LoadedDice(int numSides);
	virtual int rollDice() const;
};
