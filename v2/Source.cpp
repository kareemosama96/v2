#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;
float toFloat(string s);

int main() {
	int quit = 0;
	while (quit == 0)
	{
		//Reading the string from user and saving it as strig
		string input;
		string polygons;

		getline(cin, input);

		//Quits if the input was "Quit"
		if (input == "Quit") {
			quit = 1;
			break;
		}

		// Removing Polygos=[] from the string and saving it to polygons string
		int start = input.find("(");
		int end = input.rfind(")");
		int count = 1;

		// if empty string print "none" and break
		if (start == -1) {
			cout << "none" << endl;
			count = 0;
		}
		else
		{
			polygons = ";" + input.substr(start, end - start + 1) + ";";
		}
		//Counting the polygons
		while (count == 1)
		{
			int polyNo = 0;
			for (int i = 0; i <= polygons.length(); i++) {
				if (polygons[i] == ';') {
					polyNo++;
				}
			}
			cout << polyNo - 1 << endl;	//Polygons number
			count = 0;
		}

		//Counting the points
		int pointsNo = 0;
		for (int i = 0; i <= polygons.length(); i++) {
			if (polygons[i] == '(') {
				pointsNo++;
			}
		}
		if (pointsNo != 0)
			cout << pointsNo << endl;	//points number
		else
			cout << "none" << endl;
		//****************************************************************************************************End of 1,2 Operations

		//Cutting Polygons in arrays
		string pol[1][1000];  // pol[1][polygon's number]

		int firstSemi = polygons.find(";");
		int secSemi = polygons.find(";", firstSemi + 1);
		for (int i = 0; i <= 2; i++) {
			if (firstSemi != string::npos) {
				pol[0][i] = polygons.substr(firstSemi + 1, secSemi - firstSemi - 1);
				firstSemi = secSemi;
				secSemi = polygons.find(";", firstSemi + 1);
			}
			else
				break;
		}
		//finding X and Y of all points and storing them in two arrays
		//Changning Format
		string str = polygons;
		for (int i = 0; i <= 2; i++) {
			for (int i = 0; i <= str.length(); i++) {
				if (str.substr(i, 3) == "),(")
					str.replace(i, 3, "s");

				if (str.substr(i, 3) == ");(")
					str.replace(i, 3, "s");

				if (str[i] == ')')
					str.replace(i, 1, "s");

				if (str[i] == '(')
					str.replace(i, 1, "s");

				if (str[i] == ',')
					str.replace(i, 1, "s");
			}
		}

		//Array of X points
		float xPoints[10000] = { 0 };
		float yPoints[10000] = { 0 };
		int firstS = str.find("s");
		int secS = str.find("s", firstS + 1);
		for (int i = 0; i <= str.length(); i++) {
			if (firstS != string::npos && secS != string::npos) {
				xPoints[i] = toFloat(str.substr(firstS + 1, secS - firstS - 1));
				firstS = secS;
				secS = str.find("s", firstS + 1);
				firstS = secS;
				secS = str.find("s", firstS + 1);
			}
			else
				break;
		}
		firstS = str.find("s");
		firstS = str.find("s", firstS + 1);
		secS = str.find("s", firstS + 1);
		for (int i = 0; i <= str.length(); i++) {
			if (firstS != string::npos && secS != string::npos) {
				yPoints[i] = toFloat(str.substr(firstS + 1, secS - firstS - 1));
				firstS = secS;
				secS = str.find("s", firstS + 1);
				firstS = secS;
				secS = str.find("s", firstS + 1);
			}
			else
				break;
		}
		//Finding and printing Max X and min X
		float Xmax = xPoints[0];
		float Xmin = xPoints[0];
		for (int i = 0; i < 10000; i++) {
			if (xPoints[i] > Xmax)
				Xmax = xPoints[i];
			if (xPoints[i] < Xmin)
				Xmin = xPoints[i];
		}
		if (Xmin != 0)
			cout << Xmin << endl;	//points number
		else
			cout << "none" << endl;
		if (Xmax != 0)
			cout << Xmax << endl;	//points number
		else
			cout << "none" << endl;


		//Finding and printing Max Y and min Y
		float Ymax = yPoints[0];
		float Ymin = yPoints[0];
		for (int i = 0; i < 10000; i++) {
			if (yPoints[i] > Ymax)
				Ymax = yPoints[i];
			if (yPoints[i] < Ymin)
				Ymin = yPoints[i];
		}
		if (Ymin != 0)
			cout << Ymin << endl;	//points number
		else
			cout << "none" << endl;
		if (Ymax != 0)
			cout << Ymax << endl;	//points number
		else
			cout << "none" << endl;

		//*****************************************************************************************End of 3,4,5,6 Operations







	}
	return 0;
}

float toFloat(string s) {
	return atof(s.c_str());
}
