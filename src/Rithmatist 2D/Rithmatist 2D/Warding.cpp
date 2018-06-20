#include "Warding.h"

Warding::Warding(std::vector<sf::Vector2f> data)
{
	regressionCircle.setOutlineThickness(1.0f);
	regressionCircle.setFillColor(sf::Color::Black);

	points = data;
	for (int i = 0; i < points.size(); i++)
	{
		x.push_back(points[i].x);
		y.push_back(points[i].y);
	}

	//CircularRegression();
	CircleFitByTaubin();

	std::cout << "Strength: " << strength << std::endl;
}

Warding::~Warding()
{
}

void Warding::draw(sf::RenderTarget& target)
{
	target.draw(regressionCircle);
}

float Warding::mean(std::vector<float> values)
{
	//Find mean
	float sum = 0.0f;
	for (int i = 0; i < values.size(); i++)
	{
		sum += values[i];
	}
	return sum / values.size();
}

void Warding::CircularRegression()
{
	// Find center and distance and evaluate circle, return strength of ward line
	// Find center as centroid of points
	float cX = mean(x);
	float cY = mean(y);

	// Strength should be based on the maximum and mininum radii of the shape that was drawn.
	float avgDist = 0;
	float minRadius = std::numeric_limits<float>::max();
	float maxRadius = 0;
	float tempDist;
	for (int i = 0; i < points.size(); i++) {
		tempDist = std::hypot(cX - x[i], cY - y[i]);
		avgDist += tempDist;
		if (tempDist < minRadius) minRadius = tempDist;
		if (tempDist > maxRadius) maxRadius = tempDist;
	}
	avgDist = avgDist / x.size();
	strength = 100.0f*(maxRadius - minRadius) / maxRadius; // Ratio keeps it uniform over all size circles		

	// Get distance between first and last point to make sure its a circle
	if (std::hypot(x.back() - x[0], y.back() - y[0]) > 50.0f)
	{
		//Fail to draw
	}

	regressionCircle.setRadius(avgDist - 1.0f);
	regressionCircle.setPosition(sf::Vector2f(cX, cY));
	
}

void Warding::CircleFitByTaubin()
{
///Modified from http://people.cas.uab.edu/~mosya/cl/CircleFitByTaubin.cpp
/*
Circle fit to a given set of data points (in 2D)

This is an algebraic fit, due to Taubin, based on the journal article

G. Taubin, "Estimation Of Planar Curves, Surfaces And Nonplanar
Space Curves Defined By Implicit Equations, With
Applications To Edge And Range Image Segmentation",
IEEE Trans. PAMI, Vol. 13, pages 1115-1138, (1991)

Input:  data     - the class of data (contains the given points):

data.n   - the number of data points
data.X[] - the array of X-coordinates
data.Y[] - the array of Y-coordinates

Output:
circle - parameters of the fitting circle:

circle.a - the X-coordinate of the center of the fitting circle
circle.b - the Y-coordinate of the center of the fitting circle
circle.r - the radius of the fitting circle
circle.s - the root mean square error (the estimate of sigma)
circle.j - the total number of iterations

The method is based on the minimization of the function

sum [(x-a)^2 + (y-b)^2 - R^2]^2
F = -------------------------------
sum [(x-a)^2 + (y-b)^2]

This method is more balanced than the simple Kasa fit.

It works well whether data points are sampled along an entire circle or
along a small arc.

It still has a small bias and its statistical accuracy is slightly
lower than that of the geometric fit (minimizing geometric distances),
but slightly higher than that of the very similar Pratt fit.
Besides, the Taubin fit is slightly simpler than the Pratt fit

It provides a very good initial guess for a subsequent geometric fit.

Nikolai Chernov  (September 2012)

*/
	int i, iter, IterMAX = 99;

	float Xi, Yi, Zi;
	float Mz, Mxy = 0.0f, Mxx = 0.0f, Myy = 0.0f, Mxz = 0.0f, Myz = 0.0f, Mzz = 0.0f, Cov_xy, Var_z;
	float A0, A1, A2, A22, A3, A33;
	float Dy, xnew, X, ynew, Y;
	float DET, Xcenter, Ycenter;

	for (i = 0; i < points.size(); i++)
	{
		float Xi = x[i] - mean(x);   //  centered x-coordinates
		float Yi = y[i] - mean(y);   //  centered y-coordinates
		Zi = Xi * Xi + Yi * Yi;

		Mxy += Xi * Yi;
		Mxx += Xi * Xi;
		Myy += Yi * Yi;
		Mxz += Xi * Zi;
		Myz += Yi * Zi;
		Mzz += Zi * Zi;
	}
	Mxx /= points.size();
	Myy /= points.size();
	Mxy /= points.size();
	Mxz /= points.size();
	Myz /= points.size();
	Mzz /= points.size();

	//      computing coefficients of the characteristic polynomial

	Mz = Mxx + Myy;
	Cov_xy = Mxx * Myy - Mxy * Mxy;
	Var_z = Mzz - Mz * Mz;
	A3 = 4.0f * Mz;
	A2 = -3.0f * Mz*Mz - Mzz;
	A1 = Var_z * Mz + 4.0f * Cov_xy*Mz - Mxz * Mxz - Myz * Myz;
	A0 = Mxz * (Mxz*Myy - Myz * Mxy) + Myz * (Myz*Mxx - Mxz * Mxy) - Var_z * Cov_xy;
	A22 = A2 + A2;
	A33 = A3 + A3 + A3;

	//    finding the root of the characteristic polynomial
	//    using Newton's method starting at x=0  
	//     (it is guaranteed to converge to the right root)

	for (X = 0.0f, Y = A0, iter = 0; iter < IterMAX; iter++)  // usually, 4-6 iterations are enough
	{
		Dy = A1 + X * (A22 + A33 * X);
		xnew = X - Y / Dy;
		if ((xnew == X) || (!isfinite(xnew))) break;
		ynew = A0 + xnew * (A1 + xnew * (A2 + xnew * A3));
		if (std::abs(ynew) >= std::abs(Y))  break;
		X = xnew;  Y = ynew;
	}

	//       computing paramters of the fitting circle

	DET = X * X - X * Mz + Cov_xy;
	Xcenter = (Mxz*(Myy - X) - Myz * Mxy) / DET / 2.0f;
	Ycenter = (Myz*(Mxx - X) - Mxz * Mxy) / DET / 2.0f;

	//       assembling the output
	regressionCircle.setRadius(std::sqrt(Xcenter*Xcenter + Ycenter * Ycenter + Mz) - 1.0f);
	regressionCircle.setOrigin(regressionCircle.getRadius(), regressionCircle.getRadius());
	regressionCircle.setPosition(sf::Vector2f(Xcenter + mean(x), Ycenter + mean(y)));
	//Choose appropiate point count for circle
	if (regressionCircle.getRadius() > 50.0f)
	{
		regressionCircle.setPointCount(std::ceil(regressionCircle.getRadius() / 4.0f));
	}

	//iter;  //  return the number of iterations, too

	///RMSD Evaluation Method
	//RMSD = RMSD(data, circle); 

	/// Strength should be based on the maximum and mininum radii of the shape that was drawn.
	float avgDist = 0;
	float minRadius = std::numeric_limits<float>::max();
	float maxRadius = 0;
	float tempDist;
	for (int i = 0; i < points.size(); i++) {
		tempDist = std::hypot(mean(x) - x[i], mean(y) - y[i]);
		avgDist += tempDist;
		if (tempDist < minRadius) minRadius = tempDist;
		if (tempDist > maxRadius) maxRadius = tempDist;
	}
	avgDist = avgDist / x.size();
	strength = 180.0f*(maxRadius - minRadius) / maxRadius; // Ratio keeps it uniform over all size circles


}
