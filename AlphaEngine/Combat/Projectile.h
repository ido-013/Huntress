// Author : sinu

#pragma once
#include <iostream>
#include <fstream>

using namespace std;
/// <summary>
/// 1. vxt(t, vx0, ax) 시간과 초기 속도 가속도를 받아 t에서의 x축으로의 속도를 계산해주는 함수입니다.
/// 2. vyt(t, vy0, ax) 시간과 초기 속도 가속도를 받아 t에서의 y축으로의 속도를 계산해주는 함수입니다.
/// 3. integrate_x(init, fin, dt, a, v0) : vxt를 적분해주는 함수 입니다.
/// 4. integrate_y(init, fin, dt, a, v0) : vyt를 적분해주는 함수 입니다.
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
  포물선 운동은 x 방향으로 물체가 등속도 운동을 하는 상황에서 중력에 의해 
y 방향으로 등가속도 운동을 하는 물체의 운동을 말합니다.

  즉 Vx(x축으로의 속도) = v0(초기속도) * t로 표현할 수 있고, 
Vy(y축으로의 속도) = v0(초기속도) * t + a(가속도) * t로 
x 축과 y축의 속도를 시간에 대해서 나타낼 수 있습니다.

  이 때 이 속도를 시간 구간에서 적분을 해주면 이동한 거리를 알 수있습니다. 
  
  만약 초기 위치만 주어진다면, 결론적으로 물체의 움직임을 시간마다 알아낼 수 있습니다.
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