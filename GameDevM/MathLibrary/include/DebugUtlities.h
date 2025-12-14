#pragma once
#include "MathLib.h"
//#include "MathLibEx.h

#include <glm/vec3.hpp> /// glm::vec3
#include <glm/vec4.hpp> /// glm::vec4, glm::ivec4
#include <glm/mat4x4.hpp> /// glm::mat4
#include <glm/gtc/matrix_transform.hpp> /// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> /// glm::value_ptr
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/hash.hpp>

// Figuring out colored text and background using https://medium.com/@vitorcosta.matias/print-coloured-texts-in-console-a0db6f589138
const std::string PASSED { "\033[42mPASSED\033[m" };
const std::string FAILED { "\033[41mFAILED\033[m" };



/// Utility print() calls for glm to math library format 
void glmPrintM4(glm::mat4  mat, const char* comment = nullptr);
void glmPrintM3(glm::mat3  mat, const char* comment = nullptr);

void glmPrintQ(glm::quat q, const char* comment = nullptr);
void glmPrintV3(glm::vec3 v, const char* comment = nullptr);
void glmPrintV4(glm::vec4 v, const char* comment = nullptr);

/// Utility Compare() calls for testing 
bool compare(float f1, float f2, float epsilon);

bool compare(const Vec3& v1, const glm::vec3& v2, float epsilon);
bool compare(const Vec4& v1, const glm::vec4& v2, float epsilon);

bool compare(const Matrix3& m1, const glm::mat3& m2, float epsilon);
bool compare(const Matrix3& m1, const Matrix3& m2, float epsilon);

bool compare(const Matrix4& m1, const Matrix4& m2, float epsilon);
bool compare(const Matrix4& m1, const glm::mat4& m2, float epsilon);

bool compare(const Quaternion& q1, const Quaternion& q2, float epsilon);
bool compare(const Quaternion& q1, const glm::quat& q2, float epsilon);

void printPassedOrFailed(bool flag, const std::string& name);
