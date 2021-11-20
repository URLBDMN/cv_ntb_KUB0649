
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <cstdarg>

using namespace std;



struct Subject
{
	short id;
	string name;
	unsigned int start;
	unsigned int finish;
	string description;
	vector<int> priority;

	Subject(short _id, string _name, unsigned int _start, unsigned int _finish, string _description)
	{
		id = _id;
		name = _name;
		start = _start;
		finish = _finish;
		description = _description;
	}
};

bool CheckSubjects(vector<Subject> subjects)
{
	bool valid = true;
	for (int i = 0; i < subjects.size(); i++)
	{
		if (subjects[i].finish < subjects[i].start || subjects[i].finish > 18 || subjects[i].start < 5)
		{
			cout << "Zle zadany subject -> " << subjects[i].name << endl;
			valid = false;
			continue;
		}
	}
	if (valid)
	{
		cout << "Subjecty su validne" << endl;
		return true;
	}
	else
	{
		return false;
	}

}

bool myComparison(Subject& a, const Subject& b)
{
	return a.finish < b.finish;
}

void printVec(vector<Subject> subjects)
{
	for (size_t i = 0; i < subjects.size(); i++)
	{
		cout << subjects[i].name << "(" << subjects[i].start << "," << subjects[i].finish << ")" << " ";;

	}

}


Subject AddPriority(Subject toAddPrio, int cnt_of_priorities, ...)
{
	vector<int> i_prio;
	va_list valist;
	va_start(valist, cnt_of_priorities);

	for (int i = 0; i < cnt_of_priorities; i++)
	{
		i_prio.push_back(va_arg(valist, int));
	}

	for (size_t i = 0; i < i_prio.size(); i++)
	{
		toAddPrio.priority.push_back(i_prio[i]);
	}

	return toAddPrio;
}

pair<vector<vector<Subject>>, vector<Subject>> SubjectsInVecVecWithPrio(vector<Subject> subjects)
{
	vector<vector<Subject>> final;
	vector<Subject> hlp0 = subjects;
	vector<Subject> hlp1;

	pair<vector<vector<Subject>>, vector<Subject>> result;

	vector<Subject> Mon;
	for (size_t i = 0; i < 5; i++)
	{
		final.push_back(Mon);
	}


	int counter = 0;
	bool correct = false;
	while (!hlp0.empty())
	{
		if (!hlp0[0].priority.empty())
		{
			for (size_t i = 0; i < hlp0[0].priority.size(); i++)
			{
				if (correct)
				{
					break;
				}
				if (final[hlp0[0].priority[i]].empty())
				{
					final[hlp0[0].priority[i]].push_back(hlp0[0]);
					hlp0.erase(hlp0.begin());
					break;
				}
				else
				{

					for (size_t j = 0; j < final[hlp0[0].priority[i]].size(); j++)
					{
						if (correct)
						{
							break;
						}
						if (hlp0[0].start >= final[hlp0[0].priority[i]][j].finish)
						{
							final[hlp0[0].priority[i]].push_back(hlp0[0]);
							hlp0.erase(hlp0.begin());
							correct = true;
							break;
						}
						else
						{
							correct = false;
						}


					}
					if (!correct)
					{
						for (size_t i = 0; i < final.size(); i++)
						{
							if (final[i].empty())
							{
								final[i].push_back(hlp0[0]);
								hlp0.erase(hlp0.begin());
								correct = true;
								break;
							}
							else
							{
								if (correct)
								{
									break;
								}
								for (size_t j = 0; j < final[i].size(); j++)
								{
									if (final[i][j].finish <= hlp0[0].start)
									{
										final[i].push_back(hlp0[0]);
										hlp0.erase(hlp0.begin());
										correct = true;
										break;
									}

								}
							}

						}
					}

				}


			}

		}
		else
		{
			correct = false;

			for (size_t i = 0; i < final.size(); i++)
			{
				if (correct)
				{
					break;
				}
				if (final[i].empty())
				{
					final[i].push_back(hlp0[0]);
					hlp0.erase(hlp0.begin());
					break;
				}
				else
				{
					if (final[i][final[i].size() - 1].finish < hlp0[0].start)
					{
						final[i].push_back(hlp0[0]);
						hlp0.erase(hlp0.begin());
						correct = true;
						break;
					}
					if (i == final.size() - 1)
					{
						hlp1.push_back(hlp0[0]);
						hlp0.erase(hlp0.begin());
						correct = true;
						break;

					}
				}

			}
		}
	}
	result.first = final;
	result.second = hlp1;
	return result;
}


vector<vector<Subject>> SubjectsInVecVecWithoutPrio(vector<Subject> subjects)
{
	vector<Subject> hlp0 = subjects;
	vector<Subject> hlp1;
	vector<Subject> hlp2;

	vector<vector<Subject>> final;


	int counter = 0;
	int go = hlp0.size();


	for (size_t i = 0; i < 5; i++)
	{

		if (!hlp2.empty())
		{
			hlp0 = hlp2;
			hlp2.clear();
		}
		hlp1.push_back(hlp0[0]);
		hlp0.erase(hlp0.begin());
		while (!hlp0.empty())
		{


			if (hlp1[counter].finish < hlp0[0].start)
			{
				hlp1.push_back(hlp0[0]);
				hlp0.erase(hlp0.begin());
				counter++;
			}
			else
			{
				hlp2.push_back(hlp0[0]);
				hlp0.erase(hlp0.begin());
			}


		}
		final.insert(final.begin() + i, hlp1);
		hlp1.clear();
		counter = 0;
		if (i == 4 && !hlp2.empty())
		{
			cout << endl;
			cout << "Tieto predmety nevosli do rozvrhu: ";

			for (size_t i = 0; i < hlp2.size(); i++)
			{
				printVec(hlp2);
			}
			cout << endl;
		}
	}
	return final;
}

vector<Subject> FillSubjects()
{
	vector <Subject> subjects;

	subjects.push_back(Subject(0, "DS", 10, 12, "bolest v2"));
	subjects.push_back(Subject(1, "SJL", 5, 13, "Vyuka slovenciny"));
	subjects.push_back(Subject(2, "ANJ", 7, 9, "Vyuka anglictiny"));
	subjects.push_back(Subject(3, "APPS", 5, 6, "bolest"));
	subjects.push_back(Subject(4, "ALG", 5, 9, "Vyuka o algoritmoch"));
	subjects.push_back(Subject(5, "NAIT", 9, 15, "Etika,dusa,moralka"));
	subjects.push_back(Subject(6, "SKJ", 14, 18, "Skripty"));
	subjects.push_back(Subject(8, "MAT", 6, 10, "Pocitanie cisel"));
	subjects.push_back(Subject(9, "TAMZ", 9, 12, "tvorba app"));
	subjects.push_back(Subject(10, "SP", 10, 13, "semestralka"));

	return subjects;
}

int SubjectByName(string name)
{
	vector<Subject> hlp = FillSubjects();
	sort(hlp.begin(), hlp.end(), myComparison);

	for (size_t i = 0; i < hlp.size(); i++)
	{
		if (hlp[i].name.compare(name) == 0)
		{
			return i;
		}
	}


}

int main(void)
{


	vector<Subject> subjects = FillSubjects();
	vector<vector<Subject>> final;
	string school_days[5] = { "Pondelok", "Utorok", "Streda",
		"Stvrtok","Piatok" };
	vector<int> j;

	for (size_t i = 0; i < j.size(); i++)
	{
		cout << "a";
	}

	if (!CheckSubjects(subjects))
	{
		exit(1);
	}

	cout << "\nPredmety: ";
	printVec(subjects);
	cout << endl;

	sort(subjects.begin(), subjects.end(), myComparison);

	cout << "Predmety: ";
	printVec(subjects);


	subjects[SubjectByName("APPS")] = AddPriority(subjects[SubjectByName("APPS")], 2, 2, 3);
	subjects[SubjectByName("ANJ")] = AddPriority(subjects[SubjectByName("ANJ")], 2, 2, 3);



	final = SubjectsInVecVecWithPrio(subjects).first;
	cout << endl;


	cout << "Rozvrh: " << endl;

	for (size_t i = 0; i < (sizeof(school_days) / sizeof(*school_days)); i++)
	{
		cout << school_days[i] << ": ";
		printVec(final[i]);
		cout << endl;

	}


	return 0;
}