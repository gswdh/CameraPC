#include <iostream>
#include "gscamera.h"


using namespace std;

int main()
{
	cout << "Hello World" << endl;

	gscamera cam;

	int cam_result = cam.connect("GSW1G8LTV");

	if(cam_result == FT_OK) cout << "Connection worked!" << endl;
	else cout << "Didn't work :(" << endl;

	/*
	ftdi ft;

	int ft_result = ft.connect("GSW1G8LTV");

	if(ft_result == FT_OK) cout << "Connection worked!" << endl;
	else cout << "Didn't work :(" << endl;

	ft.disconnect();

*/





}
