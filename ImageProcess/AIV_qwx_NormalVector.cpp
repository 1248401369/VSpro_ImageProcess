#include "AIV_qwx_NormalVector.h"

AIV_qwx_NormalVector::AIV_qwx_NormalVector() :theta_resolution(CV_PI / 180.0), phi_resolution(CV_PI / 180.0)
{
	input = cv::Mat();
	normalvectors = cv::Mat();
}

AIV_qwx_NormalVector::AIV_qwx_NormalVector(const cv::Mat &_src, float _theta_resolution, float _phi_resolution) :theta_resolution(_theta_resolution), phi_resolution(_phi_resolution)
{
	_src.copyTo(input);
	normalvectors = cv::Mat(input.rows, input.cols, CV_32FC3);
}

AIV_qwx_NormalVector::~AIV_qwx_NormalVector()
{

}

void AIV_qwx_NormalVector::setImage(const cv::Mat &_src)
{
	_src.copyTo(input);
	normalvectors = cv::Mat(input.rows, input.cols, CV_32FC3);
}

cv::Mat AIV_qwx_NormalVector::Getnormalvectors()
{
	return normalvectors;
}
bool AIV_qwx_NormalVector::compute()
{
	if (input.rows < 3 || input.cols < 3)
		return false;
	float *src_data = (float *)input.data,
		*output_data = (float *)normalvectors.data;
	int width = input.cols,
		height = input.rows;
	cv::Point3f delta_V_theta,
		delta_V_phi;
	float rho0 = 0.0,
		rho1 = 0.0;
	float theta0 = 0.0,
		theta1 = 0.0,
		phi0 = 0.0,
		phi1 = 0.0;
	float sin_theta0,
		cos_theta0,
		sin_phi0,
		cos_phi0,
		sin_theta1,
		cos_theta1,
		sin_phi1,
		cos_phi1;
	//4个角点

	
	for (int i = width; i < width*height - width; i += width)
	{
		//最左列
		rho0 = src_data[i + width - 1];
		rho1 = src_data[i + 1];
		theta0 = -theta_resolution;
		theta1 = theta_resolution;
		phi0 = i / width*phi_resolution;
		delta_V_theta = getDelta_V_theta(theta0, theta1, phi0, rho0, rho1);
		rho0 = src_data[i + width];
		rho1 = src_data[i - width];
		theta0 = 0.0;
		phi0 = (i / width + 1)*phi_resolution;
		phi1 = (i / width - 1)*phi_resolution;
		delta_V_phi = getDelta_V_phi(theta0, phi0, phi1, rho0, rho1);
		cv::Point3f normal = getNormal(delta_V_theta, delta_V_phi);
		output_data[3 * i - 3] = normal.x;
		output_data[3 * i - 2] = normal.y;
		output_data[3 * i - 1] = normal.z;
		//最右列
		int right = i + width - 1;
		rho0 = src_data[right - 1];
		rho1 = src_data[i];
		theta0 = 2 * CV_PI - 2 * theta_resolution;
		theta1 = 2 * CV_PI;
		phi0 = right / width*phi_resolution;
		delta_V_theta = getDelta_V_theta(theta0, theta1, phi0, rho0, rho1);
		rho0 = src_data[right + width];
		rho1 = src_data[right - width];
		theta0 = 2 * CV_PI - theta_resolution;
		phi0 = (right / width + 1)*phi_resolution;
		phi1 = (right / width - 1)*phi_resolution;
		delta_V_phi = getDelta_V_phi(theta0, phi0, phi1, rho0, rho1);
		normal = getNormal(delta_V_theta, delta_V_phi);
		output_data[3 * right - 3] = normal.x;
		output_data[3 * right - 2] = normal.y;
		output_data[3 * right - 1] = normal.z;
		//中间部分
		for (int j = 1; j < width - 1; ++j)
		{
			int k = i + j;
			rho0 = src_data[k - 1];
			rho1 = src_data[k + 1];
			theta0 = (j - 1)*theta_resolution;
			theta1 = (j + 1)*theta_resolution;
			phi0 = k / width*phi_resolution;
			delta_V_theta = getDelta_V_theta(theta0, theta1, phi0, rho0, rho1);
			rho0 = src_data[k + width];
			rho1 = src_data[k - width];
			theta0 = j*theta_resolution;
			phi0 = (k / width + 1)*phi_resolution;
			phi1 = (k / width - 1)*phi_resolution;
			delta_V_phi = getDelta_V_phi(theta0, phi0, phi1, rho0, rho1);
			normal = getNormal(delta_V_theta, delta_V_phi);
			output_data[3 * k - 3] = normal.x;
			output_data[3 * k - 2] = normal.y;
			output_data[3 * k - 1] = normal.z;
		}
	}
	
}

cv::Point3f AIV_qwx_NormalVector::getDelta_V_theta(float _theta0, float _theta1, float _phi, float _rho0, float _rho1)
{
	float sin_theta0,
		cos_theta0,
		sin_theta1,
		cos_theta1,
		sin_phi,
		cos_phi;
	sin_theta0 = sinf(_theta0);
	cos_theta0 = cosf(_theta0);
	sin_theta1 = sinf(_theta1);
	cos_theta1 = cosf(_theta1);
	sin_phi = sinf(_phi);
	cos_phi = cosf(_phi);
	cv::Point3f output;
	output.x = _rho1*cos_phi*cos_theta1 - _rho0*cos_phi*cos_theta0;
	output.y = _rho1*cos_phi*sin_theta1 - _rho0*cos_phi*sin_theta0;
	output.z = _rho1*sin_phi - _rho0*sin_phi;
	return output;
}

cv::Point3f AIV_qwx_NormalVector::getDelta_V_phi(float _theta, float _phi0, float _phi1, float _rho0, float _rho1)
{
	float sin_theta,
		cos_theta,
		sin_phi0,
		cos_phi0,
		sin_phi1,
		cos_phi1;
	sin_theta = sinf(_theta);
	cos_theta = cosf(_theta);
	sin_phi0 = sinf(_phi0);
	cos_phi0 = cosf(_phi0);
	sin_phi1 = sinf(_phi1);
	cos_phi1 = cosf(_phi1);
	cv::Point3f output;
	output.x = _rho1*cos_phi1*cos_theta - _rho0*cos_phi0*cos_theta;
	output.y = _rho1*cos_phi1*sin_theta - _rho0*cos_phi0*sin_theta;
	output.z = _rho1*sin_phi1 - _rho0*sin_phi0;
	return output;
}

cv::Point3f AIV_qwx_NormalVector::getNormal(const cv::Point3f &_delta_V_theta, const cv::Point3f &_delta_V_phi)
{
	cv::Point3f output;
	output.x = _delta_V_theta.y*_delta_V_phi.z - _delta_V_theta.z*_delta_V_phi.y;
	output.y = _delta_V_theta.z*_delta_V_phi.x - _delta_V_theta.x*_delta_V_phi.z;
	output.z = _delta_V_theta.x*_delta_V_phi.y - _delta_V_theta.y*_delta_V_phi.x;
	return output;
}