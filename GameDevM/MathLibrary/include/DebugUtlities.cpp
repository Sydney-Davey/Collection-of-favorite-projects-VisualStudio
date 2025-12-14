#include "DebugUtlities.h"

#include <string>
#include <iostream>

/// These are print statements for glm - they don't have them  
void glmPrintM4(glm::mat4  mat, const char* comment) {
	int i, j;
	if (comment) printf("%s\n", comment);
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			printf("%1.4f ", mat[i][j]);
		}
		printf("\n");
	}
}
void glmPrintM3(glm::mat3  mat, const char* comment) {
	int i, j;
	if (comment) printf("%s\n", comment);
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			printf("%1.4f ", mat[i][j]);
		}
		printf("\n");
	}
}

void glmPrintQ(glm::quat q, const char* comment) {
	if (comment) printf("%s\n", comment);
	///                                    w     i     j     k
	printf("%1.4f %1.4f %1.4f %1.4f \n", q[3], q[0], q[1], q[2]);
}

void glmPrintV3(glm::vec3 v, const char* comment) {
	if (comment) printf("%s\n", comment);
	printf("%1.4f %1.4f %1.4f\n", v[0], v[1], v[2]);
}

void glmPrintV4(glm::vec4 v, const char* comment) {
	if (comment) printf("%s\n", comment);
	printf("%1.4f %1.4f %1.4f %1.4f\n", v[0], v[1], v[2], v[3]);
}




// Utilities to print passed or failed message
void printPassedOrFailed(bool flag, const std::string& name) {
	if (flag) {
		std::cout << PASSED + name << "\n";
	}
	else {
		std::cout << FAILED + name << "\n";
	}
}


bool compare(float  f1, float f2, float epsilon) {
	for (int i = 0; i < 3; ++i) {
		if (std::fabs(f1 - f2) > epsilon) {
			return false;
		}
	}
	return true;
}
bool compare(const Vec3& v1, const glm::vec3& v2, float epsilon) {
	for (int i = 0; i < 3; ++i) {
		if (std::fabs(v1[i] - v2[i]) > epsilon) {
			return false;
		}
	}
	return true;
}

bool compare(const Vec4& v1, const glm::vec4& v2, float epsilon) {
	for (int i = 0; i < 4; ++i) {
		if (std::fabs(v1[i] - v2[i]) > epsilon) {
			return false;
		}
	}
	return true;
}

bool compare(const Matrix3& m1, const Matrix3& m2, float epsilon) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (std::fabs(m1[i * 3 + j] - m2[i * 3 + j]) > epsilon) {
				return false;
			}
		}
	}
	return true;
}
bool compare(const Matrix3& m1, const glm::mat3& m2, float epsilon) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (std::fabs(m1[i * 3 + j] - m2[i][j]) > epsilon) {
				return false;
			}
		}
	}
	return true;
}

bool compare(const Matrix4& m1, const Matrix4& m2, float epsilon) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (std::fabs(m1[i * 4 + j] - m2[i * 4 + j]) > epsilon) {
				return false;
			}
		}
	}
	return true;
}


bool compare(const Matrix4& m1, const glm::mat4& m2, float epsilon) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (std::fabs(m1[i * 4 + j] - m2[i][j]) > epsilon) {
				return false;
			}
		}
	}
	return true;
}

bool compare(const Quaternion& q1, const Quaternion& q2, float epsilon) {
	for (int i = 0; i < 4; ++i) {
		if (std::fabs(q1[i] - q2[i]) > epsilon) {
			return false;
		}
	}
	return true;
}

bool compare(const Quaternion& q1, glm::quat& q2, float epsilon) {
	for (int i = 0; i < 4; ++i) {
		if (std::fabs(q1[i] - q2[i]) > epsilon) {
			return false;
		}
	}
	return true;
}