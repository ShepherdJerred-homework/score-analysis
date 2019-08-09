/*
* Jerred Shepherd
* COMP 150
* Stats
*/

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

void Swap(float &a, float &b) {

	float c = a;
	a = b;
	b = c;

}

int GetMinPos(float numbers[], int first, int last) {

	int pos;

	int minpos = first;
	float minval = numbers[first];

	for (pos = first + 1; pos <= last; pos++) {

		if (numbers[pos] < minval) {

			minpos = pos;
			minval = numbers[pos];

		}

	}

	return minpos;
}

void SelSort(float numbers[], int quantity) {

	int minpos, pos;

	for (pos = 0; pos < quantity - 1; pos++) {

		minpos = GetMinPos(numbers, pos, quantity - 1);

		Swap(numbers[minpos], numbers[pos]);

	}

}

float findStandardDeviation(float grades[], int total, float average) {

	float sum = 0;

	for (int count = 0; count < total; count++) {

		sum += (grades[count] - average) * (grades[count] - average);

	}

	return sqrt(sum / (total - 1));

}

float findAverage(float grades[], int total) {

	float sum = 0;

	for (int count = 0; count < total; count++) {

		sum += grades[count];

	}

	return sum / total;

}

float findMedian(float grades[], int total) {

	bool even = total % 2;

	if (even) {

		return grades[total / 2];

	} else {

		return (grades[total / 2] + grades[(total / 2) - 1]) / 2;

	}

}

void findFrequency(float grades[], int total, float unique[], int frequency[]) {

	for (int countGrades = 0; countGrades < total; countGrades++) {

		bool found = false;

		for (int count = 0; count < total; count++) {

			if (grades[countGrades] == unique[count]) {

				found = true;

				frequency[count] += 1;

				break;

			}

		}

		if (!found) {

			for (int count = 0; count < total; count++) {

				if (unique[count] == -1) {

					unique[count] = grades[countGrades];
					frequency[count] = 1;

					break;

				}

			}

		}

	}

}

void outputMode(float grades[], int total, float unique[], int frequency[]) {

	int max = 0;
	int repeats = 0;

	for (int count = 0; count < total; count++) {

		if (unique[count] != -1) {

			if (frequency[count] == max) {

				repeats += 1;

			}
			else if (frequency[count] > max) {

				max = frequency[count];
				repeats = 0;

			}

		}

	}

	if (repeats == 0) {

		cout << "The mode score was ";

	}
	else {

		cout << "The mode scores were ";

	}

	for (int count = 0; count < total; count++) {

		if (unique[count] != -1) {

			if (frequency[count] == max) {

				cout << unique[count] << " (" << max << ")";

				if (repeats > 0) {

					cout << ", ";
					repeats -= 1;

				}

			}

		}

	}

	cout << endl;

}

void getletterGrades(float grades[], int total, int letterGrades[]) {

	for (int count = 0; count < total; count++) {

		int grade = grades[count];

		if (grade >= 90) {

			letterGrades[0] += 1;

		}

		else if (grade >= 80) {

			letterGrades[1] += 1;

		}

		else if (grade >= 70) {

			letterGrades[2] += 1;

		}

		else if (grade >= 60) {

			letterGrades[3] += 1;

		}
		else {

			letterGrades[4] += 1;

		}

	}

}

void main() {

	int currentGrade = 0, letterGrades[5]{0, 0, 0, 0 , 0}, frequency[100];
	float grades[100], input, min = 100, max = 0, average, median, standardDeviation, unique[100];

	cout.precision(1);
	cout.setf(ios::fixed | ios::showpoint);

	for (int count = 0; count < 99; count++) {

		unique[count] = -1;

	}

	do {

		do {

			cout << "Score? ";

			cin >> input;

			if (input > 100 || (input < 0 && input != -1)) {

				cout << "Invalid score, grades must be between 0-100, or enter -1 to finish inputting scores" << endl;

			}

		} while (input > 100 || (input < 0 && input != -1));

		if (input != -1) {

			grades[currentGrade] = input;
			currentGrade++;

			if (input > max) {

				max = input;

			}

			if (input < min) {

				min = input;

			}

		}

	} while (input != -1 && currentGrade != 99);

	SelSort(grades, currentGrade);

	average = findAverage(grades, currentGrade);
	median = findMedian(grades, currentGrade);
	standardDeviation = findStandardDeviation(grades, currentGrade, average);
	getletterGrades(grades, currentGrade, letterGrades);

	findFrequency(grades, currentGrade, unique, frequency);

	cout << endl << "There were " << currentGrade << " scores entered" << endl;
	cout << "The maximum score was " << max << endl;
	cout << "The minimum score was " << min << endl;
	cout << "The mean score was " << average << endl;
	cout << "The median score was " << median << endl;

	outputMode(grades, currentGrade, unique, frequency);

	cout << "The standard deviation was " << standardDeviation << endl;

	cout << "There were " << letterGrades[0] << " As, " << letterGrades[1] << " Bs, " << letterGrades[2] << " Cs, " << letterGrades[3] << " Ds, " << letterGrades[4] << " Fs";

	cout << endl << endl << "Scores in order:" << endl << endl;

	int row = 1;

	for (int count = currentGrade - 1; count > -1; count--) {

		cout << setw(5) << grades[count] << " ";

		if (row == 10) {

			cout << endl;
			row = 0;

		}

		row++;

	}

	cout << endl << endl;

	system("pause");

}