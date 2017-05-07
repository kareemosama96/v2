#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;
float toFloat(string s);
float slope(float x1, float x2, float y1, float y2);

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
		float xPoints[10000];
		float yPoints[10000];
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
			if (xPoints[i] != -107374176.) {
				if (xPoints[i] > Xmax)
					Xmax = xPoints[i];
				if (xPoints[i] < Xmin)
					Xmin = xPoints[i];
			}
		}

		if (pointsNo != 0) {
			cout << Xmin << endl;	//Min Y
			cout << Xmax << endl;	//Max Y
		}
		else {
			cout << "none" << endl;
			cout << "none" << endl;
		}




		//Finding and printing Max Y and min Y
		float Ymax = yPoints[0];
		float Ymin = yPoints[0];
		for (int i = 0; i < 10000; i++) {
			if (yPoints[i] != -107374176.) {
				if (yPoints[i] > Ymax)
					Ymax = yPoints[i];
				if (yPoints[i] < Ymin)
					Ymin = yPoints[i];
			}
		}
		if (pointsNo != 0) {
			cout << Ymin << endl;	//Min Y
			cout << Ymax << endl;	//Max Y
		}
		else {
			cout << "none" << endl;
			cout << "none" << endl;
		}


		//Printing The enclousing rectanngle
		if (pointsNo != 0)
			cout << "(" << Xmax << "," << Ymax << ")" << ","
			<< "(" << Xmax << "," << Ymin << ")" << ","
			<< "(" << Xmin << "," << Ymin << ")" << ","
			<< "(" << Xmin << "," << Ymax << ")" << endl;
		else
			cout << "none" << endl;



		//*****************************************************************************************End of 3,4,5,6,7 Operations

		//Cutting Polygons in arrays
		string pol[1000];  // pol[polygon's number-1] array of polygons

		int firstSemi = polygons.find(";");
		int secSemi = polygons.find(";", firstSemi + 1);
		for (int i = 0; i <= 100; i++) {
			if (firstSemi != string::npos) {
				pol[i] = "s" + polygons.substr(firstSemi + 1, secSemi - firstSemi - 1) + "s";
				firstSemi = secSemi;
				secSemi = polygons.find(";", firstSemi + 1);
			}
			else
				break;
		}


		//finding Redundant points (repeated points) (point lying on a line of previous and next points)
		// repeated points

		//removing separating commas and putting s instead of it
		for (int j = 0; j < 1000; j++) {
			for (int i = 0; i < pol[j].length(); i++) {
				if (pol[j].substr(i, 3) == "),(")
					pol[j].replace(i, 3, ")s(");
			}
		}
		string polygonsPoints[100][100];	//array of [100 polygons] and [100 points for each poylgon]
		for (int j = 0; j < 100; j++) {
			int s1 = pol[j].find("s");
			int s2 = pol[j].find("s", s1 + 1);
			int sNo = 0;
			for (int i = 0; i <= pol[j].length(); i++) {	//couting number of polygons to leave empty ones
				if (pol[j].substr(i, 1) == "s")
					sNo++;
			}
			for (int i = 0; i <= sNo - 1; i++) {	//geting points of each polygon
				if (s1 != string::npos) {
					polygonsPoints[j][i] = pol[j].substr(s1 + 1, s2 - s1 - 1);
					s1 = s2;
					s2 = pol[j].find("s", s1 + 1);
				}
				else
					break;
			}
		}
		//counting reduntant points 
		//removing it from "polygonsPoints" array
		// point lying on a line of previous and next points or equal points
		float xPointsForRed[100][100];	//array of x points for each polygon
		float yPointsForRed[100][100];	//array of y points for each polygon

		for (int i = 0; i < 100; i++) {		//looping polygonspoints[j][const] "polygons"
			for (int j = 0; j < 100; j++) {		//looping polygonspoints[const][i] "polygon's points"
				if (polygonsPoints[j][i] != "") {
					for(int k = 0; k < 100; k++){
						if (polygonsPoints[j][k] != "") {
							int one = polygonsPoints[j][k].find("(");
							int two = polygonsPoints[j][k].find(",");
							int three = polygonsPoints[j][k].find(")");
							if (one == -1)
								break;
							//	convert the x from string to float and store it in "xPointsForRed" array
							xPointsForRed[j][k] = toFloat( polygonsPoints[j][k].substr(one + 1, two - one - 1) );
							//	convert the y from string to float and store it in "yPointsForRed" array
							yPointsForRed[j][k]	= toFloat(polygonsPoints[j][k].substr(two + 1, three - two - 1));
						}
					}
				}
			}
		}
		int redundant = 0;
		for (int i = 0; i < 100; i++) {		//looping polygons 
			for (int j = 0; j < 100; j++) {		//looping points
				if (xPointsForRed[i][j]!= -107374176.) {	//leaving empty float
					float m1 = slope(xPointsForRed[i][j], xPointsForRed[i][j + 1], yPointsForRed[i][j], yPointsForRed[i][j + 1]);
					float m2 = slope(xPointsForRed[i][j + 1], xPointsForRed[i][j + 2], yPointsForRed[i][j + 1], yPointsForRed[i][j + 2]);
					// point lying on a line of previous and next points
					// point equals next point
					if (m1 == m2 ||(xPointsForRed[i][j] == xPointsForRed[i][j + 1]  && yPointsForRed[i][j] == yPointsForRed[i][j + 1]) ) {
						redundant++;
						polygonsPoints[i][j + 1] = "";
					}
				}
			}
		}
		cout << redundant << endl; 
		


	} // end of last(9) operation of level 1
	return 0;
}
/* description: change the string to float
* param: string to converted to float should be string of numbebrs
* return: the converted float number
*/
float toFloat(string s) {
	return atof(s.c_str());
}

/* description: calculate the slope between two points
* param1(float): the x of first point (x1)
* param2(float): the x of second point (x2)
* param3(float): the y of first point (y1)
* param4(float): the y of second point (y2)
* return(float): slope of the line joining the two points
*/
float slope(float x1, float x2, float y1, float y2) {
	return (y2-y1) / (x2-x1);
}
