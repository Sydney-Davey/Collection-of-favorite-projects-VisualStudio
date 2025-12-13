#include "Entity.h"

Entity::Entity() : // this is an initializer list
	surface(nullptr)
	, texture(nullptr)
	, angleDeg(0.0f)
	, mass(1.0f)
	, radius(1.0f)
	
{
}

Entity::~Entity() {
	// This is the destructor for Entity (notice the little squiggle ~)
	// Clean up the surface and texture data
	//SDL_DestroySurface(surface);
	//SDL_DestroyTexture(texture);
	surface = nullptr;
	texture = nullptr;
}

void Entity::SetImage(const char* filename, SDL_Renderer* renderer) 
{
    // Load image into a surface
    surface = IMG_Load(filename);
    if (!surface) {
		std::cerr << "THE WORLD IS ENDING HEEELLLLLPPPPPP...."
			<< std::endl << "But also did you spell the file right? "
			<< std::endl << "~ Brought to you by a spontaneous message from Syd"
			<< std::endl;
        return;
    }

    // Store width & height immediately
    width  = (float)surface->w;
    height = (float)surface->h;

    // Convert surface to texture
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Entity::SetImage " 
			<< std::endl << "- texture = SDL_CreateTextureFromSurface(renderer, surface) - "
			<< std::endl << "Failed to create texture from surface." 
			<< std::endl;
    }
}



void Entity::ApplyForce(Vec3 netForce)
{
	// Code this up like assignment 1
	// But remember, we need x and y motion
	acc = netForce / mass;
}

void Entity::Update(float deltaTime)
{
	// Code this up like assignment 1
	// But remember, we need x and y motion
	vel +=  acc * deltaTime;
	pos += vel * deltaTime + 0.5f * acc * (deltaTime * deltaTime);
}

bool Entity::UpdateHover(float mouseX, float mouseY)
{
	bool newHover =
		(mouseX >= rect.x && mouseX <= rect.x + rect.w &&
			mouseY >= rect.y && mouseY <= rect.y + rect.h);

	wasHovered = isHovered;
	isHovered = newHover;

	return newHover;
}


bool Entity::UpdateClicky()
{
	if (isHovered) {
		isClicked = true;
	}
	return true;
}

void Entity::Relesed()
{
	isClicked = false;
}

void Entity::UpdateScreenRect(const Matrix4& projection)
{
	Vec3 screen = projection * pos;

	rect.x = screen.x;
	rect.y = screen.y;
	rect.w = width;
	rect.h = height;
}


