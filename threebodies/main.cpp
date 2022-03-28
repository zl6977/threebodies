#include <QtCore/QCoreApplication>
#include "vectorzz.h"
#include "CalcClass.h"
#include "DynamicStatus.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	//CalcClass calcworld;
	ofstream outputfile, outputfile2, outputfile3;               //定义输出文件
	outputfile.open("myfile.txt");     //作为输出文件打开
	outputfile2.open("myfile2.txt");     //作为输出文件打开
	//outputfile3.open("myfile3.txt");     //作为输出文件打开
	DynamicStatus A, B, C;
	A = DynamicStatus("a", 1e24, 1e5*vectorzz(1.0f, 1.0f, 0.0f), vectorzz(-7680.0, 7680.0, 0.0));
	B = DynamicStatus("b", 1e24, 1e5*vectorzz(-1.0f, -1.0f, 0.0f), vectorzz(7680.0, -7680.0, 0.0));
	C = DynamicStatus("c", 3e3, 1e14*vectorzz(2.0f, 8.0f, -7.0), vectorzz(0.0, 0.0, 0.0));

	double time, deltaT = 0.01;
	//vectorzz distanceAB, distanceBC, distanceAC;
	//distanceAB = A.postion - B.postion;
	//distanceBC = B.postion - C.postion;
	//distanceAC = A.postion - C.postion;
	for (time = 0; time <= 200; time += deltaT)
	{
		CalcClass::RK4zz(A, B, C, deltaT);

		outputfile << time << "\t" << A.name << "\t" << A.postion.x << "\t" << A.postion.y << "\t" << A.postion.z << "\t"
			<< time << "\t" << B.name << "\t" << B.postion.x << "\t" << B.postion.y << "\t" << B.postion.z << "\t"
			<< time << "\t" << C.name << "\t" << C.postion.x << "\t" << C.postion.y << "\t" << C.postion.z << "\n";

		outputfile2 << time << "\t" << A.name << "\t" << A.postion.x << "\t" << A.postion.y << "\t" << A.postion.z << "\t"
			<< A.velocity.x << "\t" << A.velocity.y << "\t" << A.velocity.z << "\t"
			<< A.acceleration.x << "\t" << A.acceleration.y << "\t" << A.acceleration.z << "\n";
		/*outputfile2 << time << "\t" << B.name << "\t" << B.postion.x << "\t" << B.postion.y << "\n";
		outputfile3 << time << "\t" << C.name << "\t" << C.postion.x << "\t" << C.postion.y << "\n";
*/
//std::cout << time << " " << B.name << " " << B.postion.x << " " << B.postion.y << "\n";
//std::cout << time << " " << C.name << " " << C.postion.x << " " << C.postion.y << "\n";
//std::cout << time << " " << A.name << " " << A.postion.x << " " << A.postion.y << " " << A.postion.z << "\n";
	}

	outputfile.close();
	outputfile2.close();
	/*outputfile3.close();*/
	cout << "Finish\n";

	return a.exec();
}
