class PuzzleButtonScoreTracker
{
private:
	float score;
	float old_score;
public:
	void addToScore(float amount_to_add)
	{
		score += amount_to_add;
	}
	float getScore()
	{
		return score;
	}
	void reset()
	{
		score = 0.f;
	}
	bool didScoreChange()
	{
		bool ret = (score != old_score);
		old_score = score;
		return ret;
	}
};