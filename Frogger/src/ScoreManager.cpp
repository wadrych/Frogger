#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::init()
{
	results_amt_ = 10;
	
	FILE* results = NULL;
	errno_t passed = fopen_s(&results, "high_score.txt", "r");

	if(passed != 0)
	{
		printf("Couldn't open high_score.txt");
		return;
	}

	for(int i = 0; i < results_amt_; i++)
	{
		sprintf(names_[i], "%s", "");
	}


	int temp_score = 0;
	
	for(int i = 0; i < results_amt_; i++)
	{
		temp_score = 0;
		int res = fscanf(results, "%i %s", &temp_score, names_[i]);

		//if name is empty then don't save score
		if(res == EOF)
		{
			best_results_[i].score = 0;
		}
		else
		{
			best_results_[i].score = temp_score;
		}

		best_results_[i].name = names_[i];
	}

	fclose(results);
}

bool ScoreManager::is_higher_than_saved(int score)
{
	for(int i = 0; i <= results_amt_; i++)
	{
		if(best_results_[i].score < score)
		{
			return true;
		}
	}

	return  false;
}

void ScoreManager::set_new_high_score(int score, char* name)
{
	int penultimate = results_amt_ - 2;
	
	for (int i = 0; i < results_amt_; i++)
	{
		if (best_results_[i].score < score)
		{
			for(int j = penultimate; j >= i; j--)
			{
				best_results_[j + 1].score = best_results_[j].score;
				best_results_[j + 1].name = best_results_[j].name;
			}

			best_results_[i].score = score;
			best_results_[i].name = name;
			
			break;
		}
	}
	save_results();
}

void ScoreManager::save_results()
{
	FILE* results = NULL;
	errno_t passed = fopen_s(&results, "high_score.txt", "w");

	if (passed != 0)
	{
		printf("Couldn't open high_score.txt");
		return;
	}

	for(int i = 0; i < results_amt_; i++)
	{
		fprintf(results, "%i %s \n", best_results_[i].score, best_results_[i].name);
	}

	fclose(results);
}

result* ScoreManager::get_results()
{
	return best_results_;
}

int ScoreManager::get_results_amt()
{
	init();
	return results_amt_;
}
