// Author : sinu

#pragma once
#include <iostream>
#include <fstream>

using namespace std;
/// <summary>
/// 1. vxt(t, vx0, ax) �ð��� �ʱ� �ӵ� ���ӵ��� �޾� t������ x�������� �ӵ��� ������ִ� �Լ��Դϴ�.
/// 2. vyt(t, vy0, ax) �ð��� �ʱ� �ӵ� ���ӵ��� �޾� t������ y�������� �ӵ��� ������ִ� �Լ��Դϴ�.
/// 3. integrate_x(init, fin, dt, a, v0) : vxt�� �������ִ� �Լ� �Դϴ�.
/// 4. integrate_y(init, fin, dt, a, v0) : vyt�� �������ִ� �Լ� �Դϴ�.
/// </summary>
/// <param name="t"></param>
/// <param name="vx0"></param>
/// <param name="ax"></param>
/// 
/// <param name="init"></param>
/// <param name="fin"></param>
/// <param name="dt"></param>
/// <param name="a"></param>
/// <param name="v0"></param>
/// <returns></returns>

float vxt(float t, float vx0, float ax);
float vyt(float t, float vy0, float ay);
float integrate_x(float init, float fin, float dt, float a, float v0);
float integrate_y(float init, float fin, float dt, float a, float v0);


/*
  ������ ��� x �������� ��ü�� ��ӵ� ��� �ϴ� ��Ȳ���� �߷¿� ���� 
y �������� ��ӵ� ��� �ϴ� ��ü�� ��� ���մϴ�.

  �� Vx(x�������� �ӵ�) = v0(�ʱ�ӵ�) * t�� ǥ���� �� �ְ�, 
Vy(y�������� �ӵ�) = v0(�ʱ�ӵ�) * t + a(���ӵ�) * t�� 
x ��� y���� �ӵ��� �ð��� ���ؼ� ��Ÿ�� �� �ֽ��ϴ�.

  �� �� �� �ӵ��� �ð� �������� ������ ���ָ� �̵��� �Ÿ��� �� ���ֽ��ϴ�. 
  
  ���� �ʱ� ��ġ�� �־����ٸ�, ��������� ��ü�� �������� �ð����� �˾Ƴ� �� �ֽ��ϴ�.
*/

/*
int main() {
	float x0 = 0;
	float y0 = 10;
	ofstream out("motion.txt");
	for (float T = 0; T < 10; T += 0.1) {
		out << T << " " << integrate_x(0, T, 0.01, 0, 10) << " " << integrate_y(0, T, 0.01, -9.8, 30) << endl;
	}
	return 0;
}
*/