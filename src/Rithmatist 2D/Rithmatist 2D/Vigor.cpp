#include "Vigor.h"

Vigor::Vigor(std::vector<sf::Vector2f> data)
{
	send = false;
	type = 'v';

	hitEdge = false;
	pixTraveled = 0;

	swap = false;

	strength = 1000.0f;

	power = 50.0f;

	amplitude = 15.0f;
	period = 100.0f;
	phaseShift = 0.0f; // Random maybe
	midline = 0.0f;

	regPoints.setPrimitiveType(sf::LineStrip);
	points = data;
	for (int i = 0; i < points.size(); i++)
	{
		x.push_back(points[i].x);
		y.push_back(points[i].y);
	}

	currentX = 0.0f;
	//std::cout << "cx1: " << currentX << std::endl;

	if (std::hypot(x.back() - x.front(), y.back() - y.front()) > 100.0f)
	{
		//if (SinReg())
		//{

		//}

		linReg();
	}
	else
	{
		//strength = 0.0f;
		std::cout << "Failed to draw Vigor (Too Short)" << std::endl;
	}
}

Vigor::~Vigor()
{

}

void Vigor::draw(sf::RenderTarget& target)
{
	target.draw(regPoints);
}

void Vigor::pack(sf::Packet& packet)
{
	std::cout << "Pack Vigor\n";
	packet << type;
	sf::Uint16 pointCount = x.size();
	packet << pointCount;

	for (int i = 0; i < x.size(); i++)
	{
		packet << x[i] << 1000.0f - y[i];
	}
}


float Vigor::mean(std::vector<float> values)
{
	//Find mean
	float sum = 0.0f;
	for (int i = 0; i < values.size(); i++)
	{
		sum += values[i];
	}
	return sum / values.size();
}

void Vigor::linReg()
{
	//if (abs((y.back() - y[0]) / (x.back() - x[0])) > 1.5f)
	//{
	//	std::cout << "Swap" << std::endl;
	//	x.swap(y);
	//	swap = true;
	//}

	//slope
	float numerator = 0.0f;
	float denominator = 0.0f;
	for (int i = 0; i < points.size(); i++)
	{
		numerator += (x[i] - mean(x))*(y[i] - mean(y));
		denominator += (x[i] - mean(x))*(x[i] - mean(x));
	}

	m = numerator / denominator;
	b = y.front();
	//b = mean(y) - m * mean(x);

	//if (abs(m) > 20.0f) // Near Vertical
	//{
	//	m = (y[0] - y[points.size() - 1]) / (x[0] - x[points.size() - 1]);
	//	theta = atan2f((y[0] - y[points.size() - 1]), (x[0] - x[points.size() - 1]));
	//	b = y[0] - m * x[0];
	//}
	
	if (swap)
	{
		x.swap(y);

		b = -b / m;
		m = 1.0f / m;
	
		numerator = 0.0f;
		denominator = 0.0f;
		for (int i = 0; i < points.size(); i++)
		{
			numerator += (x[i] - mean(x))*(y[i] - mean(y));
			denominator += (x[i] - mean(x))*(x[i] - mean(x));
		}
		
	}
	
	theta = atan2f(numerator, denominator);

	//std::cout << "Theta: " << theta << std::endl;
}

bool Vigor::checkIntersect(float x0, float y0, float x1, float y1)
{
	return false;
}

void Vigor::Visualize()
{
	if (!hitEdge)
	{
		//std::cout << "cx2: " << currentX << std::endl;

		float x_ = currentX, y_ = PredictY(currentX-x.front());
		//std::cout << "cy1: " << y_ << std::endl;
		float xPrime = x_ * cosf(theta) - y_ * sinf(theta) + x.front();
		float yPrime = x_ * sinf(theta) + y_ * cosf(theta);
		//std::cout << "x: " << xPrime << " y: " << yPrime + b << std::endl;
		if (xPrime <= 1000.0f && xPrime >= 0.0f && yPrime + b <= 1000.0f && yPrime + b >= 0.0f)
		{
			regPoints.append(sf::Vertex(sf::Vector2f(xPrime, yPrime + b))); // Append new point with midline transform (b)
			//std::cout << "x: " << xPrime << " y: " << yPrime + b << std::endl;
		}
		else
		{
			hitEdge = true;
		}
		if (regPoints.getVertexCount() > 0)
		{
			if (x[0] <= x.back())
			{
				currentX += 7;
			}
			else
			{
				currentX -= 7;
			}
		}
	}
	if (hitEdge)
	{
		if (pixTraveled < regPoints.getVertexCount())
		{
			//Animate leaving screen
			int count = 0;
			while (count < 1)
			{
				if (pixTraveled < regPoints.getVertexCount())
				{
					//Make from start to finish vertexes transparent
					regPoints[pixTraveled].color.a = 0;
					pixTraveled++;
					count++;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			//Done leaving screen, kill
			strength = 0;
		}
	}
}

float Vigor::PredictY(float xValue)
{
	//std::cout << "sin: " << sinf((6.2832f / period)*(xValue - phaseShift)) << std::endl;
	return amplitude * sinf((6.2832f/period)*(xValue - phaseShift)) + midline;
}

bool Vigor::SinReg()
{
	return true;
}

/*void Vigor::SinReg() //Modified from http://mariotapilouw.blogspot.com/2012/03/sine-fitting.html
{
	///y(x) = A + C * sin(x + b)

	int numOfData = points.size();

	float M_PI = 3.141592f;
	float * datax = new float[numOfData];
	float * datay = new float[numOfData];
	float * dataz = new float[numOfData];
	float phase(0);
	float mag(0);

	for (int i = 0; i < numOfData; i++)
	{
		datax[i] = cos((2 * M_PI) * float(i%numOfData) / float(numOfData));
		datay[i] = sin((2 * M_PI) * float(i%numOfData) / float(numOfData));
		dataz[i] = yourData[i];
	}

	float a(0);
	float b(0);
	float c(0);
	float p[3] = { 0 }; // product of fitting equation 
	float XiYi(0);
	float XiZi(0);
	float YiZi(0);
	float XiXi(0);
	float YiYi(0);
	float Xi(0);
	float Yi(0);
	float Zi(0);

	for (int i = 0; i < numOfData; i++)
	{
		XiYi += datax[i] * datay[i];
		XiZi += datax[i] * dataz[i];
		YiZi += datay[i] * dataz[i];
		XiXi += datax[i] * datax[i];
		YiYi += datax[i] * datay[i];
		Xi += datax[i];
		Yi += datay[i];
		Zi += dataz[i];
	}
	
	//Inverse of the matrix
	float A[3][3];
	float B[3][3];
	float C[3][3];
	float X[3][3];
	int i;
	int j;
	float x = 0;
	float n = 0; //n is the determinant of A

	A[0][0] = XiXi;
	A[0][1] = XiYi;
	A[0][2] = Xi;
	A[1][0] = XiYi;
	A[1][1] = YiYi;
	A[1][2] = Yi;
	A[2][0] = Xi;
	A[2][1] = Yi;
	A[2][2] = numOfData;

	for (i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			B[i][j] = 0;
			C[i][j] = 0;
		}
	}

	for (i = 0, j = 0; j<3; j++)
	{
		if (j == 2)
		{
			n += A[i][j] * A[i + 1][0] * A[i + 2][1];
		}
		else if (j == 1)
		{
			n += A[i][j] * A[i + 1][j + 1] * A[i + 2][0];
		}
		else
		{
			n += A[i][j] * A[i + 1][j + 1] * A[i + 2][j + 2];
		}
	}

	for (i = 2, j = 0; j<3; j++)
	{
		if (j == 2)
		{
			n -= A[i][j] * A[i - 1][0] * A[i - 2][1];
		}
		else if (j == 1)
		{
			n -= A[i][j] * A[i - 1][j + 1] * A[i - 2][0];
		}
		else
		{
			n -= A[i][j] * A[i - 1][j + 1] * A[i - 2][j + 2];
		}
	}

	// Check determinant n of matrix A
	if (n)
	{
		x = 1.0 / n;

		for (i = 0; i<3; i++)
		{
			for (j = 0; j<3; j++)
			{
				B[i][j] = A[j][i];
			}
		}

		C[0][0] = (B[1][1] * B[2][2]) - (B[2][1] * B[1][2]);
		C[0][1] = ((B[1][0] * B[2][2]) - (B[2][0] * B[1][2])) * (-1);
		C[0][2] = (B[1][0] * B[2][1]) - (B[2][0] * B[1][1]);

		C[1][0] = ((B[0][1] * B[2][2]) - (B[2][1] * B[0][2])) * (-1);
		C[1][1] = (B[0][0] * B[2][2]) - (B[2][0] * B[0][2]);
		C[1][2] = ((B[0][0] * B[2][1]) - (B[2][0] * B[0][1])) * (-1);

		C[2][0] = (B[0][1] * B[1][2]) - (B[1][1] * B[0][2]);
		C[2][1] = ((B[0][0] * B[1][2]) - (B[1][0] * B[0][2])) * (-1);
		C[2][2] = (B[0][0] * B[1][1]) - (B[1][0] * B[0][1]);

		for (i = 0; i<3; i++)
		{
			for (j = 0; j<3; j++)
			{
				X[i][j] = C[i][j] * x;
			}
		}

		p[0] = XiZi;
		p[1] = YiZi;
		p[2] = Zi;

		a = X[0][0] * p[0] + X[0][1] * p[1] + X[0][2] * p[2];
		b = X[1][0] * p[0] + X[1][1] * p[1] + X[1][2] * p[2];
		c = X[2][0] * p[0] + X[2][1] * p[1] + X[2][2] * p[2];
	}
	else  // determinant=0
	{
		a = 1;
		b = 1;
		c = 0;
	}

	mag = sqrt(a*a + b * b);

	float phi = 0;

	if ((b == 0) && (a >= 0))
	{
		phase = M_PI / 2;
	}
	else if ((b == 0) && (a >= 0))
	{
		phase = 3 * M_PI / 2;
	}
	else if ((a >= 0) && (b > 0))
	{
		phi = atan(fabs(a / b));
		phase = phi;
	}
	else if ((a >= 0) && (b < 0))
	{
		phi = atan(fabs(a / b));
		phase = M_PI - phi;
	}
	else if ((a <  0) && (b > 0))
	{
		phi = atan(fabs(a / b));
		phase = 2 * M_PI - phi;
	}
	else if ((a <  0) && (b < 0))
	{
		phi = atan(fabs(a / b));
		phase = phi + M_PI;
	}

	amplitude = mag;
	phaseShift = phase;
	midline = c;

	delete datax;
	delete datay;
	delete dataz; 
}*/
