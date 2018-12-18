#include <opencv2/opencv.hpp>
#include <vector>

class AIV_qwx_NormalVector
{
private:
	float theta_resolution,
		phi_resolution;
	cv::Mat input;
	cv::Mat normalvectors;
public:
	AIV_qwx_NormalVector();
	AIV_qwx_NormalVector(const cv::Mat &_src, float _theta_resolution, float _phi_resolution);
	~AIV_qwx_NormalVector();
	void setImage(const cv::Mat &_src);
	bool compute();
	cv::Mat Getnormalvectors();
private:
	cv::Point3f getNormal(const cv::Point3f &_delta_V_theta, const cv::Point3f &_delta_V_phi);
	cv::Point3f getDelta_V_theta(float _theta0, float _theta1, float _phi, float _rho0, float _rho1);
	cv::Point3f getDelta_V_phi(float _theta, float _phi0, float _phi1, float _rho0, float _rho1);
};