#pragma once

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "Global.h"

class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();
	
	void init();
	bool is_higher_than_saved(int score);
	void set_new_high_score(int score, char* name);
	void save_results();

	int get_results_amt();
	result* get_results();
	
private:
	result best_results_[10];
	int results_amt_;
	char names_[10][128];
};

