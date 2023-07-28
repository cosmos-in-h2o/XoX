module;
#include <Eigen/Eigen>
export module matrix;
export namespace xox{
	using Matrix2=Eigen::Matrix<double,2,2>;
	using Matrix3=Eigen::Matrix<double,3,3>;
	using Matrix4=Eigen::Matrix<double,4,4>;
	using Eigen::Matrix;
	Matrix2 mat;
}