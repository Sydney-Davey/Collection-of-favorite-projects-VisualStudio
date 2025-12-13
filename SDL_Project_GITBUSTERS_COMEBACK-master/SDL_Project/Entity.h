#ifndef ENTITY_H
#define ENTITY_H

#include <Vector.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Matrix.h>

using namespace MATH;

class Entity {
protected: //Protected so child class can use
	// Keep these private as we should only build them in the setImage method
	// I do listen to Scott sometimes...
	SDL_Surface* surface; // Used to get the width and height of the image
	SDL_Texture* texture; // Used to render the image

public:
	float angleDeg;
	Vec3 pos;
	Vec3 vel;
	Vec3 acc;
	float mass;
	float width;
	float height;
	// Let's pretend all entities are circles
	float radius;

	SDL_Rect rect;
	bool isClicked;
	bool wasHovered;
	bool isHovered;
	
	

	Entity();
	~Entity();
	void SetImage(const char* filename, SDL_Renderer* renderer);

	// Just like assignment 1!
	void ApplyForce(Vec3 netForce);
	void Update(float deltaTime);

	// Need getters for private member variables. 
	SDL_Surface* GetSurface() const { return surface; }
	SDL_Texture* GetTexture() const { return texture; }

	bool UpdateHover(float mouseX, float mouseY);
	bool UpdateClicky();
	void Relesed();
	void UpdateScreenRect(const Matrix4& projection);
	


};

#endif