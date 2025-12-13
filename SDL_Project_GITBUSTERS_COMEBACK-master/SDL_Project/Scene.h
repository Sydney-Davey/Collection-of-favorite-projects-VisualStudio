#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	//Added variables
	int LevelCount = -1;
	bool LevelDiffsPresent = 0;
	bool FrontDoorUsed = 0;

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents(const SDL_Event &event) = 0;
	virtual int SceneSwitch() = 0;
};

#endif
