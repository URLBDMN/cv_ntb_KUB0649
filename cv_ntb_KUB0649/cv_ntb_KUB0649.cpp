
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <cstdarg>

using namespace std;

#define Timetable pair<vector<vector<Subject>>, vector<Subject>>

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
	for (size_t i = 0; i < subjects.size(); i++)
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

Timetable SubjectsInVecVecWithPrio(vector<Subject> subjects)
{
	vector<vector<Subject>> result1;
	vector<Subject> result2;
	Timetable result;

	vector<Subject> hlp0 = subjects;

	vector<Subject> Mon;
	for (size_t i = 0; i < 5; i++)
	{
		result1.push_back(Mon);
	}

	int counter = 0;
	bool correct = false;
	while (!hlp0.empty())
	{
		if (!hlp0[0].priority.empty())
		{
			correct = false;
			for (size_t i = 0; i < hlp0[0].priority.size(); i++)
			{
				if (correct)
				{
					break;
				}
				if (result1[hlp0[0].priority[i]].empty())
				{
					result1[hlp0[0].priority[i]].push_back(hlp0[0]);
					hlp0.erase(hlp0.begin());
					break;
				}
				else
				{
					if (hlp0[0].start > result1[hlp0[0].priority[i]][result1[hlp0[0].priority[i]].size() - 1].finish)
					{
						result1[hlp0[0].priority[i]].push_back(hlp0[0]);
						hlp0.erase(hlp0.begin());
						correct = true;
						break;
					}
					else if ((!correct) & (i == hlp0[0].priority.size() - 1))
					{
						for (size_t i = 0; i < result1.size(); i++)
						{
							if (correct)
							{
								break;
							}
							if (result1[i].empty())
							{
								result1[i].push_back(hlp0[0]);
								hlp0.erase(hlp0.begin());
								break;
							}
							else
							{
								if (result1[i][result1[i].size() - 1].finish < hlp0[0].start)
								{
									result1[i].push_back(hlp0[0]);
									hlp0.erase(hlp0.begin());
									correct = true;
									break;
								}
								if (i == result1.size() - 1)
								{
									result2.push_back(hlp0[0]);
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
		else
		{
			correct = false;

			for (size_t i = 0; i < result1.size(); i++)
			{
				if (correct)
				{
					break;
				}
				if (result1[i].empty())
				{
					result1[i].push_back(hlp0[0]);
					hlp0.erase(hlp0.begin());
					break;
				}
				else
				{
					if (result1[i][result1[i].size() - 1].finish < hlp0[0].start)
					{
						result1[i].push_back(hlp0[0]);
						hlp0.erase(hlp0.begin());
						correct = true;
						break;
					}
					if (i == result1.size() - 1)
					{
						result2.push_back(hlp0[0]);
						hlp0.erase(hlp0.begin());
						correct = true;
						break;

					}
				}

			}
		}
	}
	result.first = result1;
	result.second = result2;
	return result;
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

	return -1;
}

int main(void)
{


	vector<Subject> subjects = FillSubjects();
	Timetable final;
	string school_days[5] = { "Pondelok", "Utorok", "Streda","Stvrtok","Piatok" };
	vector<Subject> SpareSubjects;


	if (!CheckSubjects(subjects))
	{
		exit(1);
	}

	sort(subjects.begin(), subjects.end(), myComparison);

	cout << "Predmety: ";
	printVec(subjects);


	subjects[SubjectByName("APPS")] = AddPriority(subjects[SubjectByName("APPS")], 2, 2, 3);
	subjects[SubjectByName("ALG")] = AddPriority(subjects[SubjectByName("ALG")], 2, 2, 3);
	subjects[SubjectByName("SJL")] = AddPriority(subjects[SubjectByName("SJL")], 2, 2, 3);


	cout << endl;
	final = SubjectsInVecVecWithPrio(subjects);
	cout << endl;


	cout << "Rozvrh: " << endl;

	for (size_t i = 0; i < (sizeof(school_days) / sizeof(*school_days)); i++)
	{
		cout << school_days[i] << ": ";
		printVec(final.first[i]);
		cout << endl;

	}

	cout << "\nPredmety, ktore sa nevosli do rozvrhu: ";
	printVec(final.second);
	cout << endl;


	return 0;
}